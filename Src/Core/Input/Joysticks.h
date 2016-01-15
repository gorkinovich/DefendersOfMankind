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

#ifndef __CORE_JOYSTICKS_H__
#define __CORE_JOYSTICKS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>

#include "Core/Input/JoystickState.h"

//************************************************************************************************************
// OIS
//************************************************************************************************************

namespace OIS {
	class JoyStick;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class InputManager;

	/**
	 * Esta clase representa el gestor de los mandos.
	 */
	class Joysticks {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el estado actual.
		 */
		const JoystickState & getState(unsigned int device) const;

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
		inline static Joysticks * GetInstance() {
			return _instance;
		}

		/**
		 * Obtiene el estado actual.
		 */
		inline static const JoystickState & GetState(unsigned int device) {
			return _instance->getState(device);
		}

		/**
		 * Obtiene el número de mandos.
		 */
		inline static unsigned int GetNumOfDevices() {
			return _instance->_states.size();
		}

		/**
		 * Reinicia el estado de los joysticks.
		 */
		inline static void ResetStates() {
			_instance->resetStates();
		}

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Reinicia el estado de los joysticks.
		 */
		void resetStates();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~Joysticks() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un vector de dispositivos.
		 */
		typedef std::vector<OIS::JoyStick *> DeviceVector;

		/**
		 * Este tipo representa un vector de estados.
		 */
		typedef std::vector<JoystickState> StateVector;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static Joysticks * _instance;

		/**
		 * El dispositivo OIS.
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
		 * Actualiza el estado actual de un joystick.
		 */
		inline void updateState(unsigned int index, OIS::JoyStick * device);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Joysticks() {}

		friend class Core::InputManager;
	};
}

#endif
