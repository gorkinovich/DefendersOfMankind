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

//TODO: Completar y comentar el fichero...

#include "Game/States/GraphicsOptionsState.h"

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
	// Campos est�ticos
	//********************************************************************************************************

	const std::string GraphicsOptionsState::StateName = std::string(GRAPHICS_OPTIONS_STATE_NAME);

	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	bool GraphicsOptionsState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("GraphicsOptions.layout", "GraphicsOptions")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("GraphicsOptions/AcceptButton", &GraphicsOptionsState::acceptButton, this);
		SubscribeToClickedEvent("GraphicsOptions/CancelButton", &GraphicsOptionsState::cancelButton, this);

		//TODO: Completar el m�todo...
		/*
		// Obtenemos los objetos interactivos de la ventana actual.
		//*/

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsOptionsState::release() {
		//TODO: Completar el m�todo...
		/*
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		//*/

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsOptionsState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		//TODO: Completar el m�todo...
		// Inicializamos los objetos interactivos de la ventana actual.
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsOptionsState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsOptionsState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicsOptionsState::acceptButton(const CEGUI::EventArgs & e) {
		//TODO: Completar el m�todo...
		//...
		_application->popState();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicsOptionsState::cancelButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GraphicsOptionsState::GraphicsOptionsState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	GraphicsOptionsState::~GraphicsOptionsState() {}
}
