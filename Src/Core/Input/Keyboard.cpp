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
#include <OISKeyboard.h>
#include <OISInputManager.h>

#include "Core/Input/InputManager.h"
#include "Core/Input/Keyboard.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	Keyboard * Keyboard::_instance = new Keyboard();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool Keyboard::isModifierDown(ModifierCode modifier) const {
		assert(_device && "Keyboard::isModifierDown -> The device has not been created...");
		return _device->isModifierDown((OIS::Keyboard::Modifier)modifier);
	}

	//--------------------------------------------------------------------------------------------------------

	bool Keyboard::isModifierUp(ModifierCode modifier) const {
		assert(_device && "Keyboard::isModifierUp -> The device has not been created...");
		return !_device->isModifierDown((OIS::Keyboard::Modifier)modifier);
	}

	//--------------------------------------------------------------------------------------------------------

	void Keyboard::initialize() {
		assert(InputManager::GetInstance() && InputManager::GetInstance()->_system &&
			"Keyboard::initialize -> The input manager has not been created...");
		OIS::InputManager * system = InputManager::GetInstance()->_system;
		// Obtenemos el dispositivo del teclado si hay alguno conectado.
		if(system->getNumberOfDevices(OIS::OISKeyboard) > 0) {
			_device = static_cast<OIS::Keyboard *>(system->createInputObject(OIS::OISKeyboard, true));
		}
		// Inicializamos el estado teclado que vamos a guardar en el objeto.
		for(int i = 0; i < CORE_KEYBOARD_MAX_KEYS; ++i) {
			_currentValue[i] = false;
			_previousValue[i] = false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Keyboard::release() {
		assert(InputManager::GetInstance() && InputManager::GetInstance()->_system &&
			"Keyboard::release -> The input manager has not been created...");
		OIS::InputManager * system = InputManager::GetInstance()->_system;
		// Destruimos el dispositivo del teclado de haber obtenido alguno.
		if(_device) {
			system->destroyInputObject(_device);
			_device = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Keyboard::update() {
		assert(_device && "Keyboard::update -> The device has not been created...");
		_device->capture();
		// Actualizamos el estado teclado que vamos a guardar en el objeto.
		for(int i = 0; i < CORE_KEYBOARD_MAX_KEYS; ++i) {
			_previousValue[i] = _currentValue[i];
			_currentValue[i] = _device->isKeyDown((OIS::KeyCode)i);
		}
	}
}
