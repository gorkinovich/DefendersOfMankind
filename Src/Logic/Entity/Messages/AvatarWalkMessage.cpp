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

#include "Logic/Entity/Messages/AvatarWalkMessage.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void AvatarWalkMessage::copyFrom(const Core::Object & obj) {
		if(checkType<AvatarWalkMessage>(obj)) {
			AvatarWalkMessage::AvatarWalkMessage(static_cast<const AvatarWalkMessage &>(obj));
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************
	
	AvatarWalkMessage::AvatarWalkMessage(const Vector3 & movement) : _movement(movement) {}
	
	//--------------------------------------------------------------------------------------------------------
	
	AvatarWalkMessage::AvatarWalkMessage(const AvatarWalkMessage & obj) {
		_movement = obj._movement;
	}
	
	//--------------------------------------------------------------------------------------------------------
	
	AvatarWalkMessage::~AvatarWalkMessage() {}
}
