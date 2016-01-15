//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
//************************************************************************************************************

#include "Game/States/ConfirmExitGameState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos est�ticos
	//********************************************************************************************************

	const std::string ConfirmExitGameState::StateName = std::string(CONFIRM_EXIT_GAME_STATE_NAME);

	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	bool ConfirmExitGameState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ConfirmExitGame.layout", "ConfirmExitGame")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ConfirmExitGame/YesButton", &ConfirmExitGameState::yesButton, this);
		SubscribeToClickedEvent("ConfirmExitGame/NoButton", &ConfirmExitGameState::noButton, this);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitGameState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitGameState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitGameState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ConfirmExitGameState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ConfirmExitGameState::yesButton(const CEGUI::EventArgs & e) {
		// Salimos de la partida actual.
		if(Logic::GameManager::GetInstance()->finishCurrentGame()) {
			// Y cambiamos al men� del jugador actual.
			_application->changeState(RELEASE_GAME_STATE_NAME);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ConfirmExitGameState::noButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ConfirmExitGameState::ConfirmExitGameState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	ConfirmExitGameState::~ConfirmExitGameState() {}
}
