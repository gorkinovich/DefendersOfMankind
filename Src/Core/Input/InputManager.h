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

#ifndef __CORE_INPUTMANAGER_H__
#define __CORE_INPUTMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <list>
#include <string>
#include <functional>

#include "Core/Input/IInputItem.h"
#include "Core/Input/Keys.h"
#include "Core/Input/MouseButtonElement.h"
#include "Core/Input/MouseAxisElement.h"
#include "Core/Input/GamePadButtonElement.h"
#include "Core/Input/GamePadAxisElement.h"

//************************************************************************************************************
// OIS
//************************************************************************************************************

namespace OIS {
	class InputManager;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Keyboard;
	class Mouse;
	class Joysticks;
	class GamePads;
	class InputListenersManager;
	class IKeyboardInputActionMethod;
	class IMouseButtonInputActionMethod;
	class IMouseAxisInputActionMethod;
	class IGamePadButtonInputActionMethod;
	class IGamePadAxisInputActionMethod;
	class KeyboardInputItem;
	class MouseButtonInputItem;
	class MouseAxisInputItem;
	class GamePadButtonInputItem;
	class GamePadAxisInputItem;

	/**
	 * Esta clase representa al gestor del motor de entrada.
	 */
	class InputManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el gestor OIS para manejar la entrada.
		 */
		inline OIS::InputManager * getOISInputManager() const { return _system; }

		/**
		 * Obtiene el gestor del teclado.
		 */
		inline Keyboard * getKeyboard() const { return _keyboard; }

		/**
		 * Obtiene el gestor del ratón.
		 */
		inline Mouse * getMouse() const { return _mouse; }

		/**
		 * Obtiene el gestor de los joysticks.
		 */
		inline Joysticks * getJoysticks() const { return _joysticks; }

