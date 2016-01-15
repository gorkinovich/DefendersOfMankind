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

#include "Logic/MissionManager.h"
#include "Logic/Entity/Types of movement/RegisterMovement.h"

// Inclusiones de los diferentes movimientos predefinidos para que estos se registren en la factoría
#include "Logic/Entity/Types of movement/HorizontalMovement.h"
#include "Logic/Entity/Types of movement/SinusoidalMovement.h"
#include "Logic/Entity/Types of movement/TriangleMovement.h"
#include "Logic/Entity/Types of movement/UpDownMovement.h"
#include "Logic/Entity/Types of movement/CircumferenceMovement.h"
#include "Logic/Entity/Types of movement/RectilinearMovement.h"
#include "Logic/Entity/Types of movement/GoToPlayerMovement.h"
#include "Logic/Entity/Types of movement/GoToQuadrantMovement.h"

#include "Logic/Entity/Types of movement/BulletHorizontalMovement.h"
#include "Logic/Entity/Types of movement/BulletHorizontalMovementPlayer.h"
#include "Logic/Entity/Types of movement/BulletGoToPlayerMovement.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MissionManager::registerMovementTypes() {
		// Registramos cada tipo de movimiento
		if(!RegisterMovement(HorizontalMovement)) return false;
		if(!RegisterMovement(SinusoidalMovement)) return false;
		if(!RegisterMovement(TriangleMovement)) return false;
		if(!RegisterMovement(UpDownMovement)) return false;
		if(!RegisterMovement(CircumferenceMovement)) return false;
		if(!RegisterMovement(RectilinearMovement)) return false;
		if(!RegisterMovement(GoToPlayerMovement)) return false;
		if(!RegisterMovement(GoToQuadrantMovement)) return false;

		if(!RegisterMovement(BulletHorizontalMovement)) return false;
		if(!RegisterMovement(BulletHorizontalMovementPlayer)) return false;
		if(!RegisterMovement(BulletGoToPlayerMovement)) return false;

		return true;
	}
}
