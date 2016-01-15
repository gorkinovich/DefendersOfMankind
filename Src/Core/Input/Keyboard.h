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

#ifndef __CORE_KEYBOARD_H__
#define __CORE_KEYBOARD_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Input/Keys.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define CORE_KEYBOARD_MAX_KEYS 256

//************************************************************************************************************
// OIS
//************************************************************************************************************

namespace OIS {
	class Keyboard;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class InputManager;

	/**
	 * Esta clase representa el gestor del teclado.
	 */
	class Keyboard {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el dispositivo OIS para manejar el teclado.
		 */
		inline OIS::Keyboard * getOISKeyboard() const { return _device; }

		/**
		 * Obtiene si el dispositivo está conectado al sistema.
		 */
		inline bool isConnected() const { return _device != 0; }

		//----------------------------------------------------------------------------------------------------
		// Métodos estáticos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static Keyboard * GetInstance() {
			return _instance;
		}

		/**
		 * Obtiene si el dispositivo está conectado al sistema.
		 */
		inline static bool IsConnected() {
			return _instance->isConnected();
		}

		/**
		 * Obtiene si una tecla está pulsada.
		 */
		inline static bool IsKeyDown(KeyCode key) {
			return _instance->isKeyDown(key);
		}

		/**
		 * Obtiene si una tecla está sin pulsar.
		 */
		inline static bool IsKeyUp(KeyCode key) {
			return _instance->isKeyUp(key);
		}

		/**
		 * Obtiene si una tecla modificadora está pulsada.
		 */
		inline static bool IsModifierDown(ModifierCode modifier) {
			return _instance->isModifierDown(modifier);
		}

		/**
		 * Obtiene si una tecla modificadora está sin pulsar.
		 */
		inline static bool IsModifierUp(ModifierCode modifier) {
			return _instance->isModifierUp(modifier);
		}

		/**
		 * Obtiene si una tecla ha sido pulsada.
		 */
		inline static bool IsKeyPressed(KeyCode key) {
			return _instance->isKeyPressed(key);
		}

		/**
		 * Obtiene si una tecla ha sido liberada.
		 */
		inline static bool IsKeyReleased(KeyCode key) {
			return _instance->isKeyReleased(key);
		}

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene si una tecla está pulsada.
		 */
		inline bool isKeyDown(KeyCode key) const {
			return _currentValue[key];
		}

		/**
		 * Obtiene si una tecla está sin pulsar.
		 */
		inline bool isKeyUp(KeyCode key) const {
			return !_currentValue[key];
		}

		/**
		 * Obtiene si una tecla modificadora está pulsada.
		 */
		bool isModifierDown(ModifierCode modifier) const;

		/**
		 * Obtiene si una tecla modificadora está sin pulsar.
		 */
		bool isModifierUp(ModifierCode modifier) const;

		/**
		 * Obtiene si una tecla ha sido pulsada.
		 */
		inline bool isKeyPressed(KeyCode key) const {
			return _currentValue[key] && !_previousValue[key];
		}

		/**
		 * Obtiene si una tecla ha sido liberada.
		 */
		inline bool isKeyReleased(KeyCode key) const {
			return !_currentValue[key] && _previousValue[key];
		}

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~Keyboard() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static Keyboard * _instance;

		/**
		 * El dispositivo OIS.
		 */
		OIS::Keyboard * _device;

		/**
		 * El valor actual del teclado.
		 */
		bool _currentValue[CORE_KEYBOARD_MAX_KEYS];

		/**
		 * El valor previo del teclado.
		 */
		bool _previousValue[CORE_KEYBOARD_MAX_KEYS];

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

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Keyboard() : _device(0) {}

		friend class Core::InputManager;
	};
}

#endif
