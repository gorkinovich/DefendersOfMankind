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

#include "Core/Data/ComplexEntityInfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ComplexEntityInfoTable::TypeAttributeKey = std::string("type");
	const std::string ComplexEntityInfoTable::NameSeparator = std::string(".");

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	void ComplexEntityInfoTable::setSuperInfoTable(const ComplexEntityInfoTable * value) {
		// Asignamos la tabla padre.
		_superInfoTable = value;
		// Asignamos los componentes padres.
		ComponentsTable::iterator i = _components.begin();
		ComponentsTable::iterator end = _components.end();
		if(_superInfoTable) {
			// Si la tabla padre apunta a algún objeto buscamos los componentes que tengan en común.
			for(; i != end; ++i) {
				ComponentInfoTable & cmp = i->second;
				const std::string & cmpName = cmp.getName();
				// Aquí comprobamos que la tabla padre tenga el componente actual.
				if(_superInfoTable->hasComponent(cmpName)) {
					// Y si lo tiene le pasamos la dirección del componente en la tabla padre.
					cmp.setSuperInfoTable(&(_superInfoTable->getComponent(cmpName)));
				}
			}
		} else {
			// Si la tabla padre no apunta a ningún objeto, borramos las referencias en los componentes.
			for(; i != end; ++i) {
				i->second.setSuperInfoTable(0);
			}
		}
		// Indicamos que el conjunto de nombres de los componentes está desactualizado.
		_componentsNamesUpdated = false;
	}

	//--------------------------------------------------------------------------------------------------------

	const ComplexEntityInfoTable::StringSet & ComplexEntityInfoTable::getComponentsNames() {
		// Mandamos actualizar al conjunto de nombres.
		updateComponentsNames();
		// Y finalmente devolvemos una referencia al conjunto en cuestión.
		return _componentsNames;
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::getComponentsNames(ComplexEntityInfoTable::StringSet & names) const {
		names.clear();
		updateComponentsNames(names, this);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ComplexEntityInfoTable::hasAttribute(const std::string & name) const {
		std::string cmpName, cmpKey;
		if(splitComponentName(name, cmpName, cmpKey)) {
			if(hasComponent(cmpName) && getComponent(cmpName).hasAttribute(cmpKey)) {
				return true;
			} else {
				return _superInfoTable && _superInfoTable->hasComponent(cmpName) &&
					_superInfoTable->getComponent(cmpName).hasAttribute(cmpKey);
			}
		} else {
			if(name == TypeAttributeKey || InfoTableWithName::hasAttribute(name)) {
				return true;
			} else {
				return _superInfoTable && _superInfoTable->hasAttribute(name);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	const std::string & ComplexEntityInfoTable::getAttribute(const std::string & name) const {
		std::string cmpName, cmpKey;
		if(splitComponentName(name, cmpName, cmpKey)) {
			if(hasComponent(cmpName)) {
				const ComponentInfoTable & aux = getComponent(cmpName);
				if(aux.hasAttribute(cmpKey)) {
					return aux.getAttribute(cmpKey);
				}
			} else if(_superInfoTable && _superInfoTable->hasComponent(cmpName)) {
				const ComponentInfoTable & aux = _superInfoTable->getComponent(cmpName);
				if(aux.hasAttribute(cmpKey)) {
					return aux.getAttribute(cmpKey);
				}
			}
			throw std::exception("ComplexEntityInfoTable::getAttribute => The component attribute doesn't exists...");
		} else {
			if(name == TypeAttributeKey) {
				return _type;
			} else if(InfoTableWithName::hasAttribute(name)) {
				return InfoTableWithName::getAttribute(name);
			} else if(_superInfoTable) {
				return _superInfoTable->getAttribute(name);
			} else {
				throw std::exception("ComplexEntityInfoTable::getAttribute => The attribute doesn't exists...");
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::setAttribute(const std::string & name, const std::string & value) {
		std::string cmpName, cmpKey;
		if(splitComponentName(name, cmpName, cmpKey)) {
			if(!hasComponent(cmpName)) {
				setComponent(cmpName, ComponentInfoTable(cmpName));
			}
			ComponentInfoTable & aux = const_cast<ComponentInfoTable &>(getComponent(cmpName));
			aux.setAttribute(cmpKey, value);
		} else {
			if(name == TypeAttributeKey) {
				_type = value;
			} else {
				InfoTableWithName::setAttribute(name, value);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ComplexEntityInfoTable::hasComponent(const std::string & name) const {
		if(_components.count(name) > 0) {
			return true;
		} else {
			return _superInfoTable && _superInfoTable->hasComponent(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	const ComponentInfoTable & ComplexEntityInfoTable::getComponent(const std::string & name) const {
		ComponentsTable::const_iterator victim = _components.find(name);
		if(victim != _components.end()) {
			return victim->second;
		} else if(_superInfoTable) {
			return _superInfoTable->getComponent(name);
		} else {
			throw std::exception("ComplexEntityInfoTable::getComponent => The component doesn't exists...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::setComponent(const std::string & name, const ComponentInfoTable & value) {
		_components[name] = value;
		_componentsNamesUpdated = false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::removeComponent(const std::string & name) {
		_components.erase(name);
		_componentsNamesUpdated = false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::updateComponentsNames() {
		// Comprobamos si el conjunto de nombres de los componentes está desactualizado.
		if(!_componentsNamesUpdated) {
			//Primero borramos el conjunto de nombres.
			_componentsNames.clear();
			// Luego lo rellenamos con los nombres tengamos.
			updateComponentsNames(_componentsNames, this);
			// Y por último marcamos como actualizado el conjunto.
			_componentsNamesUpdated = true;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::clearComponentsNames() {
		_componentsNames.clear();
		_componentsNamesUpdated = false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ComplexEntityInfoTable::updateComponentsNames(StringSet & victimSet, const ComplexEntityInfoTable * victimInfoTable) const {
		// Si la tabla que le hemos pasado no apunta a NULL añadiremos los nombres de componentes que tenga.
		if(victimInfoTable) {
			// Comprobamos ya de paso que la tabla que le hemos pasado no esté actualizada.
			if(victimInfoTable->_componentsNamesUpdated) {
				// Si está actualizada copiamos su conjunto de nombres.
				victimSet.insert(victimInfoTable->_componentsNames.begin(), victimInfoTable->_componentsNames.end());
			} else {
				// Recorremos todos los componentes de la tabla actual.
				ComponentsTable::const_iterator i = victimInfoTable->_components.begin();
				ComponentsTable::const_iterator end = victimInfoTable->_components.end();
				for(; i != end; ++i) {
					// Por cada componente añadimos al conjunto su nombre clave.
					victimSet.insert(i->first);
				}
				// Y finalmente añadimos al conjunto los nombres de componentes de la tabla padre.
				updateComponentsNames(victimSet, victimInfoTable->_superInfoTable);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ComplexEntityInfoTable::splitComponentName(const std::string & name, std::string & cmpName, std::string & cmpKey) const {
		std::string::size_type dotPos = name.find('.');
		if(dotPos != std::string::npos) {
			cmpName = name.substr(0, dotPos);
			cmpKey = name.substr(dotPos + 1);
			return (cmpName.size() > 0) && (cmpKey.size() > 0);
		} else {
			return false;
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ComplexEntityInfoTable::ComplexEntityInfoTable(const std::string & name) : InfoTableWithName(name), _type(""),
	_superInfoTable(0), _componentsNamesUpdated(false) {}

	//--------------------------------------------------------------------------------------------------------

	ComplexEntityInfoTable::ComplexEntityInfoTable(const ComplexEntityInfoTable & obj) : InfoTableWithName(obj) {
		_type = obj._type;
		_components = obj._components;
		_superInfoTable = obj._superInfoTable;
		_componentsNames = obj._componentsNames;
		_componentsNamesUpdated = obj._componentsNamesUpdated;
	}

	//--------------------------------------------------------------------------------------------------------

	ComplexEntityInfoTable::~ComplexEntityInfoTable() {
		_components.clear();
		_componentsNames.clear();
	}
}
