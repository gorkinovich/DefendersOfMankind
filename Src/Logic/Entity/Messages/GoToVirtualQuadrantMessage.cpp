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

#include "Logic/Entity/Messages/GoToVirtualQuadrantMessage.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void GoToVirtualQuadrantMessage::copyFrom(const Core::Object & obj) {
		if(checkType<GoToVirtualQuadrantMessage>(obj)) {
			GoToVirtualQuadrantMessage::GoToVirtualQuadrantMessage(static_cast<const GoToVirtualQuadrantMessage &>(obj));
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************
	
	GoToVirtualQuadrantMessage::GoToVirtualQuadrantMessage(int Q1, int Q2): _Q1(Q1), _Q2(Q2) {}
	
	//--------------------------------------------------------------------------------------------------------
	
	GoToVirtualQuadrantMessage::GoToVirtualQuadrantMessage(const GoToVirtualQuadrantMessage & obj) {
		 _Q1 = obj._Q1;
		 _Q2 = obj._Q2;
	}
	
	//--------------------------------------------------------------------------------------------------------
	
	GoToVirtualQuadrantMessage::~GoToVirtualQuadrantMessage() {}
}
