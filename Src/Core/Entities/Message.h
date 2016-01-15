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

#ifndef __CORE_MESSAGE_H__
#define __CORE_MESSAGE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Entities/GenericMessage.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un mensaje entre componentes de una entidad.
	 */
	class Message : public GenericMessage {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene los datos del mensaje.
		 */
		inline const Object & getData() const { return *_data; }

		/**
		 * Obtiene el puntero reconvertido a otro tipo sin comprobaciones.
		 */
		template<class T>
		inline const T * getDataPtrAs() const { return static_cast<const T *>(_data); }

		/**
		 * Obtiene la referencia reconvertida a otro tipo sin comprobaciones.
		 */		
		template<class T>
		inline const T & getDataRefAs() const { return static_cast<const T &>(*_data); }

		/**
		 * Obtiene el puntero reconvertido a otro tipo con comprobaciones.
		 */
		template<class T>
		inline const T * getDataSafePtrAs() const { return dynamic_cast<const T *>(_data); }

		/**
		 * Obtiene la referencia reconvertida a otro tipo con comprobaciones.
		 */		
		template<class T>
		inline const T & getDataSafeRefAs() const { return dynamic_cast<const T &>(*_data); }

		/**
		 * Obtiene el nombre de la entidad destino.
		 */
		inline const char * getEntityTargetName() const { return _entityTargetName; }

		/**
		 * Obtiene el tipo de la entidad destino.
		 */
		inline const char * getEntityTargetType() const { return _entityTargetType; }

		/**
		 * Obtiene el nombre del componente destino.
		 */
		inline const char * getComponentTargetName() const { return _componentTargetName; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param type El tipo del mensaje.
		 * @param data Los datos del mensaje.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 */
		Message(int type, Object * data, const char * entityTargetName = 0, const char * entityTargetType = 0,
			const char * componentTargetName = 0);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Message(const Message & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Message();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Los datos del mensaje.
		 */
		SmartObject _data;

		/**
		 * El nombre de la entidad destino.
		 */
		const char * _entityTargetName;

		/**
		 * El tipo de la entidad destino.
		 */
		const char * _entityTargetType;

		/**
		 * El nombre del componente destino.
		 */
		const char * _componentTargetName;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Copia el contenido de un objeto en el actual.
		 * @param obj El objeto a copiar.
		 */
		virtual void copyFrom(const Object & obj);
	};

	/**
	 * Este tipo es un puntero inteligente a un Message.
	 */
	typedef SmartPointer<Message> SmartMessage;
}

#endif
