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

#include "Core/Entities/Component.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool Component::spawn(const EntityInfoTable * entityInfo) {
		assert(_owner && "Component::initialize -> The owner cann't be null...");
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Component::activate() {
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void Component::deactivate() {
	}

	//--------------------------------------------------------------------------------------------------------

	void Component::prepareUpdate(unsigned int lastInterval) {
	}
	
	//--------------------------------------------------------------------------------------------------------

	void Component::update(unsigned int lastInterval) {
		processMessages();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Component::Component(const std::string & name) : CommunicationPort(), _name(name), _owner(0), _priority(0) {
		assert(name.size() > 0 && "Component::Component -> The name can't be empty...");
	}

	//--------------------------------------------------------------------------------------------------------

	Component::Component(const Component & obj) : CommunicationPort(obj) {
		_name = obj._name;
		_owner = obj._owner;
	}

	//--------------------------------------------------------------------------------------------------------

	Component::~Component() {}
}
