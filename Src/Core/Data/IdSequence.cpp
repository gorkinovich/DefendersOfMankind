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

#include <assert.h>

#include "Core/Data/IdSequence.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	IdType IdSequence::getNextId() {
		IdType next = _nextId++;
		assert(next != IdSequence::Unassigned && "IdSequence::getNextId -> Invalid next id...");
		return next;
	}

	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	void IdSequence::reset() {
		_nextId = IdSequence::FirstId;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	IdSequence::IdSequence() : _nextId(IdSequence::FirstId) {}

	//--------------------------------------------------------------------------------------------------------

	IdSequence::IdSequence(const IdSequence & obj) {
		_nextId = obj._nextId;
	}

	//--------------------------------------------------------------------------------------------------------

	IdSequence::~IdSequence() {}
}
