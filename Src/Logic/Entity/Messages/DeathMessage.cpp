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

#include "Logic/Entity/Messages/DeathMessage.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void DeathMessage::copyFrom(const Core::Object & obj) {
		if(checkType<DeathMessage>(obj)) {
			DeathMessage::DeathMessage(static_cast<const DeathMessage &>(obj));
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************
	
	DeathMessage::DeathMessage(float timeToDie) : _timeToDie(timeToDie) {}
	
	//--------------------------------------------------------------------------------------------------------
	
	DeathMessage::DeathMessage(const DeathMessage & obj) {
		_timeToDie = obj._timeToDie;
	}
	
	//--------------------------------------------------------------------------------------------------------
	
	DeathMessage::~DeathMessage() {}
}
