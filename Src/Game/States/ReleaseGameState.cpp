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

#include "Game/States/ReleaseGameState.h"

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

	const std::string ReleaseGameState::StateName = std::string(RELEASE_GAME_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ReleaseGameState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ReleaseGame.layout", "ReleaseGame")) return false;

		//TODO: Completar el método...
		/*
		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("xxx/xxx", &xxx::xxx, this);
		//*/
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseGameState::release() {
		//TODO: Completar el método...
		/*
		//*/
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseGameState::activate() {
		// Activamos la ventana del estado.
		activateWindow(false, true);
		//TODO: Completar el método...
		/*
		//*/
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseGameState::deactivate() {
		//TODO: Completar el método...
		/*
		//*/
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseGameState::update(unsigned int lastInterval) {
		//TODO: Completar el método...
		_application->sleep(100);
		_application->popToState(MAIN_PLAYER_MENU_STATE_NAME);
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	/*
	bool ReleaseGameState::xxx(const CEGUI::EventArgs & e) {
		//TODO: Completar el método...
		return true;
	}
	//*/

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ReleaseGameState::ReleaseGameState(Core::GenericApplication * application) : GenericMenuState(application) {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	ReleaseGameState::~ReleaseGameState() {
		//TODO: Completar el método...
	}
}
