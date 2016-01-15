//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
// 
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//************************************************************************************************************
// Defenders of Mankind: Juego shoot'em up de naves en 3D.
// Copyright  (c) 2011  Grupo 03
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
//************************************************************************************************************

/**
Contiene la implementaci�n del componente encargado de la representaci�n f�sica de las
entidades que no son character controllers.
*/

#include <assert.h>

#include "Logic/Entity/Components/PhysicEntity.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Physics/IPhysicObj.h"
#include "Physics/PhysicModelSimple.h"
#include "Physics/PhysicModelGeneric.h"
#include "Physics/PhysicObj.h"
#include "Physics/Server.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/ChangeTransformMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

#include "Core/Scripting/ScriptingManager.h"

using namespace Physics;

namespace Logic
{
	PhysicEntity::PhysicEntity() : Component("PhysicEntity"), _physicObj(NULL)
	{
		_physicServer = CServer::getSingletonPtr();
		//TODO: Prueba de prioridad...
		setPriority(1);
		//...
	}

	PhysicEntity::PhysicEntity(const std::string & name) : Component(name), _physicObj(NULL)
	{
		_physicServer = CServer::getSingletonPtr();
	}

	//---------------------------------------------------------

	PhysicEntity::~PhysicEntity() 
	{
		if(_physicObj) {
			// Eliminar el objeto f�sico de la escena
			_physicServer->destroyObject(_physicObj);
			_physicObj = NULL;
		}
		
		_physicServer = NULL;
	} 

	//---------------------------------------------------------

	bool PhysicEntity::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		// Crear el objeto f�sico asociado al componente
		_physicObj = createPhysicEntity(entityInfo);

//=====================================
// GRUPOS DE COLISI�N -- In progress...
//=====================================
		CPhysicObj* po = dynamic_cast<CPhysicObj*>(_physicObj);
		int nActors = po->GetNumParts();
		for (int i=0; i<nActors; ++i)
		{
			NxActor* actor = po->GetActor(i);
			// Obtenemos sus shapes...
			int nShapes = actor->getNbShapes();

			//NxShape* const* shapes = actor->getShapes();	// Puntero a un array de punteros a shapes
			// Comprobamos si existe colisi�n entre cada shape y la AABB reci�n creada
			for (int j=0; j<nShapes; ++j)
			{
				//shapes[i]->setGroup(entityInfo->getAttributeAsInteger(STR_PHYSIC_COLLISION_GROUP));
				if(entityInfo->hasAttribute(STR_PHYSIC_COLLISION_GROUP)) {
					actor->getShapes()[j]->setGroup(entityInfo->getAttributeAsInteger(STR_PHYSIC_COLLISION_GROUP));
				}
			}
		}
//=====================================
//=====================================*/

		// Anotar su posici�n y rotaci�n actual
		_transform = Position::GetTransform(entityInfo);

		if (_physicObj->IsKinematic()) 
			_physicServer->move(_physicObj, _transform);

