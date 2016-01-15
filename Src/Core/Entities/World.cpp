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

#include "Core/Entities/World.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/Component.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Graphics/Scene.h"
#include "Core/Graphics/GraphicsManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	Entity * World::getEntityById(Core::IdType entityId) {
		EntityIdTableIterator victim = _entitiesById.find(entityId);
		return (victim != _entitiesById.end()) ? victim->second : 0;
	}

	//--------------------------------------------------------------------------------------------------------

	Entity * World::getEntityByName(const std::string & entityName, Entity * start) {
		// Primero buscamos la lista de entidades con un nombre determinado.
		EntityStringTableIterator i = _entitiesByName.find(entityName);
		if(i != _entitiesByName.end()) {
			// Si hay alguna lista obtenemos los iteradores de inicio y final.
			EntityListIterator j = i->second.begin();
			EntityListIterator end = i->second.end();
			// En caso de pasarle una entidad como punto de partida, recorreremos la lista para encontrar
			// dicha entidad y poner al iterador de inicio en el lugar correcto.
			if(start) {
				for(; j != end; ++j) {
					// Para encontrar la entidad comprobamos que tenga el mismo identificador único.
					if((*j)->getEntityId() == start->getEntityId()) {
						// Si es la que buscábamos, pasamos a la siguiente posición y salimos del bucle.
						++j;
						break;
					}
				}
			}
			// En caso de no haber sobrepasado el final, devolvemos el elemento actual de la lista.
			if(j != end) {
				return (*j);
			}
		}
		return 0;
	}

	//--------------------------------------------------------------------------------------------------------

	EntityListIterator World::getEntitiesByNameBegin(const std::string & entityName) {
		EntityStringTableIterator victim = _entitiesByName.find(entityName);
		if(victim != _entitiesByName.end()) {
			return victim->second.begin();
		} else {
			throw std::exception("World::getEntitiesByNameBegin => Invalid table key...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	EntityListIterator World::getEntitiesByNameEnd(const std::string & entityName) {
		EntityStringTableIterator victim = _entitiesByName.find(entityName);
		if(victim != _entitiesByName.end()) {
			return victim->second.end();
		} else {
			throw std::exception("World::getEntitiesByNameEnd => Invalid table key...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	EntityListIterator World::getEntitiesByTypeBegin(const std::string & entityType) {
		EntityStringTableIterator victim = _entitiesByType.find(entityType);
		if(victim != _entitiesByType.end()) {
			return victim->second.begin();
		} else {
			throw std::exception("World::getEntitiesByTypeBegin => Invalid table key...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	EntityListIterator World::getEntitiesByTypeEnd(const std::string & entityType) {
		EntityStringTableIterator victim = _entitiesByType.find(entityType);
		if(victim != _entitiesByType.end()) {
			return victim->second.end();
		} else {
			throw std::exception("World::getEntitiesByTypeEnd => Invalid table key...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool World::existsEntitiesByName(const std::string & entityName) {
		return _entitiesByName.find(entityName) != _entitiesByName.end();
	}

	//--------------------------------------------------------------------------------------------------------

	bool World::existsEntitiesByType(const std::string & entityType) {
		return _entitiesByType.find(entityType) != _entitiesByType.end();
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool World::activate() {
		// Ponemos la escena del mundo como escena actual del gestor del motor gráfico.
		GraphicsManager::GetInstance()->changeCurrentScene(_scene);

		// Activamos todas las entidades que han sido registradas en el mundo.
		EntityIdTableIterator i = _entitiesById.begin();
		EntityIdTableIterator end = _entitiesById.end();
		for(; i != end; ++i) {
			if(!i->second->activate()) return false;
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void World::deactivate() {
		// Desactivamos todas las entidades que han sido registradas en el mundo.
		EntityIdTableIterator i = _entitiesById.begin();
		EntityIdTableIterator end = _entitiesById.end();
		for(; i != end; ++i) {
			if(i->second->isActivated()) {
				i->second->deactivate();
			}
		}

		// Quitamos la escena del mundo como escena actual del gestor del motor gráfico.
		GraphicsManager::GetInstance()->changeCurrentScene(0);
	}

	//--------------------------------------------------------------------------------------------------------

	void World::prepareUpdate(unsigned int lastInterval) {
		// Actualizamos todas las entidades que han sido registradas en el mundo.
		EntityIdTableIterator i = _entitiesById.begin();
		EntityIdTableIterator end = _entitiesById.end();
		for(; i != end; ++i) {
			i->second->prepareUpdate(lastInterval);
		}
	}
	
	//--------------------------------------------------------------------------------------------------------

	void World::update(unsigned int lastInterval) {
		// Actualizamos todas las entidades que han sido registradas en el mundo.
		EntityIdTableIterator i = _entitiesById.begin();
		EntityIdTableIterator end = _entitiesById.end();
		for(; i != end; ++i) {
			i->second->update(lastInterval);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool World::sendMessage(SmartMessage & message, Component * sender) {
		bool anyReceiver = false;
		if(message->getEntityTargetType()) {
			// Intentamos conseguir una lista con todas las entidades que comparten un tipo determinado.
			std::string targetType(message->getEntityTargetType());
			EntityStringTableIterator victim = _entitiesByType.find(targetType);
			if(victim != _entitiesByType.end()) {
				EntityListIterator i = victim->second.begin();
				EntityListIterator end = victim->second.end();
				if(message->getEntityTargetName()) {
					// Mandamos el mensaje a todas las entidades con un tipo y nombre determinado.
					std::string targetName(message->getEntityTargetName());
					for(; i != end; ++i) {
						if((*i)->getName() == targetName) {
							anyReceiver = (*i)->sendMessage(message, sender) || anyReceiver;
						}
					}
				} else {
					// Mandamos el mensaje a todas las entidades con un tipo determinado.
					for(; i != end; ++i) {
						anyReceiver = (*i)->sendMessage(message, sender) || anyReceiver;
					}
				}
			}

		} else if(message->getEntityTargetName()) {
			// Intentamos conseguir una lista con todas las entidades que comparten un nombre determinado.
			std::string targetName(message->getEntityTargetName());
			EntityStringTableIterator victim = _entitiesByName.find(targetName);
			if(victim != _entitiesByName.end()) {
				// Mandamos el mensaje a todas las entidades con un nombre determinado.
				EntityListIterator i = victim->second.begin();
				EntityListIterator end = victim->second.end();
				for(; i != end; ++i) {
					anyReceiver = (*i)->sendMessage(message, sender) || anyReceiver;
				}
			}

		} else {
			// Mandamos el mensaje a todas las entidades que han sido registradas.
			EntityIdTableIterator i = _entitiesById.begin();
			EntityIdTableIterator end = _entitiesById.end();
			for(; i != end; ++i) {
				anyReceiver = i->second->sendMessage(message, sender) || anyReceiver;
			}
		}
		return anyReceiver;
	}

	//--------------------------------------------------------------------------------------------------------

	void World::addEntity(Entity * entity) {
		// Comprobamos que la entidad no haya sido añadida ya al mundo.
		if(entity && _entitiesById.count(entity->getEntityId()) == 0) {
			// Añadimos la entidad a la tabla maestra del mundo.
			_entitiesById[entity->getEntityId()] = entity;
			// Añadimos la entidad a la tabla organizada por nombres.
			addEntityToStringTable(entity, _entitiesByName, entity->getName());
			// Añadimos la entidad a la tabla organizada por tipos.
			addEntityToStringTable(entity, _entitiesByType, entity->getType());
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void World::removeEntity(Entity * entity) {
		// Comprobamos que la entidad haya sido añadida al mundo.
		if(entity && _entitiesById.count(entity->getEntityId()) != 0) {
			// Desactivamos la entidad y eliminamos la referencia al mundo.
			if(entity->isActivated()) entity->deactivate();
			entity->_world = 0;
			// Eliminamos las referencias a la entidad desde las tablas y listas del mundo.
			_entitiesById.erase(entity->getEntityId());
			removeEntityFromStringTable(entity, _entitiesByName, entity->getName());
			removeEntityFromStringTable(entity, _entitiesByType, entity->getType());
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void World::removeAllEntities() {
		// Obtenemos la referencia al gestor de entidades.
		EntitiesManager * entitiesManager = EntitiesManager::GetInstance();

		// Recorremos todas las entidades actualmente registradas.
		EntityIdTableIterator i = _entitiesById.begin();
		EntityIdTableIterator end = _entitiesById.end();
		Entity * victim = 0;
		while(i != end) {
			// Por cada entidad que encontremos llamamos al gestor de entidades para borrarla.
			victim = i->second;
			++i;
			entitiesManager->deleteEntity(victim);
		}

		// Borramos las tablas actuales.
		_entitiesById.clear();
		_entitiesByName.clear();
		_entitiesByType.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	void World::addEntityToStringTable(Entity * entity, EntityStringTable & table, const std::string & key) {
		// Probamos ver si la clave existe en la tabla.
		EntityStringTableIterator i = table.find(key);
		if(i == table.end()) {
			// Si no existe entrada para esa clave, creamos una nueva lista y la añadimos.
			EntityList aux;
			aux.push_back(entity);
			table[key] = aux;
		} else {
			// Si existe la entrada, añadimos la entidad al final de la lista.
			i->second.push_back(entity);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void World::removeEntityFromStringTable(Entity * entity, EntityStringTable & table, const std::string & key) {
		// Probamos ver si la clave existe en la tabla.
		EntityStringTableIterator i = table.find(key);
		if(i != table.end()) {
			// Si existe la entrada, eliminamos la entidad de la lista.
			i->second.remove(entity);
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	World::World(const std::string & name) : _name(name) {
		_scene = GraphicsManager::GetInstance()->createScene(name);
	}

	//--------------------------------------------------------------------------------------------------------

	World::~World() {
		removeAllEntities();
		GraphicsManager::GetInstance()->removeScene(_scene);
	}
}
