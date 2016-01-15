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

#ifndef __CORE_INPUTLISTENERSMANAGER_H__
#define __CORE_INPUTLISTENERSMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <vector>
#include <string>
#include <functional>

#include "Core/Input/Keys.h"
#include "Core/Input/MouseState.h"
#include "Core/Input/JoystickState.h"
#include "Core/Input/GamePadState.h"

//************************************************************************************************************
// Macros
//************************************************************************************************************

#define CreateKeyboardDelegate(fun, obj) std::tr1::bind(fun, obj, std::tr1::placeholders::_1)
#define CreateMouseDelegate(fun, obj) std::tr1::bind(fun, obj, std::tr1::placeholders::_1)
#define CreateGamePadDelegate(fun, obj) std::tr1::bind(fun, obj, std::tr1::placeholders::_1, std::tr1::placeholders::_2)

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa al gestor de los listeners asociados a la entrada.
	 */
	class InputListenersManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Tipo que representa un delegado para gestionar el evento del teclado.
		 */
		typedef std::tr1::function<bool (KeyCode)> KeyboardDelegate;

		/**
		 * Tipo que representa un delegado para gestionar el evento del ratón.
		 */
		typedef std::tr1::function<bool (const MouseState &)> MouseDelegate;

		/**
		 * Tipo que representa un delegado para gestionar el evento del gamepad.
		 */
		typedef std::tr1::function<bool (const GamePadState &, unsigned short)> GamePadDelegate;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static InputListenersManager * GetInstance() {
			return _instance;
		}

		/**
		 * Inicializa el gestor.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize();

		/**
		 * Finaliza el gestor.
		 */
		void release();

		/**
		 * Actualiza el estado del gestor.
		 */
		void update();

		/**
		 * Añade un delegado para el evento de tecla pulsada.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addKeyPressedDelegate(const void * obj, const KeyboardDelegate & method);

		/**
		 * Añade un delegado para el evento de tecla soltada.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addKeyReleasedDelegate(const void * obj, const KeyboardDelegate & method);

		/**
		 * Añade un delegado para el evento de mover el ratón.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addMouseAxisDelegate(const void * obj, const MouseDelegate & method);

		/**
		 * Añade un delegado para el evento de pulsar el ratón.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addMousePressedDelegate(const void * obj, const MouseDelegate & method);

		/**
		 * Añade un delegado para el evento de soltar el ratón.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addMouseReleasedDelegate(const void * obj, const MouseDelegate & method);

		/**
		 * Añade un delegado para el evento de mover el mando.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addGamePadAxisDelegate(const void * obj, const GamePadDelegate & method);

		/**
		 * Añade un delegado para el evento de pulsar el mando.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addGamePadPressedDelegate(const void * obj, const GamePadDelegate & method);

		/**
		 * Añade un delegado para el evento de soltar el mando.
		 * @param obj El objeto identificador del delegado.
		 * @param method El delegado que va a recibir los eventos.
		 */
		void addGamePadReleasedDelegate(const void * obj, const GamePadDelegate & method);

		/**
		 * Elimina un delegado para el evento de tecla pulsada.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeKeyPressedDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de tecla soltada.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeKeyReleasedDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de mover el ratón.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeMouseAxisDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de pulsar el ratón.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeMousePressedDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de soltar el ratón.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeMouseReleasedDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de mover el mando.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeGamePadAxisDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de pulsar el mando.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeGamePadPressedDelegate(const void * obj);

		/**
		 * Elimina un delegado para el evento de soltar el mando.
		 * @param obj El objeto identificador del delegado.
		 */
		void removeGamePadReleasedDelegate(const void * obj);

		/**
		 * Elimina todos los delegados para el evento de tecla pulsada.
		 */
		void removeAllKeyPressedDelegates();

		/**
		 * Elimina todos los delegados para el evento de tecla soltada.
		 */
		void removeAllKeyReleasedDelegates();

		/**
		 * Elimina todos los delegados para el evento de mover el ratón.
		 */
		void removeAllMouseAxisDelegates();

		/**
		 * Elimina todos los delegados para el evento de pulsar el ratón.
		 */
		void removeAllMousePressedDelegates();

		/**
		 * Elimina todos los delegados para el evento de soltar el ratón.
		 */
		void removeAllMouseReleasedDelegates();

		/**
		 * Elimina todos los delegados para el evento de mover el mando.
		 */
		void removeAllGamePadAxisDelegates();

		/**
		 * Elimina todos los delegados para el evento de pulsar el mando.
		 */
		void removeAllGamePadPressedDelegates();

		/**
		 * Elimina todos los delegados para el evento de soltar el mando.
		 */
		void removeAllGamePadReleasedDelegates();

		/**
		 * Elimina todos los delegados para eventos del teclado.
		 */
		void removeAllKeyDelegates();

		/**
		 * Elimina todos los delegados para eventos del ratón.
		 */
		void removeAllMouseDelegates();

		/**
		 * Elimina todos los delegados para eventos del mando.
		 */
		void removeAllGamePadDelegates();

		/**
		 * Elimina todos los delegados para eventos.
		 */
		void removeAllDelegates();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~InputListenersManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un vector de estados.
		 */
		typedef std::vector<GamePadState> GamePadStateVector;

		/**
		 * Tipo que representa una lista de delegados de eventos del teclado.
		 */
		typedef std::map<const void *, KeyboardDelegate> KeyboardDelegateTable;

		/**
		 * Tipo que representa una lista de delegados de eventos del ratón.
		 */
		typedef std::map<const void *, MouseDelegate> MouseDelegateTable;

		/**
		 * Tipo que representa una lista de delegados de eventos de un mando.
		 */
		typedef std::map<const void *, GamePadDelegate> GamePadDelegateTable;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static InputListenersManager * _instance;

		/**
		 * El estado previo del ratón.
		 */
		MouseState _previousMouseState;

		/**
		 * El estado previo del mando.
		 */
		GamePadStateVector _previousGamePadStates;

		/**
		 * La lista de delegados para el evento que se produce al pulsar una tecla.
		 */
		KeyboardDelegateTable _keyPressedDelegates;

		/**
		 * La lista de delegados para el evento que se produce al soltar una tecla.
		 */
		KeyboardDelegateTable _keyReleasedDelegates;

		/**
		 * La lista de delegados para el evento que se produce al mover el ratón.
		 */
		MouseDelegateTable _mouseAxisDelegates;

		/**
		 * La lista de delegados para el evento que se produce al pulsar un botón del ratón.
		 */
		MouseDelegateTable _mousePressedDelegates;

		/**
		 * La lista de delegados para el evento que se produce al pulsar un botón del ratón.
		 */
		MouseDelegateTable _mouseReleasedDelegates;

		/**
		 * La lista de delegados para el evento que se produce al mover un mando.
		 */
		GamePadDelegateTable _gamePadAxisDelegates;

		/**
		 * La lista de delegados para el evento que se produce al pulsar un botón de un mando.
		 */
		GamePadDelegateTable _gamePadPressedDelegates;

		/**
		 * La lista de delegados para el evento que se produce al pulsar un botón de un mando.
		 */
		GamePadDelegateTable _gamePadReleasedDelegates;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza el estado del gestor.
		 */
		inline void updateKeyboard();

		/**
		 * Actualiza el estado del gestor.
		 */
		inline void updateMouse();

		/**
		 * Actualiza el estado del gestor.
		 */
		inline void updateGamePads();

		//----------------------------------------------------------------------------------------------------
		// Constructore
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		InputListenersManager() {}
	};
}

#endif
