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

#include "Logic/Data/WorkshopInfo.h"
#include "Core/Scripting/LuabindUtils.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	bool WorkshopInfoLoadPartInfo(luabind::object & table, WorkshopInfo::PartInfo & victim) {
		std::string stringValue;
		bool boolValue;
		int intValue;

		// Obtenemos el nombre de la parte.
		luabind::object auxObj = table["name"];
		if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
		victim.name = stringValue;

		// Obtenemos los componentes de la parte.
		auxObj = table["components"];
		if(!Core::LuaIsTable(auxObj)) return false;

		// Recorremos todos los componentes de la parte.
		luabind::object objVal;
		luabind::iterator i(auxObj), end;
		WorkshopInfo::ComponentInfo componentVictim;
		for(; i != end; ++i) {
			objVal = *i;
			if(!Core::LuaIsTable(objVal)) return false;

			// Obtenemos el nombre del componente.
			auxObj = objVal["name"];
			if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
			componentVictim.name = stringValue;

			// Obtenemos la descripción del componente.
			auxObj = objVal["description"];
			if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
			componentVictim.description = stringValue;

			// Obtenemos el coste del componente.
			auxObj = objVal["cost"];
			if(!Core::LuaConvertToInteger(auxObj, intValue)) return false;
			componentVictim.cost = intValue;

			// Obtenemos si está comprado el componente.
			auxObj = objVal["buyed"];
			componentVictim.buyed = Core::LuaConvertToBool(auxObj, boolValue) ? boolValue : false;

			// Obtenemos si está seleccionado el componente.
			auxObj = objVal["selected"];
			componentVictim.selected = Core::LuaConvertToBool(auxObj, boolValue) ? boolValue : false;

			victim.components.push_back(componentVictim);
		}

		return true;
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool WorkshopInfo::containsPart(const std::string & name) {
		return _parts.count(name) > 0;
	}

	//--------------------------------------------------------------------------------------------------------

	WorkshopInfo::PartInfo & WorkshopInfo::findPart(const std::string & name) {
		PartInfoTable::iterator victim = _parts.find(name);
		if(victim != _parts.end()) {
			return victim->second;
		} else {
			throw std::exception("WorkshopInfo::findPart => Part not found...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopInfo::addPart(const std::string & name, const ComponentInfoVector & components) {
		if(name.size() > 0) {
			// Inicializamos la parte.
			PartInfo victim;
			victim.name = name;
			victim.components = components;
			// Y la añadimos a las partes del taller.
			_parts[name] = victim;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopInfo::loadParts() {
		// Obtenemos la variable global que tiene la información descriptiva del juego.
		luabind::object gameGlobalData;
		if(Core::LuaGetGlobal("GameGlobalData", gameGlobalData)) {
			// Obtenemos el apartado dedicado a la tienda.
			luabind::object workshopData = gameGlobalData["Workshop"];
			if(workshopData.is_valid()) {
				// Recorremos todas las entradas de la tienda.
				luabind::iterator i(workshopData), end;
				luabind::object objKey, objVal;
				std::string currentKey;
				for(; i != end; ++i) {
					// Obtenemos el nombre clave de la entrada.
					objKey = i.key();
					if(Core::LuaConvertToString(objKey, currentKey)) {
						// Comprobamos que la entrada es una tabla.
						objVal = *i;
						if(Core::LuaIsTable(objVal)) {
							// Cargamos la información de la entrada en un objeto PartInfo.
							PartInfo victim;
							if(WorkshopInfoLoadPartInfo(objVal, victim)) {
								// Si la carga sale bien se añade a las partes de la tienda.
								_parts[currentKey] = victim;
							}
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopInfo::unloadParts() {
		// Recorremos todas las partes para borrar los componentes.
		PartInfoTable::iterator i = _parts.begin();
		PartInfoTable::iterator end = _parts.end();
		for(; i != end; ++i) {
			i->second.components.clear();
		}
		// Borramos las partes del taller.
		_parts.clear();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	WorkshopInfo::WorkshopInfo() {
		loadParts();
	}

	//--------------------------------------------------------------------------------------------------------

	WorkshopInfo::~WorkshopInfo() {
		unloadParts();
	}
}
