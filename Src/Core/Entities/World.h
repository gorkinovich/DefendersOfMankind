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

#ifndef __CORE_WORLD_H__
#define __CORE_WORLD_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/IdType.h"
#include "Core/Types/EntitiesTypes.h"
#include "Core/Entities/Message.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntitiesManager;
	class Component;
	class Entity;
	class Scene;

	/**
	 * Esta clase representa un mundo, que es una escena lógica con la que poder trabajar el juego.
	 * @remarks Solo el gestor de entidades puede crear y destruir mundos.
	 */
	class World {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre del escenario.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene la escena gráfica donde está la representación visual del mundo.
		 */
		inline Scene * getScene() { return _scene; }

		/**
		 * Obtiene una entidad en base a su identificador único.
		 */
		Entity * getEntityById(Core::IdType entityId);

		/**
		 * Obtiene una entidad en base a su nombre.
		 * @remark El parámetro start sirve para en caso de haber varias entidades con el mismo nombre
		 *         devolver la siguiente que se encuentre después de la indicada en el parámetro.
		 */
		Entity * getEntityByName(const std::string & entityName, Entity * start = 0);

		/**
		 * Obtiene el iterador de inicio de la tabla de entidades.
		 */
		inline EntityIdTableIterator getEntitiesBegin() { return _entitiesById.begin(); }

		/**
		 * Obtiene el iterador final de la tabla de entidades.
		 */
		inline EntityIdTableIterator getEntitiesEnd() { return _entitiesById.end(); }

		/**
		 * Obtiene el iterador de inicio de la lista de entidades en base a su nombre.
		 */
		EntityListIterator getEntitiesByNameBegin(const std::string & entityName);

		/**
		 * Obtiene el iterador final de la lista de entidades en base a su nombre.
		 */
		EntityListIterator getEntitiesByNameEnd(const std::string & entityName);

		/**
		 * Obtiene el iterador de inicio de la lista de entidades en base a su tipo.
		 */
		EntityListIterator getEntitiesByTypeBegin(const std::string & entityType);

		/**
		 * Obtiene el iterador final de la lista de entidades en base a su tipo.
		 */
		EntityListIterator getEntitiesByTypeEnd(const std::string & entityType);

		/**
		 * Obtiene si existe alguna lista de entidades en base a un nombre.
		 */
		bool existsEntitiesByName(const std::string & entityName);

		/**
		 * Obtiene si existe alguna lista de entidades en base a un tipo.
		 */
		bool existsEntitiesByType(const std::string & entityType);

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Activa el mundo.
		 * @return Devuelve true si se activa correctamente.
		 */
		bool activate();

		/**
		 * Desactiva el mundo.
		 */
		void deactivate();

		/**
		 * Prepara el mundo para la futura actualización del estado del mundo.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		void prepareUpdate(unsigned int lastInterval);

		/**
		 * Actualiza el estado del mundo.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		void update(unsigned int lastInterval);

		/**
		 * Envia un mensaje a todas las entidades.
		 * @param message El mensaje que va a ser enviado a todas las entidades.
		 * @param sender El componente que envia el mensaje.
		 * @return Da true si el mensaje ha sido admitido por alguna entidad.
		 */
		bool sendMessage(SmartMessage & message, Component * sender = 0);

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de listas de entidades en base a una cadena.
		 */
		typedef std::map<std::string, EntityList> EntityStringTable;

		/**
		 * Este tipo representa un iterador de una tabla de listas de entidades en base a una cadena.
		 */
		typedef EntityStringTable::iterator EntityStringTableIterator;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre del escenario.
		 */
		std::string _name;

		/**
		 * La escena gráfica donde está la representación visual del mundo.
		 */
		Scene * _scene;

		/**
		 * Tabla de las entidades del mundo organizadas por su identificador único.
		 */
		EntityIdTable _entitiesById;

		/**
		 * Tabla de listas de entidades del mundo organizadas por el nombre de entidad.
		 * @remark Usamos listas de entidades porque el nombre de la entidad puede no ser único.
		 */
		EntityStringTable _entitiesByName;

		/**
		 * Tabla de listas de entidades del mundo organizadas por el tipo de entidad.
		 */
		EntityStringTable _entitiesByType;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade una entidad al mundo.
		 * @param entity La entidad a añadir.
		 * @remark Este método solo se puede llamar una vez ha sido configurada la entidad correctamente
		 *         tras el spawn, para coger el nombre y el tipo de dicha entidad.
		 */
		void addEntity(Entity * entity);

		/**
		 * Elimina una entidad del mundo.
		 * @param entity La entidad a eliminar.
		 * @remark Este método solo se debe llamar desde Entity o EntitiesManager.
		 */
		void removeEntity(Entity * entity);

		/**
		 * Elimina todas las entidades del mundo.
		 * @remark Este método, de forma adicional, se encarga de borrar de la memoria las entidades.
		 * @remark Este método solo se debe llamar desde EntitiesManager.
		 */
		void removeAllEntities();

		/**
		 * Añade una entidad a una tabla del mundo.
		 * @param entity La entidad a añadir.
		 * @param table La tabla a la que añadir la entidad.
		 * @param key La clave asociada a la entidad.
		 */
		inline void addEntityToStringTable(Entity * entity, EntityStringTable & table, const std::string & key);

		/**
		 * Elimina una entidad de una tabla del mundo.
		 * @param entity La entidad a eliminar.
		 * @param table La tabla de la que eliminar la entidad.
		 * @param key La clave asociada a la entidad.
		 */
		inline void removeEntityFromStringTable(Entity * entity, EntityStringTable & table, const std::string & key);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre del mundo.
		 */
		World(const std::string & name);

		/**
		 * Destructor del objeto.
		 */
		virtual ~World();

		friend class Core::EntitiesManager;
		friend class Core::Entity;
	};
}

#endif
