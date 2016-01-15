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

#ifndef __CORE_BASEFACTORY_H__
#define __CORE_BASEFACTORY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <string>
#include <exception>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa la base para una factoría encargada de crear objetos.
	 */
	template<class T>
	class BaseFactory {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade un método factoría asociado a un tipo.
		 * @param name El nombre del tipo.
		 * @param method El método factoría.
		 */
		inline void add(const std::string & name, const T & method) {
			if(name.size() > 0) {
				_table[name] = method;
			} else {
				throw std::exception("BaseFactory::add => Invalid parameters...");
			}
		}

		/**
		 * Elimina un método factoría asociado a un tipo.
		 * @param name El nombre del tipo.
		 */
		inline void remove(const std::string & name) {
			Map::const_iterator victim = _table.find(name);
			if(victim != _table.end()) {
				_table.erase(victim);
			}
		}

		/**
		 * Elimina todos los métodos factoría registrados.
		 */
		inline void clear() {
			Map::const_iterator current = _table.begin();
			Map::const_iterator end = _table.end();
			Map::const_iterator victim;
			while(current != end) {
				victim = current++;
				_table.erase(victim);
			}
		}

		/**
		 * Comprueba si está un método factoría registrado.
		 * @param name El nombre del tipo asociado al método factoría.
		 * @return Si el método asociado a un tipo está registrado o no.
		 */
		inline bool contains(const std::string & name) const {
			return _table.count(name) > 0;
		}

		//----------------------------------------------------------------------------------------------------
		// Constructor y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		BaseFactory(const BaseFactory & obj) {
			_table = obj._table;
		}

		/**
		 * Destructor del objeto.
		 */
		virtual ~BaseFactory() {
			clear();
		}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Tipo Pair del Map de la factoría.
		 */
		typedef std::pair<std::string, T> Pair;

		/**
		 * Tipo Map de la factoría.
		 */
		typedef std::map<std::string, T> Map;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Tabla con los métodos factoría para crear objetos.
		 */
		Map _table;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		BaseFactory() {}
	};
}

#endif
