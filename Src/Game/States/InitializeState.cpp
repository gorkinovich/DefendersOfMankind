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

#include <OgreLog.h>

#include "Game/States/InitializeState.h"

#include "Core/BaseManager.h"
#include "Core/GenericApplication.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Physics/Server.h"
#include "Logic/GameManager.h"
#include "Logic/Controllers/MusicController.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string InitializeState::StateName = std::string(INITIALIZE_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InitializeState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("Initialize.layout", "Initialize")) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeState::activate() {
		// Activamos la ventana del estado.
		activateWindow(false, true);

		// Configuramos las variables de control del proceso.
		_step = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeState::update(unsigned int lastInterval) {
		// Pasos que dar para terminar el proceso de inicialización del juego.
		switch(_step) {
			case 0:
				// Inicializamos el gestor de la física.
				if(!Physics::CServer::Init()) {
					_baseManager->getOgreLog()->logMessage("InitializeState::update -> Physics server initialization failed...");
					_application->exitRequest();
				}
				break;

			case 1:
				// Cargamos los datos que describen al juego.
				if(!Core::ScriptingManager::GetInstance()->loadAndRunFile("Game.lua")) {
					_baseManager->getOgreLog()->logMessage("InitializeState::update -> Game.lua script not loaded...");
					_application->exitRequest();
				}
				break;

			case 2:
				// Inicializamos el gestor base del juego.
				if(!Logic::GameManager::GetInstance()->initialize()) {
					_baseManager->getOgreLog()->logMessage("InitializeState::update -> Game manager initialization failed...");
					_application->exitRequest();
				}
				break;

			default:
				// Cambiamos al estado del menú principal del juego.
				_application->changeState(MAIN_MENU_STATE_NAME);
				Logic::GameManager::GetInstance()->getMusic()->loadSong("MenuMusic.mp3");
				Logic::GameManager::GetInstance()->getMusic()->playSong();
				break;
		}

		// Avanzamos un paso dentro del proceso.
		++_step;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	InitializeState::InitializeState(Core::GenericApplication * application) : GenericMenuState(application), _step(0) {}

	//--------------------------------------------------------------------------------------------------------

	InitializeState::~InitializeState() {}
}
