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

#ifndef __CORE_INFOTABLEWITHNAME_H__
#define __CORE_INFOTABLEWITHNAME_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Data/InfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una tabla con nombre que contiene información asociada a una clave determinada.
	 * La clave es una cadena y la información se almacena también como una cadena, no obstante podemos
	 * recibirla transformada como un número entero o real, un booleano, un vector, etcétera.
	 */
	class InfoTableWithName : public InfoTable {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * Clave para el atributo del nombre de la tabla.
		 */
		static const std::string NameAttributeKey;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre de la tabla.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Modifica el nombre de la tabla.
		 */
		inline void setName(const std::string & value) { _name = value; }

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

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		virtual void setAttribute(const std::string & name, const std::string & value);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la tabla.
		 */
		InfoTableWithName(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		InfoTableWithName(const InfoTableWithName & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~InfoTableWithName();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre de la tabla.
		 */
		std::string _name;
	};
}

#endif
