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
Contiene la implementación del componente que envia un mensaje SWITCH a una
entidad cuando su entidad es tocada o dejada de ser tocada.
*/

#include <assert.h>

#include "Logic/Entity/Components/SwitchTrigger.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool SwitchTrigger::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		assert(entityInfo->hasAttribute("target") && "Hay que especificar el atributo target");

		if(entityInfo->hasAttribute("target")) {	
			_targetName = entityInfo->getAttribute("target");
		}

		return true;
	}
	
	//---------------------------------------------------------

	bool SwitchTrigger::activate()
	{
		// Obtenemos la entidad objetivo a lanzar.
		if(_targetName.length())
			_target = _owner->getWorld()->getEntityByName(_targetName);

		return true;
	}
	
	//---------------------------------------------------------

	void SwitchTrigger::deactivate()
	{
		_target = 0;
	}
	
	//---------------------------------------------------------

	bool SwitchTrigger::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_TOUCHED ||
			message->getType() == MESSAGE_TYPE_UNTOUCHED;
	}
	
	//---------------------------------------------------------

	void SwitchTrigger::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_TOUCHED:
			// Verificamos que la entidad que la ha tocado es el jugador
			{
				const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
				if(msgData.getVictim()->getType() == _targetName)
				{
					// Enviamos un mensaje de tipo SWITCH
					_target->sendMessage(MessageFactory::CreateSwitchMessage(1));
				}
			}
			break;

		case MESSAGE_TYPE_UNTOUCHED:
			// Verificamos que la entidad que la ha tocado es el jugador
			{
				const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
				if(_target && msgData.getVictim()->getComponentAs<GeneralData>("GeneralData")->isPlayer())
				{
					// Enviamos un mensaje de tipo SWITCH
					_target->sendMessage(MessageFactory::CreateSwitchMessage(0));
				}
			}
			break;
		}
	}
}
