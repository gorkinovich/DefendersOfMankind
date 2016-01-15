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

#include "Core/Entities/CommunicationPort.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	bool CommunicationPort::addMessage(SmartMessage & message) {
		// Primero se comprueba si el mensaje es aceptado por el componente.
		if(acceptMessage(message)) {
			// De ser aceptado, se a�ade a la cola de mensajes del componente.
			_messages.push_back(message);
			return true;
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void CommunicationPort::processMessages() {
		// Procesamos cada elemento de la cola de forma individual por el componente.
		MessageList::iterator end = _messages.end();
		for(MessageList::iterator i = _messages.begin(); i != end; ++i) {
			processMessage(*i);
		}
		// Tras terminar de procesar los mensajes, vaciamos la cola.
		_messages.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommunicationPort::acceptMessage(const SmartMessage & message) {
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void CommunicationPort::processMessage(const SmartMessage & message) {
	}

	//--------------------------------------------------------------------------------------------------------

	void CommunicationPort::clearMessages() {
		_messages.clear();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	CommunicationPort::CommunicationPort() {
	}

	//--------------------------------------------------------------------------------------------------------

	CommunicationPort::CommunicationPort(const CommunicationPort & obj) {
		_messages = obj._messages;
	}

	//--------------------------------------------------------------------------------------------------------

	CommunicationPort::~CommunicationPort() {
		_messages.clear();
	}
}
