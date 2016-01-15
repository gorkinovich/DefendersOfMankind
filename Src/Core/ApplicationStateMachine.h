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

#ifndef __CORE_APPLICATIONSTATEMACHINE_H__
#define __CORE_APPLICATIONSTATEMACHINE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <stack>
#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ApplicationState;

	/**
	 * Esta clase representa un gestor para m�quinas de estados en una aplicaci�n.
	 */
	class ApplicationStateMachine {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el estado actual en la cima de la pila.
		 */
		inline ApplicationState * getCurrentState() {
			return _stack.empty() ? 0 : _stack.top();
		}

		/**
		 * Obtiene si la pila est� vac�a.
		 */
		inline bool isStackEmpty() { return _stack.empty(); }

		/**
		 * Obtiene el n�mero de elementos dentro de la pila.
		 */
		inline unsigned int getStackSize() { return _stack.size(); }

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si el estado actual en la cima de la pila es del tipo indicado.
		 * @param name El nombre del estado.
		 * @return Devuelve true si el tipo del estado actual corresponde con el indicado en el nombre.
		 */
		bool checkCurrentState(const std::string & name);

		/**
		 * Cambia el estado actual (el que est� en la cima de la pila de estados).
		 * @param name El nombre del estado.
		 * @return Devuelve true si la operaci�n se realiz� correctamente.
		 */
		bool changeState(const std::string & name);

		/**
		 * Introduce un nuevo estado en la pila de estados.
		 * @param name El nombre del estado.
		 * @return Devuelve true si la operaci�n se realiz� correctamente.
		 */
		bool pushState(const std::string & name);

		/**
		 * Vuelve al estado anterior en la pila de estados.
		 */
		void popState();

		/**
		 * A�ade un estado en la tabla de estados.
		 * @param name El nombre del estado.
		 * @param victim El estado a a�adir.
		 * @return Devuelve true si la operaci�n se realiz� correctamente.
		 * @remarks La eliminaci�n del puntero al estado a�adido es gestionada por la clase.
		 */
		bool addToTable(const std::string & name, ApplicationState * victim);

		/**
		 * Borra un estado de la tabla de estados.
		 * @param name El nombre del estado.
		 */
		void removeFromTable(const std::string & name);

		/**
		 * Comprueba si existe un estado dentro de la tabla.
		 * @param name El nombre del estado.
		 * @return Devuelve true si el estado existe en la tabla.
		 */
		bool existsInTable(const std::string & name);

		/**
		 * Limpia la tabla de estados.
		 */
		void clearTable();

		/**
		 * Limpia la pila de estados.
		 */
		void clearStack();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ApplicationStateMachine();

		/**
		 * Destructor del objeto.
		 */
		virtual ~ApplicationStateMachine();

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de estados.
		 */
		typedef std::map<std::string, ApplicationState *> StatesTable;

		/**
		 * Este tipo representa una pila de estados.
		 */
		typedef std::stack<ApplicationState *> StatesStack;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La tabla con todos los estados almacenados.
		 */
		StatesTable _table;

		/**
		 * La pila actual de estados.
		 */
		StatesStack _stack;

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Busca un estado dentro de la tabla de estados.
		 * @param name El nombre del estado.
		 * @return Devuelve NULL si no encuentra ning�n estado.
		 */
		inline ApplicationState * getState(const std::string & name);
	};
}

#endif