		/**
		 * Obtiene el gestor de los gamepads.
		 */
		inline GamePads * getGamepads() const { return _gamepads; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static InputManager * GetInstance() {
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
		 * Añade una acción al gestor de entrada.
		 * @param key El valor de la tecla.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 */
		void addAction(KeyCode key, const std::string & name, IKeyboardInputActionMethod & method);

		/**
		 * Elimina una acción del gestor de entrada.
		 * @param key El valor de la tecla.
		 * @param name El nombre de la acción.
		 */
		void removeAction(KeyCode key, const std::string & name);

		/**
		 * Elimina todas las acciones de una categoría en el gestor de entrada.
		 * @param key El valor de la tecla.
		 */
		void removeAllActions(KeyCode key);

		/**
		 * Elimina una categoría de acciones en el gestor de entrada.
		 * @param key El valor de la tecla.
		 */
		void removeInputItem(KeyCode key);

		/**
		 * Añade una acción al gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 */
		void addAction(MouseButtonElement type, const std::string & name, IMouseButtonInputActionMethod & method);

		/**
		 * Elimina una acción del gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param name El nombre de la acción.
		 */
		void removeAction(MouseButtonElement type, const std::string & name);

		/**
		 * Elimina todas las acciones de una categoría en el gestor de entrada.
		 * @param type El tipo del elemento.
		 */
		void removeAllActions(MouseButtonElement type);

		/**
		 * Elimina una categoría de acciones en el gestor de entrada.
		 * @param type El tipo del elemento.
		 */
		void removeInputItem(MouseButtonElement type);

		/**
		 * Añade una acción al gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 */
		void addAction(MouseAxisElement type, const std::string & name, IMouseAxisInputActionMethod & method);

		/**
		 * Elimina una acción del gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param name El nombre de la acción.
		 */
		void removeAction(MouseAxisElement type, const std::string & name);

		/**
		 * Elimina todas las acciones de una categoría en el gestor de entrada.
		 * @param type El tipo del elemento.
		 */
		void removeAllActions(MouseAxisElement type);

		/**
		 * Elimina una categoría de acciones en el gestor de entrada.
		 * @param type El tipo del elemento.
		 */
		void removeInputItem(MouseAxisElement type);

		/**
		 * Añade una acción al gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 */
		void addAction(GamePadButtonElement type, unsigned short player, const std::string & name, IGamePadButtonInputActionMethod & method);

		/**
		 * Elimina una acción del gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 * @param name El nombre de la acción.
		 */
		void removeAction(GamePadButtonElement type, unsigned short player, const std::string & name);

		/**
		 * Elimina todas las acciones de una categoría en el gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 */
		void removeAllActions(GamePadButtonElement type, unsigned short player);

		/**
		 * Elimina una categoría de acciones en el gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 */
		void removeInputItem(GamePadButtonElement type, unsigned short player);

		/**
		 * Añade una acción al gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 */
		void addAction(GamePadAxisElement type, unsigned short player, const std::string & name, IGamePadAxisInputActionMethod & method);

		/**
		 * Elimina una acción del gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 * @param name El nombre de la acción.
		 */
		void removeAction(GamePadAxisElement type, unsigned short player, const std::string & name);

		/**
		 * Elimina todas las acciones de una categoría en el gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 */
		void removeAllActions(GamePadAxisElement type, unsigned short player);

		/**
		 * Elimina una categoría de acciones en el gestor de entrada.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 */
		void removeInputItem(GamePadAxisElement type, unsigned short player);

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~InputManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una lista de elementos de entrada de acción.
		 */
		typedef std::list<IInputItem *> InputItemList;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static InputManager * _instance;

		/**
		 * El gestor OIS de la entrada.
		 */
		OIS::InputManager * _system;

		/**
		 * El gestor del teclado.
		 */
		Keyboard * _keyboard;

		/**
		 * El gestor del ratón.
		 */
		Mouse * _mouse;

		/**
		 * El gestor de los joysticks.
		 */
		Joysticks * _joysticks;

		/**
		 * El gestor de los gamepads.
		 */
		GamePads * _gamepads;

		/**
		 * La lista de elementos de entrada de acción.
		 */
		InputItemList _inputItems;

		/**
		 * El gestor de los listeners asociados a la entrada.
		 */
		InputListenersManager * _listenersManager;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade una acción al gestor de entrada.
		 * @param victim La categoría del gestor de entrada.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 * @param create La función factoría.
		 */
		template<class TInputItem, class TMethod>
		inline void addAction(TInputItem * victim, const std::string & name, TMethod & method,
			std::tr1::function<TInputItem * ()> create);

		/**
		 * Elimina una acción del gestor de entrada.
		 * @param victim La categoría del gestor de entrada.
		 * @param name El nombre de la acción.
		 */
		template<class TInputItem>
		inline void removeAction(TInputItem * victim, const std::string & name);

		/**
		 * Elimina todas las acciones de una categoría en el gestor de entrada.
		 * @param victim La categoría del gestor de entrada.
		 */
		template<class TInputItem>
		inline void removeAllActions(TInputItem * victim);

		/**
		 * Elimina un elemento de entrada en base a una función de comprobación.
		 * @param test La función de comprobación.
		 */
		template<class TInputItem>
		inline void removeInputItem(std::tr1::function<bool (TInputItem *)> test);

		/**
		 * Busca un elemento de entrada en base a una función de comprobación.
		 * @param test La función de comprobación.
		 * @return Si no encuentra nada devuelve NULL, si encuentra algo devuelve el objeto.
		 */
		template<class TInputItem>
		inline TInputItem * findInputItem(std::tr1::function<bool (TInputItem *)> test);

		/**
		 * Busca un elemento de entrada del teclado.
		 * @param key El valor de la tecla.
		 * @return Si no encuentra nada devuelve NULL, si encuentra algo devuelve el objeto.
		 */
		KeyboardInputItem * findInputItem(KeyCode key);

		/**
		 * Busca un elemento de entrada de los botones del ratón.
		 * @param type El tipo del elemento.
		 * @return Si no encuentra nada devuelve NULL, si encuentra algo devuelve el objeto.
		 */
		MouseButtonInputItem * findInputItem(MouseButtonElement type);

		/**
		 * Busca un elemento de entrada de los ejes del ratón.
		 * @param type El tipo del elemento.
		 * @return Si no encuentra nada devuelve NULL, si encuentra algo devuelve el objeto.
		 */
		MouseAxisInputItem * findInputItem(MouseAxisElement type);

		/**
		 * Busca un elemento de entrada de los botones del mando.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 * @return Si no encuentra nada devuelve NULL, si encuentra algo devuelve el objeto.
		 */
		GamePadButtonInputItem * findInputItem(GamePadButtonElement type, unsigned short player);

		/**
		 * Busca un elemento de entrada de los ejes del mando.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 * @return Si no encuentra nada devuelve NULL, si encuentra algo devuelve el objeto.
		 */
		GamePadAxisInputItem * findInputItem(GamePadAxisElement type, unsigned short player);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		InputManager() : _system(0), _keyboard(0), _mouse(0), _joysticks(0), _gamepads(0), _listenersManager(0) {}

		friend class Core::Keyboard;
		friend class Core::Mouse;
		friend class Core::Joysticks;
		friend class Core::GamePads;
	};
}

#endif
