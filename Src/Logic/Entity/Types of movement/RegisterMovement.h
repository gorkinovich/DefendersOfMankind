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

#ifndef __LOGIC_MOVEMENTSMACROS_H__
#define __LOGIC_MOVEMENTSMACROS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Logic/MissionManager.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	/**
	 * Registra un método factoría en una factoría de movimientos.
	 * @param name El nombre con el que se registra el método.
	 * @return Devuelve true si se ha logrado registrar el movimiento.
	 */
	template<class T>
	bool RegisterInMovementsFactory(const std::string & name) {
		MovementsFactory & factory = MissionManager::GetInstance()->getMovementsFactory();
		if(!factory.contains(name)) {
			factory.add(name, T::create);
			return factory.contains(name);
		} else {
			return true;
		}
	}
}

//************************************************************************************************************
// Macros
//************************************************************************************************************

#define RegisterMovement(ClassType) Logic::RegisterInMovementsFactory<ClassType>(#ClassType)

#endif
