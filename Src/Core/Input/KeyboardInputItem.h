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

#ifndef __CORE_KEYBOARDINPUTITEM_H__
#define __CORE_KEYBOARDINPUTITEM_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Input/InputItem.h"
#include "Core/Input/IKeyboardInputActionMethod.h"
#include "Core/Input/Keys.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un elemento de entrada del teclado.
	 */
	class KeyboardInputItem : public InputItem<bool, IKeyboardInputActionMethod> {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el valor de la tecla.
		 */
		inline KeyCode getKey() const { return _key; }

		/**
		 * Obtiene si la tecla está pulsada.
		 */
		inline bool isPressed() const { return getCurrentValue(); }

		/**
		 * Obtiene si la tecla no está pulsada.
		 */
		inline bool isReleased() const { return getPreviousValue(); }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param key El valor de la tecla.
		 */
		KeyboardInputItem(KeyCode key);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		KeyboardInputItem(const KeyboardInputItem & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~KeyboardInputItem();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El valor de la tecla.
		 */
		KeyCode _key;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si ha cambiado el estado de la información del elemento.
		 * @return De haber cambiado el estado devolverá true.
		 */
		virtual bool changeCondition() const;

		/**
		 * Actualiza el valor interno del elemento.
		 */
		virtual void updateCurrentValue();

		/**
		 * Invoca un método dentro de un objeto.
		 * @param method El objeto con el método.
		 */
		virtual void callMethod(IKeyboardInputActionMethod & method);
	};
}

#endif
