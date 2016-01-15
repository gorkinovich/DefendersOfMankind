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

#ifndef __CORE_INPUTITEM_H__
#define __CORE_INPUTITEM_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>
#include <map>

#include "Core/Input/IInputItem.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un elemento de entrada genérico.
	 */
	template<class TValue, class TMethod>
	class InputItem : public IInputItem {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el valor actual del elemento.
		 */
		inline const TValue & getCurrentValue() const { return _currentValue; }

		/**
		 * Obtiene el valor previo del elemento.
		 */
		inline const TValue & getPreviousValue() const { return _previousValue; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade una acción al elemento.
		 * @param name El nombre de la acción.
		 * @param method El objeto con el método.
		 */
		void addAction(const std::string & name, TMethod * method) {
			if(name.size() > 0 && method) {
				_actions[name] = method;
			}
		}

		/**
		 * Elimina una acción al elemento.
		 * @param name El nombre de la acción.
		 */
		void removeAction(const std::string & name) {
			if(_actions.find(name) != _actions.end()) {
				_actions.erase(name);
			}
		}

		/**
		 * Elimina todas las acciones del elemento.
		 */
		void removeAllActions() {
			_actions.clear();
		}

		/**
		 * Actualiza el estado del elemento.
		 */
		virtual void update() {
			updateCurrentValue();
			if(changeCondition()) {
				ActionMap::iterator end = _actions.end();
				for(ActionMap::iterator i = _actions.begin(); i != end; ++i) {
					callMethod(*(i->second));
				}
			}
		}

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~InputItem() {
			_actions.clear();
		}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un mapa de acciones.
		 */
		typedef std::map<std::string, TMethod *> ActionMap;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Las acciones asociadas al elemento.
		 */
		ActionMap _actions;

		/**
		 * El valor actual del elemento.
		 */
		TValue _currentValue;

		/**
		 * El valor previo del elemento.
		 */
		TValue _previousValue;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Copia otro objeto al actual.
		 * @param obj El objeto a copiar.
		 */
		inline void copyFrom(const InputItem<TValue, TMethod> & obj) {
			_actions = obj._actions;
			_currentValue = obj._currentValue;
			_previousValue = obj._previousValue;
		}

		/**
		 * Comprueba si ha cambiado el estado de la información del elemento.
		 * @return De haber cambiado el estado devolverá true.
		 */
		virtual bool changeCondition() const = 0;

		/**
		 * Actualiza el valor interno del elemento.
		 */
		virtual void updateCurrentValue() = 0;

		/**
		 * Invoca un método dentro de un objeto.
		 * @param method El objeto con el método.
		 */
		virtual void callMethod(TMethod & method) = 0;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		InputItem() {}
	};
}

#endif
