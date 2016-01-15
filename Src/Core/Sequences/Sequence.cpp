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

#include <algorithm>

#include "Core/Sequences/Sequence.h"
#include "Core/Sequences/ISequenceAction.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	void Sequence::innerUpdate(unsigned int lastInterval) {
		// Ejecutamos la acci�n del paso actual y avanzamos al siguiente paso.
		_actions[_nextStep]->execute();
		++_nextStep;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Sequence::Sequence(const std::string & name) : GenericSequence(name) {}

	//--------------------------------------------------------------------------------------------------------

	Sequence::Sequence(const Sequence & obj) : GenericSequence(obj) {}

	//--------------------------------------------------------------------------------------------------------

	Sequence::~Sequence() {}
}
