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

#include "Logic/Entity/Messages/LifeCycleRELEASEMessage.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	void LifeCycleRELEASEMessage::copyFrom(const Core::Object & obj) {
		if(checkType<LifeCycleRELEASEMessage>(obj)) {
			LifeCycleRELEASEMessage::LifeCycleRELEASEMessage(static_cast<const LifeCycleRELEASEMessage &>(obj));
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************
	
	LifeCycleRELEASEMessage::LifeCycleRELEASEMessage() {}
	
	//--------------------------------------------------------------------------------------------------------
	
	LifeCycleRELEASEMessage::LifeCycleRELEASEMessage(const LifeCycleRELEASEMessage & obj) {
	}
	
	//--------------------------------------------------------------------------------------------------------
	
	LifeCycleRELEASEMessage::~LifeCycleRELEASEMessage() {}
}
