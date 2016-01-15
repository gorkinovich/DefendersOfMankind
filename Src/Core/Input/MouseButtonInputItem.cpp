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

#include "Core/Input/Mouse.h"
#include "Core/Input/MouseButtonInputItem.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MouseButtonInputItem::changeCondition() const {
		return _currentValue != _previousValue;
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseButtonInputItem::updateCurrentValue() {
		_previousValue = _currentValue;
		_updateCurrentValue();
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseButtonInputItem::callMethod(IMouseButtonInputActionMethod & method) {
		method.mouseButtonInputChanged(*this);
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseButtonInputItem::updateCurrentValueLeft() {
		_currentValue = Mouse::GetState().left;
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseButtonInputItem::updateCurrentValueMiddle() {
		_currentValue = Mouse::GetState().middle;
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseButtonInputItem::updateCurrentValueRight() {
		_currentValue = Mouse::GetState().right;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	MouseButtonInputItem::MouseButtonInputItem(MouseButtonElement type) : _type(type) {
		_previousValue = false;
		_currentValue = false;
		switch(_type) {
			default:
			case MouseButtonInputItemType::LEFT:
				_updateCurrentValue = std::tr1::bind(&MouseButtonInputItem::updateCurrentValueLeft, this);
				break;
			case MouseButtonInputItemType::MIDDLE:
				_updateCurrentValue = std::tr1::bind(&MouseButtonInputItem::updateCurrentValueMiddle, this);
				break;
			case MouseButtonInputItemType::RIGHT:
				_updateCurrentValue = std::tr1::bind(&MouseButtonInputItem::updateCurrentValueRight, this);
				break;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	MouseButtonInputItem::MouseButtonInputItem(const MouseButtonInputItem & obj) {
		InputItem::copyFrom(obj);
		_type = obj._type;
	}

	//--------------------------------------------------------------------------------------------------------

	MouseButtonInputItem::~MouseButtonInputItem() {}
}
