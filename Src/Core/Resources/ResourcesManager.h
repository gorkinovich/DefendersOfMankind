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

#ifndef __CORE_RESOURCESMANAGER_H__
#define __CORE_RESOURCESMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>
#include <vector>

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class ResourceGroupManager;
	class ResourceBackgroundQueue;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ResourcesManagerListener;

	/**
	 * Esta clase representa al gestor de recursos del motor.
	 */
	class ResourcesManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el gestor de grupos de recursos.
		 */
		inline Ogre::ResourceGroupManager * getResourceGroupManager() { return _resourceGroupManager; }

		/**
		 * Obtiene la cola para cargar recursos en segundo plano.
		 */
		inline Ogre::ResourceBackgroundQueue * getResourceBackgroundQueue() { return _resourceBackgroundQueue; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static ResourcesManager * GetInstance() {
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
		 * Crea un grupo de recursos en el gestor.
		 * @param groupName El nombre del grupo.
		 * @param inGlobalPool Con este flag activado el grupo es añadido a la cola global del motor, con lo
		 *                     que cuando se pida inicializar cualquier otro, también se inicializará este.
		 */
		void createGroup(const std::string & groupName, bool inGlobalPool = false);

		/**
		 * Elimina un grupo de recursos registrado.
		 * @param groupName El nombre del grupo.
		 */
		void removeGroup(const std::string & groupName);

		/**
		 * Limpia el contenido de un grupo de recursos registrado.
		 * @param groupName El nombre del grupo.
		 */
		void clearGroup(const std::string & groupName);

		/**
		 * Inicializa un grupos de recursos registrados.
		 * @param groupName El nombre del grupo.
		 */
		void initialiseGroup(const std::string & groupName);

		/**
		 * Inicializa todos los grupos de recursos registrados.
		 */
		void initialiseAllGroups();

		/**
		 * Carga un grupo de recursos registrados.
		 * @param groupName El nombre del grupo.
		 * @param loadMainResources Con este flag activado se carga todos recursos (que no tengan que ver con geometría).
		 * @param loadWorldGeom Con este flag activado se carga todos los recursos que tengan que ver con geometría.
		 */
		void loadGroup(const std::string & groupName, bool loadMainResources = true, bool loadWorldGeom = true);

		/**
		 * Descarga un grupo de recursos registrados.
		 * @param groupName El nombre del grupo.
		 * @param reloadableOnly Con este flag activado evitamos que se descargen recursos que no permiten
		 *                       ser recargados tras ser eliminados de la memoria.
		 */
		void unloadGroup(const std::string & groupName, bool reloadableOnly = true);

		/**
		 * Comprueba si un grupo registrado en el gestor ha sido inicializado.
		 * @param groupName El nombre del grupo.
		 * @return Devuelve true en caso de estar inicializado.
		 */
		bool isGroupInitialised(const std::string & groupName);

		/**
		 * Comprueba si un grupo registrado en el gestor ha sido cargado.
		 * @param groupName El nombre del grupo.
		 * @return Devuelve true en caso de estar cargado.
		 */
		bool isGroupLoaded(const std::string & groupName);

		/**
		 * Comprueba si existe un grupo registrado en el gestor.
		 * @param groupName El nombre del grupo.
		 * @return Devuelve true en caso de encontrar el grupo.
		 */
		bool groupExists(const std::string & groupName);

		/**
		 * Añade una localización de recursos.
		 * @param path La ruta.
		 * @param pathType El tipo de la ruta.
		 */
		void addLocation(const std::string & path, const std::string & pathType);

		/**
		 * Añade una localización de recursos.
		 * @param path La ruta.
		 * @param pathType El tipo de la ruta.
		 * @param groupName El nombre del grupo.
		 */
		void addLocation(const std::string & path, const std::string & pathType, const std::string & groupName);

		/**
		 * Elimina una localización de recursos.
		 * @param path La ruta.
		 */
		void removeLocation(const std::string & path);

		/**
		 * Elimina una localización de recursos.
		 * @param path La ruta.
		 * @param groupName El nombre del grupo.
		 */
		void removeLocation(const std::string & path, const std::string & groupName);

		/**
		 * Comprueba si existe un fichero en cualquier grupo registrado en el gestor.
		 * @param fileName El nombre del fichero.
		 * @return Devuelve true en caso de encontrar el fichero en alguna localización.
		 */
		bool fileExists(const std::string & fileName);

		/**
		 * Comprueba si existe un fichero en cualquier grupo registrado en el gestor.
		 * @param fileName El nombre del fichero.
		 * @param groupName El nombre del grupo.
		 * @return Devuelve true en caso de encontrar el fichero en alguna localización.
		 */
		bool fileExists(const std::string & fileName, const std::string & groupName);

		/**
		 * Da una lista de los recursos contenidos en un grupo.
		 * @param groupName El nombre del grupo.
		 * @param showDirs Un flag para indicar si los directorios deben ser listados o no.
		 * @return Una lista de recursos.
		 */
		std::vector<std::string> listResources(const std::string & groupName, bool showDirs = false);

		/**
		 * Da una lista de rutas de localización de recursos.
		 * @param groupName El nombre del grupo.
		 * @return Una lista de rutas.
		 */
		std::vector<std::string> listLocations(const std::string & groupName);

		/**
		 * Obtiene el nombre de un grupo que contenga el fichero indicado.
		 * @param fileName El nombre del fichero.
		 * @param groupName El nombre del grupo devuelto.
		 * @return Devuelve true en caso de encontrar el fichero en algún grupo.
		 */
		bool getGroupName(const std::string & fileName, std::string & groupName);

		/**
		 * Obtiene la ruta completa para un fichero de existir en alguna localización de algún grupo.
		 * @param fileName El nombre del fichero.
		 * @param fullPath La ruta completa devuelta.
		 * @return Devuelve true en caso de encontrar el fichero en alguna localización.
		 */
		bool getFullPath(const std::string & fileName, std::string & fullPath);


		/**
		 * Carga un fichero con un modelo gráfico.
		 * @param fileName El nombre del fichero.
		 */
		void loadMeshFile(const std::string & fileName);


		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~ResourcesManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static ResourcesManager * _instance;

		/**
		 * El encargado de recibir los eventos de la carga de recursos.
		 */
		ResourcesManagerListener * _listener;

		/**
		 * El gestor de grupos de recursos.
		 */
		Ogre::ResourceGroupManager * _resourceGroupManager;

		/**
		 * La cola para cargar recursos en segundo plano.
		 */
		Ogre::ResourceBackgroundQueue * _resourceBackgroundQueue;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Carga las rutas de recursos contenidas en el fichero de resources.cfg.
		 */
		void loadLocations();

		//----------------------------------------------------------------------------------------------------
		// Métodos experimentales del gestor de carga de recursos en el background
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa un grupos de recursos registrados.
		 * @param groupName El nombre del grupo.
		 * @remark Este método no está completado por lo que no debe ser usado.
		 */
		void backgroundInitialiseGroup(const std::string & groupName);

		/**
		 * Inicializa todos los grupos de recursos registrados.
		 * @remark Este método no está completado por lo que no debe ser usado.
		 */
		void backgroundInitialiseAllGroups();

		/**
		 * Prepara un grupos de recursos registrados.
		 * @param groupName El nombre del grupo.
		 * @remark Este método no está completado por lo que no debe ser usado.
		 */
		void backgroundPrepareGroup(const std::string & groupName);

		/**
		 * Carga un grupo de recursos registrados.
		 * @param groupName El nombre del grupo.
		 * @remark Este método no está completado por lo que no debe ser usado.
		 */
		void backgroundLoadGroup(const std::string & groupName);

		/**
		 * Descarga un grupo de recursos registrados.
		 * @param groupName El nombre del grupo.
		 * @remark Este método no está completado por lo que no debe ser usado.
		 */
		void backgroundUnloadGroup(const std::string & groupName);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ResourcesManager() : _listener(0), _resourceGroupManager(0), _resourceBackgroundQueue(0) {}
	};
}

#endif
