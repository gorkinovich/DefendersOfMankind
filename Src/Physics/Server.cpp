/**
@file Server.cpp

Contiene la implementaci�n del servidor de f�sica. 

@see Physics::CServer

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/

#include "Server.h"
#include "CollisionMng.h"
#include "Conversions.h"

#include "PhysicEngine.h"
#include "PhysicScene.h"
#include "IPhysicModel.h"
#include "PhysicModelSimple.h"
#include "PhysicModelGeneric.h"
#include "PhysicModelCharacter.h"
#include "PhysicObjSimple.h"
#include "PhysicObjGeneric.h"
#include "PhysicObjCharacter.h"

#include "Core/Math.h"
#include "Core/Entities/Entity.h"
#include "Logic/Entity/Components/PhysicEntity.h"

#include <NxUserAllocatorDefault.h> 

using namespace std;
using namespace Physics;
using namespace Logic;

// �nica instancia del servidor
CServer *CServer::_instance = NULL;

//--------------------------------------------------------

/**
Transforma entre enumerados.
*/
IPhysicObj::EPhysicMode getPhysicMode(TPhysicMode mode)
{
	switch(mode) {
		case PM_STATIC:		return IPhysicObj::PMODE_STATIC;
		case PM_DYNAMIC:	return IPhysicObj::PMODE_DYNAMIC;
		case PM_KINEMATIC:	return IPhysicObj::PMODE_KINEMATIC;
		default:
			assert(0);
			return IPhysicObj::PMODE_STATIC; // Aqui no deber�amos llegar
	}
}

//--------------------------------------------------------

CServer::CServer() 
{
	assert(!_instance && "Segunda inicializaci�n de Physics::CServer no permitida!");

	// Creamos el gestor de colisiones
	_collisionMng = new CCollisionMng();

} 

//--------------------------------------------------------

CServer::~CServer() 
{
	if (_collisionMng) {
		delete _collisionMng;
		_collisionMng = NULL;
	}
	
	// Liberar los modelos f�sicos
	list<IPhysicModel*>::iterator it;
	for (it = models.begin(); it != models.end(); it++) {
		delete *it;
	}
	models.clear();
} 

//--------------------------------------------------------

bool CServer::Init() 
{
	if (!_instance) {
		_instance = new CServer();

		// Inicializamos el gestor de memoria que usa CPhysicEngine
		Globals::g_pUserAllocator = new NxUserAllocatorDefault();

		// Inicializaci�n del motor de f�sica
		CPhysicEngine::Init();
	}

	return true;
} 

//--------------------------------------------------------

void CServer::Release()
{
	if(_instance) {
		delete _instance;
		_instance = NULL;

		// Finalizaci�n del motor de f�sica
		CPhysicEngine::ShutDown();

		// Liberar el gestor de memoria que usa CPhysicEngine
		if (Globals::g_pUserAllocator) {
			delete Globals::g_pUserAllocator;
			Globals::g_pUserAllocator = NULL;
		}
	}
} 

//--------------------------------------------------------

void CServer::createScene ()
{
	assert(CPhysicEngine::Ref().GetNumScenes() == 0);
	
	// Crear la escena
	CPhysicScene::TInitInfo initInfo;
	initInfo.bWaterMngEnabled = false;      // Desactivar el simulador de fluidos
	initInfo.pCollisionMng = _collisionMng; // Asignar el gestor de colisiones
	CPhysicScene *scene = CPhysicEngine::Ref().CreateScene(initInfo);

	// Activar / desactivar la detecci�n de colisiones entre grupos de colisi�n.
	// En realidad solo hace falta indicar los grupos que NO colisionan entre s� (por defecto todos colisionan con todos)
	// TODO: recorrer una matriz ?? Leer los datos de un descriptor ??
	NxScene* PhysicScene = scene->GetNxScene();
	PhysicScene->setGroupCollisionFlag(0,2,true);	

	PhysicScene->setGroupCollisionFlag(0,1,false);
	PhysicScene->setGroupCollisionFlag(1,2,true);
	PhysicScene->setGroupCollisionFlag(2,6,true);

	PhysicScene->setGroupCollisionFlag(2,2,false);

	PhysicScene->setGroupCollisionFlag(2,3,false);

	PhysicScene->setGroupCollisionFlag(0,5,true);

	PhysicScene->setGroupCollisionFlag(1,1,false);
	PhysicScene->setGroupCollisionFlag(1,3,false);
	PhysicScene->setGroupCollisionFlag(3,3,false);

	



}

