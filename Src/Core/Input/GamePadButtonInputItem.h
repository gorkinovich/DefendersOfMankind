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

#ifndef __CORE_GAMEPADBUTTONINPUTITEM_H__
#define __CORE_GAMEPADBUTTONINPUTITEM_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <functional>

#include "Core/Input/InputItem.h"
#include "Core/Input/IGamePadButtonInputActionMethod.h"
#include "Core/Input/GamePadButtonElement.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un elemento de entrada de los botones del mando.
	 */
	class GamePadButtonInputItem : public InputItem<bool, IGamePadButtonInputActionMethod> {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el tipo del elemento.
		 */
		inline GamePadButtonElement getType() const { return _type; }

		/**
		 * Obtiene el número mando del jugador.
		 */
		inline unsigned short getPlayer() const { return _player; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param type El tipo del elemento.
		 * @param player El número mando del jugador.
		 */
		GamePadButtonInputItem(GamePadButtonElement type, unsigned short player);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		GamePadButtonInputItem(const GamePadButtonInputItem & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~GamePadButtonInputItem();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El tipo del elemento.
		 */
		GamePadButtonElement _type;

		/**
		 * El número mando del jugador.
		 */
		unsigned short _player;

		/**
		 * La función de actualización del valor actual.
		 */
		std::tr1::function<void ()> _updateCurrentValue;

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
		virtual void callMethod(IGamePadButtonInputActionMethod & method);

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueA();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueB();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueX();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueY();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueLeftShoulder();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueRightShoulder();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueLeftStick();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueRightStick();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueBack();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueStart();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueUp();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueDown();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueLeft();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueRight();
	};
}

#endif
