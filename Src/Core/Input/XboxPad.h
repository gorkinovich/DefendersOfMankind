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

#ifndef __CORE_XBOXPAD_H__
#define __CORE_XBOXPAD_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define XBOXPAD_MAX_PLAYERS 4

#define XBOXPAD_PLAYER1 0
#define XBOXPAD_PLAYER2 1
#define XBOXPAD_PLAYER3 2
#define XBOXPAD_PLAYER4 3

#define XBOXPAD_MIN_VIBRATION 0
#define XBOXPAD_MAX_VIBRATION 65535

#define XBOXPAD_MIN_TRIGGER 0
#define XBOXPAD_MAX_TRIGGER 255

#define XBOXPAD_MIN_THUMB -32768
#define XBOXPAD_MAX_THUMB 32767

#define XBOXPAD_LEFT_THUMB_DEADZONE  7849
#define XBOXPAD_RIGHT_THUMB_DEADZONE 8689
#define XBOXPAD_TRIGGER_THRESHOLD    30

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un mando de la xbox.
	 */
	class XboxPad {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el estado actual.
		 */
		inline const XINPUT_STATE & getState() const {
			return _state;
		}

		/**
		 * Obtiene el número de jugador.
		 */
		inline unsigned short getPlayer() const {
			return _player;
		}

		/**
		 * Obtiene si el mando está conectado o no.
		 */
		inline bool isConnected() {
			// Se limpia la estructura con el estado actual.
			ZeroMemory(&_state, sizeof(XINPUT_STATE));
			// Y luego se obtiene el estado del jugador asignado.
			DWORD result = XInputGetState(_player, &_state);
			return (result == ERROR_SUCCESS);
		}

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza el estado actual del dispositivo.
		 */
		inline void update() {
			// Se limpia la estructura con el estado actual.
			ZeroMemory(&_state, sizeof(XINPUT_STATE));
			// Y luego se obtiene el estado del jugador asignado.
			XInputGetState(_player, &_state);
		}

		/**
		 * Envia al mando una orden de vibración.
		 * @param left Velocidad del motor izquierdo.
		 * @param right Velocidad del motor derecho.
		 */
		inline void vibrate(WORD left = 0, WORD right = 0) {
			// Primero, creamos el mensaje de vibración.
			XINPUT_VIBRATION message;
			ZeroMemory(&message, sizeof(XINPUT_VIBRATION));
			// Segundo, inicializamos el mensaje de vibración.
			message.wLeftMotorSpeed = left;
			message.wRightMotorSpeed = right;
			// Y finalmente, enviamos el mensaje.
			XInputSetState(_player, &message);
		}

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param player El número del jugador (1..4)
		 */
		XboxPad(unsigned short player = XBOXPAD_PLAYER1) : _player(player) {
			ZeroMemory(&_state, sizeof(XINPUT_STATE));
		}

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		XboxPad(const XboxPad & obj) {
			_state = obj._state;
			_player = obj._player;
		}

		/**
		 * Destructor del objeto.
		 */
		virtual ~XboxPad() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El estado actual.
		 */
		XINPUT_STATE _state;

		/**
		 * El número de jugador.
		 */
		unsigned short _player;
	};
}

#endif
