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

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void CoreScriptFunctions::ScriptingRegister(lua_State * luaState) {
		typedef bool (*Scripting01)(const std::string &);
		typedef bool (*Scripting02)(const std::string &, unsigned int);
		typedef bool (*Scripting03)();
		typedef bool (*Scripting04)(unsigned int);
		typedef void (*Scripting11)();
		typedef void (*Scripting12)(unsigned int);

		luabind::module(luaState)[
			luabind::def("include",                      (Scripting01) &(CoreScriptFunctions::ScriptingInclude)),
			luabind::def("import",                       (Scripting01) &(CoreScriptFunctions::ScriptingInclude)),
			luabind::def("using",                        (Scripting01) &(CoreScriptFunctions::ScriptingInclude)),
			luabind::def("ScriptingLoadAndRunFile",      (Scripting01) &(CoreScriptFunctions::ScriptingLoadAndRunFile)),
			luabind::def("ScriptingLoadAndRunScript",    (Scripting01) &(CoreScriptFunctions::ScriptingLoadAndRunScript)),
			luabind::def("ScriptingLoadAndRunFileEx",    (Scripting02) &(CoreScriptFunctions::ScriptingLoadAndRunFile)),
			luabind::def("ScriptingLoadAndRunScriptEx",  (Scripting02) &(CoreScriptFunctions::ScriptingLoadAndRunScript)),
			luabind::def("ScriptingReloadAndRun",        (Scripting03) &(CoreScriptFunctions::ScriptingReloadAndRun)),
			luabind::def("ScriptingReloadAndRunEx",      (Scripting04) &(CoreScriptFunctions::ScriptingReloadAndRun)),
			luabind::def("ScriptingClearCache",          (Scripting11) &(CoreScriptFunctions::ScriptingClearCache)),
			luabind::def("ScriptingClearFilesCache",     (Scripting11) &(CoreScriptFunctions::ScriptingClearFilesCache)),
			luabind::def("ScriptingClearScriptsCache",   (Scripting11) &(CoreScriptFunctions::ScriptingClearScriptsCache)),
			luabind::def("ScriptingClearCacheEx",        (Scripting12) &(CoreScriptFunctions::ScriptingClearCache)),
			luabind::def("ScriptingClearFilesCacheEx",   (Scripting12) &(CoreScriptFunctions::ScriptingClearFilesCache)),
			luabind::def("ScriptingClearScriptsCacheEx", (Scripting12) &(CoreScriptFunctions::ScriptingClearScriptsCache))
		];
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingInclude(const std::string & path) {
		return _scriptingManager->includeFile(path);
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingLoadAndRunFile(const std::string & path) {
		return _scriptingManager->loadAndRunFile(path);
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingLoadAndRunScript(const std::string & script) {
		return _scriptingManager->loadAndRunScript(script);
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingLoadAndRunFile(const std::string & path, unsigned int gid) {
		return _scriptingManager->loadAndRunFile(path, gid);
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingLoadAndRunScript(const std::string & script, unsigned int gid) {
		return _scriptingManager->loadAndRunScript(script, gid);
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingReloadAndRun() {
		return _scriptingManager->reloadAndRun();
	}

	//--------------------------------------------------------------------------------------------------------

	bool CoreScriptFunctions::ScriptingReloadAndRun(unsigned int gid) {
		return _scriptingManager->reloadAndRun(gid);
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::ScriptingClearCache() {
		_scriptingManager->clearCache();
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::ScriptingClearFilesCache() {
		_scriptingManager->clearFilesCache();
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::ScriptingClearScriptsCache() {
		_scriptingManager->clearScriptsCache();
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::ScriptingClearCache(unsigned int gid) {
		_scriptingManager->clearCache(gid);
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::ScriptingClearFilesCache(unsigned int gid) {
		_scriptingManager->clearFilesCache(gid);
	}

	//--------------------------------------------------------------------------------------------------------

	void CoreScriptFunctions::ScriptingClearScriptsCache(unsigned int gid) {
		_scriptingManager->clearScriptsCache(gid);
	}
}
