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

#ifndef __CORE_MOUSESTATE_H__
#define __CORE_MOUSESTATE_H__

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta estructura representa el estado del ratón.
	 */
	typedef struct {
		// Botones del ratón.
		bool left, middle, right;
		// Valores relativos de los ejes.
		int x, y, scrollWheel;
		// Tamaño de la ventana.
		unsigned int screenWidth, screenHeight;
		// Valores absolutos de los ejes.
		unsigned int screenAbsX, screenAbsY;
		// Valores relativos a la pantalla (0.0f .. 1.0f).
		float screenRelX, screenRelY;
	} MouseState;
}

#endif
