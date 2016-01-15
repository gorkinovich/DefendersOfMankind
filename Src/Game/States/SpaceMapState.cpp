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

#include "Game/States/SpaceMapState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Logic/Data/SpaceMapInfo.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string SpaceMapState::StateName = std::string(SPACE_MAP_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool SpaceMapState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("SpaceMap.layout", "SpaceMap")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("SpaceMap/Mission01", &SpaceMapState::missionButton, this);
		SubscribeToClickedEvent("SpaceMap/Mission02", &SpaceMapState::missionButton, this);
		SubscribeToClickedEvent("SpaceMap/BackButton", &SpaceMapState::backButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		CEGUI::PushButton * aux = 0;

		aux = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>("SpaceMap/Mission01");
		if(!aux) return false;
		_missionButtons.push_back(aux);

		aux = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>("SpaceMap/Mission02");
		if(!aux) return false;
		_missionButtons.push_back(aux);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void SpaceMapState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_missionButtons.clear();

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void SpaceMapState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		// Inicializamos los elementos interactivos de la ventana.
		Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
		Logic::SpaceMapInfo * spaceMap = gameManager->getSpaceMapInfo();
		Logic::SpaceMapInfo::MissionInfoVector::iterator i = spaceMap->getMissionsBegin();
		Logic::SpaceMapInfo::MissionInfoVector::iterator end = spaceMap->getMissionsEnd();
		for(; i != end; ++i) {
			if(Core::GUIManager::GetInstance()->containsWindow(i->buttonName)) {
				CEGUI::PushButton * victim = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>(i->buttonName);
				if(victim) {
					if(i->requires.size() > 0) {
						bool isEnable = true;
						unsigned int k = 0;
						for(unsigned int j = 0; j < i->requires.size(); ++j) {
							if(spaceMap->containsMission(i->requires[j]) && spaceMap->findMission(i->requires[j]).isDone) {
								++k;
							}
						}
						victim->setEnabled(k > 0);
					} else {
						victim->setEnabled(true);
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void SpaceMapState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void SpaceMapState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SpaceMapState::missionButton(const CEGUI::EventArgs & e) {
		if(typeid(CEGUI::WindowEventArgs) == typeid(e)) {
			const CEGUI::WindowEventArgs & wea = dynamic_cast<const CEGUI::WindowEventArgs &>(e);
			Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
			Logic::SpaceMapInfo * spaceMap = gameManager->getSpaceMapInfo();
			Logic::SpaceMapInfo::MissionInfoVector::iterator i = spaceMap->getMissionsBegin();
			Logic::SpaceMapInfo::MissionInfoVector::iterator end = spaceMap->getMissionsEnd();
			for(; i != end; ++i) {
				if(i->buttonName == std::string(wea.window->getName().c_str())) {
					gameManager->startMission(i->file);
					break;
				}
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SpaceMapState::backButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	SpaceMapState::SpaceMapState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	SpaceMapState::~SpaceMapState() {}
}
