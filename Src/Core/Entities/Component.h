//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
//************************************************************************************************************

#ifndef __CORE_COMPONENT_H__
#define __CORE_COMPONENT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Core/Entities/CommunicationPort.h"

//************************************************************************************************************
// Macros
//************************************************************************************************************

#define ComponentCreateMethod(ClassType) static Core::Component * create() { return new ClassType(); }

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntityInfoTable;
	class Entity;

	/**
	 * Esta clase representa un componente gen�rico que formar� parte de una entidad dentro del juego.
	 */
	class Component : public CommunicationPort {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre del componente.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene la entidad due�a del componente.
		 */
		inline Entity * getOwner() const { return _owner; }

		/**
		 * Obtiene la prioridad del componente a la hora de ser actualizado.
		 */
		inline unsigned int getPriority() const { return _priority; }

		/**
		 * Modifica la prioridad del componente a la hora de ser actualizado.
		 */
		inline void setPriority(unsigned int value) { _priority = value; }

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~Component();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre del componente.
		 */
		std::string _name;

		/**
		 * La entidad due�a del componente.
		 */
		Entity * _owner;

		/**
		 * La prioridad del componente a la hora de ser actualizado.
		 * @remark 0 equivale a la prioridad por defecto, cuanto m�s alta sea m�s prioridad tendr�.
		 */
		unsigned int _priority;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Modifica la entidad due�a del componente.
		 */
		inline void setOwner(Entity * value) { _owner = value; }

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el componente a la hora de ser a�adido al mundo.
		 * @param info La informaci�n inicial del componente.
		 * @return Devuelve true si se inicializa correctamente.
		 * @remark Este m�todo es invocado cuando la entidad due�a es inicializada al a�adirse al mundo.
		 * @remark En este m�todo es cuando los componentes toman los datos de inicializaci�n o de gestores
		 *         del juego, lo que no se debe hacer es coger datos de otros componentes, porque cabe
		 *         la posibilidad de que todav�a no se haya inicializado porque no se haya llamado todav�a
		 *         a su respectivo spawn (para este caso en particular existe activate).
		 */
		virtual bool spawn(const EntityInfoTable * info);

		/**
		 * Activa el componente.
		 * @return Devuelve true si se activa correctamente.
		 * @remark Este m�todo es invocado cuando la entidad due�a es activada.
		 * @remark En este m�todo es cuando los componentes deber�a obtener las referencias de datos
		 *         de otros componentes, que ya por fin est�n todos inicializados.
		 */
		virtual bool activate();

		/**
		 * Desactiva el componente.
		 * @remark Este m�todo es invocado cuando la entidad due�a es desactivada.
		 */
		virtual void deactivate();

		/**
		 * Prepara la l�gica interna del componente para ser actualizado correctamente.
		 * @param lastInterval El tiempo total del �ltimo intervalo entre frame y frame.
		 * @remark Este m�todo es invocado cuando la entidad due�a es actualizada.
		 */
		virtual void prepareUpdate(unsigned int lastInterval);

		/**
		 * Actualiza la l�gica interna del componente llamando a processMessages(), por lo que si una
		 * clase hija decide sobre-escribir este m�todo o llama al padre o directamente invoca el m�todo
		 * para procesar todos los mensajes pendientes en la lista de mensajes pendientes de procesar.
		 * @param lastInterval El tiempo total del �ltimo intervalo entre frame y frame.
		 * @remark Este m�todo es invocado cuando la entidad due�a es actualizada.
		 */
		virtual void update(unsigned int lastInterval);

		//----------------------------------------------------------------------------------------------------
		// Constructores
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre del componente.
		 */
		Component(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Component(const Component & obj);

		friend class Core::Entity;
	};
}

#endif
