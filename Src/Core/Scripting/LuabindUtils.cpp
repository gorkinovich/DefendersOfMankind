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

#include "Core/Scripting/LuabindUtils.h"
#include "Core/Scripting/ScriptingManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	bool LuaGetGlobal(const char * name, luabind::object & retValue) {
		lua_State * luaState = ScriptingManager::GetInstance()->getLuaState();
		retValue = luabind::globals(luaState)[name];
		return retValue.is_valid();
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaIsTable(const luabind::object & victim) {
		return victim.is_valid() && luabind::type(victim) == LUA_TTABLE;
	}

	//--------------------------------------------------------------------------------------------------------

	template<class T>
	inline bool LuaConvertTo(luabind::object & victim, int luaType, T & retValue) {
		if(victim.is_valid() && luabind::type(victim) == luaType) {
			retValue = luabind::object_cast<T>(victim);
			return true;
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaConvertToBool(luabind::object & victim, bool & retValue) {
		return LuaConvertTo<bool>(victim, LUA_TBOOLEAN, retValue);
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaConvertToNumber(luabind::object & victim, double & retValue) {
		return LuaConvertTo<double>(victim, LUA_TNUMBER, retValue);
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaConvertToFloat(luabind::object & victim, float & retValue) {
		return LuaConvertTo<float>(victim, LUA_TNUMBER, retValue);
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaConvertToInteger(luabind::object & victim, int & retValue) {
		return LuaConvertTo<int>(victim, LUA_TNUMBER, retValue);
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaConvertToString(luabind::object & victim, std::string & retValue) {
		if(victim.is_valid() && luabind::type(victim) == LUA_TSTRING) {
			const char * aux = luabind::object_cast<const char *>(victim);
			retValue = std::string(aux);
			return true;
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool LuaConvertToUserData(luabind::object & victim, void * & retValue) {
		return LuaConvertTo<void *>(victim, LUA_TUSERDATA, retValue);
	}
}
