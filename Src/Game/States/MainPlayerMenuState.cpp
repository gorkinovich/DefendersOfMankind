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

#include "Game/States/MainPlayerMenuState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Game/StatesNames.h"
#include "Logic/GameManager.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string MainPlayerMenuState::StateName = std::string(MAIN_PLAYER_MENU_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MainPlayerMenuState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("MainPlayerMenu.layout", "MainPlayerMenu")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("MainPlayerMenu/NewGameButton", &MainPlayerMenuState::newGameButton, this);
		SubscribeToClickedEvent("MainPlayerMenu/LoadGameButton", &MainPlayerMenuState::loadGameButton, this);
		SubscribeToClickedEvent("MainPlayerMenu/OptionsButton", &MainPlayerMenuState::optionsButton, this);
		SubscribeToClickedEvent("MainPlayerMenu/ExitProfileButton", &MainPlayerMenuState::exitProfileButton, this);
		SubscribeToClickedEvent("MainPlayerMenu/ExitGameButton", &MainPlayerMenuState::exitGameButton, this);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void MainPlayerMenuState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void MainPlayerMenuState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void MainPlayerMenuState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void MainPlayerMenuState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->pushState(CONFIRM_EXIT_PROFILE_STATE_NAME);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainPlayerMenuState::newGameButton(const CEGUI::EventArgs & e) {
		//_application->pushState(CHOOSE_DIFFICULTY_LEVEL_STATE_NAME);
		if(Logic::GameManager::GetInstance()->startNewGame(Logic::GameManager::NormalDifficulty)) {
			_application->changeState(INITIALIZE_GAME_STATE_NAME);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainPlayerMenuState::loadGameButton(const CEGUI::EventArgs & e) {
		_application->pushState(LOAD_GAME_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainPlayerMenuState::optionsButton(const CEGUI::EventArgs & e) {
		_application->pushState(OPTIONS_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainPlayerMenuState::exitProfileButton(const CEGUI::EventArgs & e) {
		_application->pushState(CONFIRM_EXIT_PROFILE_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainPlayerMenuState::exitGameButton(const CEGUI::EventArgs & e) {
		_application->pushState(CONFIRM_EXIT_STATE_NAME);
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	MainPlayerMenuState::MainPlayerMenuState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	MainPlayerMenuState::~MainPlayerMenuState() {}
}
