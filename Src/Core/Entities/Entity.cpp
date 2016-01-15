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
#include <algorithm>

#include "Core/Entities/Entity.h"
#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Component.h"
#include "Core/Entities/World.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	inline bool EntityUtilExistsNameInList(const StringList & victimList, const std::string & victimValue) {
		StringList::const_iterator i = victimList.begin();
		StringList::const_iterator end = victimList.end();
		StringList::const_iterator aux = std::find(i, end, victimValue);
		return aux != end;
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool Entity::sendMessage(SmartMessage & message, Component * sender) {
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		bool anyReceiver = false;
		// Primero comprobamos si el mensaje es para un tipo determinado de componente.
		if(message->getComponentTargetName()) {
			// Recorremos todos los componentes disponibles para ser actualizados, buscando un
			// componente del tipo objetivo del mensaje para añadírselo.
			std::string componentTargetName(message->getComponentTargetName());
			for(; i != end; ++i) {
				if(sender != (*i) && (*i)->getName() == componentTargetName) {
					return (*i)->addMessage(message);
				}
			}
		} else {
			// Recorremos todos los componentes disponibles para ser actualizados, buscando todo
			// componente distinto del componente emisor para añadirle el mensaje.
			for(; i != end; ++i) {
				if(sender != (*i)) {
					anyReceiver = (*i)->addMessage(message) || anyReceiver;
				}
			}
		}
		// Devolvemos si algún componente han recibido el mensaje.
		return anyReceiver;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::sleepComponent(const std::string & name, bool clearMessages) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		while(i != end) {
			// Comprobamos si el componente actual es el que estamos buscando.
			if((*i)->getName() == name) {
				// Si es el que estamos buscando lo borramos de la lista de componentes actualizables,
				// comprobando antes si hemos de borrar los mensajes pendientes en el componente.
				if(clearMessages) {
					(*i)->clearMessages();
				}
				_updateableComponents.erase(i);
				return true;
			} else {
				// Si no es el que estamos buscando, pasamos al siguiente componente.
				++i;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::awakeComponent(const std::string & name) {
		// Comprobamos que el componente no esté despierto.
		if(!isAwakeComponent(name)) {
			// Si no lo está, buscamos en la tabla de componentes el que buscamos.
			ComponentTable::iterator victim = _components.find(name);
			// Si no se encuentra ninguna víctima, devolvemos que la operación ha fallado.
			if(victim == _components.end()) return false;
			// Si se ha encontrado la víctima, la añadimos a la lista de componentes actualizables.
			addToUpdateableComponents(victim->second);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::isAwakeComponent(const std::string & name) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		for(; i != end; ++i) {
			// Comprobamos si el componente actual es el que estamos buscando.
			if((*i)->getName() == name) {
				return true;
			}
		}
		// Si no hemos encontrado el componente que buscábamos, devolveremos falso como respuesta.
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::sleepComponents(const StringList & names, bool clearMessages) {
		// Recorremos todos los nombres disponibles en la lista.
		StringList::const_iterator i = names.begin();
		StringList::const_iterator end = names.end();
		bool allSleep = true;
		for(; i != end; ++i) {
			// Comprobamos que el componente esté despierto.
			if(isAwakeComponent(*i)) {
				// Intentamos dormir al componente con el mismo nombre.
				allSleep = sleepComponent(*i, clearMessages) && allSleep;
			}
		}
		return allSleep;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::awakeComponents(const StringList & names) {
		// Recorremos todos los nombres disponibles en la lista.
		StringList::const_iterator i = names.begin();
		StringList::const_iterator end = names.end();
		bool allAwake = true;
		for(; i != end; ++i) {
			// Intentamos despertar al componente con el mismo nombre.
			allAwake = awakeComponent(*i) && allAwake;
		}
		return allAwake;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::sleepAllComponentsExcept(const StringList & names, bool clearMessages) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		ComponentList::iterator victim;
		while(i != end) {
			// Comprobamos si el componente actual no está en la lista.
			if(!EntityUtilExistsNameInList(names, (*i)->getName())) {
				// Cogemos el nodo actual y lo borramos de la lista de componentes actualizables,
				// comprobando antes si hemos de borrar los mensajes pendientes en el componente.
				victim = i++;
				if(clearMessages) {
					(*victim)->clearMessages();
				}
				_updateableComponents.erase(victim);
			} else {
				// Si está en la lista, pasamos al siguiente componente.
				++i;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::awakeAllComponentsExcept(const StringList & names) {
		// Recorremos todos los componentes añadidos a la entidad.
		ComponentTable::iterator i = _components.begin();
		ComponentTable::iterator end = _components.end();
		bool allAwake = true;
		for(; i != end; ++i) {
			// Comprobamos si el componente actual no está en la lista.
			if(!EntityUtilExistsNameInList(names, i->first)) {
				// Intentamos despertar al componente, esté o no dormido.
				allAwake = awakeComponent(i->first) && allAwake;
			}
		}
		return allAwake;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::sleepAllComponents(bool clearMessages) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		ComponentList::iterator victim;
		while(i != end) {
			// Cogemos el nodo actual y lo borramos de la lista de componentes actualizables,
			// comprobando antes si hemos de borrar los mensajes pendientes en el componente.
			victim = i++;
			if(clearMessages) {
				(*victim)->clearMessages();
			}
			_updateableComponents.erase(victim);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::awakeAllComponents() {
		// Recorremos todos los componentes añadidos a la entidad.
		ComponentTable::iterator i = _components.begin();
		ComponentTable::iterator end = _components.end();
		bool allAwake = true;
		for(; i != end; ++i) {
			// Intentamos despertar al componente, esté o no dormido.
			allAwake = awakeComponent(i->first) && allAwake;
		}
		return allAwake;
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::sortUpdateableComponents() {
		_updateableComponents.sort(&(Entity::componentPriorityComparer));
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::removeComponent(const std::string & component) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		ComponentList::iterator victim;
		while(i != end) {
			victim = i++;
			// Comprobamos si el componente actual es el que estamos buscando.
			if((*victim)->getName() == component) {
				_updateableComponents.erase(victim);
			}
		}

		// Buscamos el componente dento de la tabla de la entidad.
		ComponentTable::iterator victim2 = _components.find(component);
		if(victim2 != _components.end()) {
			// Si se encuentra alguno se borra y se elimina de la tabla.
			victim2->second->setOwner(0);
			victim2->second->deactivate();
			delete victim2->second;
			_components.erase(victim2);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::addToUpdateableComponents(Component * victim) {
		assert(victim && "Entity::addToUpdateableComponents -> Invalid NULL component...");
		// Recorremos todos los componentes disponibles para buscar donde insertar el componente.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		for(; i != end; ++i) {
			// Comprobamos que el nodo actual tenga una prioridad menor o igual, para insertar el componente.
			if((*i)->getPriority() <= victim->getPriority()) {
				// Insertamos el componente y salimos del método.
				_updateableComponents.insert(i, victim);
				return;
			}
		}
		// En caso de haber llegado al final de la lista, lo añadimos al final.
		_updateableComponents.push_back(victim);
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::addComponent(Component * component) {
		assert(component && "Entity::addComponent -> Invalid NULL component...");
		_components[component->getName()] = component;
		component->setOwner(this);
		addToUpdateableComponents(component);
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::removeComponent(Component * component) {
		assert(component && "Entity::removeComponent -> Invalid NULL component...");
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		ComponentList::iterator victim;
		while(i != end) {
			victim = i++;
			// Comprobamos si el componente actual es el que estamos buscando.
			if((*victim)->getName() == component->getName()) {
				_updateableComponents.erase(victim);
			}
		}

		// Buscamos el componente dento de la tabla de la entidad.
		ComponentTable::iterator victim2 = _components.find(component->getName());
		if(victim2 != _components.end()) {
			// Si se encuentra alguno se quita su entidad dueña y se elimina de la tabla.
			component->setOwner(0);
			_components.erase(victim2);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::removeAllComponents() {
		assert(!_activated && "Entity::removeAllComponents -> The entity must be deactivated before remove any component...");
		// Recorremos todos los componentes añadidos a la entidad.
		ComponentTable::iterator i = _components.begin();
		ComponentTable::iterator end = _components.end();
		ComponentTable::iterator victim;
		while(i != end) {
			// Por cada componente, lo borramos de la memoria el componente.
			victim = i++;
			delete victim->second;
			// Después de borrarlo de la memoria, lo borramos de la tabla.
			_components.erase(victim);
		}

		// Y por último borramos la lista de componentes disponibles para ser actualizados.
		_updateableComponents.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::spawn(World * world, const EntityInfoTable * info) {
		// Configuramos las propiedades comunes de toda entidad.
		_world = world;
		_worldEntityInfo = info;
		_name = _worldEntityInfo->getName();
		_type = _worldEntityInfo->getType();

		// Añadimos la entidad al mundo. No se puede añadir antes de haber configurado el nombre y el tipo
		// de la entidad, porque el mundo los necesita para poder ubicar correctamente en las tablas internas.
		_world->addEntity(this);

		// Recorremos todos los componentes añadidos a la entidad.
		ComponentTable::iterator i = _components.begin();
		ComponentTable::iterator end = _components.end();
		bool correct = true;
		for(; correct && i != end; ++i) {
			// Inicializamos el componente actual.
			correct = correct && i->second->spawn(_worldEntityInfo);
		}

		// Si la inicialización de algún componente falla, borramos la entidad del mundo.
		if(!correct) {
			_world->removeEntity(this);
		}

		// Ordenamos la lista de componentes disponibles para ser actualizados en base a la prioridad, para
		// cubrir el caso de que se haya alterado la prioridad de los componentes tras la inicialización.
		sortUpdateableComponents();

		// Y finalmente devolvemos el resultado de la inicialización de la entidad.
		return correct;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::activate() {
		// Marcamos como activada la entidad a la espera de comprobar que todos los componentes
		// que han sido añadidos, también se activen correctamente.
		_activated = true;

		// Recorremos todos los componentes añadidos a la entidad.
		ComponentTable::iterator i = _components.begin();
		ComponentTable::iterator end = _components.end();
		for(; _activated && i != end; ++i) {
			// Activamos el componente actual.
			_activated = _activated && i->second->activate();
		}

		// Y finalmente devolvemos si la entidad se ha podido activar correctamente.
		return _activated;
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::deactivate() {
		// Recorremos todos los componentes añadidos a la entidad.
		ComponentTable::iterator i = _components.begin();
		ComponentTable::iterator end = _components.end();
		for(; i != end; ++i) {
			// Desactivamos el componente actual.
			i->second->deactivate();
		}
		// Y finalmente marcamos como desactivada la entidad.
		_activated = false;
	}

	//--------------------------------------------------------------------------------------------------------

	void Entity::prepareUpdate(unsigned int lastInterval) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		for(; i != end; ++i) {
			// Preparamos la actualización del componente actual.
			(*i)->prepareUpdate(lastInterval);
		}
	}
	
	//--------------------------------------------------------------------------------------------------------

	void Entity::update(unsigned int lastInterval) {
		// Recorremos todos los componentes disponibles para ser actualizados.
		ComponentList::iterator i = _updateableComponents.begin();
		ComponentList::iterator end = _updateableComponents.end();
		for(; i != end; ++i) {
			// Actualizamos el componente actual.
			(*i)->update(lastInterval);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool Entity::componentPriorityComparer(Component * left, Component * right) {
		return left->getPriority() > right->getPriority();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Entity::Entity(IdType entityId) : _entityId(entityId), _name(""), _type(""), _world(0), _worldEntityInfo(0), _activated(false) {
		assert(entityId != ID_TYPE_UNASSIGNED && "Entity::Entity -> Invalid entity ID...");
	}

	//--------------------------------------------------------------------------------------------------------

	Entity::Entity(const Entity & obj) {
		_entityId = obj._entityId;
		_name = obj._name;
		_type = obj._type;
		_world = obj._world;
		_worldEntityInfo = obj._worldEntityInfo;
		_components = obj._components;
		_updateableComponents = obj._updateableComponents;
		_activated = obj._activated;
	}

	//--------------------------------------------------------------------------------------------------------

	Entity::~Entity() {
		assert(!_world && "Entity::~Entity -> Please, remove the entity from the world first...");
		removeAllComponents();
	}
}
