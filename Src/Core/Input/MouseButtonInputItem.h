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

#ifndef __CORE_MOUSEBUTTONINPUTITEM_H__
#define __CORE_MOUSEBUTTONINPUTITEM_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <functional>

#include "Core/Input/InputItem.h"
#include "Core/Input/IMouseButtonInputActionMethod.h"
#include "Core/Input/MouseButtonElement.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un elemento de entrada de los botones del ratón.
	 */
	class MouseButtonInputItem : public InputItem<bool, IMouseButtonInputActionMethod> {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el tipo del elemento.
		 */
		inline MouseButtonElement getType() const { return _type; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param type El tipo del elemento.
		 */
		MouseButtonInputItem(MouseButtonElement type);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		MouseButtonInputItem(const MouseButtonInputItem & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~MouseButtonInputItem();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El tipo del elemento.
		 */
		MouseButtonElement _type;

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
		virtual void callMethod(IMouseButtonInputActionMethod & method);

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueLeft();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueMiddle();

		/**
		 * Actualiza el valor interno del elemento.
		 */
		void updateCurrentValueRight();
	};
}

#endif
