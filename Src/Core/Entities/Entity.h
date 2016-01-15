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

#ifndef __CORE_ENTITY_H__
#define __CORE_ENTITY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Math.h"
#include "Core/IdType.h"
#include "Core/Types/StdTypes.h"
#include "Core/Types/EntitiesTypes.h"
#include "Core/Entities/Message.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntityInfoTable;
	class EntitiesManager;
	class Component;
	class World;

	/**
	 * Esta clase representa una entidad genérica que formará parte del juego.
	 */
	class Entity {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el identificador único de la entidad.
		 */
		inline IdType getEntityId() const { return _entityId; }

		/**
		 * Obtiene el nombre de la entidad.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene el tipo de la entidad.
		 */
		inline const std::string & getType() const { return _type; }

		/**
		 * Obtiene el mundo al que pertenece la entidad.
		 */
		inline World * getWorld() { return _world; }

		/**
		 * Obtiene el mundo al que pertenece la entidad.
		 */
		inline const World * getWorld() const { return _world; }

		/**
		 * Obtiene la tabla con información inicial de la entidad.
		 */
		inline const EntityInfoTable * getInfo() const { return _worldEntityInfo; }

		/**
		 * Obtiene el flag que indica si la entidad está activada o no.
		 */
		inline bool isActivated() const { return _activated; }

		/**
		 * Obtiene un componente de la entidad.
		 */
		template<class T>
		T * getComponentAs(const std::string & name) {
			ComponentTable::iterator c = _components.find(name);
			return (c != _components.end()) ? dynamic_cast<T *>(c->second) : 0;
		}

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Envia un mensaje a todos los componentes de la entidad.
		 * @param message El mensaje que va a ser enviado a todos los componentes.
		 * @param sender El componente que envia el mensaje.
		 * @return Da true si el mensaje ha sido admitido por algún componente.
		 */
		bool sendMessage(SmartMessage & message, Component * sender = 0);

		/**
		 * Duerme a un componente para que no se pueda actualizar.
		 * @param name El nombre del componente.
		 * @param clearMessages Flag para indicar si los mensajes pendientes deben ser borrados.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool sleepComponent(const std::string & name, bool clearMessages = true);

		/**
		 * Despierta a un componente para que pueda volver a actualizarse.
		 * @param name El nombre del componente.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool awakeComponent(const std::string & name);

		/**
		 * Comprueba si un componente está despierto para que pueda volver a actualizarse.
		 * @param name El nombre del componente.
		 * @return Devuelve true si el componente está despierto.
		 */
		bool isAwakeComponent(const std::string & name);

		/**
		 * Duerme a una lista de componentes para que no se puedan actualizar.
		 * @param names La lista de nombres de componentes a dormir.
		 * @param clearMessages Flag para indicar si los mensajes pendientes deben ser borrados.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool sleepComponents(const StringList & names, bool clearMessages = true);

		/**
		 * Despierta a una lista de componentes para que puedan volver a actualizarse.
		 * @param names La lista de nombres de componentes a despertar.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool awakeComponents(const StringList & names);

		/**
		 * Duerme a todos los componentes, salvo los indicados en una lista determinada,
		 * para que no se puedan volver a actualizar.
		 * @param names La lista de nombres de componentes que no se van a dormir.
		 * @param clearMessages Flag para indicar si los mensajes pendientes deben ser borrados.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool sleepAllComponentsExcept(const StringList & names, bool clearMessages = true);

		/**
		 * Despierta a todos los componentes, salvo los indicados en una lista determinada,
		 * para que no se puedan volver a actualizar.
		 * @param names La lista de nombres de componentes que no se van a despertar.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool awakeAllComponentsExcept(const StringList & names);

		/**
		 * Duerme a todos los componentes para que no se puedan volver a actualizar.
		 * @param clearMessages Flag para indicar si los mensajes pendientes deben ser borrados.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool sleepAllComponents(bool clearMessages = true);

		/**
		 * Despierta todos los componentes para que puedan volver a actualizarse.
		 * @return Devuelve true si la operación se realiza correctamente.
		 */
		bool awakeAllComponents();

		/**
		 * Ordena la lista de componentes disponibles para ser actualizados en base a la prioridad.
		 * @remark Se ordena de mayor a menor, siendo la prioridad más baja el 0.
		 */
		void sortUpdateableComponents();

		/**
		 * Elimina un componente de la entidad.
		 * @param component El nombre del componente a eliminar.
		 * @remark Este método borra de la memoria y desactiva al componente.
		 */
		void removeComponent(const std::string & component);

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El identificador único de la entidad.
		 */
		IdType _entityId;

		/**
		 * El nombre de la entidad.
		 */
		std::string _name;

		/**
		 * El tipo de la entidad.
		 */
		std::string _type;

		/**
		 * El mundo al que pertenece la entidad.
		 */
		World * _world;

		/**
		 * La tabla con información inicial de la entidad.
		 */
		const EntityInfoTable * _worldEntityInfo;

		/**
		 * La tabla de componentes.
		 */
		ComponentTable _components;

		/**
		 * La lista de componentes disponibles para ser actualizados.
		 */
		ComponentList _updateableComponents;

		/**
		 * El flag que indica si la entidad está activada o no.
		 */
		bool _activated;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade un componente a la lista de componentes disponibles para ser actualizados, de forma
		 * ordenada en base a la prioridad del componente.
		 * @param victim El componente a añadir.
		 * @remark No utilizar este método fuera de Entity.
		 */
		void addToUpdateableComponents(Component * victim);

		/**
		 * Añade un componente a la entidad.
		 * @param component El componente a añadir.
		 */
		void addComponent(Component * component);

		/**
		 * Elimina un componente de la entidad.
		 * @param component El componente a eliminar.
		 * @remark Este método ni borra de la memoria, ni desactiva al componente.
		 */
		void removeComponent(Component * component);

		/**
		 * Elimina todos los componentes de la entidad.
		 * @remark Este método borra de la memoria los componentes de la entidad.
		 */
		void removeAllComponents();

		/**
		 * Inicializa la entidad y la añade al mundo.
		 * @param world El mundo lógico al que pertenece la entidad.
		 * @param info La información inicial de la entidad.
		 * @return Devuelve true si se inicializa correctamente.
		 */
		bool spawn(World * world, const EntityInfoTable * info);

		/**
		 * Activa la entidad.
		 * @return Devuelve true si se activa correctamente.
		 */
		bool activate();

		/**
		 * Desactiva la entidad.
		 */
		void deactivate();

		/**
		 * Prepara la entidad para la futura actualización de la lógica interna.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		void prepareUpdate(unsigned int lastInterval);

		/**
		 * Actualiza la lógica interna de la entidad.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		void update(unsigned int lastInterval);

		/**
		 * Compara dos componentes en base a su prioridad, para poder ordenarlos de mayor a menor.
		 * @param left El elemento a la derecha de la comparación.
		 * @param right El elemento a la izquierda de la comparación.
		 * @return Devuelve true cuando left > right.
		 */
		static bool componentPriorityComparer(Component * left, Component * right);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param entityId El identificador único de la entidad.
		 * @remark Para crear un objeto Entity se debe hacer desde EntitiesManager.
		 */
		Entity(IdType entityId);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 * @remark Para crear un objeto Entity se debe hacer desde EntitiesManager.
		 */
		Entity(const Entity & obj);

		/**
		 * Destructor del objeto.
		 * @remark Para destruir un objeto Entity se debe hacer desde EntitiesManager.
		 */
		virtual ~Entity();

		friend class Core::EntitiesManager;
		friend class Core::World;
	};
}

#endif
