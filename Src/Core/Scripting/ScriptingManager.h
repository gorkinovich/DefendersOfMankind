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

#ifndef __CORE_SCRIPTINGMANAGER_H__
#define __CORE_SCRIPTINGMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <list>
#include <string>

#include "Core/Scripting/ScriptObject.h"

//************************************************************************************************************
// Lua
//************************************************************************************************************

extern "C" {
	struct lua_State;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa al gestor del motor de scripting.
	 */
	class ScriptingManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el contexto con el que poder gestionar Lua.
		 */
		inline lua_State * getLuaState() const { return _state; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static ScriptingManager * GetInstance() {
			return _instance;
		}

		/**
		 * Inicializa el gestor.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize();

		/**
		 * Finaliza el gestor.
		 */
		void release();

		/**
		 * Actualiza el estado del gestor.
		 */
		void update();

		/**
		 * Obtiene una variable de la máquina virtual.
		 * @param name El nombre de la variable global.
		 * @return Un objeto para manejar la variable.
		 */
		ScriptObject getGlobal(const std::string & name);

		/**
		 * Ejecuta un código de script.
		 * @param script El código del script.
		 * @return Devuelve true si se logra cargar y ejecutar el código.
		 */
		bool executeScript(const char * script);

		/**
		 * Carga y ejecuta un fichero de script.
		 * @param path La ruta del fichero.
		 * @return Devuelve true si se logra cargar y ejecutar el fichero.
		 * @remark Esta función no añade el fichero a la caché del gestor.
		 */
		bool includeFile(const std::string & path);

		/**
		 * Carga y ejecuta un fichero de script.
		 * @param path La ruta del fichero.
		 * @param gid El identificador de grupo.
		 * @return Devuelve true si se logra cargar y ejecutar el fichero.
		 */
		bool loadAndRunFile(const std::string & path, unsigned int gid = 0);

		/**
		 * Carga y ejecuta un código de script.
		 * @param script El código del script.
		 * @param gid El identificador de grupo.
		 * @return Devuelve true si se logra cargar y ejecutar el código.
		 */
		bool loadAndRunScript(const std::string & script, unsigned int gid = 0);

		/**
		 * Carga y ejecuta todos los ficheros y códigos de script previamente registrados.
		 * @return Devuelve true si se logra cargar y ejecutar los ficheros y códigos.
		 */
		bool reloadAndRun();

		/**
		 * Carga y ejecuta un grupo de ficheros y códigos de script previamente registrados.
		 * @param gid El identificador de grupo.
		 * @return Devuelve true si se logra cargar y ejecutar los ficheros y códigos.
		 */
		bool reloadAndRun(unsigned int gid);

		/**
		 * Elimina la caché guardada de ficheros y códigos de script previamente registrados.
		 */
		void clearCache();

		/**
		 * Elimina la caché guardada de ficheros de script previamente registrados.
		 */
		void clearFilesCache();

		/**
		 * Elimina la caché guardada de códigos de script previamente registrados.
		 */
		void clearScriptsCache();

		/**
		 * Elimina un grupo de la caché guardada de ficheros y códigos de script previamente registrados.
		 * @param gid El identificador de grupo.
		 */
		void clearCache(unsigned int gid);

		/**
		 * Elimina un grupo de la caché guardada de ficheros de script previamente registrados.
		 * @param gid El identificador de grupo.
		 */
		void clearFilesCache(unsigned int gid);

		/**
		 * Elimina un grupo de la caché guardada de códigos de script previamente registrados.
		 * @param gid El identificador de grupo.
		 */
		void clearScriptsCache(unsigned int gid);

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~ScriptingManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Esta estructura representa un grupo dentro de las listas del gestor.
		 */
		typedef struct {
			std::string content;
			unsigned int gid;
		} Group;

		/**
		 * Este tipo representa una lista de grupos.
		 */
		typedef std::list<Group> GroupList;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static ScriptingManager * _instance;

		/**
		 * El contexto con el que poder gestionar Lua.
		 */
		lua_State * _state;

		/**
		 * Los ficheros previamente cargados por el gestor.
		 */
		GroupList _files;

		/**
		 * Los scripts previamente cargados por el gestor.
		 */
		GroupList _scripts;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Carga y ejecuta un fichero de script.
		 * @param path La ruta completa del fichero.
		 * @return Devuelve true si se logra cargar y ejecutar el fichero.
		 */
		inline bool loadAndRunLuaFile(const char * path);

		/**
		 * Carga y ejecuta un código de script.
		 * @param script El código del script.
		 * @return Devuelve true si se logra cargar y ejecutar el código.
		 */
		inline bool loadAndRunLuaScript(const char * script);

		/**
		 * Añade un grupo a una lista de caché guardada.
		 * @param list La lista de caché
		 * @param content El contenido.
		 * @param gid El identificador de grupo.
		 */
		inline void addToCache(GroupList & list, const std::string & content, unsigned int gid);

		/**
		 * Elimina un grupo de una lista de caché guardada.
		 * @param list La lista de caché
		 * @param gid El identificador de grupo.
		 */
		inline void clearCache(GroupList & list, unsigned int gid);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ScriptingManager() : _state(0) {}
	};
}

#endif