//--------------------------------------------------------

void CServer::destroyScene ()
{
	assert(CPhysicEngine::Ref().GetNumScenes() == 1);
	
	// Eliminar la escena
	CPhysicScene *pScene = CPhysicEngine::Ref().GetScene(0);
	CPhysicEngine::Ref().DestroyScene(pScene);
}

//--------------------------------------------------------

CPhysicScene* CServer::getScene() const
{
	assert(CPhysicEngine::Ref().GetNumScenes() == 1);
	
	// Devuelve la escena 
	return CPhysicEngine::Ref().GetScene(0);
}

//--------------------------------------------------------

bool CServer::update(float secs) 
{
	assert(CPhysicEngine::Ref().GetNumScenes() == 1);
	
	// Realizar la simulaci�n f�sica.
	getScene()->StepSimulation(secs);

	// Actualizar la informaci�n asociada a los controllers (es necesario
	// hacerlo de forma expl�cita).
	CPhysicEngine::Ref().GetNxControllerMgr()->updateControllers();

	return true;
} 

//--------------------------------------------------------

CPhysicModelSimple* CServer::createModelSimple()
{
	// Crear el modelo f�sico
	IPhysicModel *model = IPhysicModel::Factory(IPhysicModel::MODEL_SIMPLE);
	models.push_back(model);

	return (CPhysicModelSimple *) model;
}

//--------------------------------------------------------

CPhysicModelGeneric* CServer::createModelGeneric(const string &file)
{
	// Crear el modelo f�sico
	CPhysicModelGeneric *model = dynamic_cast<CPhysicModelGeneric *> (IPhysicModel::Factory(IPhysicModel::MODEL_GENERIC));
	models.push_back(model);

	// Cargar el modelo a partir de un fichero
	CPhysicModelGeneric::TInitInfo  initInfo;
	initInfo.pszModelFile = file.c_str();
	model->Init(initInfo);

	return model;
}

//--------------------------------------------------------

CPhysicModelCharacter* CServer::createModelCapsuleCharacter(float radius, float height)
{
	assert((radius > 0) && (height > 0));
	
	// Crear el modelo f�sico
	CPhysicModelCharacter *model = dynamic_cast<CPhysicModelCharacter *> (IPhysicModel::Factory(IPhysicModel::MODEL_CHARACTER));
	models.push_back(model);
	
	// Crear el volumen de colisi�n adecuado.
	model->SetControllerType(NX_CONTROLLER_CAPSULE);
	NxCapsuleControllerDesc &desc = model->EditCapsuleParams();
	desc.radius = radius;
	desc.height = height;
	desc.slopeLimit = cos(Math::FromDegreesToRadians(45.0f));
	desc.stepOffset = 1.0f;

	return model;
}

//--------------------------------------------------------

void CServer::createCapsuleShape(CPhysicModelSimple *model, float radius, float height, int group)
{
	assert((radius > 0) && (height > 0) && (group >= 0));
	
	// Nota: la l�gica asume que el origen del sistema de coordenadas local (SCL)
	// asociado a la entidad est� colocado en la parte inferior (los pies) de la 
	// entidad. En PhysX, sin embargo, el origen del SCL se coloca por defecto en el centro
	// de la entidad. Para que ambos sistemas concuerden trasladamos el de PhysX la
	// mitad de la altura del volumen de colisi�n elegido.	
	
	int shapeIdx = model->CreateShape(NX_SHAPE_CAPSULE);
	NxCapsuleShapeDesc &desc = dynamic_cast<NxCapsuleShapeDesc &> (model->EditShape(shapeIdx));
	desc.radius = radius;
	desc.height = height;
	desc.group = group;

	// La altura de la capsula es la mitad de la altura del cilindro central, 
	// m�s el radio de la semicircunferencia superior.
	desc.localPose.t.y = desc.height / 2.0f + desc.radius;
}

