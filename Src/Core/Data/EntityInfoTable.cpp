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

#include <exception>

#include "Core/Data/EntityInfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string EntityInfoTable::TypeAttributeKey = std::string("type");
	const std::string EntityInfoTable::NameSeparator = std::string(".");

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	EntityInfoTable::StringSet EntityInfoTable::getAllComponents() const {
		StringSet names;
		updateComponentsNames(names, this);
		return names;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::getAllComponents(EntityInfoTable::StringSet & names) const {
		names.clear();
		updateComponentsNames(names, this);
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::getAllAttributes(EntityInfoTable::StringSet & names) const {
		names.clear();
		updateAttributesNames(names, this);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool EntityInfoTable::hasAttribute(const std::string & name) const {
		if(name == TypeAttributeKey || InfoTableWithName::hasAttribute(name)) {
			return true;
		} else {
			return _superInfoTable && _superInfoTable->hasAttribute(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	const std::string & EntityInfoTable::getAttribute(const std::string & name) const {
		if(name == TypeAttributeKey) {
			return _type;
		} else if(InfoTableWithName::hasAttribute(name)) {
			return InfoTableWithName::getAttribute(name);
		} else if(_superInfoTable) {
			return _superInfoTable->getAttribute(name);
		} else {
			throw std::exception("EntityInfoTable::getAttribute => The attribute doesn't exists...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::setAttribute(const std::string & name, const std::string & value) {
		if(name == TypeAttributeKey) {
			_type = value;
		} else {
			InfoTableWithName::setAttribute(name, value);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool EntityInfoTable::hasComponent(const std::string & name) const {
		if(_components.count(name) > 0) {
			return true;
		} else {
			return _superInfoTable && _superInfoTable->hasComponent(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::addComponent(const std::string & name) {
		_components.insert(name);
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::removeComponent(const std::string & name) {
		_components.erase(name);
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::updateComponentsNames(StringSet & victimSet, const EntityInfoTable * victimInfoTable) const {
		// Si la tabla que le hemos pasado no apunta a NULL añadiremos los nombres de componentes que tenga.
		if(victimInfoTable) {
			// Copiamos el conjunto de nombres de componentes de la tabla.
			victimSet.insert(victimInfoTable->_components.begin(), victimInfoTable->_components.end());
			// Y después añadimos al conjunto los nombres de componentes de la tabla padre.
			updateComponentsNames(victimSet, victimInfoTable->_superInfoTable);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void EntityInfoTable::updateAttributesNames(StringSet & victimSet, const EntityInfoTable * victimInfoTable) const {
		// Si la tabla que le hemos pasado no apunta a NULL añadiremos los nombres de atributos que tenga.
		if(victimInfoTable) {
			// Copiamos el conjunto de nombres de atributos de la tabla.
			AttributesTable::const_iterator i = victimInfoTable->_attributes.begin();
			AttributesTable::const_iterator end = victimInfoTable->_attributes.end();
			for(; i != end; ++i) {
				victimSet.insert(i->first);
			}
			// Y después añadimos al conjunto los nombres de atributos de la tabla padre.
			updateAttributesNames(victimSet, victimInfoTable->_superInfoTable);
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	EntityInfoTable::EntityInfoTable(const std::string & name) : InfoTableWithName(name), _type(""), _superInfoTable(0) {}

	//--------------------------------------------------------------------------------------------------------

	EntityInfoTable::EntityInfoTable(const EntityInfoTable & obj) : InfoTableWithName(obj) {
		_type = obj._type;
		_components = obj._components;
		_superInfoTable = obj._superInfoTable;
	}

	//--------------------------------------------------------------------------------------------------------

	EntityInfoTable::~EntityInfoTable() {
		_components.clear();
	}
}
