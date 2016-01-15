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

#include <CEGUIWindow.h>
#include "Core/Graphics/GraphicsManager.h"
#include "Core/GUI/GUIManager.h"
#include "Game/GenericMenuState.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************
	
	bool GenericMenuState::initializeWindow(const std::string & fileName, const std::string & windowName) {
		// Mandamos cargar el objeto ventana que se va a mostrar como pantalla del men�.
		Core::GUIManager::GetInstance()->loadWindow(fileName);
		// Despu�s de cargarlo, pedimos que nos entreguen el objeto ventana cargado.
		_window = Core::GUIManager::GetInstance()->getWindow(windowName);
		// Y devolvemos si realmente se ha inicializado todo correctamente.
		return _window != 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericMenuState::releaseWindow() {
		// Mandamos destruir el objeto ventana.
		_window->destroy();
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericMenuState::activateWindow(bool showMouse, bool updateGraphics) {
		// Establecemos el objeto ventana como el nodo ra�z de la interfaz gr�fica.
		Core::GUIManager::GetInstance()->setRootWindow(_window);
		// Hacemos que el objeto ventana pueda ser visible.
		_window->setVisible(true);
		// Activamos el objeto ventana.
		_window->activate();
		// Comprobamos si el flag de mostrar el cursor rat�n est� activado.
		if(showMouse) {
			// Mandamos mostrar el cursor del rat�n de la interfaz gr�fica.
			Core::GUIManager::GetInstance()->showMouseCursor();
		} else {
			// Mandamos ocultar el cursor del rat�n de la interfaz gr�fica.
			Core::GUIManager::GetInstance()->hideMouseCursor();
		}
		// Comprobamos el flag que indica si se debe actualizar el motor gr�fico o no.
		if(updateGraphics) {
			// Actualizamos el gestor del motor gr�fico, para actualizar la interfaz gr�fica.
			Core::GraphicsManager::GetInstance()->update(0);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericMenuState::deactivateWindow(bool hideMouse) {
		// Comprobamos si el flag de ocultar el cursor rat�n est� activado.
		if(hideMouse) {
			// Mandamos ocultar el cursor del rat�n de la interfaz gr�fica.
			Core::GUIManager::GetInstance()->hideMouseCursor();
		} else {
			// Mandamos mostrar el cursor del rat�n de la interfaz gr�fica.
			Core::GUIManager::GetInstance()->showMouseCursor();
		}
		// Desactivamos el objeto ventana.
		_window->deactivate();
		// Hacemos que el objeto ventana no est� visible.
		_window->setVisible(false);
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************
	
	GenericMenuState::GenericMenuState(Core::GenericApplication * application)
	: ApplicationState(application), _window(0) {}
	
	//--------------------------------------------------------------------------------------------------------
	
	GenericMenuState::~GenericMenuState() {}
}