//--------------------------------------------------------

void CServer::createBoxShape(CPhysicModelSimple *model, const Vector3 &dimensions, int group)
{
	assert(model && (group >= 0));
	assert((dimensions.x > 0) && (dimensions.y > 0) && (dimensions.z > 0));
	
	// Nota: la l�gica asume que el origen del sistema de coordenadas local (SCL)
	// asociado a la entidad est� colocado en la parte inferior (los pies) de la 
	// entidad. En PhysX, sin embargo, el origen del SCL se coloca por defecto en el centro
	// de la entidad. Para que ambos sistemas concuerden trasladamos el de PhysX la
	// mitad de la altura del volumen de colisi�n elegido.	

	int shapeIdx = model->CreateShape(NX_SHAPE_BOX);
	NxBoxShapeDesc &desc = dynamic_cast<NxBoxShapeDesc &> (model->EditShape(shapeIdx));
	desc.dimensions = Vector3ToNxVec3(dimensions);
	desc.group = group;

	// La altura de una caja es la mitad de la altura en el eje Y. El atributo
	// dimensions ya almacena la longitud de los lados dividida entre 2.
	desc.localPose.t.y = desc.dimensions.y;
}

//--------------------------------------------------------

void CServer::createPlaneShape(CPhysicModelSimple *model, const Vector3 &normal, int group)
{
	assert(model && (group >= 0));
	assert(normal != Vector3::ZERO);

	int shapeIdx = model->CreateShape(NX_SHAPE_PLANE);
	NxPlaneShapeDesc &desc = dynamic_cast<NxPlaneShapeDesc &> (model->EditShape(shapeIdx));
	desc.normal = Vector3ToNxVec3(normal);
	desc.group = group;
}

//--------------------------------------------------------

void CServer::setTrigger(CPhysicModelSimple *model, int idxShape, bool isTrigger)
{
	assert(model && (idxShape < model->GetNumShapes()));	
	
	NxShapeDesc &desc = model->EditShape(idxShape);
		
	// Activar / desactivar el flag correspondiente
	if (isTrigger) {
		desc.shapeFlags |= NX_TRIGGER_ENABLE;
	} else {
		desc.shapeFlags &= ~NX_TRIGGER_ENABLE;
	}
}

//--------------------------------------------------------

void CServer::setMass(CPhysicModelSimple *model, float mass)
{
	assert(model && (mass >= 0));

	model->SetMass(mass);
}

//--------------------------------------------------------

IPhysicObj* CServer::createObject(PhysicEntity *component, TPhysicMode mode, 
								  const Vector3 &position, const Matrix3 &orientation, 
								  const IPhysicModel *model)
{
	assert(component && model);
	assert(model->GetType() == IPhysicModel::MODEL_SIMPLE ||
		   model->GetType() == IPhysicModel::MODEL_GENERIC ||
		   model->GetType() == IPhysicModel::MODEL_CHARACTER);
	
	// Crear la entidad f�sica 
	IPhysicObj::TInitInfo initInfo;
	initInfo.ePhysicMode = getPhysicMode(mode);
	initInfo.vWorldPose.t = Vector3ToNxVec3(position);
	initInfo.vWorldPose.M = Matrix3ToNxMat33(orientation);
	initInfo.pPhysicModel = model;
	CPhysicObj *obj = dynamic_cast<CPhysicObj *> (getScene()->CreatePhysicObj(initInfo));
	
	// Vincular la entidad f�sica con el componente l�gico para recibir notificaciones
	// de colisiones
	obj->userData = component;

	// Activar la entidad f�sica
	obj->Activate();

	return obj;
}

//--------------------------------------------------------

void CServer::destroyObject(IPhysicObj *obj)
{
	assert(obj);

	getScene()->DestroyPhysicObj(obj);
}

//--------------------------------------------------------

Vector3 CServer::getPosition(const IPhysicObj *obj)
{
	assert(obj);
	
	return NxVec3ToVector3(obj->GetWorldPosition());
}

