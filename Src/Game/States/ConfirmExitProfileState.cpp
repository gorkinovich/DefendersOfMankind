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

#include "Game/States/ConfirmExitProfileState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Logic/Controllers/ProfileController.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ConfirmExitProfileState::StateName = std::string(CONFIRM_EXIT_PROFILE_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ConfirmExitProfileState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ConfirmExitProfile.layout", "ConfirmExitProfile")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ConfirmExitProfile/YesButton", &ConfirmExitProfileState::yesButton, this);
		SubscribeToClickedEvent("ConfirmExitProfile/NoButton", &ConfirmExitProfileState::noButton, this);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitProfileState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitProfileState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitProfileState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitProfileState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ConfirmExitProfileState::yesButton(const CEGUI::EventArgs & e) {
		// Salimos del perfil actualmente cargado.
		Logic::GameManager::GetInstance()->getProfile()->exitCurrentProfile();
		// Y cambiamos al menú principal del juego.
		_application->popToState(MAIN_MENU_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ConfirmExitProfileState::noButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ConfirmExitProfileState::ConfirmExitProfileState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	ConfirmExitProfileState::~ConfirmExitProfileState() {}
}
