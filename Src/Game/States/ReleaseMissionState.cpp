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

#include "Game/States/ReleaseMissionState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
//#include "Logic/MissionManager.h"
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

	const std::string ReleaseMissionState::StateName = std::string(RELEASE_MISSION_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ReleaseMissionState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ReleaseMission.layout", "ReleaseMission")) return false;

		//TODO: Completar el método...
		/*
		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("xxx/xxx", &xxx::xxx, this);
		//*/
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseMissionState::release() {
		//TODO: Completar el método...
		/*
		//*/
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseMissionState::activate() {
		// Activamos la ventana del estado.
		activateWindow(false, true);
		//TODO: Completar el método...
		/*
		//*/
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseMissionState::deactivate() {
		//TODO: Completar el método...
		/*
		//*/
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseMissionState::update(unsigned int lastInterval) {
		//TODO: Completar el método...
		_application->sleep(100);
		_application->popToState(SPACE_MAP_STATE_NAME);
		Logic::GameManager::GetInstance()->getMusic()->unloadSong();
		Logic::GameManager::GetInstance()->getMusic()->loadSong("MenuMusic.mp3");
		Logic::GameManager::GetInstance()->getMusic()->playSong();
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	/*
	bool ReleaseMissionState::xxx(const CEGUI::EventArgs & e) {
		//TODO: Completar el método...
		return true;
	}
	//*/

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ReleaseMissionState::ReleaseMissionState(Core::GenericApplication * application) : GenericMenuState(application) {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	ReleaseMissionState::~ReleaseMissionState() {
		//TODO: Completar el método...
	}
}
