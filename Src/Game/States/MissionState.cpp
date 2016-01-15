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

#include "Game/States/MissionState.h"

#include "Core/GenericApplication.h"
#include "Core/Input/Keyboard.h"
//#include "Logic/MissionManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string MissionState::StateName = std::string(MISSION_STATE_NAME);

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	//--------------------------------------------------------------------------------------------------------

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MissionState::initialize() {
		//TODO: Completar el método...
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionState::release() {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionState::activate() {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionState::deactivate() {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionState::update(unsigned int lastInterval) {
		//TODO: Completar el método...
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->pushState(MISSION_MENU_STATE_NAME);
		} else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_N1)) {
			_application->changeState(SHOW_STATISTICS_STATE_NAME);
		} else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_N2)) {
			_application->changeState(MISSION_FAILED_STATE_NAME);
		}
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	MissionState::MissionState(Core::GenericApplication * application) : ApplicationState(application) {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	MissionState::~MissionState() {
		//TODO: Completar el método...
	}
}
