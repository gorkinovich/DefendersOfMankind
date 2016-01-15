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

#ifndef __CORE_VARIABLE_H__
#define __CORE_VARIABLE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Object.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una variable genérica.
	 */
	template<class T>
	class Variable : public Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el dato.
		 */
		inline const T & getDataAsConstRef() const { return _data; }

		/**
		 * Obtiene el dato.
		 */
		inline T & getDataAsRef() { return _data; }

		/**
		 * Obtiene el dato.
		 */
		inline T getData() { return _data; }

		/**
		 * Modifica el dato.
		 */
		inline void setData(T value) { _data = value; }

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Variable() {}

		/**
		 * Construye un nuevo objeto.
		 */
		Variable(T data) : _data(data) {}

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Variable(const Variable<T> & obj) : _data(obj._data) {}

		/**
		 * Destructor del objeto.
		 */
		virtual ~Variable() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Copia el contenido de un objeto en el actual.
		 * @param obj El objeto a copiar.
		 */
		virtual void copyFrom(const Object & obj) {
			if(checkType<Variable<T>>(obj)) {
				Variable::Variable(static_cast<const Variable<T> &>(obj));
			}
		}

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El dato interno de la variable.
		 */
		T _data;
	};
}

#endif
