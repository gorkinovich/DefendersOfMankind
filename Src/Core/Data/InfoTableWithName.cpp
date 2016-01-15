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

#include "Core/Data/InfoTableWithName.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string InfoTableWithName::NameAttributeKey = std::string("name");

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InfoTableWithName::hasAttribute(const std::string & name) const {
		if(name == NameAttributeKey) {
			return true;
		} else {
			return InfoTable::hasAttribute(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	const std::string & InfoTableWithName::getAttribute(const std::string & name) const {
		if(name == NameAttributeKey) {
			return _name;
		} else {
			return InfoTable::getAttribute(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTableWithName::setAttribute(const std::string & name, const std::string & value) {
		if(name == NameAttributeKey) {
			_name = value;
		} else {
			InfoTable::setAttribute(name, value);
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	InfoTableWithName::InfoTableWithName(const std::string & name) : InfoTable(), _name(name) {}

	//--------------------------------------------------------------------------------------------------------

	InfoTableWithName::InfoTableWithName(const InfoTableWithName & obj) : InfoTable(obj) {
		_name = obj._name;
	}

	//--------------------------------------------------------------------------------------------------------

	InfoTableWithName::~InfoTableWithName() {}
}
