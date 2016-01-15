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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Core/GenericApplication.h"
#include "Core/ApplicationState.h"
#include "Core/BaseManager.h"
#include "Core/Clock.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/Input/InputManager.h"
#include "Core/Resources/LoadingObserver.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Sound/SoundManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	GenericApplication * GenericApplication::_instance = 0;

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GenericApplication::initialize(const char * title, const char * logPath) {
		// Inicializamos el nucleo del motor.
		if(!BaseManager::GetInstance()->initialize(title, logPath)) return false;

		// Creamos el reloj interno de la aplicación.
		_clock = new Clock();
		if(!_clock) return false;
		LoadingObserver::GetInstance()->setClock(_clock);

		// Inicializamos las variables de control del bucle principal.
		_exit = false;
		_currentState = 0;
		_changeRequest.changeType = GenericApplication::SCT_NONE;
		_graphics = BaseManager::GetInstance()->getGraphics();
		_input = BaseManager::GetInstance()->getInput();
		_sound = BaseManager::GetInstance()->getSound();
		_scripting = BaseManager::GetInstance()->getScripting();

		// Y devolvemos que todo ha ido bien.
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::release() {
		// Borramos la información relacionada con los estados.
		clearTable();

		// Borramos el reloj interno de la aplicación.
		delete _clock;

		// Borramos las referencias a gestores del nucleo del motor.
		_graphics = 0;
		_input = 0;
		_sound = 0;
		_scripting = 0;

		// Liberamos el nucleo del motor.
		BaseManager::GetInstance()->release();
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::run() {
		assert(_clock && "GenericApplication::run -> The clock has not been created...");

		// Primero actualizamos el reloj, para evitar que el primer frame tenga una cifra "astronómica".
		_clock->update();

		// Entonces iniciamos el bucle principal, comprobando siempre si se ha pedido salir.
		while(!getExit()) {
			// En caso de que se haya pedido cambiar de estado, actualizaremos el cambio de estado actual.
			if(_changeRequest.changeType != GenericApplication::SCT_NONE) {
				updateChange();
			}
			// Actualizamos el reloj para obtener el intervalo de tiempo entre frame y frame.
			_clock->update();
			// Y actualizamos la lógica interna de la aplicación.
			update(_clock->getLastInterval());
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::changeState(const std::string & name) {
		_changeRequest.changeType = GenericApplication::SCT_CHANGE;
		_changeRequest.nextState = name;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::cleanAndChangeState(const std::string & name) {
		_changeRequest.changeType = GenericApplication::SCT_CLEAN_AND_CHANGE;
		_changeRequest.nextState = name;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::pushState(const std::string & name) {
		_changeRequest.changeType = GenericApplication::SCT_PUSH;
		_changeRequest.nextState = name;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::popState() {
		_changeRequest.changeType = GenericApplication::SCT_POP;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::popToState(const std::string & name) {
		_changeRequest.changeType = GenericApplication::SCT_POP_TO_STATE;
		_changeRequest.nextState = name;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::popToBaseState() {
		_changeRequest.changeType = GenericApplication::SCT_POP_TO_BASE;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GenericApplication::addToTable(const std::string & name, ApplicationState * victim) {
		return _fsm.addToTable(name, victim);
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::removeFromTable(const std::string & name) {
		_fsm.removeFromTable(name);
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::clearTable() {
		// Borramos el contenido de la pila primero.
		clearStack();
		// Y luego la tabla de estados.
		_fsm.clearTable();
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::clearStack() {
		// Borramos el contenido de la pila.
		_fsm.clearStack();
		// Y luego quitamos la referencia al estado actual.
		_currentState = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::sleep(unsigned int milliseconds) {
		Sleep(milliseconds);
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::update(unsigned int lastInterval) {
		// Actualizamos el estado de la entrada.
		_input->update();
		// Actualizamos el estado del sonido.
		_sound->update();
		// Si tenemos un estado activo lo actualizamos.
		if(_currentState) _currentState->update(lastInterval);
		// Actualizamos el estado del motor de script.
		_scripting->update();
		// Actualizamos el estado de los gráficos.
		_graphics->update(((float)lastInterval) / 1000.0f);
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericApplication::updateChange() {
		switch(_changeRequest.changeType) {
			// Cambia el estado actual en la cima por otro.
			case GenericApplication::SCT_CHANGE:
				if(_fsm.changeState(_changeRequest.nextState)) {
					_currentState = _fsm.getCurrentState();
				}
				break;

			// Borra la pila y añade un nuevo estado.
			case GenericApplication::SCT_CLEAN_AND_CHANGE:
				if(_fsm.existsInTable(_changeRequest.nextState)) {
					_fsm.clearStack();
					_fsm.pushState(_changeRequest.nextState);
					_currentState = _fsm.getCurrentState();
				}
				break;

			// Mete en la pila un nuevo estado.
			case GenericApplication::SCT_PUSH:
				if(_fsm.pushState(_changeRequest.nextState)) {
					_currentState = _fsm.getCurrentState();
				}
				break;

			// Vuelve la aplicación a un estado anterior en la pila.
			case GenericApplication::SCT_POP:
				_fsm.popState();
				_currentState = _fsm.getCurrentState();
				break;

			// Vuelve la aplicación a un estado anterior en la pila.
			case GenericApplication::SCT_POP_TO_STATE:
				while(_fsm.getStackSize() > 1 && !_fsm.checkCurrentState(_changeRequest.nextState)) {
					_fsm.popState();
				}
				_currentState = _fsm.getCurrentState();
				break;

			// Vuelve la aplicación al estado en el fondo de la pila.
			case GenericApplication::SCT_POP_TO_BASE:
				while(_fsm.getStackSize() > 1) {
					_fsm.popState();
				}
				_currentState = _fsm.getCurrentState();
				break;
		}
		_changeRequest.changeType = GenericApplication::SCT_NONE;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GenericApplication::GenericApplication() : _currentState(0), _exit(false), _clock(0), _graphics(0),
	_input(0), _sound(0), _scripting(0) {
		assert(!_instance && "GenericApplication::GenericApplication -> Can't create more than one application...");
		// Asignamos a la supuestamente única instancia en la aplicación una referencia a este nuevo objeto creado.
		_instance = this;
		// Inicializamos las variables importantes que quedan.
		_changeRequest.changeType = GenericApplication::SCT_NONE;
	}

	//--------------------------------------------------------------------------------------------------------

	GenericApplication::~GenericApplication() {
		_instance = 0;
	}
}
