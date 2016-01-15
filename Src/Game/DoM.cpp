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

//************************************************************************************************************
// Includes
//************************************************************************************************************

// Inclusión de la librería para controlar la detección de memory leaks.
#ifdef _DEBUG
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vld.h> 
#endif

// Las librerías para arrancar y finalizar el juego.
#include "Game/DoMApplication.h"
#include "Core/MetalMeltdown.h"
#include "Logic/KilledByDeath.h"

//************************************************************************************************************
// Función de entrada
//************************************************************************************************************

#if (defined _DEBUG) || !(defined _WIN32)
int main(int argc, char **argv) {
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow) {
#endif

	// Creamos la instancia del juego.
	Game::DoMApplication game;

	// Tratamos de inicializarlo.
	if(game.initialize()) {
		// Si lo inicializamos iniciamos el bucle principal.
		game.run();
	}

	// Tras salir del bucle principal, liberamos al juego.
	game.release();

	// Para evitar en modo debug que salten los avisos de memory leaks.
	MetalMeltdown();
	KilledByDeath();

	return 0;
}
