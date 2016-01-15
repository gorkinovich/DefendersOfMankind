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

#ifndef __LOGIC_MESSAGETYPES_H__
#define __LOGIC_MESSAGETYPES_H__

//************************************************************************************************************
// Constantes
//************************************************************************************************************

// General
#define MESSAGE_TYPE_UNASSIGNED         0000

// Gráficos
#define MESSAGE_TYPE_CHANGE_TRANSFORM   1001
#define MESSAGE_TYPE_AVATAR_WALK        1002
#define MESSAGE_TYPE_CHANGE_ANIMATION   1003
#define MESSAGE_TYPE_STOP_ANIMATION     1004
#define MESSAGE_TYPE_CHANGE_VIEW        1005
#define MESSAGE_TYPE_PARTICLE_SYSTEM    1006
#define MESSAGE_TYPE_PARTICLE_SYSTEM_END	1007
#define MESSAGE_TYPE_SHOW_HIDE_ENTITY	1008
#define MESSAGE_TYPE_SET_ANGLE_TO_ROTATE	1009

// Física
#define MESSAGE_TYPE_TOUCHED            2001
#define MESSAGE_TYPE_UNTOUCHED          2002
#define MESSAGE_TYPE_SWITCH             2003

// Lógica
#define MESSAGE_TYPE_DAMAGED            3001
#define MESSAGE_TYPE_CREATE_CHILD       3002
#define MESSAGE_TYPE_DEATH				3003
#define MESSAGE_TYPE_END_OF_LEVEL		3004
#define MESSAGE_TYPE_LIFE_CYCLE_ON		3005
#define MESSAGE_TYPE_LIFE_CYCLE_OFF		3006
#define MESSAGE_TYPE_LIFE_CYCLE_RELEASE	3007
#define MESSAGE_TYPE_PLAYER_POSITIONED	3008
#define MESSAGE_TYPE_PLAYER_DEAD		3009
#define MESSAGE_TYPE_POWER_UP			3010
#define MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT		3011
#define MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_END	3012
#define MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_ABORT	3013

// IA
#define MESSAGE_TYPE_ROUTE_TO           4001
#define MESSAGE_TYPE_MOVE_TO            4002
#define MESSAGE_TYPE_FINISHED_ROUTE     4003
#define MESSAGE_TYPE_FAILED_ROUTE       4004

// Sonido
#define MESSAGE_TYPE_PLAY_SOUND			5001
#define MESSAGE_TYPE_PAUSE_SOUND		5002
#define MESSAGE_TYPE_STOP_SOUND			5003

#endif
