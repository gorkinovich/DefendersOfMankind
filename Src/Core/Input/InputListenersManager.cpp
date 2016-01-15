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

#include <algorithm>

#include "Core/Input/InputListenersManager.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/Joysticks.h"
#include "Core/Input/GamePads.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	InputListenersManager * InputListenersManager::_instance = new InputListenersManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InputListenersManager::initialize() {
		// Capturamos el estado inicial del ratón.
		_previousMouseState = Mouse::GetState();

		// Capturamos el estado inicial de los mandos, estén o no conectados.
		_previousGamePadStates.resize(PAD_MAX_PLAYERS);
		for(unsigned short i = PAD_PLAYER1; i < PAD_MAX_PLAYERS; ++i) {
			_previousGamePadStates[i] = GamePads::GetState(i);
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::release() {
		// Borramos todos los delegados asociados a la entrada.
		removeAllDelegates();

		// Borramos los estados guardados de los mandos.
		_previousGamePadStates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::update() {
		if(Keyboard::IsConnected()) updateKeyboard();
		if(Mouse::IsConnected()) updateMouse();
		updateGamePads();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addKeyPressedDelegate(const void * obj, const KeyboardDelegate & method) {
		if(obj) {
			_keyPressedDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addKeyReleasedDelegate(const void * obj, const KeyboardDelegate & method) {
		if(obj) {
			_keyReleasedDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addMouseAxisDelegate(const void * obj, const MouseDelegate & method) {
		if(obj) {
			_mouseAxisDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addMousePressedDelegate(const void * obj, const MouseDelegate & method) {
		if(obj) {
			_mousePressedDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addMouseReleasedDelegate(const void * obj, const MouseDelegate & method) {
		if(obj) {
			_mouseReleasedDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addGamePadAxisDelegate(const void * obj, const GamePadDelegate & method) {
		if(obj) {
			_gamePadAxisDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addGamePadPressedDelegate(const void * obj, const GamePadDelegate & method) {
		if(obj) {
			_gamePadPressedDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::addGamePadReleasedDelegate(const void * obj, const GamePadDelegate & method) {
		if(obj) {
			_gamePadReleasedDelegates[obj] = method;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeKeyPressedDelegate(const void * obj) {
		KeyboardDelegateTable::iterator victim = _keyPressedDelegates.find(obj);
		if(victim != _keyPressedDelegates.end()) {
			_keyPressedDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeKeyReleasedDelegate(const void * obj) {
		KeyboardDelegateTable::iterator victim = _keyReleasedDelegates.find(obj);
		if(victim != _keyReleasedDelegates.end()) {
			_keyReleasedDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeMouseAxisDelegate(const void * obj) {
		MouseDelegateTable::iterator victim = _mouseAxisDelegates.find(obj);
		if(victim != _mouseAxisDelegates.end()) {
			_mouseAxisDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeMousePressedDelegate(const void * obj) {
		MouseDelegateTable::iterator victim = _mousePressedDelegates.find(obj);
		if(victim != _mousePressedDelegates.end()) {
			_mousePressedDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeMouseReleasedDelegate(const void * obj) {
		MouseDelegateTable::iterator victim = _mouseReleasedDelegates.find(obj);
		if(victim != _mouseReleasedDelegates.end()) {
			_mouseReleasedDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeGamePadAxisDelegate(const void * obj) {
		GamePadDelegateTable::iterator victim = _gamePadAxisDelegates.find(obj);
		if(victim != _gamePadAxisDelegates.end()) {
			_gamePadAxisDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeGamePadPressedDelegate(const void * obj) {
		GamePadDelegateTable::iterator victim = _gamePadPressedDelegates.find(obj);
		if(victim != _gamePadPressedDelegates.end()) {
			_gamePadPressedDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeGamePadReleasedDelegate(const void * obj) {
		GamePadDelegateTable::iterator victim = _gamePadReleasedDelegates.find(obj);
		if(victim != _gamePadReleasedDelegates.end()) {
			_gamePadReleasedDelegates.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllKeyPressedDelegates() {
		_keyPressedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllKeyReleasedDelegates() {
		_keyReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllMouseAxisDelegates() {
		_mouseAxisDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllMousePressedDelegates() {
		_mousePressedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllMouseReleasedDelegates() {
		_mouseReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllGamePadAxisDelegates() {
		_gamePadAxisDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllGamePadPressedDelegates() {
		_gamePadPressedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllGamePadReleasedDelegates() {
		_gamePadReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllKeyDelegates() {
		_keyPressedDelegates.clear();
		_keyReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllMouseDelegates() {
		_mouseAxisDelegates.clear();
		_mousePressedDelegates.clear();
		_mouseReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllGamePadDelegates() {
		_gamePadAxisDelegates.clear();
		_gamePadPressedDelegates.clear();
		_gamePadReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::removeAllDelegates() {
		_keyPressedDelegates.clear();
		_keyReleasedDelegates.clear();
		_mouseAxisDelegates.clear();
		_mousePressedDelegates.clear();
		_mouseReleasedDelegates.clear();
		_gamePadAxisDelegates.clear();
		_gamePadPressedDelegates.clear();
		_gamePadReleasedDelegates.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::updateKeyboard() {
		if(_keyPressedDelegates.size() > 0 || _keyReleasedDelegates.size() > 0) {
			// Se comprueba cualquier cambio en las teclas.
			for(int i = 0; i < CORE_KEYBOARD_MAX_KEYS; ++i) {
				KeyCode key = (KeyCode)i;
				if(Keyboard::IsKeyPressed(key)) {
					KeyboardDelegateTable::iterator j = _keyPressedDelegates.begin();
					KeyboardDelegateTable::iterator end = _keyPressedDelegates.end();
					for(; j != end; ++j) {
						if(j->second(key)) break;
					}
				} else if(Keyboard::IsKeyReleased(key)) {
					KeyboardDelegateTable::iterator j = _keyReleasedDelegates.begin();
					KeyboardDelegateTable::iterator end = _keyReleasedDelegates.end();
					for(; j != end; ++j) {
						if(j->second(key)) break;
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::updateMouse() {
		if(_mouseAxisDelegates.size() > 0 || _mousePressedDelegates.size() > 0 || _mouseReleasedDelegates.size() > 0) {
			// Se comprueba cualquier cambio en los ejes o los botones.
			const MouseState & current = Mouse::GetState();
			bool changed = false;
			if(_mouseAxisDelegates.size() > 0 && (current.x != _previousMouseState.x ||
				current.y != _previousMouseState.y || current.scrollWheel != _previousMouseState.scrollWheel)) {
				// Ante cualquier cambio en los ejes mandamos la notificación
				// a todos los delegados registrados dentro del gestor.
				MouseDelegateTable::iterator j = _mouseAxisDelegates.begin();
				MouseDelegateTable::iterator end = _mouseAxisDelegates.end();
				for(; j != end; ++j) {
					if(j->second(current)) break;
				}
				changed = true;
			}
			if(_mousePressedDelegates.size() > 0 && ((current.left && !_previousMouseState.left) ||
				(current.right && !_previousMouseState.right) || (current.middle && !_previousMouseState.middle))) {
				// Ante cualquier cambio en los botones mandamos la notificación
				// a todos los delegados registrados dentro del gestor.
				MouseDelegateTable::iterator j = _mousePressedDelegates.begin();
				MouseDelegateTable::iterator end = _mousePressedDelegates.end();
				for(; j != end; ++j) {
					if(j->second(current)) break;
				}
				changed = true;
			}
			if(_mouseReleasedDelegates.size() > 0 && ((!current.left && _previousMouseState.left) ||
				(!current.right && _previousMouseState.right) || (!current.middle && _previousMouseState.middle))) {
				// Ante cualquier cambio en los botones mandamos la notificación
				// a todos los delegados registrados dentro del gestor.
				MouseDelegateTable::iterator j = _mouseReleasedDelegates.begin();
				MouseDelegateTable::iterator end = _mouseReleasedDelegates.end();
				for(; j != end; ++j) {
					if(j->second(current)) break;
				}
				changed = true;
			}
			// Si ha habido algún cambio guardamos el estado actual.
			if(changed) {
				_previousMouseState = current;
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InputListenersManager::updateGamePads() {
		// Comprobamos por cada posible mando si ha habido algún cambio.
		for(unsigned short i = PAD_PLAYER1; i < PAD_MAX_PLAYERS; ++i) {
			const GamePadState & current = GamePads::GetState(i);
			// Si está conectado el mando, se comprueba cualquier cambio en los ejes o los botones.
			if(current.isConnected) {
				bool changed = false;
				if(_gamePadAxisDelegates.size() > 0 &&
					(current.leftStick.x != _previousGamePadStates[i].leftStick.x ||
					current.leftStick.y != _previousGamePadStates[i].leftStick.y ||
					current.rightStick.x != _previousGamePadStates[i].rightStick.x ||
					current.rightStick.y != _previousGamePadStates[i].rightStick.y ||
					current.leftTrigger != _previousGamePadStates[i].leftTrigger ||
					current.rightTrigger != _previousGamePadStates[i].rightTrigger)) {
					// Ante cualquier cambio en los ejes (sticks y triggers) mandamos la notificación
					// a todos los delegados registrados dentro del gestor.
					GamePadDelegateTable::iterator j = _gamePadAxisDelegates.begin();
					GamePadDelegateTable::iterator end = _gamePadAxisDelegates.end();
					for(; j != end; ++j) {
						if(j->second(current, i)) break;
					}
					changed = true;
				}
				if(_gamePadPressedDelegates.size() > 0 &&
					((current.buttons.a && !_previousGamePadStates[i].buttons.a) ||
					(current.buttons.b && !_previousGamePadStates[i].buttons.b) ||
					(current.buttons.x && !_previousGamePadStates[i].buttons.x) ||
					(current.buttons.y && !_previousGamePadStates[i].buttons.y) ||
					(current.buttons.leftShoulder && !_previousGamePadStates[i].buttons.leftShoulder) ||
					(current.buttons.rightShoulder && !_previousGamePadStates[i].buttons.rightShoulder) ||
					(current.buttons.back && !_previousGamePadStates[i].buttons.back) ||
					(current.buttons.start && !_previousGamePadStates[i].buttons.start) ||
					(current.buttons.leftStick && !_previousGamePadStates[i].buttons.leftStick) ||
					(current.buttons.rightStick && !_previousGamePadStates[i].buttons.rightStick) ||
					(current.dpad.up && !_previousGamePadStates[i].dpad.up) ||
					(current.dpad.down && !_previousGamePadStates[i].dpad.down) ||
					(current.dpad.left && !_previousGamePadStates[i].dpad.left) ||
					(current.dpad.right && !_previousGamePadStates[i].dpad.right))) {
					// Ante cualquier cambio en los botones mandamos la notificación
					// a todos los delegados registrados dentro del gestor.
					GamePadDelegateTable::iterator j = _gamePadPressedDelegates.begin();
					GamePadDelegateTable::iterator end = _gamePadPressedDelegates.end();
					for(; j != end; ++j) {
						if(j->second(current, i)) break;
					}
					changed = true;
				}
				if(_gamePadReleasedDelegates.size() > 0 &&
					((!current.buttons.a && _previousGamePadStates[i].buttons.a) ||
					(!current.buttons.b && _previousGamePadStates[i].buttons.b) ||
					(!current.buttons.x && _previousGamePadStates[i].buttons.x) ||
					(!current.buttons.y && _previousGamePadStates[i].buttons.y) ||
					(!current.buttons.leftShoulder && _previousGamePadStates[i].buttons.leftShoulder) ||
					(!current.buttons.rightShoulder && _previousGamePadStates[i].buttons.rightShoulder) ||
					(!current.buttons.back && _previousGamePadStates[i].buttons.back) ||
					(!current.buttons.start && _previousGamePadStates[i].buttons.start) ||
					(!current.buttons.leftStick && _previousGamePadStates[i].buttons.leftStick) ||
					(!current.buttons.rightStick && _previousGamePadStates[i].buttons.rightStick) ||
					(!current.dpad.up && _previousGamePadStates[i].dpad.up) ||
					(!current.dpad.down && _previousGamePadStates[i].dpad.down) ||
					(!current.dpad.left && _previousGamePadStates[i].dpad.left) ||
					(!current.dpad.right && _previousGamePadStates[i].dpad.right))) {
					// Ante cualquier cambio en los botones mandamos la notificación
					// a todos los delegados registrados dentro del gestor.
					GamePadDelegateTable::iterator j = _gamePadReleasedDelegates.begin();
					GamePadDelegateTable::iterator end = _gamePadReleasedDelegates.end();
					for(; j != end; ++j) {
						if(j->second(current, i)) break;
					}
					changed = true;
				}
				// Si ha habido algún cambio guardamos el estado actual.
				if(changed) {
					_previousGamePadStates[i] = current;
				}
			}
		}
	}
}
