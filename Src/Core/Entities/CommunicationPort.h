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

#ifndef __CORE_COMMUNICATIONPORT_H__
#define __CORE_COMMUNICATIONPORT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <list>

#include "Core/Entities/Message.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Entity;

	/**
	 * Esta clase representa un puerto de comunicación para que los componentes de las entidades puedan
	 * comunicarse mediante el envio y recepción de mensajes.
	 */
	class CommunicationPort {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade un mensaje siempre pueda ser aceptado.
		 * @param message El mensaje enviado al puerto.
		 * @return Da true si el mensaje ha sido admitido.
		 */
		bool addMessage(SmartMessage & message);

		/**
		 * Procesa todos los mensajes pendientes en la lista.
		 */
		void processMessages();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		CommunicationPort();

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		CommunicationPort(const CommunicationPort & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~CommunicationPort();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Tipo MessageList donde se van a guardar los mensajes a la espera de ser procesados.
		 */
		typedef std::list<SmartMessage> MessageList;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La lista de mensajes pendientes de procesar.
		 */
		MessageList _messages;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si un mensaje es válido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser válido devolverá true.
		 */
		virtual bool acceptMessage(const SmartMessage & message);

		/**
		 * Procesa un mensaje recién sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const SmartMessage & message);

		/**
		 * Elimina todos los mensajes de la lista.
		 */
		void clearMessages();

		friend class Core::Entity;
	};
}

#endif
