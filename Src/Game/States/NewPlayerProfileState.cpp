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

#include <elements/CEGUIEditbox.h>

#include "Game/States/NewPlayerProfileState.h"

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

	const std::string NewPlayerProfileState::StateName = std::string(NEW_PLAYER_PROFILE_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool NewPlayerProfileState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("NewPlayerProfile.layout", "NewPlayerProfile")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("NewPlayerProfile/AcceptButton", &NewPlayerProfileState::acceptButton, this);
		SubscribeToClickedEvent("NewPlayerProfile/CancelButton", &NewPlayerProfileState::cancelButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_playerName = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::Editbox>("NewPlayerProfile/PlayerName");
		if(!_playerName) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void NewPlayerProfileState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_playerName = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void NewPlayerProfileState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void NewPlayerProfileState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void NewPlayerProfileState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool NewPlayerProfileState::acceptButton(const CEGUI::EventArgs & e) {
		// Obtenemos el nombre introducido por el jugador.
		std::string name = _playerName->getText().c_str();
		// Intentamos añadirlo a los perfiles del juego.
		Logic::ProfileController * controller = Logic::GameManager::GetInstance()->getProfile();
		if(controller->addNewPlayerProfile(name)) {
			// Si se logra añadir, cambiamos al menú del jugador actual.
			_application->pushState(MAIN_PLAYER_MENU_STATE_NAME);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool NewPlayerProfileState::cancelButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	NewPlayerProfileState::NewPlayerProfileState(Core::GenericApplication * application)
	: GenericMenuState(application), _playerName(0) {}

	//--------------------------------------------------------------------------------------------------------

	NewPlayerProfileState::~NewPlayerProfileState() {}
}
