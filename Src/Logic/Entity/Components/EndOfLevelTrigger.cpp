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
Contiene la implementación del componente que activa el final de nivel cuando su 
entidad es tocada.
*/

#include <assert.h>

#include "Logic/Entity/Components/EndOfLevelTrigger.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool EndOfLevelTrigger::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		return true;
	}

	//---------------------------------------------------------

	bool EndOfLevelTrigger::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_TOUCHED;
	}
	
	//---------------------------------------------------------

	void EndOfLevelTrigger::processMessage(const Core::SmartMessage & message)
	{
		const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
		if(msgData.getVictim()->getComponentAs<GeneralData>("GeneralData")->isPlayer()) {
			printf("Has llegado al fin del nivel.\n");
			Logic::MissionManager::GetInstance()->setEndOfLevel(true);
		}
	}
}
