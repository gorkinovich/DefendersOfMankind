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

#ifndef __CORE_ENTITYINFOTABLE_H__
#define __CORE_ENTITYINFOTABLE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <set>

#include "Core/Data/InfoTableWithName.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una tabla con información, sobre una entidad del mundo, asociada a una clave
	 * determinada. La clave es una cadena y la información se almacena también como una cadena, no obstante
	 * podemos recibirla transformada como un número entero o real, un booleano, un vector, etcétera.
	 */
	class EntityInfoTable : public InfoTableWithName {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * Clave para el atributo del tipo de la entidad.
		 */
		static const std::string TypeAttributeKey;

		/**
		 * El separador entre el nombre de un componente y el nombre de su atributo.
		 */
		static const std::string NameSeparator;

		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un conjunto de cadenas.
		 */
		typedef std::set<std::string> StringSet;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el tipo de la entidad.
		 */
		inline const std::string & getType() const { return _type; }

		/**
		 * Modifica el tipo de la entidad.
		 */
		inline void setType(const std::string & value) { _type = value; }

		/**
		 * Obtiene la tabla general de la que poder heredar información que no tenga la actual.
		 */
		inline const EntityInfoTable * getSuperInfoTable() const { return _superInfoTable; }

		/**
		 * Modifica la tabla general de la que poder heredar información que no tenga la actual.
		 */
		inline void setSuperInfoTable(const EntityInfoTable * value) { _superInfoTable = value; }

		/**
		 * Obtiene los componentes de la entidad.
		 */
		inline const StringSet & getComponents() const { return _components; }

		/**
		 * Obtiene el número de componentes que tiene la tabla.
		 * @remark Este método no cuenta con los componentes de la tabla general si la tiene.
		 */
		inline unsigned int getNumberOfComponents() const { return _components.size(); }

		/**
		 * Obtiene el conjunto con los nombres de todos los componentes que forman la entidad.
		 * @remark En esta función no se actualiza el estado interno del objeto para devolver el conjunto.
		 */
		StringSet getAllComponents() const;

		/**
		 * Obtiene el conjunto con los nombres de todos los componentes que forman la entidad.
		 * @remark En esta función no se actualiza el estado interno del objeto para devolver el conjunto.
		 */
		void getAllComponents(StringSet & names) const;

		/**
		 * Obtiene el conjunto con los nombres de todos los atributos que forman la entidad.
		 * @remark En esta función no se actualiza el estado interno del objeto para devolver el conjunto.
		 */
		void getAllAttributes(StringSet & names) const;

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

		/**
		 * Comprueba si la entidad tiene un componente determinado.
		 * @param name El nombre del componente.
		 * @return Devuelve true en caso de existir el componente.
		 */
		bool hasComponent(const std::string & name) const;

		/**
		 * Añade un componente determinado de la entidad.
		 * @param name El nombre del componente.
		 */
		void addComponent(const std::string & name);

		/**
		 * Borra un componente determinado de la entidad.
		 * @param name El nombre del componente.
		 */
		void removeComponent(const std::string & name);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 */
		EntityInfoTable(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		EntityInfoTable(const EntityInfoTable & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~EntityInfoTable();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El tipo de la entidad.
		 */
		std::string _type;

		/**
		 * Los componentes de la entidad.
		 */
		StringSet _components;

		/**
		 * La tabla general de la que poder heredar información que no tenga la actual.
		 * @remark La tabla a la que apunta no podrá ser modificada desde la actual.
		 */
		const EntityInfoTable * _superInfoTable;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza el contenido de un conjunto de nombres de componentes.
		 * @param victimSet El conjunto con los nombres de todos los componentes.
		 * @param victimInfoTable La tabla actual con la información sobre la entidad.
		 */
		void updateComponentsNames(StringSet & victimSet, const EntityInfoTable * victimInfoTable) const;

		/**
		 * Actualiza el contenido de un conjunto de nombres de atributos.
		 * @param victimSet El conjunto con los nombres de todos los atributos.
		 * @param victimInfoTable La tabla actual con la información sobre la entidad.
		 */
		void updateAttributesNames(StringSet & victimSet, const EntityInfoTable * victimInfoTable) const;
	};
}

#endif
