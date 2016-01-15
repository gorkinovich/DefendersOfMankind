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

#include <CEGUIWindow.h>
#include <elements/CEGUIProgressBar.h>
#include <OgreStringConverter.h>

#include "Game/States/InitializeGameState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/GUIManager.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string InitializeGameState::StateName = std::string(INITIALIZE_GAME_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InitializeGameState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("InitializeGame.layout", "InitializeGame")) return false;

		// Obtenemos los objetos interactivos de la ventana actual.
		_loadingBar = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::ProgressBar>("InitializeGame/LoadingBar");
		if(!_loadingBar) return false;

		_loadingText = Core::GUIManager::GetInstance()->getWindow("InitializeGame/LoadingText");
		if(!_loadingText) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeGameState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_loadingBar = 0;
		_loadingText = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeGameState::activate() {
		// Activamos la ventana del estado.
		activateWindow(false, true);

		// Configuramos las variables de control del proceso.
		_step = 0;

		// Inicializamos los elementos interactivos de la ventana.
		_loadingBar->setProgress(0.0f);
		_loadingText->setText("0%");
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeGameState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeGameState::update(unsigned int lastInterval) {
		// Pasos que dar para terminar el proceso de inicialización de la partida.
		switch(_step) {
			case 0:
				//TODO: Completar el método...
				_application->sleep(100);
				//...
				break;

			default:
				// Cambiamos al estado del menú principal de la partida.
				_application->changeState(COMMAND_CENTER_MENU_STATE_NAME);
				break;
		}

		// Avanzamos un paso dentro del proceso.
		++_step;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	InitializeGameState::InitializeGameState(Core::GenericApplication * application)
	: GenericMenuState(application), _step(0), _loadingBar(0), _loadingText(0) {}

	//--------------------------------------------------------------------------------------------------------

	InitializeGameState::~InitializeGameState() {}
}
