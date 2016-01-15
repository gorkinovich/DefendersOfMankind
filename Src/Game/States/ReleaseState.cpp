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

#include "Game/States/ReleaseState.h"

#include "Core/GenericApplication.h"
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

	const std::string ReleaseState::StateName = std::string(RELEASE_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ReleaseState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("Release.layout", "Release")) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		// Configuramos las variables de control del proceso.
		_step = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ReleaseState::update(unsigned int lastInterval) {
		// Pasos que dar para empezar el proceso de finalización del juego.
		switch(_step) {
			case 0:
				Logic::GameManager::GetInstance()->getMusic()->unloadSong();
				break;
				
			case 1:
				// Finalizamos el gestor base del juego.
				if(Logic::GameManager::GetInstance()) {
					Logic::GameManager::GetInstance()->release();
				}
				break;

			case 2:
				// Finalizamos el gestor de la física.
				if(Physics::CServer::getSingletonPtr()) {
					Physics::CServer::Release();
				}
				break;

			default:
				// Pedimos salir del bucle principal del juego.
				_application->exitRequest();
				break;
		}

		// Avanzamos un paso dentro del proceso.
		++_step;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ReleaseState::ReleaseState(Core::GenericApplication * application) : GenericMenuState(application), _step(0) {}

	//--------------------------------------------------------------------------------------------------------

	ReleaseState::~ReleaseState() {}
}
