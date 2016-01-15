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

#include "Core/ApplicationState.h"
#include "Core/ApplicationStateMachine.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ApplicationStateMachine::checkCurrentState(const std::string & name) {
		// Obtenemos las víctimas de la comprobación.
		ApplicationState * victim1 = getCurrentState();
		ApplicationState * victim2 = getState(name);
		// Y siempre que no sean nulas, comprobamos sus tipos.
		return victim1 && victim2 && typeid(*victim1) == typeid(*victim2);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ApplicationStateMachine::changeState(const std::string & name) {
		// Primero buscamos en la tabla de estados alguno con el mismo nombre.
		if(ApplicationState * victim = getState(name)) {
			// Si hay alguno, pasamos a mirar si la pila no está vacía.
			if(!_stack.empty()) {
				// Si hay un estado en la cima, lo cogemos.
				ApplicationState * top = _stack.top();
				// Lo desactivamos y luego lo liberamos.
				top->deactivate();
				top->release();
				// Entonces quitamos de la cima el estado.
				_stack.pop();
			}
			// Inicializamos y activamos el estado nuevo.
			victim->initialize();
			victim->activate();
			// Y finalmente, lo metemos en la pila.
			_stack.push(victim);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ApplicationStateMachine::pushState(const std::string & name) {
		// Primero buscamos en la tabla de estados alguno con el mismo nombre.
		if(ApplicationState * victim = getState(name)) {
			// Si hay alguno, pasamos a mirar si la pila no está vacía.
			if(!_stack.empty()) {
				// Si hay un estado en la cima, lo cogemos y lo desactivamos.
				ApplicationState * top = _stack.top();
				top->deactivate();
			}
			// Inicializamos y activamos el estado nuevo.
			victim->initialize();
			victim->activate();
			// Y finalmente, lo metemos en la pila.
			_stack.push(victim);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ApplicationStateMachine::popState() {
		// Primero comprobamos que no esté vacía la pila.
		if(!_stack.empty()) {
			// De no estarlo, cogemos el estado en la cima.
			ApplicationState * victim = _stack.top();
			// Lo desactivamos y luego lo liberamos.
			victim->deactivate();
			victim->release();
			// Entonces quitamos de la cima el estado.
			_stack.pop();
			// Volvemos a comprobar que no esté vacía la pila.
			if(!_stack.empty()) {
				// De no estarlo, cogemos el estado en la cima.
				victim = _stack.top();
				// Y lo activamos de nuevo.
				victim->activate();
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ApplicationStateMachine::addToTable(const std::string & name, ApplicationState * victim) {
		if(victim && name.size() > 0 && _table.find(name) == _table.end()) {
			_table[name] = victim;
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ApplicationStateMachine::removeFromTable(const std::string & name) {
		StatesTable::iterator i = _table.find(name);
		if(i != _table.end()) {
			delete i->second;
			_table.erase(i);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ApplicationStateMachine::existsInTable(const std::string & name) {
		StatesTable::iterator i = _table.find(name);
		return i != _table.end();
	}

	//--------------------------------------------------------------------------------------------------------

	void ApplicationStateMachine::clearTable() {
		StatesTable::iterator end = _table.end();
		for(StatesTable::iterator i = _table.begin(); i != end; ++i) {
			delete i->second;
		}
		_table.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void ApplicationStateMachine::clearStack() {
		ApplicationState * victim;
		while(!_stack.empty()) {
			victim = _stack.top();
			victim->deactivate();
			victim->release();
			_stack.pop();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	ApplicationState * ApplicationStateMachine::getState(const std::string & name) {
		StatesTable::iterator i = _table.find(name);
		return (i != _table.end()) ? i->second : 0;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ApplicationStateMachine::ApplicationStateMachine() {}

	//--------------------------------------------------------------------------------------------------------

	ApplicationStateMachine::~ApplicationStateMachine() {
		// Eliminamos la pila de estados.
		clearStack();
		// Y luego eliminamos la tabla de estados.
		clearTable();
	}
}
