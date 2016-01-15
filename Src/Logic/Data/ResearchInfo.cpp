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

#include "Logic/Data/ResearchInfo.h"
#include "Core/Scripting/LuabindUtils.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	bool ResearchInfoLoadAreaResearchInfo(luabind::object & table, ResearchInfo::AreaResearchInfoVector & victim) {
		// Comprobamos que estamos manejando una tabla de lua.
		if(!Core::LuaIsTable(table)) return false;

		// Recorremos todas las entradas del presunto array con investigaciones.
		luabind::iterator i(table), end;
		luabind::object objItem, objKey, objVal;
		std::string currentKey, stringValue;
		bool boolValue;
		int intValue;
		for(; i != end; ++i) {
			objItem = *i;
			// Comprobamos que el elemento actual sea una tabla.
			if(Core::LuaIsTable(objItem)) {
				// Creamos la investigación que vamos a rellenar con lo que leamos.
				ResearchInfo::AreaResearchInfo currentNode;
				currentNode.name = "";
				currentNode.description = "";
				currentNode.cost = 0;
				currentNode.buyed = false;
				// Recorremos todos los campos de la tabla actual.
				luabind::iterator j(objItem);
				for(; j != end; ++j) {
					objKey = j.key();
					// Comprobamos que la clave sea una cadena.
					if(Core::LuaConvertToString(objKey, currentKey)) {
						objVal = *j;
						// Comprobamos qué campo es y tratamos de obtener su valor para asignarlo
						// a la variable auxiliar que vamos a añadir al array de investigaciones.
						if((currentKey == "name") && Core::LuaConvertToString(objVal, stringValue)) {
							currentNode.name = stringValue;
						} else if((currentKey == "description") && Core::LuaConvertToString(objVal, stringValue)) {
							currentNode.description = stringValue;
						} else if((currentKey == "cost") && Core::LuaConvertToInteger(objVal, intValue)) {
							currentNode.cost = intValue;
						} else if((currentKey == "buyed") && Core::LuaConvertToBool(objVal, boolValue)) {
							currentNode.buyed = boolValue;
						}
					}
				}
				// Si tiene nombre, añadimos la investigación al array de investigaciones.
				if(currentNode.name.size() > 0) {
					victim.push_back(currentNode);
				}
			}
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchInfoLoadAreaInfo(luabind::object & table, ResearchInfo::AreaInfo & victim) {
		std::string stringValue;

		// Obtenemos el nombre del área.
		luabind::object auxObj = table["name"];
		if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
		victim.name = stringValue;

		// Obtenemos las investigaciones del área.
		auxObj = table["left"];
		if(!ResearchInfoLoadAreaResearchInfo(auxObj, victim.left)) return false;

		auxObj = table["middle"];
		if(!ResearchInfoLoadAreaResearchInfo(auxObj, victim.middle)) return false;

		auxObj = table["right"];
		if(!ResearchInfoLoadAreaResearchInfo(auxObj, victim.right)) return false;

		return true;
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ResearchInfo::containsArea(const std::string & name) {
		return _areas.count(name) > 0;
	}

	//--------------------------------------------------------------------------------------------------------

	ResearchInfo::AreaInfo & ResearchInfo::findArea(const std::string & name) {
		AreaInfoTable::iterator victim = _areas.find(name);
		if(victim != _areas.end()) {
			return victim->second;
		} else {
			throw std::exception("ResearchInfo::findPart => Area not found...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchInfo::loadParts() {
		// Obtenemos la variable global que tiene la información descriptiva del juego.
		luabind::object gameGlobalData;
		if(Core::LuaGetGlobal("GameGlobalData", gameGlobalData)) {
			// Obtenemos el apartado dedicado a la investigación.
			luabind::object researchData = gameGlobalData["Research"];
			if(researchData.is_valid()) {
				// Recorremos todas las entradas de áreas de investigación.
				luabind::iterator i(researchData), end;
				luabind::object objVal;
				for(; i != end; ++i) {
					// Comprobamos que la entrada es una tabla.
					objVal = *i;
					if(Core::LuaIsTable(objVal)) {
						// Cargamos la información de la entrada en un objeto AreaInfo.
						AreaInfo victim;
						if(ResearchInfoLoadAreaInfo(objVal, victim)) {
							// Si la carga sale bien se añade el área.
							_areas[victim.name] = victim;
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchInfo::unloadParts() {
		// Recorremos todas las áreas para borrar las investigaciones.
		AreaInfoTable::iterator i = _areas.begin();
		AreaInfoTable::iterator end = _areas.end();
		for(; i != end; ++i) {
			i->second.left.clear();
			i->second.middle.clear();
			i->second.right.clear();
		}
		// Borramos las áreas de investigación.
		_areas.clear();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ResearchInfo::ResearchInfo() {
		loadParts();
	}

	//--------------------------------------------------------------------------------------------------------

	ResearchInfo::~ResearchInfo() {
		unloadParts();
	}
}
