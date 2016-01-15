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
Contiene la implementación del componente que controla el movimiento de
una entidad que tiene dos estado (posiciones) para ir de una a otra.
*/

#include <assert.h>

#include "Logic/Entity/Components/SwitchPosition.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/SwitchMessage.h"

namespace Logic 
{
	SwitchPosition::SwitchPosition() : Component("SwitchPosition"), _targetPosition(Vector3::ZERO), _speed(0.05f), _loop(false)
	{
		_position[0] = Vector3::ZERO;
		_position[1] = Vector3::ZERO;
	}

	//---------------------------------------------------------

	bool SwitchPosition::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getAttributeAsFloat("speed");

		if(entityInfo->hasAttribute("loop"))
			_loop = entityInfo->getAttributeAsBool("loop");

		const Core::EntityInfoTableNames * attributeNames = Core::EntitiesManager::GetInstance()->getAttributeNames();
		if(entityInfo->hasAttribute("position")) {
			_position[0] = entityInfo->getAttributeAsVector3("position");
			_targetPosition = _position[0];
		} else if(entityInfo->hasAttribute(attributeNames->position)) {
			_position[0] = entityInfo->getAttributeAsVector3(attributeNames->position);
			_targetPosition = _position[0];
		}

		if(entityInfo->hasAttribute("position2")) 
			_position[1] = entityInfo->getAttributeAsVector3("position2");

		return true;
	}

	
	//---------------------------------------------------------

	bool SwitchPosition::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_SWITCH;
	}
	
	//---------------------------------------------------------

	void SwitchPosition::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_SWITCH:
			const SwitchMessage & msg = message->getDataRefAs<SwitchMessage>();
			assert((msg.getTouched() >= 0) && (msg.getTouched() <= 1));
			_targetPosition = _position[msg.getTouched()];
			break;
		}
	}
	
	//---------------------------------------------------------

	void SwitchPosition::update(unsigned int lastInterval)
	{
		// Invocamos al método de la clase padre
		Component::update(lastInterval);

		// Si la posición actual aun no es la objetivo nos desplazamos hacia ella.
		Position * positionComponent = _owner->getComponentAs<Position>("Position");
		float distance = positionComponent->getPosition().distance(_targetPosition);
		if(distance > 0.0001)
		{
			// Calcular vector de desplazamiento
			Vector3 direction = _targetPosition - positionComponent->getPosition();
			direction.normalise();
			direction *= lastInterval * _speed;

			// Controlamos que no nos pasemos del destino
			if (direction.length() > distance) {
				direction /= direction.length() / distance;
			}

			// Movemos la entidad a la nueva posición
			positionComponent->setPosition(positionComponent->getPosition() + direction);
		}
		// Si estamos en loop y hemos llegado a una posición transitamos a la otra.
		else if(_loop)
		{
			_targetPosition = _position[(_targetPosition == _position[0]) ? 1 : 0];
		}
	}
}
