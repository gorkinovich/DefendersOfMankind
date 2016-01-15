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

#ifndef __CORE_COMPLEXENTITYINFOTABLE_H__
#define __CORE_COMPLEXENTITYINFOTABLE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <set>

#include "Core/Data/InfoTableWithName.h"
#include "Core/Data/ComponentInfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una tabla con informaci�n, sobre una entidad del mundo, asociada a una clave
	 * determinada. La clave es una cadena y la informaci�n se almacena tambi�n como una cadena, no obstante
	 * podemos recibirla transformada como un n�mero entero o real, un booleano, un vector, etc�tera.
	 */
	class ComplexEntityInfoTable : public InfoTableWithName {
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
		 * Obtiene la tabla general de la que poder heredar informaci�n que no tenga la actual.
		 */
		inline const ComplexEntityInfoTable * getSuperInfoTable() const { return _superInfoTable; }

		/**
		 * Modifica la tabla general de la que poder heredar informaci�n que no tenga la actual.
		 */
		void setSuperInfoTable(const ComplexEntityInfoTable * value);

		/**
		 * Obtiene el conjunto con los nombres de todos los componentes que forman la entidad.
		 */
		const StringSet & getComponentsNames();

		/**
		 * Obtiene el conjunto con los nombres de todos los componentes que forman la entidad.
		 * @remark En esta funci�n no se actualiza el estado interno del objeto para devolver el conjunto.
		 */
		void getComponentsNames(StringSet & names) const;

		/**
		 * Obtiene el n�mero de componentes que tiene la tabla.
		 * @remark Este m�todo no cuenta con los componentes de la tabla general si la tiene.
		 */
		inline unsigned int getNumberOfComponents() const { return _components.size(); }

		//----------------------------------------------------------------------------------------------------
		// M�todos
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
		 * @return El valor del atributo, si no existe devuelve una excepci�n.
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
		 * Obtiene el valor de un componente determinado.
		 * @param name El nombre del componente.
		 * @return El valor del componente, si no existe devuelve una excepci�n.
		 */
		const ComponentInfoTable & getComponent(const std::string & name) const;

		/**
		 * Modifica el valor de un componente determinado.
		 * @param name El nombre del componente.
		 * @param value El valor del componente.
		 */
		void setComponent(const std::string & name, const ComponentInfoTable & value);

		/**
		 * Borra un componente determinado de la entidad.
		 * @param name El nombre del componente.
		 */
		void removeComponent(const std::string & name);

		/**
		 * Actualiza el conjunto con los nombres de todos los componentes que forman la entidad.
		 */
		void updateComponentsNames();

		/**
		 * Borra el conjunto con los nombres de todos los componentes que forman la entidad.
		 */
		void clearComponentsNames();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 */
		ComplexEntityInfoTable(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		ComplexEntityInfoTable(const ComplexEntityInfoTable & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~ComplexEntityInfoTable();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de componentes.
		 */
		typedef std::map<std::string, ComponentInfoTable> ComponentsTable;

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
		ComponentsTable _components;

		/**
		 * La tabla general de la que poder heredar informaci�n que no tenga la actual.
		 * @remark La tabla a la que apunta no podr� ser modificada desde la actual.
		 */
		const ComplexEntityInfoTable * _superInfoTable;

		/**
		 * El conjunto con los nombres de todos los componentes que forman la entidad.
		 */
		StringSet _componentsNames;

		/**
		 * Flag para comprobar si el conjunto de nombres de los componentes est� desactualizado.
		 */
		bool _componentsNamesUpdated;

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza el contenido de un conjunto de nombres de componentes.
		 * @param victimSet El conjunto con los nombres de todos los componentes.
		 * @param victimInfoTable La tabla actual con la informaci�n sobre la entidad.
		 */
		void updateComponentsNames(StringSet & victimSet, const ComplexEntityInfoTable * victimInfoTable) const;

		/**
		 * Parte una cadena en dos partes, una el nombre del componente y la otra el nombre del atributo.
		 * @param name El nombre del atributo.
		 * @param cmpName El nombre del componente.
		 * @param cmpKey El nombre del atributo del componente.
		 * @return Devuelve true si logra hacer la partici�n de forma correcta.
		 */
		bool splitComponentName(const std::string & name, std::string & cmpName, std::string & cmpKey) const;
	};
}

#endif
