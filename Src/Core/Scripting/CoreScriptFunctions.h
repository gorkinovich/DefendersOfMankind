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

//TODO: Completar y comentar el fichero...

#ifndef __CORE_CORESCRIPTFUNCTIONS_H__
#define __CORE_CORESCRIPTFUNCTIONS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <list>
#include <string>

#include "Core/Scripting/ScriptingInclude.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ScriptingManager;

	/**
	 * Esta clase estática representa la capa intermedia con la que el motor de scripting se va a
	 * comunicar a la hora de tener que interactuar con Core.
	 */
	class CoreScriptFunctions {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa la capa de comunicación con el motor de scripting.
		 */
		static void Initialize();

		/**
		 * Finaliza la capa de comunicación con el motor de scripting.
		 */
		static void Release();

		/**
		 * Actualiza las acciones pendientes de ejecutarse por el motor.
		 */
		static void Update();

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		static ScriptingManager * _scriptingManager;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (AI)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (Entities)
		//----------------------------------------------------------------------------------------------------

		static void EntitiesRegister(lua_State * luaState);

		static bool EntitiesRegisterBlueprints(const luabind::object & blueprints);

		static luabind::object EntitiesBlueprintsGet(const std::string & name);
		static bool EntitiesBlueprintsAdd(const std::string & name);
		static bool EntitiesBlueprintsContains(const std::string & name);
		static void EntitiesBlueprintsRemove(const std::string & name);
		static void EntitiesBlueprintsClear();

		static bool EntitiesLoadCurrentWorld(const std::string & name);
		static void EntitiesUnloadCurrentWorld();
		static bool EntitiesActivateCurrentWorld();
		static void EntitiesDeactivateCurrentWorld();

		//----------------------------------------------------------------------------------------------------
		// Métodos (Graphics)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (GUI)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (Input)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (Physics)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (Resources)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos (Scripting)
		//----------------------------------------------------------------------------------------------------

		static void ScriptingRegister(lua_State * luaState);

		static bool ScriptingInclude(const std::string & path);
		static bool ScriptingLoadAndRunFile(const std::string & path);
		static bool ScriptingLoadAndRunScript(const std::string & script);
		static bool ScriptingLoadAndRunFile(const std::string & path, unsigned int gid);
		static bool ScriptingLoadAndRunScript(const std::string & script, unsigned int gid);

		static bool ScriptingReloadAndRun();
		static bool ScriptingReloadAndRun(unsigned int gid);

		static void ScriptingClearCache();
		static void ScriptingClearFilesCache();
		static void ScriptingClearScriptsCache();
		static void ScriptingClearCache(unsigned int gid);
		static void ScriptingClearFilesCache(unsigned int gid);
		static void ScriptingClearScriptsCache(unsigned int gid);

		//----------------------------------------------------------------------------------------------------
		// Métodos (Sound)
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		CoreScriptFunctions() {}
		virtual ~CoreScriptFunctions() {}
	};
}

#endif
