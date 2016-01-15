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

#include <assert.h>

#include "Logic/Entity/Components/GeneralData.h"

#include "Core/Data/EntityInfoTable.h"
#include "Logic/MissionManager.h"

namespace Logic {

	bool GeneralData::spawn(const Core::EntityInfoTable * entityInfo) {
		assert(_owner && "The component does not have an entity...");

		if(entityInfo->hasAttribute("isPlayer")) {
			_isPlayer = entityInfo->getAttributeAsBool("isPlayer");
		}

		if(entityInfo->hasAttribute("isCamera")) {
			_isCamera = entityInfo->getAttributeAsBool("isCamera");
		}

		if(entityInfo->hasAttribute("idSquadron")) {
			_IDSquadron = entityInfo->getAttributeAsInteger("idSquadron");
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GeneralData::activate() {
		MissionManager * manager = MissionManager::GetInstance();

		// Si somos jugador, se lo decimos al servidor
		if(isPlayer()) {
			manager->setPlayer(_owner);
		}

		// Si somos cámara, se lo decimos al servidor
		if(isCamera()) {
			manager->setCamera(_owner);
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GeneralData::deactivate() {
		// Si éramos el jugador, le decimos al servidor que ya no hay.
		if(isPlayer()) {
			MissionManager::GetInstance()->setPlayer(0);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool GeneralData::acceptMessage(const Core::SmartMessage & message) {
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void GeneralData::processMessage(const Core::SmartMessage & message) {
	}
}
