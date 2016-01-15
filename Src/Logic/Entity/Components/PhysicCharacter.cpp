//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodríguez, Gorka Suárez, Roberto Jiménez
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
// Grupo 03: David Entrena, David Rodríguez, Gorka Suárez, Roberto Jiménez
//************************************************************************************************************

/**
Contiene la implementación del componente que se utiliza para representar jugadores y enemigos en
el mundo físico usando character controllers.
*/

#include <assert.h>

#include "Logic/Entity/Components/PhysicCharacter.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Physics/PhysicModelCharacter.h"
#include "Physics/PhysicObjCharacter.h"
#include "Physics/Server.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/AvatarWalkMessage.h"
//#include "Logic/Entity/Messages/ChangeTransformMessage.h"
#include "Logic/Entity/Messages/MessageTypes.h"

using namespace Physics;

namespace Logic
{
	PhysicCharacter::PhysicCharacter() : PhysicEntity("PhysicCharacter"), _offsetY(0), _movement(0,0,0), _falling(false)
	{
		//TODO: Prueba de prioridad...
		setPriority(1);
		//...
	}

	//---------------------------------------------------------

	PhysicCharacter::~PhysicCharacter() 
	{
	} 

	//---------------------------------------------------------

	bool PhysicCharacter::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		// Invocar al método de la clase padre
		if(!PhysicEntity::spawn(entityInfo)) return false;

		if (_physicObj->IsKinematic()) 
			_physicServer->moveCharacter((CPhysicObjCharacter *)_physicObj, _transform.getTrans());

		return (_physicObj != NULL);
	} 

	//---------------------------------------------------------

	bool PhysicCharacter::acceptMessage(const Core::SmartMessage & message)
	{

		return ((message->getType() == MESSAGE_TYPE_AVATAR_WALK)||(message->getType() == MESSAGE_TYPE_CHANGE_TRANSFORM));
	} 

	//---------------------------------------------------------

	void PhysicCharacter::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_AVATAR_WALK:
			// Anotamos el vector de desplazamiento para usarlo posteriormente en 
			// el método tick. De esa forma, si recibimos varios mensajes AVATAR_WALK
			// en el mismo ciclo sólo tendremos en cuenta el último.
			_movement = message->getDataRefAs<AvatarWalkMessage>().getMovement();

			break;
		/*case MESSAGE_TYPE_CHANGE_TRANSFORM:
			_transform =  message->getDataRefAs<ChangeTransformMessage>().getTransform();
			break;*/
		}
	} 

	//---------------------------------------------------------

	void PhysicCharacter::prepareUpdate(unsigned int lastInterval){
	
		// Si estamos cayendo modificar el vector de desplazamiento para
		// simular el efecto de la gravedad
		if (_falling) {
			_movement += Vector3(0,-1,0);
		}
		// Mover el character controller y actualizar el flag de caida
		unsigned flags = _physicServer->moveCharacter((CPhysicObjCharacter *)_physicObj, _movement);
		//_physicServer->move(_physicObj, _transform);
		//_falling =  !(flags & NXCC_COLLISION_DOWN);
		_movement = Vector3::ZERO;
	}

	void PhysicCharacter::update(unsigned int lastInterval)
	{
		// Llamar al método de la clase padre (IMPORTANTE).
		Component::update(lastInterval);

		// Los controllers no tienen orientación, así que sólo actualizamos su posición.
		// Es importante transformar entre posiciones lógicas y posiciones físicas.
		Vector3 physicPos = _physicServer->getPosition(_physicObj);
		Position * positionComponent = _owner->getComponentAs<Position>("Position");
		positionComponent->setPosition(fromPhysicsToLogic(physicPos));
	}

	//---------------------------------------------------------

	IPhysicObj* PhysicCharacter::createPhysicEntity(const Core::EntityInfoTable *entityInfo)
	{
		// Creamos la entidad física invocando al método de la clase padre.
		CPhysicObjCharacter *obj = (CPhysicObjCharacter *) PhysicEntity::createPhysicEntity(entityInfo);

		// A continuación debemos colocar la entidad física en su sitio, ya que con la invocación
		// al método anterior no hemos tenido en cuenta la diferencia de sistemas de coordenadas.
		// Además sumaremos un pequeño desplazamiento en el eje Y para asegurarnos de que el
		// controller queda por encima del suelo y no lo atraviesa.
		Vector3 pos = fromLogicToPhysics(_physicServer->getPosition(obj));// + Vector3(0,2,0);
		_physicServer->setPosition(obj, pos);

		return obj;
	} 

	//---------------------------------------------------------

	IPhysicModel* PhysicCharacter::createPhysicModel(const Core::EntityInfoTable *entityInfo)
	{
		// Comprobar que estamos creando una entidad física de tipo character controller
		const std::string entity = entityInfo->getAttribute(STR_PHYSIC_ENTITY);
		assert(entity == STR_CONTROLLER);

		// Comprobar que el volumen de colision es una capsula
		if (entityInfo->hasAttribute(STR_PHYSIC_SHAPE)) {
			const std::string shape = entityInfo->getAttribute(STR_PHYSIC_SHAPE);
			assert(shape == STR_CAPSULE && "Tipo de shape no permitida en un character controller");
		}

		// Crear el modelo físico
		float radius = entityInfo->getAttributeAsFloat(STR_PHYSIC_RADIUS);
		float height = entityInfo->getAttributeAsFloat(STR_PHYSIC_HEIGHT);
		CPhysicModelCharacter *model = _physicServer->createModelCapsuleCharacter(radius, height);
			
		// Calculamos el desplazamiento necesario para transformar entre el sistema de 
		// coordenadas local de PhysX, que tiene su origen en el centro de la entidad, 
		// y el de la lógica, que tiene su origen en los pies de la entidad.
		_offsetY = height / 2.0f + radius;
		
		return model;
	}

	void PhysicCharacter::setMovement(Vector3 move){
		_movement += move;
	}
}
