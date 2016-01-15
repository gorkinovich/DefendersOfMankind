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

#ifndef __CORE_TERRAINMANAGER_H__
#define __CORE_TERRAINMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Core/Math.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
    class TerrainGlobalOptions;
    class TerrainGroup;
	class SceneManager;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa al gestor de terrenos.
	 */
	class TerrainManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static TerrainManager * GetInstance() {
			return _instance;
		}

		/**
		 * Obtiene las opciones por defecto para los terrenos.
		 */
		inline Ogre::TerrainGlobalOptions * getTerrainGlobalOptions() { return _terrainGlobalOptions; }

		/**
		 * Obtiene el gestor de conjuntos de terrenos.
		 */
		inline Ogre::TerrainGroup * getTerrainGroup() { return _terrainGroup; }

		/**
		 * Obtiene el flag que indica si el gestor está inicializado o no.
		 */
		inline bool isInitialized() const { return _isInitialized; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el gestor de forma parcial.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize();

		/**
		 * Inicializa el gestor.
		 * @param sceneManager El gestor de la escena.
		 * @param terrainSize El tamaño de cada fragmento de terreno.
		 * @param worldSize El tamaño de cada fragmento de terreno en unidades del mundo.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize);

		/**
		 * Finaliza el gestor.
		 */
		void release();

		/**
		 * Reinicia el gestor.
		 * @param sceneManager El gestor de la escena.
		 * @param terrainSize El tamaño de cada fragmento de terreno.
		 * @param worldSize El tamaño de cada fragmento de terreno en unidades del mundo.
		 * @return Devuelve true si se logra reiniciar el manager.
		 */
		bool reset(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize);

		/**
		 * Inicializa el gestor de conjuntos de terrenos.
		 * @param sceneManager El gestor de la escena.
		 * @param terrainSize El tamaño de cada fragmento de terreno.
		 * @param worldSize El tamaño de cada fragmento de terreno en unidades del mundo.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initializeTerrainGroup(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize);

		/**
		 * Finaliza el gestor de conjuntos de terrenos.
		 */
		void releaseTerrainGroup();

		/**
		 * Reinicia el gestor de conjuntos de terrenos.
		 * @param sceneManager El gestor de la escena.
		 * @param terrainSize El tamaño de cada fragmento de terreno.
		 * @param worldSize El tamaño de cada fragmento de terreno en unidades del mundo.
		 * @return Devuelve true si se logra reiniciar el gestor de conjuntos de terrenos.
		 */
		bool resetTerrainGroup(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize);

		/**
		 * Actualiza el gestor.
		 */
		void update();

		/**
		 * Configura algunos datos del gestor de conjuntos de terrenos.
		 * @param groupName El grupo del que va a sacar los recursos al cargar.
		 * @param origin El punto de origen en el gestor.
		 */
		void configureTerrainGroup(const std::string & groupName, const Vector3 & origin = Vector3::ZERO);

		/**
		 * Define un fragmento de terreno.
		 * @param x La coordenada x del fragmento en la rejilla.
		 * @param y La coordenada y del fragmento en la rejilla.
		 * @param fileName El fichero con la información del fragmento.
		 */
		void defineTerrain(long x, long y, const std::string & fileName);

		/**
		 * Carga godos los fragmentos de terreno definidos.
		 * @param synchronous Flag para indicar si la carga se hace de forma síncrona o asíncrona.
		 */
		void loadAllTerrains(bool synchronous = true);

		/**
		 * Borra los archivos temporales que no sean ya necesarios.
		 */
		void freeTemporaryResources();

		/**
		 * Borra todos los fragmentos de terreno.
		 * @remark Este método no puede ser llamado después de destruir el grafo de escena.
		 */
		void removeAllTerrains();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~TerrainManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static TerrainManager * _instance;

		/**
		 * Las opciones por defecto para los terrenos.
		 */
		Ogre::TerrainGlobalOptions * _terrainGlobalOptions;

		/**
		 * El gestor de conjuntos de terrenos.
		 */
		Ogre::TerrainGroup * _terrainGroup;

		/**
		 * El flag que indica si el gestor está inicializado o no.
		 */
		bool _isInitialized;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		TerrainManager() : _terrainGlobalOptions(0), _terrainGroup(0), _isInitialized(false) {}
	};
}

#endif
