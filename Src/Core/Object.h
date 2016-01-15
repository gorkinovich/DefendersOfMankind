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

#ifndef __CORE_OBJECT_H__
#define __CORE_OBJECT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Pointer.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase abstracta representa un objeto de forma genérica.
	 */
	class Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el puntero reconvertido a otro tipo sin comprobaciones.
		 */
		template<class T>
		inline T * getPtrAs() { return static_cast<T *>(this); }

		/**
		 * Obtiene la referencia reconvertida a otro tipo sin comprobaciones.
		 */		
		template<class T>
		inline T & getRefAs() { return static_cast<T &>(*this); }

		/**
		 * Obtiene el puntero reconvertido a otro tipo con comprobaciones.
		 */
		template<class T>
		inline T * getSafePtrAs() { return dynamic_cast<T *>(this); }

		/**
		 * Obtiene la referencia reconvertida a otro tipo con comprobaciones.
		 */		
		template<class T>
		inline T & getSafeRefAs() { return dynamic_cast<T &>(*this); }

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~Object();

		//----------------------------------------------------------------------------------------------------
		// Operadores
		//----------------------------------------------------------------------------------------------------

		Object & operator =(const Object & obj);

		virtual bool operator ==(const Object & obj) const;

		virtual bool operator !=(const Object & obj) const;

		virtual bool operator <(const Object & obj) const;

	protected:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Copia el contenido de un objeto en el actual.
		 * @param obj El objeto a copiar.
		 */
		virtual void copyFrom(const Object & obj) = 0;

		/**
		 * Comprueba si un objeto es de un tipo determinado.
		 * @param obj El objeto a comprobar.
		 */
		template<class T>
		inline bool checkType(Object & obj) { return typeid(obj) == typeid(T &); }

		/**
		 * Comprueba si un objeto es de un tipo determinado.
		 * @param obj El objeto a comprobar.
		 */
		template<class T>
		inline bool checkType(const Object & obj) { return typeid(obj) == typeid(const T &); }

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Object();
	};

	/**
	 * Este tipo es un puntero inteligente a un Object.
	 */
	typedef SmartPointer<Object> SmartObject;
}

#endif
