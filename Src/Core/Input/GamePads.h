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

#ifndef __CORE_GAMEPADS_H__
#define __CORE_GAMEPADS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>

#include "Core/Input/GamePadState.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class InputManager;
	class XboxPad;

	/**
	 * Esta clase representa el gestor de los mandos.
	 */
	class GamePads {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el estado actual.
		 */
		const GamePadState & getState(unsigned short player) const;

		/**
		 * Obtiene el número de mandos.
		 */
		inline unsigned int getNumOfDevices() const { return _states.size(); }

		//----------------------------------------------------------------------------------------------------
		// Métodos estáticos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static GamePads * GetInstance() {
			return _instance;
		}

		/**
		 * Obtiene el estado actual.
		 */
		inline static const GamePadState & GetState(unsigned short player) {
			return _instance->getState(player);
		}

		/**
		 * Obtiene el estado actual.
		 */
		inline static bool IsConnected(unsigned short player) {
			return _instance->getState(player).isConnected;
		}

		/**
		 * Comprueba qué mandos están conectados.
		 */
		inline static void CheckConnectedPads() {
			_instance->checkConnectedPads();
		}

		/**
		 * Envia a un mando una orden de vibración.
		 * @param left Velocidad del motor izquierdo.
		 * @param right Velocidad del motor derecho.
		 */
		inline static void Vibrate(unsigned short player, unsigned short left = 0, unsigned short right = 0) {
			_instance->vibrate(player, left, right);
		}

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba qué mandos están conectados.
		 */
		void checkConnectedPads();

		/**
		 * Envia a un mando una orden de vibración.
		 * @param left Velocidad del motor izquierdo.
		 * @param right Velocidad del motor derecho.
		 */
		void vibrate(unsigned short player, unsigned short left = 0, unsigned short right = 0);

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~GamePads() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un vector de dispositivos.
		 */
		typedef std::vector<XboxPad *> DeviceVector;

		/**
		 * Este tipo representa un vector de estados.
		 */
		typedef std::vector<GamePadState> StateVector;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static GamePads * _instance;

		/**
		 * El dispositivo XInput.
		 */
		DeviceVector _devices;

		/**
		 * El estado actual.
		 */
		StateVector _states;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el dispositivo.
		 */
		void initialize();

		/**
		 * Finaliza el dispositivo.
		 */
		void release();

		/**
		 * Actualiza el estado actual del dispositivo.
		 */
		void update();

		/**
		 * Actualiza el estado actual de un mando.
		 */
		inline void updateState(unsigned int index, XboxPad * device);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		GamePads() {}

		friend class Core::InputManager;
	};
}

#endif
