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

#include "Core/Scripting/CoreScriptFunctions.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Scripting/LuabindUtils.h"
#include "Core/Entities/EntitiesManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void CoreScriptFunctions::EntitiesRegister(lua_State * luaState) {
		typedef luabind::object (*Scripting01)(const std::string &);
		typedef bool (*Scripting02)(const std::string &);
		typedef void (*Scripting03)(const std::string &);
		typedef bool (*Scripting04)();
		typedef void (*Scripting05)();
		typedef bool (*Scripting06)(const luabind::object &);

		luabind::module(luaState)[
			luabind::def("EntitiesRegisterBlueprints",     (Scripting06) &(CoreScriptFunctions::EntitiesRegisterBlueprints)),
			luabind::def("EntitiesBlueprintsGet",          (Scripting01) &(CoreScriptFunctions::EntitiesBlueprintsGet)),
			luabind::def("EntitiesBlueprintsAdd",          (Scripting02) &(CoreScriptFunctions::EntitiesBlueprintsAdd)),
			luabind::def("EntitiesBlueprintsContains",     (Scripting02) &(CoreScriptFunctions::EntitiesBlueprintsContains)),
			luabind::def("EntitiesBlueprintsRemove",       (Scripting03) &(CoreScriptFunctions::EntitiesBlueprintsRemove)),
			luabind::def("EntitiesBlueprintsClear",        (Scripting05) &(CoreScriptFunctions::EntitiesBlueprintsClear)),
			luabind::def("EntitiesLoadCurrentWorld",       (Scripting02) &(CoreScriptFunctions::EntitiesLoadCurrentWorld)),
			luabind::def("EntitiesUnloadCurrentWorld",     (Scripting05) &(CoreScriptFunctions::EntitiesUnloadCurrentWorld)),
			luabind::def("EntitiesActivateCurrentWorld",   (Scripting04) &(CoreScriptFunctions::EntitiesActivateCurrentWorld)),
			luabind::def("EntitiesDeactivateCurrentWorld", (Scripting05) &(CoreScriptFunctions::EntitiesDeactivateCurrentWorld))
		];
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::EntitiesRegisterBlueprints(const luabind::object & blueprints) {
		bool allRegistered = true;
		if(LuaIsTable(blueprints)) {
			luabind::iterator i(blueprints), end;
			luabind::object value;
			std::string currentValue;
			for(; i != end; ++i) {
				value = *i;
				if(LuaConvertToString(value, currentValue)) {
					allRegistered = allRegistered && EntitiesBlueprintsAdd(currentValue);
				}
			}
		}
		return allRegistered;
	}

	//--------------------------------------------------------------------------------------------------------

	luabind::object CoreScriptFunctions::EntitiesBlueprintsGet(const std::string & name) {
		lua_State * luaState = ScriptingManager::GetInstance()->getLuaState();
		return luabind::globals(luaState)[name];
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::EntitiesBlueprintsAdd(const std::string & name) {
		Blueprints & blueprints = EntitiesManager::GetInstance()->getBlueprints();
		if(!blueprints.contains(name)) {
			if(ScriptingManager::GetInstance()->includeFile(name + ".lua")) {
				return blueprints.add(name);
			} else {
				return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::EntitiesBlueprintsContains(const std::string & name) {
		return EntitiesManager::GetInstance()->getBlueprints().contains(name);
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::EntitiesBlueprintsRemove(const std::string & name) {
		EntitiesManager::GetInstance()->getBlueprints().remove(name);
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::EntitiesBlueprintsClear() {
		EntitiesManager::GetInstance()->getBlueprints().clear();
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::EntitiesLoadCurrentWorld(const std::string & name) {
		return EntitiesManager::GetInstance()->loadCurrentWorld(name);
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::EntitiesUnloadCurrentWorld() {
		EntitiesManager::GetInstance()->unloadCurrentWorld();
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::EntitiesActivateCurrentWorld() {
		return EntitiesManager::GetInstance()->activateCurrentWorld();
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::EntitiesDeactivateCurrentWorld() {
		EntitiesManager::GetInstance()->deactivateCurrentWorld();
	}
}
