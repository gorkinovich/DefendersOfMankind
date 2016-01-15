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

#include "Core/Scripting/ScriptingInclude.h"
#include "Core/Scripting/CoreScriptFunctions.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Resources/ResourcesManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	ScriptingManager * ScriptingManager::_instance = new ScriptingManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ScriptingManager::initialize() {
		// Inicializamos el motor de scripting de Lua.
		_state = lua_open();
		if(!_state) return false;
		// Cargamos las librerías que podamos necesitar.
		luaopen_base(_state);
		luaopen_table(_state);
		luaopen_string(_state);
		luaopen_math(_state);
		// Inicializamos el subsistema de luabind.
		luabind::open(_state);
		ScriptObject::_scripting = this;
		// Inicializa la capa de comunicación con el motor de scripting.
		CoreScriptFunctions::Initialize();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::release() {
		// Finaliza la capa de comunicación con el motor de scripting.
		CoreScriptFunctions::Release();
		// Y luego finalizamos el motor de scripting de Lua.
		if(_state) {
			lua_close(_state);
			_state = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::update() {
		CoreScriptFunctions::Update();
	}

	//--------------------------------------------------------------------------------------------------------

	ScriptObject ScriptingManager::getGlobal(const std::string & name) {
		assert(_state && "ScriptingManager::getVariable -> The script engine has not been created...");
		return ScriptObject(name);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::executeScript(const char * script) {
		return loadAndRunLuaScript(script);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::includeFile(const std::string & path) {
		// Primero buscaremos la ruta completa del fichero dentro del gestor de recursos.
		std::string fullPath;
		if(ResourcesManager::GetInstance()->getFullPath(path, fullPath)) {
			// Probamos cargar y ejecutar el fichero de script.
			if(loadAndRunLuaFile(fullPath.c_str())) {
				return true;
			}
		}
		// Si no se hubiera cargado con éxito el fichero, se devuelve false como fallo.
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::loadAndRunFile(const std::string & path, unsigned int gid) {
		// Primero buscaremos la ruta completa del fichero dentro del gestor de recursos.
		std::string fullPath;
		if(ResourcesManager::GetInstance()->getFullPath(path, fullPath)) {
			// Probamos cargar y ejecutar el fichero de script.
			if(loadAndRunLuaFile(fullPath.c_str())) {
				// Si tiene éxito la función, añadimos a la caché la ruta del fichero.
				addToCache(_files, fullPath, gid);
				return true;
			}
		}
		// Si no se hubiera cargado con éxito el fichero, se devuelve false como fallo.
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::loadAndRunScript(const std::string & script, unsigned int gid) {
		// Probamos cargar y ejecutar el código de script.
		if(loadAndRunLuaScript(script.c_str())) {
			// Si tiene éxito la función, añadimos a la caché el código de script.
			addToCache(_scripts, script, gid);
			return true;
		}
		// Si no se hubiera cargado con éxito el código, se devuelve false como fallo.
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::reloadAndRun() {
		// Probamos cargar y ejecutar todos los ficheros de script guardados.
		GroupList::iterator i = _files.begin();
		GroupList::iterator end = _files.end();
		for(; i != end; ++i) {
			if(!loadAndRunLuaFile(i->content.c_str())) return false;
		}
		// Probamos cargar y ejecutar todos los códigos de script guardados.
		end = _scripts.end();
		for(i = _scripts.begin(); i != end; ++i) {
			if(!loadAndRunLuaScript(i->content.c_str())) return false;
		}
		// Si todo fue bien, devolvemos true como señal de éxito.
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::reloadAndRun(unsigned int gid) {
		// Probamos cargar y ejecutar todos los ficheros de script guardados.
		GroupList::iterator i = _files.begin();
		GroupList::iterator end = _files.end();
		for(; i != end; ++i) {
			if(i->gid == gid) {
				if(!loadAndRunLuaFile(i->content.c_str())) return false;
			}
		}
		// Probamos cargar y ejecutar todos los códigos de script guardados.
		end = _scripts.end();
		for(i = _scripts.begin(); i != end; ++i) {
			if(i->gid == gid) {
				if(!loadAndRunLuaScript(i->content.c_str())) return false;
			}
		}
		// Si todo fue bien, devolvemos true como señal de éxito.
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearCache() {
		_files.clear();
		_scripts.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearFilesCache() {
		_files.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearScriptsCache() {
		_scripts.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearCache(unsigned int gid) {
		clearFilesCache(gid);
		clearScriptsCache(gid);
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearFilesCache(unsigned int gid) {
		clearCache(_files, gid);
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearScriptsCache(unsigned int gid) {
		clearCache(_scripts, gid);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::loadAndRunLuaFile(const char * path) {
		assert(_state && "ScriptingManager::loadAndRunLuaFile -> The script engine has not been created...");
		// Probamos cargar el fichero de script.
		if(luaL_loadfile(_state, path) == 0) {
			// Una vez cargado, lo ejecutamos.
			lua_call(_state, 0, 0);
			return true;
		}
		// Si no se hubiera cargado con éxito el fichero, se devuelve false como fallo.
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptingManager::loadAndRunLuaScript(const char * script) {
		assert(_state && "ScriptingManager::loadAndRunLuaScript -> The script engine has not been created...");
		// Probamos cargar el código de script.
		if(luaL_loadstring(_state, script) == 0) {
			// Una vez cargado, lo ejecutamos.
			lua_call(_state, 0, 0);
			return true;
		}
		// Si no se hubiera cargado con éxito el código, se devuelve false como fallo.
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::addToCache(GroupList & list, const std::string & content, unsigned int gid) {
		// Creamos e inicializamos un nuevo nodo de grupo.
		Group victim;
		victim.content = content;
		victim.gid = gid;
		// Y lo añadimos a la lista.
		list.push_back(victim);
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptingManager::clearCache(GroupList & list, unsigned int gid) {
		// Recorremos toda la lista hasta el final.
		GroupList::iterator i = list.begin();
		GroupList::iterator end = list.end();
		while(i != end) {
			// Si encontramos un nodo que tenga el mismo identificador de grupo, lo borraremos.
			GroupList::iterator victim = i++;
			if(victim->gid == gid) {
				list.erase(victim);
			}
		}
	}
}
