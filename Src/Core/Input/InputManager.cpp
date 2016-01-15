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
#include <sstream>
#include <OISInputManager.h>

#include "Core/Input/InputManager.h"
#include "Core/Input/IInputItem.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Input/Joysticks.h"
#include "Core/Input/GamePads.h"
#include "Core/Input/InputListenersManager.h"
#include "Core/Input/KeyboardInputItem.h"
#include "Core/Input/MouseButtonInputItem.h"
#include "Core/Input/MouseAxisInputItem.h"
#include "Core/Input/GamePadButtonInputItem.h"
#include "Core/Input/GamePadAxisInputItem.h"
#include "Core/Graphics/GraphicsManager.h"

using namespace std::tr1::placeholders;

//************************************************************************************************************
// Constantes
//************************************************************************************************************

/**
 * Si se define la siguiente directiva, en modo ventana el juego no tomará el ratón y el teclado como
 * algo de uso exclusivo, sino que se seguirá viendo el del SO y se podrá usar en otras ventanas.
 */
//#define NON_EXCLUSIVE_MODE_IN_WINDOW_MODE

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones auxiliares (que feliz sería un mundo con expresiones lambda, como el de C++0x, jej...)
	//********************************************************************************************************

	bool testKeyboardInputItem(KeyboardInputItem * victim, KeyCode key) {
		return victim->getKey() == key;
	}

	//--------------------------------------------------------------------------------------------------------

	bool testMouseButtonInputItem(MouseButtonInputItem * victim, MouseButtonElement type) {
		return victim->getType() == type;
	}

	//--------------------------------------------------------------------------------------------------------

	bool testMouseAxisInputItem(MouseAxisInputItem * victim, MouseAxisElement type) {
		return victim->getType() == type;
	}

	//--------------------------------------------------------------------------------------------------------

	bool testGamePadButtonInputItem(GamePadButtonInputItem * victim, GamePadButtonElement type, unsigned short player) {
		return victim->getType() == type && victim->getPlayer() == player;
	}

	//--------------------------------------------------------------------------------------------------------

	bool testGamePadAxisInputItem(GamePadAxisInputItem * victim, GamePadAxisElement type, unsigned short player) {
		return victim->getType() == type && victim->getPlayer() == player;
	}

	//--------------------------------------------------------------------------------------------------------

	KeyboardInputItem * CreateKeyboardInputItem(KeyCode key) {
		return new KeyboardInputItem(key);
	}

	//--------------------------------------------------------------------------------------------------------

	MouseButtonInputItem * CreateMouseButtonInputItem(MouseButtonElement type) {
		return new MouseButtonInputItem(type);
	}

	//--------------------------------------------------------------------------------------------------------

	MouseAxisInputItem * CreateMouseAxisInputItem(MouseAxisElement type) {
		return new MouseAxisInputItem(type);
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadButtonInputItem * CreateGamePadButtonInputItem(GamePadButtonElement type, unsigned short player) {
		return new GamePadButtonInputItem(type, player);
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadAxisInputItem * CreateGamePadAxisInputItem(GamePadAxisElement type, unsigned short player) {
		return new GamePadAxisInputItem(type, player);
	}

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	InputManager * InputManager::_instance = new InputManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InputManager::initialize() {
		// Obtenemos las instancias de los dispositivos de entrada.
		_keyboard = Keyboard::GetInstance();
		_mouse = Mouse::GetInstance();
		_joysticks = Joysticks::GetInstance();
		_gamepads = GamePads::GetInstance();
		_listenersManager = InputListenersManager::GetInstance();

		// Cogemos las dimensiones de la ventana, para poder saber donde actua el ratón.
		unsigned int width, height;
		GraphicsManager::GetInstance()->getWindowSize(width, height);
		if(width == 0 || height == 0) return false;

		// También cogemos el manejador de la ventana para la configuración de la entrada.
		unsigned int windowHandler = GraphicsManager::GetInstance()->getWindowHandle();
		if(!windowHandler) return false;

		// Preparamos la lista de parámetros para inicializar el sistema de entrada.
		OIS::ParamList paramList;
		std::ostringstream wndHndStr;
		wndHndStr << windowHandler;
		paramList.insert(std::make_pair(std::string("WINDOW"), wndHndStr.str()));

#if defined NON_EXCLUSIVE_MODE_IN_WINDOW_MODE
		// De estar en modo ventana podría darse el caso de que no querramos que el ratón y el teclado
		// sean exclusivos de nuestra aplicación, dejando a las demás que los puedan usar.
		if(!GraphicsManager::GetInstance()->isFullScreen()) {
#if defined OIS_WIN32_PLATFORM
			paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
			paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
			paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
			paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
			paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
			paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
		}
#endif

		// Creamos el sistema gestor OIS de la entrada.
		try {
			_system = OIS::InputManager::createInputSystem(paramList);
		} catch(...) {
			return false;
		}

		// Inicializamos los dispositivos de entrada.
		_keyboard->initialize();
		_mouse->initialize();
		_joysticks->initialize();
		_gamepads->initialize();

		// Actualizamos los límites de la ventana, para limitar el movimiento del ratón.
		GraphicsManager::GetInstance()->updateWindowSize(width, height);

		// Finalmente inicializamos el gestor de los listeners asociados a la entrada.
		if(!_listenersManager->initialize()) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::release() {
		// Primero, liberamos el gestor de los listeners asociados a la entrada.
		_listenersManager->release();

		// Segundo, se borra la lista de elementos de entrada.
		InputItemList::iterator end = _inputItems.end();
		for(InputItemList::iterator i = _inputItems.begin(); i != end; ++i) {
			IInputItem * victim = *i;
			delete victim;
		}
		_inputItems.clear();

		// Tercero, se libera los dispositivos de entrada.
		_keyboard->release();
		_mouse->release();
		_joysticks->release();
		_gamepads->release();

		// Cuarto, eliminamos el gestor OIS de la entrada.
		if(_system) {
			_system->destroyInputSystem(_system);
			_system = 0;
		}

		// Finalmente quitamos las referencias a los dispositivos y demás gestores.
		_keyboard = 0;
		_mouse = 0;
		_joysticks = 0;
		_gamepads = 0;
		_listenersManager = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::update() {
		// Primero, se actualizan los dispositivos de entrada.
		if(_keyboard->isConnected()) _keyboard->update();
		if(_mouse->isConnected()) _mouse->update();
		_joysticks->update();
		_gamepads->update();

		// Y luego se actualizan las acciones asociadas a elementos de entrada.
		InputItemList::iterator end = _inputItems.end();
		for(InputItemList::iterator i = _inputItems.begin(); i != end; ++i) {
			(*i)->update();
		}

		// Por último, actualizamos el gestor de listeners asociados a la entrada.
		_listenersManager->update();
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::addAction(KeyCode key, const std::string & name, IKeyboardInputActionMethod & method) {
		addAction<KeyboardInputItem, IKeyboardInputActionMethod>(findInputItem(key),
			name, method, std::tr1::bind(CreateKeyboardInputItem, key));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAction(KeyCode key, const std::string & name) {
		removeAction<KeyboardInputItem>(findInputItem(key), name);
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAllActions(KeyCode key) {
		removeAllActions<KeyboardInputItem>(findInputItem(key));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeInputItem(KeyCode key) {
		removeInputItem<KeyboardInputItem>(std::tr1::bind(testKeyboardInputItem, _1, key));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::addAction(MouseButtonElement type, const std::string & name, IMouseButtonInputActionMethod & method) {
		addAction<MouseButtonInputItem, IMouseButtonInputActionMethod>(findInputItem(type),
			name, method, std::tr1::bind(CreateMouseButtonInputItem, type));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAction(MouseButtonElement type, const std::string & name) {
		removeAction<MouseButtonInputItem>(findInputItem(type), name);
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAllActions(MouseButtonElement type) {
		removeAllActions<MouseButtonInputItem>(findInputItem(type));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeInputItem(MouseButtonElement type) {
		removeInputItem<MouseButtonInputItem>(std::tr1::bind(testMouseButtonInputItem, _1, type));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::addAction(MouseAxisElement type, const std::string & name, IMouseAxisInputActionMethod & method) {
		addAction<MouseAxisInputItem, IMouseAxisInputActionMethod>(findInputItem(type),
			name, method, std::tr1::bind(CreateMouseAxisInputItem, type));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAction(MouseAxisElement type, const std::string & name) {
		removeAction<MouseAxisInputItem>(findInputItem(type), name);
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAllActions(MouseAxisElement type) {
		removeAllActions<MouseAxisInputItem>(findInputItem(type));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeInputItem(MouseAxisElement type) {
		removeInputItem<MouseAxisInputItem>(std::tr1::bind(testMouseAxisInputItem, _1, type));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::addAction(GamePadButtonElement type, unsigned short player, const std::string & name, IGamePadButtonInputActionMethod & method) {
		addAction<GamePadButtonInputItem, IGamePadButtonInputActionMethod>(findInputItem(type, player),
			name, method, std::tr1::bind(CreateGamePadButtonInputItem, type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAction(GamePadButtonElement type, unsigned short player, const std::string & name) {
		removeAction<GamePadButtonInputItem>(findInputItem(type, player), name);
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAllActions(GamePadButtonElement type, unsigned short player) {
		removeAllActions<GamePadButtonInputItem>(findInputItem(type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeInputItem(GamePadButtonElement type, unsigned short player) {
		removeInputItem<GamePadButtonInputItem>(std::tr1::bind(testGamePadButtonInputItem, _1, type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::addAction(GamePadAxisElement type, unsigned short player, const std::string & name, IGamePadAxisInputActionMethod & method) {
		addAction<GamePadAxisInputItem, IGamePadAxisInputActionMethod>(findInputItem(type, player),
			name, method, std::tr1::bind(CreateGamePadAxisInputItem, type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAction(GamePadAxisElement type, unsigned short player, const std::string & name) {
		removeAction<GamePadAxisInputItem>(findInputItem(type, player), name);
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeAllActions(GamePadAxisElement type, unsigned short player) {
		removeAllActions<GamePadAxisInputItem>(findInputItem(type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	void InputManager::removeInputItem(GamePadAxisElement type, unsigned short player) {
		removeInputItem<GamePadAxisInputItem>(std::tr1::bind(testGamePadAxisInputItem, _1, type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	template<class TInputItem, class TMethod>
	void InputManager::addAction(TInputItem * victim, const std::string & name, TMethod & method, std::tr1::function<TInputItem * ()> create) {
		// Dios me perdone por esta función. Aquí si recibimos un elemento de entrada existente,
		// nos limitamos a añadir la acción a dicho elemento y tan contentos.
		if(victim) {
			victim->addAction(name, &method);
		} else {
			// Pero si no existe nuestra víctima, creamos un elemento existente y luego añadimos la
			// acción al elemento, para finalmente añadir al gestor el nuevo elemento.
			victim = create();
			if(victim) {
				victim->addAction(name, &method);
				_inputItems.push_back(victim);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	template<class TInputItem>
	void InputManager::removeAction(TInputItem * victim, const std::string & name) {
		if(victim && name.size() > 0) {
			victim->removeAction(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	template<class TInputItem>
	void InputManager::removeAllActions(TInputItem * victim) {
		if(victim) {
			victim->removeAllActions();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	template<class TInputItem>
	void InputManager::removeInputItem(std::tr1::function<bool (TInputItem *)> test) {
		// Primero, recorremos todos los elementos de entrada del objeto.
		InputItemList::iterator end = _inputItems.end();
		for(InputItemList::iterator i = _inputItems.begin(); i != end; ++i) {
			// Segundo, comprobamos si el elemento actual es del tipo que necesitamos y
			// de serlo, si es capaz de pasar la función de comprobación.
			TInputItem * victim = dynamic_cast<TInputItem *>(*i);
			if(victim && test(victim)) {
				// Finalmente, si es el elemento que buscábamos lo eliminamos.
				_inputItems.remove(*i);
				delete victim;
				return;
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	template<class TInputItem>
	TInputItem * InputManager::findInputItem(std::tr1::function<bool (TInputItem *)> test) {
		// Primero, recorremos todos los elementos de entrada del objeto.
		InputItemList::iterator end = _inputItems.end();
		for(InputItemList::iterator i = _inputItems.begin(); i != end; ++i) {
			// Segundo, comprobamos si el elemento actual es del tipo que necesitamos y
			// de serlo, si es capaz de pasar la función de comprobación.
			TInputItem * victim = dynamic_cast<TInputItem *>(*i);
			if(victim && test(victim)) {
				// Finalmente, si es el elemento que buscábamos lo devolvemos.
				return victim;
			}
		}
		return 0;
	}

	//--------------------------------------------------------------------------------------------------------

	KeyboardInputItem * InputManager::findInputItem(KeyCode key) {
		return findInputItem<KeyboardInputItem>(std::tr1::bind(testKeyboardInputItem, _1, key));
	}

	//--------------------------------------------------------------------------------------------------------

	MouseButtonInputItem * InputManager::findInputItem(MouseButtonElement type) {
		return findInputItem<MouseButtonInputItem>(std::tr1::bind(testMouseButtonInputItem, _1, type));
	}

	//--------------------------------------------------------------------------------------------------------

	MouseAxisInputItem * InputManager::findInputItem(MouseAxisElement type) {
		return findInputItem<MouseAxisInputItem>(std::tr1::bind(testMouseAxisInputItem, _1, type));
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadButtonInputItem * InputManager::findInputItem(GamePadButtonElement type, unsigned short player) {
		return findInputItem<GamePadButtonInputItem>(std::tr1::bind(testGamePadButtonInputItem, _1, type, player));
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadAxisInputItem * InputManager::findInputItem(GamePadAxisElement type, unsigned short player) {
		return findInputItem<GamePadAxisInputItem>(std::tr1::bind(testGamePadAxisInputItem, _1, type, player));
	}
}
