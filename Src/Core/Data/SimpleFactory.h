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

#ifndef __CORE_SIMPLEFACTORY_H__
#define __CORE_SIMPLEFACTORY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <functional>

#include "Core/Data/BaseFactory.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una factoría simple para crear objetos.
	 */
	template<class T = void>
	class SimpleFactory : public BaseFactory<std::tr1::function<T * ()>> {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Tipo que representa un puntero a función.
		 */
		typedef T * (*FunctionPointer)();

		/**
		 * Tipo que representa un método factoría.
		 */
		typedef std::tr1::function<T * ()> FactoryMethod;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo objeto requerido.
		 * @param name El nombre del tipo.
		 * @return El nuevo objeto creado.
		 */
		inline T * create(const std::string & name) const {
			Map::const_iterator ormagoden = _table.find(name);
			if(ormagoden != _table.end()) {
				return ormagoden->second();
			} else {
				throw std::exception("SimpleFactory::create => The factory method for the object doesn't exists...");
			}
		}

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		SimpleFactory() : BaseFactory() {}

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		SimpleFactory(const SimpleFactory & obj) : BaseFactory(obj) {}

		/**
		 * Destructor del objeto.
		 */
		virtual ~SimpleFactory() {}
	};
}

#endif
