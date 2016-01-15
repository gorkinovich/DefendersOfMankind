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
Contiene la declaración de un componente que cambia el centro de la acción al ser tocado. 
El mensaje se envía a la cámara.
*/

#include <assert.h>

#include "Logic/Entity/Components/BifurcationTrigger.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool BifurcationTrigger::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		if(entityInfo->hasAttribute("newCenter")) {
			_newCenter = entityInfo->getAttributeAsVector3("newCenter");
		} else {
			return false;
		}

		return true;
	}

	//---------------------------------------------------------

	bool BifurcationTrigger::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_TOUCHED;
	}
	
	//---------------------------------------------------------

	void BifurcationTrigger::processMessage(const Core::SmartMessage & message)
	{
		// Cuando la entidad propietaria de éste componente ha sido tocada...
		switch(message->getType())
		{
		case MESSAGE_TYPE_TOUCHED:
			{
				// Si es el jugador, envía un mensaje de cambio de centro
				const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
				if(msgData.getVictim()->getComponentAs<GeneralData>("GeneralData")->isPlayer()){
					//Logic::MissionManager::GetInstance()->getGameCamera()->setCenter(_newCenter);//sendMessage(MessageFactory::CreateChangeViewMessage(_cameraPosition));
					//Logic::MissionManager::GetInstance()->getGameCamera()->interpolateCenter(_newCenter,1.0f);
					Logic::MissionManager::GetInstance()->takeBifurcation(_newCenter, 1.0f);
				}
			}
			break;
		}
	}
}
