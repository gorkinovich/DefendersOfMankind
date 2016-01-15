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

#include "Game/States/ConfirmExitMissionState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ConfirmExitMissionState::StateName = std::string(CONFIRM_EXIT_MISSION_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ConfirmExitMissionState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ConfirmExitMission.layout", "ConfirmExitMission")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ConfirmExitMission/YesButton", &ConfirmExitMissionState::yesButton, this);
		SubscribeToClickedEvent("ConfirmExitMission/NoButton", &ConfirmExitMissionState::noButton, this);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitMissionState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitMissionState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitMissionState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitMissionState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ConfirmExitMissionState::yesButton(const CEGUI::EventArgs & e) {
		_application->changeState(RELEASE_MISSION_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ConfirmExitMissionState::noButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ConfirmExitMissionState::ConfirmExitMissionState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	ConfirmExitMissionState::~ConfirmExitMissionState() {}
}
