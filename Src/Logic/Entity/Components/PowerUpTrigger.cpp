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
Contiene la implementación del componente que envia un mensaje al jugador
con un efecto concreto
*/

#include <assert.h>

#include "Logic/Entity/Components/PowerUpTrigger.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/EntitiesManager.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/PowerUpMessage.h"

namespace Logic 
{
	bool PowerUpTrigger::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		int pup = 0;

		if(entityInfo->hasAttribute("powerup")) {
			pup = entityInfo->getAttributeAsInteger("powerup");
		}

		switch (pup) {
			case 0:  _powerUp = AUTOFIRE;       break;
			case 1:  _powerUp = INVINCIBILITY;  break;
			case 2:  _powerUp = SPEEDUP;        break;
			case 3:  _powerUp = HEAL;			break;
			case 4:  _powerUp = DAMAGEUP;		break;
			case 5:  _powerUp = BERSERKER;		break;
			default: _powerUp = AUTOFIRE;       break;
		}

		return true;
	}

	//---------------------------------------------------------

	bool PowerUpTrigger::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_TOUCHED;
	}
	
	//---------------------------------------------------------

	void PowerUpTrigger::processMessage(const Core::SmartMessage & message)
	{
		// Cuando la entidad propietaria de éste componente ha sido tocada...
		switch(message->getType())
		{
		case MESSAGE_TYPE_TOUCHED:
			{
				// Si es el jugador, le envía un mensaje y hacemos desaparecer el powerup 
				const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
				if(msgData.getVictim()->getComponentAs<GeneralData>("GeneralData")->isPlayer()){
					//Crear mensaje y enviarlo
					msgData.getVictim()->sendMessage(MessageFactory::CreatePowerUpMessage(_powerUp, true));
					//Eliminamos el trigger
					Core::EntitiesManager::GetInstance()->deferredDeleteEntity(_owner);
				}
			}
			break;
		}
	}
}