		return (_physicObj != NULL);
	} 

	//---------------------------------------------------------

	bool PhysicEntity::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_CHANGE_TRANSFORM;
	}

	//---------------------------------------------------------

	void PhysicEntity::processMessage(const Core::SmartMessage & message)
	{

		switch(message->getType())
		{
		case MESSAGE_TYPE_CHANGE_TRANSFORM:
			// Anotamos la transformaci�n para usarla posteriormente en el m�todo 
			// tick. De esa forma, si recibimos varios mensajes en el mismo ciclo 
			// s�lo tendremos en cuenta el �ltimo
			_transform =  message->getDataRefAs<ChangeTransformMessage>().getTransform();
			break;
		}
	}

	//---------------------------------------------------------

	void PhysicEntity::update(unsigned int lastInterval)
	{
		// Invocar al m�todo de la clase padre (IMPORTANTE)
		Component::update(lastInterval);

		// Si el objeto f�sico es kinem�tico intentamos moverlo a la posici�n
		// recibida en el �ltimo mensaje de tipo SET_TRANSFORM
		if (_physicObj->IsKinematic()) {
			_physicServer->move(_physicObj, _transform);
		} else {
			// Actualizar la posici�n y la orientaci�n de la entidad l�gica usando la 
			// informaci�n proporcionada por el motor de f�sica
			Position * positionComponent = _owner->getComponentAs<Position>("Position");
			positionComponent->setPosition(_physicServer->getPosition(_physicObj));
			positionComponent->setOrientation(_physicServer->getOrientation(_physicObj, 0));
		}
	}

	//---------------------------------------------------------

	void PhysicEntity::onEntityHit(const Core::Entity *otherEntity) 
	{
		//TODO xDD
	}

	//---------------------------------------------------------

	void PhysicEntity::onEntityTrigger(const Core::Entity *otherEntity, bool enter, bool leave, bool stay)
	{
		// S�lo tenemos en cuenta los eventos de entrada y salida del trigger
		if(stay) return;

		// Construimos un mensaje de tipo TOUCHED o UNTOUCHED y lo enviamos a todos los
		// componentes de la entidad. 
		if(enter) {
			_owner->sendMessage(MessageFactory::CreateTouchedMessage(otherEntity));
		} else {
			_owner->sendMessage(MessageFactory::CreateUntouchedMessage(otherEntity));
		}
	}

	//---------------------------------------------------------

	IPhysicObj* PhysicEntity::createPhysicEntity(const Core::EntityInfoTable *entityInfo)
	{
		// Obtenemos el modelo f�sico que describe el tipo de entidad f�sica
		// que debemos crear
		IPhysicModel *model = createPhysicModel(entityInfo);
		

		// Obtenemos el tipo de entidad f�sica (est�tica, din�mica, kinem�tica)
		// particular que queremos crear y su posici�n en el mundo
		TPhysicMode mode = getPhysicMode(entityInfo);

		Matrix3 orientation;
		Matrix4 transform = Position::GetTransform(entityInfo);
		Vector3 position = transform.getTrans();
		transform.extract3x3Matrix(orientation);

		// Creamos la nueva entidad f�sica
		return _physicServer->createObject(this, mode, position, orientation, model); 
	}

	//---------------------------------------------------------

	IPhysicModel* PhysicEntity::createPhysicModel(const Core::EntityInfoTable *entityInfo)
	{
		// Obtenemos el tipo de entidad f�sica que debemos crear
		std::string entity = "";
		if(entityInfo->hasAttribute(STR_PHYSIC_ENTITY)) {
			entity.append(entityInfo->getAttribute(STR_PHYSIC_ENTITY));
		}

		assert((entity == STR_SIMPLE || entity == STR_GENERIC) && "Tipo de entidad no permitida en el componente f�sico");

		// Creamos el modelo correspondiente
		IPhysicModel *model = NULL;
		if (entity == STR_SIMPLE) {
			model = createPhysicModelSimple(entityInfo);
		} else if (entity == STR_GENERIC) {
			model = createPhysicModelGeneric(entityInfo);
		}

		return model;
	}

	//---------------------------------------------------------

	TPhysicMode PhysicEntity::getPhysicMode(const Core::EntityInfoTable *entityInfo) {
		// Los controladores son entidades kinem�ticas
		if (entityInfo->getAttribute(STR_PHYSIC_ENTITY) == STR_CONTROLLER) {
			return PM_KINEMATIC;
		}

		// El resto de entidades definen su tipo expl�citamente
		std::string type = "";
		if(entityInfo->hasAttribute(STR_PHYSIC_TYPE)) {
			type.append(entityInfo->getAttribute(STR_PHYSIC_TYPE));
		}

		assert(((type == STR_STATIC) || (type == STR_DYNAMIC) || (type == STR_KINEMATIC)) && "Physic type no permitido");

		if (type == STR_STATIC) {
			return PM_STATIC;
		} else if (type == STR_DYNAMIC) {
			return PM_DYNAMIC;
		} else {
			return PM_KINEMATIC;
		} 
	}

	//---------------------------------------------------------

	CPhysicModelSimple* PhysicEntity::createPhysicModelSimple(const Core::EntityInfoTable *entityInfo)
	{
		// Comprobamos que estamos creando una entidad f�sica simple
		std::string entity = "";
		if (entityInfo->hasAttribute(STR_PHYSIC_ENTITY)) {
			entity.append(entityInfo->getAttribute(STR_PHYSIC_ENTITY));
		}
		assert(entity == STR_SIMPLE);

		// Creamos el modelo f�sico correspondiente
		CPhysicModelSimple *model = _physicServer->createModelSimple();

		// Creamos el volumen de colisi�n adecuado
		createPhysicShape(entityInfo, model, 1.0f);

		// Comprobamos si estamos definiendo un trigger
		if (entityInfo->hasAttribute(STR_PHYSIC_TRIGGER) && entityInfo->getAttributeAsBool(STR_PHYSIC_TRIGGER)) {
				// Marcamos el volumen de colisi�n como trigger
				_physicServer->setTrigger(model, 0, true);

				// Las entidades f�sicas din�micas y kinem�ticas deben tener al menos un
				// volumen de colisi�n que no sea un trigger. Intuitivamente este volumen
				// de colisi�n es el que contiene la masa de la entidad.
				// HACK: creamos un volumen de colisi�n dummy m�s peque�o que el trigger de
				// manera que quede dentro.
				std::string type = "";
				if (entityInfo->hasAttribute(STR_PHYSIC_TYPE)) {
					type.append(entityInfo->getAttribute(STR_PHYSIC_TYPE));
				}
				if ((type == STR_DYNAMIC) || (type == STR_KINEMATIC)) {
					createPhysicShape(entityInfo, model, 0.99f);
				}
		}

		// Si estamos definiendo un objeto din�mico anotamos su masa.
		if (entityInfo->hasAttribute(STR_PHYSIC_MASS)) {
			float mass = entityInfo->getAttributeAsFloat(STR_PHYSIC_MASS);
			_physicServer->setMass(model, mass);
		}

		// Devolvemos el modelo resultante
		return model;
	}

	//---------------------------------------------------------

	void PhysicEntity::createPhysicShape(const Core::EntityInfoTable *entityInfo, CPhysicModelSimple *model, float scale)
	{
		// Leemos el grupo de colisi�n al que debe pertenecer la shape
		int group = 0;
		if (entityInfo->hasAttribute(STR_PHYSIC_COLLISION_GROUP)) {
			group = entityInfo->getAttributeAsInteger(STR_PHYSIC_COLLISION_GROUP);
		}
		
		// Crear el volumen de colisi�n adecuado
		std::string shape = "";
		if(entityInfo->hasAttribute(STR_PHYSIC_SHAPE)) {
			shape.append(entityInfo->getAttribute(STR_PHYSIC_SHAPE));
		}
		assert(((shape == STR_CAPSULE) || (shape == STR_PLANE) || (shape == STR_BOX)) &&
			"Tipo de shape no permitida en un objeto f�sico simple");

		// Usar una capsula?
		if (shape == STR_CAPSULE) {
			float radius = 0.0;
			float height = 0.0;

			if(entityInfo->hasAttribute(STR_PHYSIC_RADIUS)) {
				radius = entityInfo->getAttributeAsFloat(STR_PHYSIC_RADIUS);
			}

			if (entityInfo->hasAttribute(STR_PHYSIC_HEIGHT)){
				height = entityInfo->getAttributeAsFloat(STR_PHYSIC_HEIGHT);
			}

			_physicServer->createCapsuleShape(model, radius * scale, height * scale, group);

		// Usar un plano?
		} else if (shape == STR_PLANE) {
			Vector3 normal;

			if (entityInfo->hasAttribute(STR_PHYSIC_NORMAL)) {
				normal = entityInfo->getAttributeAsVector3(STR_PHYSIC_NORMAL);
			} else {
				normal = Vector3.ZERO;	//normal no ser� NULL bajo ning�n concepto
			}

			_physicServer->createPlaneShape(model, normal, group);

		// Usar una caja?
		} else if (shape == STR_BOX) {
			Vector3 dimensions;

			if (entityInfo->hasAttribute(STR_PHYSIC_DIMENSIONS)) {
				dimensions = entityInfo->getAttributeAsVector3(STR_PHYSIC_DIMENSIONS);
			} else {
				dimensions = Vector3.ZERO;	//dimensions no ser� NULL bajo ning�n concepto
			}

			_physicServer->createBoxShape(model, dimensions * scale, group);
		} 
	}

	//---------------------------------------------------------

	CPhysicModelGeneric* PhysicEntity::createPhysicModelGeneric(const Core::EntityInfoTable *entityInfo)
	{
		// Comprobar que estamos creando una entidad f�sica gen�rica
		std::string entity = "";

		if (entityInfo->hasAttribute(STR_PHYSIC_ENTITY)) {
			entity.append(entityInfo->getAttribute(STR_PHYSIC_ENTITY));
		}

		assert(entity == STR_GENERIC);
		// Crear el modelo f�sico a partir de un fichero
		std::string file = entityInfo->getAttribute(STR_PHYSIC_FILE);
		return _physicServer->createModelGeneric(file);
	}
}
