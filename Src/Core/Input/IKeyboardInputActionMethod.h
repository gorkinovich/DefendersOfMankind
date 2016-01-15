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

#ifndef __CORE_IKEYBOARDINPUTACTIONMETHOD_H__
#define __CORE_IKEYBOARDINPUTACTIONMETHOD_H__

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un elemento de entrada del teclado.
	 */
	class KeyboardInputItem;

	/**
	 * Esta interfaz representa un m�todo para recibir una actualizaci�n en la entrada.
	 */
	class IKeyboardInputActionMethod {
	public:
		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Delegado que se llama al actualizarse la entrada.
		 */
		virtual void keyboardInputChanged(const KeyboardInputItem & item) = 0;

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~IKeyboardInputActionMethod() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		IKeyboardInputActionMethod() {}
	};
}

#endif