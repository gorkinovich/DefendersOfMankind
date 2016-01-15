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

#include "Core/Entities/Blueprints.h"
#include "Core/Scripting/BlueprintsUtils.h"
#include "Core/Data/EntityInfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	EntityInfoTable * Blueprints::get(const std::string & name) {
		EntityInfoTableTableIterator victim = _table.find(name);
		return (victim != _table.end()) ? victim->second : 0;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Blueprints::add(const std::string & name) {
		// Primero intentamos obtener el objeto almacenado en la máquina virtual de Lua.
		if(EntityInfoTable * aux = BlueprintsGetEntityInfoTable(name)) {
			// Si lo obtenemos, añadimos el nuevo descriptor a la tabla.
			return addEntityInfoTable(name, aux);
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool Blueprints::add(const EntityInfoTable * info) {
		if(info) {
			return addEntityInfoTable(info->getType(), new EntityInfoTable(*info));
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Blueprints::remove(const std::string & name) {
		EntityInfoTableTableIterator victim = _table.find(name);
		if(victim != _table.end()) {
			delete victim->second;
			_table.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Blueprints::clear() {
		EntityInfoTableTableIterator current = _table.begin();
		EntityInfoTableTableIterator end = _table.end();
		EntityInfoTableTableIterator victim;
		while(current != end) {
			victim = current++;
			delete victim->second;
			_table.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool Blueprints::contains(const std::string & name) const {
		return _table.count(name) > 0;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Blueprints::addEntityInfoTable(const std::string & name, EntityInfoTable * info) {
		if(info && name.size() > 0) {
			_table[name] = info;
			return true;
		} else {
			return false;
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Blueprints::Blueprints() {}

	//--------------------------------------------------------------------------------------------------------

	Blueprints::Blueprints(const Blueprints & obj) {
		_table = obj._table;
	}

	//--------------------------------------------------------------------------------------------------------

	Blueprints::~Blueprints() {
		clear();
	}
}
