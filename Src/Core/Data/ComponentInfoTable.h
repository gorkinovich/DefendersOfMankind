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

#ifndef __CORE_COMPONENTINFOTABLE_H__
#define __CORE_COMPONENTINFOTABLE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Data/InfoTableWithName.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta tipo representa una tabla con información, de un componente en una entidad, asociada a una clave
	 * determinada. La clave es una cadena y la información se almacena también como una cadena, no obstante
	 * podemos recibirla transformada como un número entero o real, un booleano, un vector, etcétera.
	 */
	class ComponentInfoTable : public InfoTableWithName {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la tabla general de la que poder heredar información que no tenga la actual.
		 */
		inline const ComponentInfoTable * getSuperInfoTable() const { return _superInfoTable; }

		/**
		 * Modifica la tabla general de la que poder heredar información que no tenga la actual.
		 */
		inline void setSuperInfoTable(const ComponentInfoTable * value) { _superInfoTable = value; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si la tabla tiene un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return Devuelve true en caso de existir el atributo.
		 */
		virtual bool hasAttribute(const std::string & name) const;

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		virtual const std::string & getAttribute(const std::string & name) const;

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ComponentInfoTable();

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 */
		ComponentInfoTable(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		ComponentInfoTable(const ComponentInfoTable & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~ComponentInfoTable();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La tabla general de la que poder heredar información que no tenga la actual.
		 * @remark La tabla a la que apunta no podrá ser modificada desde la actual.
		 */
		const ComponentInfoTable * _superInfoTable;
	};
}

#endif
