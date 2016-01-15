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

#include <assert.h>

#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/LoadingSections.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"
#include "Core/Graphics/TerrainManager.h"
#include "Core/Resources/LoadingObserver.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Core/XML/XmlSceneLoader.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Constantes
	//********************************************************************************************************

	const EntityInfoTableNames DefaultEntityInfoTableNames;

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	EntitiesManager * EntitiesManager::_instance = new EntitiesManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool EntitiesManager::initialize() {
		// Asignamos los nombres por defecto de los atributos en la tabla descriptora de entidades.
		if(!_attributeNames) _attributeNames = &DefaultEntityInfoTableNames;
		// Obtenemos e inicializamos el gestor de terrenos.
		_terrainManager = TerrainManager::GetInstance();
		_terrainManager->initialize();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::release() {
		// Descargamos el mundo actual que estamos gestionando.
		unloadCurrentWorld();
		// Reseteamos la secuencia de identificadores para entidades.
		_sequence.reset();
		// Borramos las listas y tablas de datos del gestor.
		_componentsFactory.clear();
		_blueprints.clear();
		_entitiesToSacrifice.clear();
		// Liberamos el gestor de terrenos.
		_terrainManager->release();
	}

	//--------------------------------------------------------------------------------------------------------

	World * EntitiesManager::createWorldFromFile(const std::string & fileName) {
		// Creamos la escena lógica donde se van a almacenar las entidades.
		World * world = new World(fileName);

		// Mandamos cargar el fichero xml con la escena.
		if(!loadXmlScene(fileName, world->getScene())) {
			assert(!"EntitiesManager::createWorldFromFile -> Can't load the xml scene...");
			return 0;
		}

		// Configuramos la sección en el proceso de carga que tiene que ver con la creación de entidades.
		LoadingObserver * loadingObserver = LoadingObserver::GetInstance();
		loadingObserver->setNumberOfOperations(LOADING_SECTION_ENTITIES, _entitiesInfo.size());

		// Recorremos la lista de descriptores de entidades recién cargada.
		EntityInfoTableList::const_iterator i = _entitiesInfo.begin();
		EntityInfoTableList::const_iterator end = _entitiesInfo.end();
		Entity * entity = 0;
		for(; i != end; ++i) {
			// Por cada descriptor específico mandamos crear una entidad.
			entity = createEntity(world, *i);
			assert(entity && "EntitiesManager::createWorldFromFile -> Can't create the entity...");
			loadingObserver->operationFinished();
		}

		// Y finalmente devolvemos la escena lógica.
		return world;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::deleteWorld(World *& world) {
		if(world) {
			world->deactivate();
			delete world;
			world = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	Entity * EntitiesManager::createEntity(World * world, const EntityInfoTable * info) {
		assert(world && info && "EntitiesManager::createEntity -> Invalid NULL parameters...");
		// Buscamos el descriptor del tipo de la entidad.
		const EntityInfoTable * fatherInfo = _blueprints.get(info->getType());
		if(fatherInfo) {
			// Una vez encontrado, añadimos el descriptor general al recibido desde el fichero.
			EntityInfoTable * completeInfo = const_cast<EntityInfoTable *>(info);
			completeInfo->setSuperInfoTable(fatherInfo);
			// Mandamso crear una entidad con una serie de componentes.
			Entity * victim = assembleEntity(completeInfo->getAllComponents());
			// Si se ha creado una entidad y no se logra inicializar correctamente la borramos.
			if(victim && !victim->spawn(world, completeInfo)) {
				delete victim;
			} else {
				// Si no se crea o se crea y se inicializa correctamente, se devuelve.
				return victim;
			}
		}
		return 0;
	}

	//--------------------------------------------------------------------------------------------------------

	Entity * EntitiesManager::createAndActivateEntity(World * world, const EntityInfoTable * info) {
		Entity * victim = createEntity(world, info);
		if(victim) victim->activate();
		return victim;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::deleteEntity(Entity * entity) {
		assert(entity && "EntitiesManager::deleteEntity -> Invalid NULL entity...");
		// Si la entidad está asociada a un mundo, habrá que desactivarla y eliminarla de dicho mundo.
		World * world = entity->getWorld();
		if(world) world->removeEntity(entity);
		// Finalmente borramos de la memoria la entidad.
		delete entity;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::deferredDeleteEntity(Entity * entity) {
		assert(entity && "EntitiesManager::deferredDeleteEntity -> Invalid NULL entity...");
		_entitiesToSacrifice.push_back(entity);
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::deleteDeferredEntities() {
		// Recorremos todas las entidades pendientes de ser borradas.
		EntityList::iterator i = _entitiesToSacrifice.begin();
		EntityList::iterator end = _entitiesToSacrifice.end();
		Entity * victim = 0;
		while(i != end) {
			// Guardamos la entidad actual para pasar al nodo siguiente.
			victim = *i;
			++i;
			// Y mandamos borrar la entidad actual.
			deleteEntity(victim);
		}
		// Finalmente borramos la lista.
		_entitiesToSacrifice.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	Entity * EntitiesManager::assembleEntity(const EntityInfoTable::StringSet & componentsNames) {
		// Primero creamos una nueva entidad, asignándole el siguiente identificador único.
		Entity * victim = new Entity(_sequence.getNextId());
		if(victim) {
			// Recorremos todo el conjunto de nombres.
			EntityInfoTable::StringSet::const_iterator i = componentsNames.begin();
			EntityInfoTable::StringSet::const_iterator end = componentsNames.end();
			Component * aux = 0;
			for(; i != end; ++i) {
				// Por cada nombre, comprobamos si existe en la factoría de componentes.
				if(_componentsFactory.contains(*i)) {
					// Si existe intentamos crear un componente del tipo indicado.
					aux = _componentsFactory.create(*i);
					// Si se logra crear el componente, lo añadimos a la entidad.
					if(aux) victim->addComponent(aux);
				} else {
					// Si no existe el nombre borramos la entidad y devolvemos NULL.
					assert("EntitiesManager::assembleEntity -> Invalid component name...");
					delete victim;
					return 0;
				}
			}
		}
		// Finalmente devolvemos la entidad haya sido creada o no.
		return victim;
	}

	//--------------------------------------------------------------------------------------------------------

	bool EntitiesManager::loadXmlScene(const std::string & fileName, Scene * scene, GraphicNodeEntity * fatherNode, const std::string & nodePraefixus) {
		XmlSceneLoader loader(&_entitiesInfo, _attributeNames);
		return loader.parse(fileName, scene, fatherNode, nodePraefixus);
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::cleanEntitiesInfo() {
		EntityInfoTableList::iterator i = _entitiesInfo.begin();
		EntityInfoTableList::iterator end = _entitiesInfo.end();
		EntityInfoTableList::iterator victim;
		while(i != end) {
			victim = i++;
			delete (*victim);
			_entitiesInfo.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool EntitiesManager::loadCurrentWorld(const std::string & fileName) {
		_currentWorld = createWorldFromFile(fileName);
		return _currentWorld != 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::unloadCurrentWorld() {
		_terrainManager->removeAllTerrains();
		deleteWorld(_currentWorld);
	}

	//--------------------------------------------------------------------------------------------------------

	bool EntitiesManager::activateCurrentWorld() {
		return _currentWorld ? _currentWorld->activate() : false;
	}

	//--------------------------------------------------------------------------------------------------------

	void EntitiesManager::deactivateCurrentWorld() {
		if(_currentWorld) _currentWorld->deactivate();
	}
}
