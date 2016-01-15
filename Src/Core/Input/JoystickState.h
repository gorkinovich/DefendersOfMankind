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

#ifndef __CORE_JOYSTICKSTATE_H__
#define __CORE_JOYSTICKSTATE_H__

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define MAX_JOYSTICK_AXIS       6
#define MAX_JOYSTICK_POVS       4
#define MAX_JOYSTICK_SLIDERS    4
#define MAX_JOYSTICK_BUTTONS   32

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta estructura representa el estado de un pov en el joystick.
	 */
	typedef struct {
		bool up, down, left, right;
	} JoystickPovState;

	/**
	 * Esta estructura representa el estado de un slider en el joystick.
	 */
	typedef struct {
		int x, y;
	} JoystickSliderState;

	/**
	 * Esta estructura representa el estado de un joystick.
	 */
	typedef struct {
		// Valores de los ejes.
		int axis[MAX_JOYSTICK_AXIS];
		// Pads digitales.
		JoystickPovState povs[MAX_JOYSTICK_POVS];
		// Los sliders.
		JoystickSliderState sliders[MAX_JOYSTICK_SLIDERS];
		// Los botones.
		bool buttons[MAX_JOYSTICK_BUTTONS];
	} JoystickState;
}

#endif
