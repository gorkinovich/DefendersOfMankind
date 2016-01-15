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

#include "Core/Input/GamePads.h"
#include "Core/Input/XboxPad.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	GamePads * GamePads::_instance = new GamePads();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	const GamePadState & GamePads::getState(unsigned short player) const {
		assert(_states.size() > 0 && _states.size() > player &&
			"GamePads::getState -> The devices have not been created...");
		return _states[player];
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void GamePads::checkConnectedPads() {
		unsigned int index = 0;
		// Recorremos todos los posibles dispositivos que podrían estar conectados al sistema.
		DeviceVector::iterator end = _devices.end();
		for(DeviceVector::iterator i = _devices.begin(); i != end; ++i, ++index) {
			// Comprobamos que sea un mando que previamente no estuviera conectado.
			if(!_states[index].isConnected) {
				// Preguntamos al driver si el mando está conectado.
				_states[index].isConnected = (*i)->isConnected();
				// Y de estar conectado, actualizamos su estado interno y el estado del objeto.
				if(_states[index].isConnected) {
					(*i)->update();
					updateState(index, *i);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePads::vibrate(unsigned short player, unsigned short left, unsigned short right) {
		assert(_devices.size() > 0 && _devices.size() > player &&
			"GamePads::vibrate -> The devices have not been created...");
		_devices[player]->vibrate(left, right);
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePads::initialize() {
		_devices.resize(XBOXPAD_MAX_PLAYERS);
		_states.resize(XBOXPAD_MAX_PLAYERS);
		for(unsigned short i = XBOXPAD_PLAYER1; i < XBOXPAD_MAX_PLAYERS; ++i) {
			_devices[i] = new XboxPad(i);
			_states[i].isConnected = _devices[i]->isConnected();
			// Inicializar los sticks y triggers.
			_states[i].leftStick.x = 0;
			_states[i].leftStick.y = 0;
			_states[i].rightStick.x = 0;
			_states[i].rightStick.y = 0;
			_states[i].leftTrigger = 0;
			_states[i].rightTrigger = 0;
			// Inicializar el pad digital.
			_states[i].dpad.up = false;
			_states[i].dpad.down = false;
			_states[i].dpad.left = false;
			_states[i].dpad.right = false;
			// Inicializar los botones.
			_states[i].buttons.a = false;
			_states[i].buttons.b = false;
			_states[i].buttons.x = false;
			_states[i].buttons.y = false;
			_states[i].buttons.leftShoulder = false;
			_states[i].buttons.rightShoulder = false;
			_states[i].buttons.leftStick = false;
			_states[i].buttons.rightStick = false;
			_states[i].buttons.back = false;
			_states[i].buttons.start = false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePads::release() {
		// Destruimos los dispositivos de tipo mando que tenemos creados dentro del objeto.
		if(_devices.size() > 0) {
			DeviceVector::iterator end = _devices.end();
			for(DeviceVector::iterator i = _devices.begin(); i != end; ++i) {
				XboxPad * victim = *i;
				delete victim;
			}
			_devices.clear();
			_states.clear();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePads::update() {
		unsigned int index = 0;
		// Por cada mando conectado lo que haremos es actualizar su estado interno y el estado del objeto.
		DeviceVector::iterator end = _devices.end();
		for(DeviceVector::iterator i = _devices.begin(); i != end; ++i, ++index) {
			if(_states[index].isConnected) {
				(*i)->update();
				updateState(index, *i);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePads::updateState(unsigned int index, XboxPad * device) {
		const XINPUT_STATE & xstate = device->getState();
		GamePadState & victim = _states[index];
		// Actualizando el stick izquierdo.
		victim.leftStick.x = (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < xstate.Gamepad.sThumbLX &&
			xstate.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? 0 : xstate.Gamepad.sThumbLX;
		victim.leftStick.y = (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < xstate.Gamepad.sThumbLY &&
			xstate.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? 0 : xstate.Gamepad.sThumbLY;
		// Actualizando el stick derecho.
		victim.rightStick.x = (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < xstate.Gamepad.sThumbRX &&
			xstate.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? 0 : xstate.Gamepad.sThumbRX;
		victim.rightStick.y = (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < xstate.Gamepad.sThumbRY &&
			xstate.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? 0 : xstate.Gamepad.sThumbRY;
		// Actualizando los triggers.
		victim.leftTrigger = (xstate.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 0 : xstate.Gamepad.bLeftTrigger;
		victim.rightTrigger = (xstate.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 0 : xstate.Gamepad.bRightTrigger;
		// Actualizando el pad digital.
		victim.dpad.up = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
		victim.dpad.down = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
		victim.dpad.left = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
		victim.dpad.right = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
		// Actualizando los botones.
		victim.buttons.a = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
		victim.buttons.b = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
		victim.buttons.x = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
		victim.buttons.y = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
		victim.buttons.leftShoulder = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
		victim.buttons.rightShoulder = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
		victim.buttons.leftStick = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
		victim.buttons.rightStick = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
		victim.buttons.back = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
		victim.buttons.start = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
	}
}
