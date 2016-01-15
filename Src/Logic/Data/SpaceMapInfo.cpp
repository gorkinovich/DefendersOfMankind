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

#include <exception>

#include "Logic/Data/SpaceMapInfo.h"
#include "Core/Scripting/LuabindUtils.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	bool SpaceMapInfoLoadMissionInfo(luabind::object & table, SpaceMapInfo::MissionInfo & victim) {
		std::string stringValue;

		// Obtenemos el nombre de la misi�n.
		luabind::object auxObj = table["name"];
		if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
		victim.name = stringValue;

		// Obtenemos la descripci�n de la misi�n.
		auxObj = table["description"];
		if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
		victim.description = stringValue;

		// Obtenemos el fichero de la misi�n.
		auxObj = table["file"];
		if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
		victim.file = stringValue;

		// Obtenemos el nombre del bot�n asociado a la misi�n.
		auxObj = table["button"];
		if(!Core::LuaConvertToString(auxObj, stringValue)) return false;
		victim.buttonName = stringValue;

		// Obtenemos los requerimientos de la misi�n.
		auxObj = table["requires"];
		if(Core::LuaIsTable(auxObj)) {
			luabind::object objVal;
			luabind::iterator i(auxObj), end;
			for(; i != end; ++i) {
				objVal = *i;
				if(Core::LuaConvertToString(objVal, stringValue)) {
					victim.requires.push_back(stringValue);
				}
			}
		}

		return true;
	}

	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	bool SpaceMapInfo::containsMission(const std::string & name) {
		return findIndex(name) > -1;
	}

	//--------------------------------------------------------------------------------------------------------

	SpaceMapInfo::MissionInfo & SpaceMapInfo::findMission(const std::string & name) {
		int index = findIndex(name);
		if(index > -1) {
			return _missions[index];
		} else {
			throw std::exception("SpaceMapInfo::findPart => Part not found...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	int SpaceMapInfo::findIndex(const std::string & name) {
		int size = (int)_missions.size();
		for(int i = 0; i < size; ++i) {
			if(_missions[i].name == name) return i;
		}
		return -1;
	}

	//--------------------------------------------------------------------------------------------------------

	void SpaceMapInfo::loadParts() {
		// Obtenemos la variable global que tiene la informaci�n descriptiva del juego.
		luabind::object gameGlobalData;
		if(Core::LuaGetGlobal("GameGlobalData", gameGlobalData)) {
			// Obtenemos el apartado dedicado al mapa espacial.
			luabind::object spaceMapData = gameGlobalData["SpaceMap"];
			if(spaceMapData.is_valid()) {
				// Recorremos todas las entradas del mapa.
				luabind::iterator i(spaceMapData), end;
				luabind::object objVal;
				for(; i != end; ++i) {
					// Comprobamos que la entrada es una tabla.
					objVal = *i;
					if(Core::LuaIsTable(objVal)) {
						// Cargamos la informaci�n de la entrada en un objeto MissionInfo.
						MissionInfo victim;
						//TODO: Esto tendr�a que ser false...
						victim.isDone = true;
						//...
						if(SpaceMapInfoLoadMissionInfo(objVal, victim)) {
							// Si la carga sale bien se a�ade la misi�n al juego.
							_missions.push_back(victim);
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void SpaceMapInfo::unloadParts() {
		// Recorremos todas las misiones para borrar la informaci�n compleja interna.
		MissionInfoVector::iterator i = _missions.begin();
		MissionInfoVector::iterator end = _missions.end();
		for(; i != end; ++i) {
			i->requires.clear();
		}
		// Borramos las misiones del juego.
		_missions.clear();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	SpaceMapInfo::SpaceMapInfo() {
		loadParts();
	}

	//--------------------------------------------------------------------------------------------------------

	SpaceMapInfo::~SpaceMapInfo() {
		unloadParts();
	}
}
