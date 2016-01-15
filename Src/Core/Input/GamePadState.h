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

#ifndef __CORE_GAMEPADSTATE_H__
#define __CORE_GAMEPADSTATE_H__

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define PAD_MAX_PLAYERS 4

#define PAD_PLAYER1 0
#define PAD_PLAYER2 1
#define PAD_PLAYER3 2
#define PAD_PLAYER4 3

#define PAD_MIN_VIBRATION 0
#define PAD_MAX_VIBRATION 65535

#define PAD_MIN_TRIGGER 0
#define PAD_MAX_TRIGGER 255

#define PAD_MIN_THUMB -32768
#define PAD_MAX_THUMB 32767

#define PAD_LEFT_THUMB_DEADZONE  7849
#define PAD_RIGHT_THUMB_DEADZONE 8689
#define PAD_TRIGGER_THRESHOLD    30

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	// Notas sobre el mando de la xbox con el infame dinput:
	// Ejes:
	//     ThumbSticks
	//         Left  X = Eje X        1?
	//         Left  Y = Eje Y        2?
	//         Right X = Rotación X   4?
	//         Right Y = Rotación Y   5?
	//     Triggers
	//         Left    = Eje +Z       3?
	//         Right   = Eje -Z       3?
	// POV:
	//     DPad (Up, Down, Left, Right)
	// Botones:
	//     A     = 1
	//     B     = 2
	//     X     = 3
	//     Y     = 4
	//     LB    = 5   LeftShoulder
	//     RB    = 6   RightShoulder
	//     Back  = 7
	//     Start = 8
	//     Left  = 9   LeftStick
	//     Right = 10  RightStick

	/**
	 * Esta estructura representa el estado de un stick en el mando.
	 */
	typedef struct {
		short x, y;
	} ThumbStickState;

	/**
	 * Esta estructura representa el estado de un dpad en el mando.
	 */
	typedef struct {
		bool up, down, left, right;
	} DigitalPadState;

	/**
	 * Esta estructura representa el estado de los botones en el mando.
	 */
	typedef struct {
		bool a, b, x, y;
		bool leftShoulder, rightShoulder;
		bool back, start;
		bool leftStick, rightStick;
	} PadButtonsState;

	/**
	 * Esta estructura representa el estado de un mando.
	 */
	typedef struct {
		// Los sticks analógicos del mando.
		ThumbStickState leftStick, rightStick;
		// Los triggers del mando.
		unsigned char leftTrigger, rightTrigger;
		// El pad digital del mando.
		DigitalPadState dpad;
		// Los botones del mando.
		PadButtonsState buttons;
		// Si está conectado el mando o no.
		bool isConnected;
	} GamePadState;
}

#endif
