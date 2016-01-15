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

#include <assert.h>
#include <OISMouse.h>
#include <OISInputManager.h>

#include "Core/Input/InputManager.h"
#include "Core/Input/Mouse.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	Mouse * Mouse::_instance = new Mouse();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void Mouse::setPosition(unsigned int x, unsigned int y) {
		assert(_device && "Mouse::setPosition -> The device has not been created...");
		OIS::MouseState & victim = const_cast<OIS::MouseState &>(_device->getMouseState());
		// Asignamos las coordenadas comprobando que no se han salido de los límites.
		victim.X.abs = (int)x;
		victim.Y.abs = (int)y;
		_state.screenAbsX = (x > _state.screenWidth) ? _state.screenWidth : x;
		_state.screenAbsY = (y > _state.screenHeight) ? _state.screenHeight : y;
		// Y recalculamos las coordenadas relativas de la pantalla.
		_state.screenRelX = (float)_state.screenAbsX / (float)_state.screenWidth;
		_state.screenRelY = (float)_state.screenAbsY / (float)_state.screenHeight;
	}

	//--------------------------------------------------------------------------------------------------------

	void Mouse::setWindowSize(unsigned int width, unsigned int height) {
		assert(_device && "Mouse::setWindowSize -> The device has not been created...");
		const OIS::MouseState & devState = _device->getMouseState();
		// Cambiamos la dimensión de la ventana.
		devState.width = width;
		devState.height = height;
		_state.screenWidth = width;
		_state.screenHeight = height;
		// Comprobamos que las coordenadas actuales no se han salido de los límites.
		_state.screenAbsX = (_state.screenAbsX > _state.screenWidth) ? _state.screenWidth : _state.screenAbsX;
		_state.screenAbsY = (_state.screenAbsY > _state.screenHeight) ? _state.screenHeight : _state.screenAbsY;
		// Y recalculamos las coordenadas relativas de la pantalla.
		_state.screenRelX = (float)_state.screenAbsX / (float)_state.screenWidth;
		_state.screenRelY = (float)_state.screenAbsY / (float)_state.screenHeight;
	}

	//--------------------------------------------------------------------------------------------------------

	void Mouse::resetState() {
		assert(_device && "Mouse::resetState -> The device has not been created...");
		OIS::MouseState & victim = const_cast<OIS::MouseState &>(_device->getMouseState());
		// Reseteamos el estado interno del ratón gestionado por OIS.
		victim.clear();
		_state.screenWidth = victim.width;
		_state.screenHeight = victim.height;
		// Y actualizamos el estado actual del objeto.
		updateState();
	}

	//--------------------------------------------------------------------------------------------------------

	void Mouse::initialize() {
		assert(InputManager::GetInstance() && InputManager::GetInstance()->_system &&
			"Mouse::initialize -> The input manager has not been created...");
		OIS::InputManager * system = InputManager::GetInstance()->_system;
		// Obtenemos el dispositivo del ratón si hay alguno conectado.
		if(system->getNumberOfDevices(OIS::OISMouse) > 0) {
			_device = static_cast<OIS::Mouse *>(system->createInputObject(OIS::OISMouse, true));
			// Inicializamos el estado del ratón.
			_state.screenWidth = _device->getMouseState().width;
			_state.screenHeight = _device->getMouseState().height;
			updateState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Mouse::release() {
		assert(InputManager::GetInstance() && InputManager::GetInstance()->_system &&
			"Mouse::release -> The input manager has not been created...");
		OIS::InputManager * system = InputManager::GetInstance()->_system;
		// Destruimos el dispositivo del ratón de haber obtenido alguno.
		if(_device) {
			system->destroyInputObject(_device);
			_device = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Mouse::update() {
		assert(_device && "Mouse::update -> The device has not been created...");
		_device->capture();
		updateState();
	}

	//--------------------------------------------------------------------------------------------------------

	void Mouse::updateState() {
		const OIS::MouseState & devState = _device->getMouseState();
		// Actualizamos el valor de los botones del ratón.
		_state.left = devState.buttonDown(OIS::MB_Left);
		_state.middle = devState.buttonDown(OIS::MB_Middle);
		_state.right = devState.buttonDown(OIS::MB_Right);
		// Actualizamos el valor relativo de los ejes.
		_state.x = devState.X.rel;
		_state.y = devState.Y.rel;
		_state.scrollWheel = devState.Z.rel;
		// Actualizamos el valor absoluto de los ejes.
		_state.screenAbsX = (unsigned int)devState.X.abs;
		_state.screenAbsY = (unsigned int)devState.Y.abs;
		// Y recalculamos las coordenadas relativas de la pantalla.
		_state.screenRelX = (float)_state.screenAbsX / (float)_state.screenWidth;
		_state.screenRelY = (float)_state.screenAbsY / (float)_state.screenHeight;
	}
}
