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

//TODO: Completar y comentar el fichero...

#include "Game/States/GameplayOptionsState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
//#include "Logic/GameManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string GameplayOptionsState::StateName = std::string(GAMEPLAY_OPTIONS_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GameplayOptionsState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("GameplayOptions.layout", "GameplayOptions")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("GameplayOptions/AcceptButton", &GameplayOptionsState::acceptButton, this);
		SubscribeToClickedEvent("GameplayOptions/CancelButton", &GameplayOptionsState::cancelButton, this);

		//TODO: Completar el método...
		/*
		// Obtenemos los objetos interactivos de la ventana actual.
		//*/

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GameplayOptionsState::release() {
		//TODO: Completar el método...
		/*
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		//*/

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void GameplayOptionsState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		//TODO: Completar el método...
		// Inicializamos los objetos interactivos de la ventana actual.
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	void GameplayOptionsState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void GameplayOptionsState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameplayOptionsState::acceptButton(const CEGUI::EventArgs & e) {
		//TODO: Completar el método...
		//...
		_application->popState();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameplayOptionsState::cancelButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GameplayOptionsState::GameplayOptionsState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	GameplayOptionsState::~GameplayOptionsState() {}
}
