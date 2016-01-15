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

#ifndef __CORE_ENTITIESMANAGER_H__
#define __CORE_ENTITIESMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Data/IdSequence.h"
#include "Core/Data/SimpleFactory.h"
#include "Core/Data/EntityInfoTable.h"
#include "Core/Types/DataTypes.h"
#include "Core/Types/EntitiesTypes.h"
#include "Core/Entities/Blueprints.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntityInfoTableNames;
	class GraphicNodeEntity;
	class TerrainManager;
	class Component;
	class Entity;
	class Scene;
	class World;

	/**
	 * Este tipo representa una factoría de componentes.
	 */
	typedef SimpleFactory<Component> ComponentsFactory;

	/**
	 * Esta clase representa al gestor de entidades.
	 */
	class EntitiesManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static EntitiesManager * GetInstance() {
			return _instance;
		}

		/**
		 * Obtiene la secuencia de identificadores para entidades.
		 */
		inline IdSequence & getSequence() { return _sequence; }

		/**
		 * Obtiene la factoría de componentes.
		 */
		inline ComponentsFactory & getComponentsFactory() { return _componentsFactory; }

		/**
		 * Obtiene la tabla de descriptores de entidades.
		 */
		inline Blueprints & getBlueprints() { return _blueprints; }

		/**
		 * Obtiene la lista de descriptores de entidades.
		 */
		inline const EntityInfoTableList & getEntitiesInfo() const { return _entitiesInfo; }

		/**
		 * Obtiene los nombres de los atributos en la tabla descriptora de entidades.
		 */
		inline const EntityInfoTableNames * getAttributeNames() const { return _attributeNames; }

		/**
		 * Modifica los nombres de los atributos en la tabla descriptora de entidades.
		 */
		inline void setAttributeNames(const EntityInfoTableNames * value) { _attributeNames = value; }

		/**
		 * Obtiene el mundo actual que estamos gestionando.
		 */
		inline World * getCurrentWorld() { return _currentWorld; }

		/**
		 * Modifica el mundo actual que estamos gestionando.
		 */
		inline void setCurrentWorld(World * value) { _currentWorld = value; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

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
		 * Crea y carga desde un fichero de disco un nuevo mundo o escena lógica.
		 * @param fileName El nombre del fichero a cargar.
		 * @return Devuelve el mundo creado y si falla algo devuelve NULL.
		 */
		World * createWorldFromFile(const std::string & fileName);

		/**
		 * Elimina una escena lógica, desactivándola previamente.
		 * @param world La escena a eliminar.
		 * @remark Este método elimina a la escena de la memoria.
		 */
		void deleteWorld(World *& world);

		/**
		 * Crea e inicializa una nueva entidad en base a un descriptor de entidad que probablemente se
		 * habrá leido del fichero con los datos del mundo. Dicho descriptor indica al gestor de entidades
		 * el tipo de entidad que queremos crear, para buscarlo entre los blueprints.
		 * @param world El mundo lógico al que pertenece la entidad.
		 * @param info La información inicial de la entidad.
		 * @return Devuelve la entidad creada y si falla algo devuelve NULL.
		 */
		Entity * createEntity(World * world, const EntityInfoTable * info);

		/**
		 * Crea, inicializa y activa una nueva entidad en base a un descriptor de entidad.
		 * @param world El mundo lógico al que pertenece la entidad.
		 * @param info La información inicial de la entidad.
		 * @return Devuelve la entidad creada y si falla algo devuelve NULL.
		 */
		Entity * createAndActivateEntity(World * world, const EntityInfoTable * info);

		/**
		 * Elimina una entidad de forma inmediata. Si la entidad estuviera activada la desactiva.
		 * @param entity La entidad a eliminar.
		 * @remark Este método elimina a la entidad de la memoria.
		 */
		void deleteEntity(Entity * entity);

		/**
		 * Añade una entidad a la lista de entidades pendientes de ser borradas.
		 * @param entity La entidad a eliminar.
		 */
		void deferredDeleteEntity(Entity * entity);

		/**
		 * Elimina a todas las entidades que hay en la lista de entidades pendientes de ser borradas.
		 * @remark Este método elimina a las entidades de la memoria.
		 */
		void deleteDeferredEntities();

		/**
		 * Carga e interpreta el contenido de un fichero que describe una escena.
		 * @param fileName El nombre del fichero con la escena.
		 * @param scene La escena gráfica.
		 * @param fatherNode El nodo padre donde va a ir la escena.
		 * @param nodePraefixus El prefijo para los nombres de las entidades gráficas.
		 * @return Devuelve true si se consigue cargar la información con éxito.
		 */
		bool loadXmlScene(const std::string & fileName, Scene * scene,
			GraphicNodeEntity * fatherNode = 0, const std::string & nodePraefixus = "");

		/**
		 * Elimina todos los descriptores de entidad registrados.
		 */
		void cleanEntitiesInfo();

		/**
		 * Carga desde un fichero de disco el mundo actual que estamos gestionando.
		 * @param fileName El nombre del fichero a cargar.
		 * @return Devuelve true si la carga se realiza correctamente.
		 */
		bool loadCurrentWorld(const std::string & fileName);

		/**
		 * Descarga el mundo actual que estamos gestionando.
		 */
		void unloadCurrentWorld();

		/**
		 * Activa el mundo actual que estamos gestionando.
		 * @return Devuelve true si se activa correctamente.
		 */
		bool activateCurrentWorld();

		/**
		 * Desactiva el mundo actual que estamos gestionando.
		 */
		void deactivateCurrentWorld();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~EntitiesManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static EntitiesManager * _instance;

		/**
		 * La secuencia de identificadores para entidades.
		 */
		IdSequence _sequence;

		/**
		 * La factoría de componentes.
		 */
		ComponentsFactory _componentsFactory;

		/**
		 * La tabla de descriptores de entidades.
		 */
		Blueprints _blueprints;

		/**
		 * La lista de entidades pendientes de ser sacrificadas a los dioses del death metal.
		 */
		EntityList _entitiesToSacrifice;

		/**
		 * La lista de descriptores de entidades.
		 */
		EntityInfoTableList _entitiesInfo;

		/**
		 * Los nombres de los atributos en la tabla descriptora de entidades.
		 */
		const EntityInfoTableNames * _attributeNames;

		/**
		 * El gestor de terrenos.
		 */
		TerrainManager * _terrainManager;

		/**
		 * El mundo actual que estamos gestionando.
		 */
		World * _currentWorld;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea una nueva entidad y le añade los componentes que necesita.
		 * @param componentsNames El conjunto con los nombres de todos los componentes.
		 * @return Devuelve la entidad creada y si falla algo devuelve NULL.
		 */
		Entity * assembleEntity(const EntityInfoTable::StringSet & componentsNames);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		EntitiesManager() : _attributeNames(0), _terrainManager(0), _currentWorld(0) {}
	};
}

#endif
