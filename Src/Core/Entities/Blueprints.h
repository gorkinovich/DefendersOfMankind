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

#ifndef __CORE_BLUEPRINTS_H__
#define __CORE_BLUEPRINTS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Types/DataTypes.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntityInfoTable;

	/**
	 * Esta clase representa una colección de descriptores de entidades.
	 */
	class Blueprints {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene un tipo de entidad.
		 * @param name El nombre del tipo de entidad.
		 * @return El descriptor del tipo de entidad.
		 */
		EntityInfoTable * get(const std::string & name);

		/**
		 * Añade un tipo de entidad.
		 * @param name El nombre del tipo de entidad.
		 * @return Si el tipo de entidad se ha registrado o no.
		 */
		bool add(const std::string & name);

		/**
		 * Añade un tipo de entidad.
		 * @param info La tabla descriptora del tipo de entidad.
		 * @return Si el tipo de entidad se ha registrado o no.
		 * @remark El puntero al descriptor no es guardado, porque se crea una copia.
		 */
		bool add(const EntityInfoTable * info);

		/**
		 * Elimina tipo de entidad.
		 * @param name El nombre del tipo de entidad.
		 */
		void remove(const std::string & name);

		/**
		 * Elimina todos los tipos de entidad.
		 */
		void clear();

		/**
		 * Comprueba si está un tipo de entidad registrado.
		 * @param name El nombre del tipo de entidad.
		 * @return Si el tipo de entidad está registrado o no.
		 */
		bool contains(const std::string & name) const;

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Blueprints();

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Blueprints(const Blueprints & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Blueprints();

		//----------------------------------------------------------------------------------------------------
		// Operadores
		//----------------------------------------------------------------------------------------------------

		EntityInfoTable * operator [](const std::string & name) { return get(name); }

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La tabla con los descriptores de entidades.
		 */
		EntityInfoTableTable _table;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade un tipo de entidad.
		 * @param name El nombre del tipo de entidad.
		 * @param info La tabla descriptora del tipo de entidad.
		 * @return Si el tipo de entidad se ha registrado o no.
		 */
		bool addEntityInfoTable(const std::string & name, EntityInfoTable * info);
	};
}

#endif
