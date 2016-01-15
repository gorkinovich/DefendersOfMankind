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

#ifndef __CORE_MOUSE_H__
#define __CORE_MOUSE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Input/MouseState.h"

//************************************************************************************************************
// OIS
//************************************************************************************************************

namespace OIS {
	class Mouse;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class InputManager;

	/**
	 * Esta clase representa el gestor del rat�n.
	 */
	class Mouse {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el dispositivo OIS para manejar el rat�n.
		 */
		inline OIS::Mouse * getOISMouse() const { return _device; }

		/**
		 * Obtiene si el dispositivo est� conectado al sistema.
		 */
		inline bool isConnected() const { return _device != 0; }

		/**
		 * Obtiene el estado actual.
		 */
		inline const MouseState & getState() const { return _state; }

		//----------------------------------------------------------------------------------------------------
		// M�todos est�ticos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static Mouse * GetInstance() {
			return _instance;
		}

		/**
		 * Obtiene si el dispositivo est� conectado al sistema.
		 */
		inline static bool IsConnected() {
			return _instance->isConnected();
		}

		/**
		 * Obtiene el estado actual.
		 */
		inline static const MouseState & GetState() {
			return _instance->_state;
		}

		/**
		 * Cambia la posici�n del rat�n.
		 * @param x La coordenada x.
		 * @param y La coordenada y.
		 */
		inline static void SetPosition(unsigned int x, unsigned int y) {
			_instance->setPosition(x, y);
		}

		/**
		 * Cambia los l�mites del rat�n.
		 * @param width El ancho de la ventana.
		 * @param height El alto de la ventana.
		 */
		inline static void SetWindowSize(unsigned int width, unsigned int height) {
			_instance->setWindowSize(width, height);
		}

		/**
		 * Reinicia el estado del rat�n.
		 */
		inline static void ResetState() {
			_instance->resetState();
		}

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Cambia la posici�n del rat�n.
		 * @param x La coordenada x.
		 * @param y La coordenada y.
		 */
		void setPosition(unsigned int x, unsigned int y);

		/**
		 * Cambia los l�mites del rat�n.
		 * @param width El ancho de la ventana.
		 * @param height El alto de la ventana.
		 */
		void setWindowSize(unsigned int width, unsigned int height);

		/**
		 * Reinicia el estado del rat�n.
		 */
		void resetState();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~Mouse() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static Mouse * _instance;

		/**
		 * El dispositivo OIS.
		 */
		OIS::Mouse * _device;

		/**
		 * El estado actual.
		 */
		MouseState _state;

		//----------------------------------------------------------------------------------------------------
		// M�todos
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
		 * Actualiza el estado actual del rat�n.
		 */
		inline void updateState();

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Mouse() : _device(0) {}

		friend class Core::InputManager;
	};
}

#endif