//--------------------------------------------------------

Matrix3 CServer::getOrientation(const IPhysicObj *obj, int idxPart)
{
	assert(obj && (idxPart < obj->GetNumParts()));

	return NxMat33ToMatrix3(obj->GetWorldOrientation(idxPart));
}

//--------------------------------------------------------

void CServer::move(IPhysicObj *obj, const Vector3 &pos)
{
	assert(obj);
	
	obj->MoveWorldPosition(0, Vector3ToNxVec3(pos));
}

//--------------------------------------------------------

void CServer::move(IPhysicObj *obj, const Matrix3 &rot)
{
	assert(obj);
	
	obj->MoveWorldOrientation(0, Matrix3ToNxMat33(rot));
}

//--------------------------------------------------------

void CServer::move(IPhysicObj *obj, const Matrix4 &transf)
{
	assert(obj);
	
	move(obj, transf.getTrans());

	Matrix3 m;
	transf.extract3x3Matrix(m);
	move(obj, m);
}

//--------------------------------------------------------

unsigned CServer::moveCharacter(CPhysicObjCharacter *obj, const Vector3 &displ)
{
	assert(obj);
	
	unsigned collisionGroups = 0xFFFFFFB0; // Todos menos el grupo 0, 1, 2, 3 y 6 
	float minDist = 0.01f;
	float sharpness = 1.0f;
	return obj->Move(Vector3ToNxVec3(displ), collisionGroups, minDist, sharpness);
}
//--------------------------------------------------------

void CServer::setPosition(CPhysicObjCharacter *obj, const Vector3 &position)
{
	assert(obj);

	obj->SetWorldPosition(Vector3ToNxVec3(position));
}

//--------------------------------------------------------

Core::Entity* CServer::raycastClosest (const Ray& ray, float maxDist) const
{
	// Calcular primera intersecci�n. Si no hay devolvemos NULL.
	TIntersectInfo info;
	if (!getScene()->CalcIntersection(RayToNxRay(ray), info)) 
		return NULL;

	// Comprobar que la intersecci�n est� dentro de la distancia m�xima
	if (ray.getOrigin().distance(NxVec3ToVector3(info.vImpact)) > maxDist)
		return NULL;

	// Recuperar la entidad l�gica intersecada
	PhysicEntity *physicEntity = reinterpret_cast<PhysicEntity*> (info.pPhysicObj->userData);
	return physicEntity->getOwner();
}

//--------------------------------------------------------

bool CServer::checkHardColision(IPhysicObj* physicObj, const Vector3& center, const Vector3& dim)
{
	bool colision = false;

	// Creamos el AABB con el que comparar la colisi�n (representa la caja de la muerte)
	NxBounds3 deathBox;
	NxVec3 min, max;
	min.x = center.x - (dim.x/2);	max.x = center.x + (dim.x/2);	// Calculamos adecuadamente la posici�n del AABB
	min.y = center.y - (dim.y/2);	max.y = center.y + (dim.y/2);	// con respecto al centro y las dimensiones pasados
	min.z = center.z - (dim.z/2);	max.z = center.z + (dim.z/2);	// como par�metros

	deathBox.set(min, max);		//deathBox.set(NxVec3(200,-100,-1000), NxVec3(400,200,0));

	// Para cada actor del objeto f�sico de la entidad...
	CPhysicObj* po = dynamic_cast<CPhysicObj*>(physicObj);
	int nActors = po->GetNumParts();
	for (int i=0; i<nActors; ++i)
	{
		NxActor* actor = po->GetActor(i);
		// Obtenemos sus shapes...
		int nShapes = actor->getNbShapes();
		NxShape* const* shapes = actor->getShapes();	// Puntero a un array de punteros a shapes
		// Comprobamos si existe colisi�n entre cada shape y la AABB reci�n creada
		for (int j=0; j<nShapes; ++j)
		{
			colision = colision || shapes[j]->checkOverlapAABB(deathBox);
		}
	}

	// Si todos los shapes estan dentro del AABB devolvemos true
	return colision;
}