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
#include "Core/Input/MouseAxisInputItem.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MouseAxisInputItem::changeCondition() const {
		return _currentValue != _previousValue;
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseAxisInputItem::updateCurrentValue() {
		_previousValue = _currentValue;
		_updateCurrentValue();
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseAxisInputItem::callMethod(IMouseAxisInputActionMethod & method) {
		method.mouseAxisInputChanged(*this);
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseAxisInputItem::updateCurrentValueX() {
		_currentValue = Mouse::GetState().x;
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseAxisInputItem::updateCurrentValueY() {
		_currentValue = Mouse::GetState().y;
	}

	//--------------------------------------------------------------------------------------------------------

	void MouseAxisInputItem::updateCurrentValueScroll() {
		_currentValue = Mouse::GetState().scrollWheel;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	MouseAxisInputItem::MouseAxisInputItem(MouseAxisElement type) : _type(type) {
		_previousValue = 0;
		_currentValue = 0;
		switch(_type) {
			default:
			case MouseAxisInputItemType::X:
				_updateCurrentValue = std::tr1::bind(&MouseAxisInputItem::updateCurrentValueX, this);
				break;
			case MouseAxisInputItemType::Y:
				_updateCurrentValue = std::tr1::bind(&MouseAxisInputItem::updateCurrentValueY, this);
				break;
			case MouseAxisInputItemType::SCROLL:
				_updateCurrentValue = std::tr1::bind(&MouseAxisInputItem::updateCurrentValueScroll, this);
				break;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	MouseAxisInputItem::MouseAxisInputItem(const MouseAxisInputItem & obj) {
		InputItem::copyFrom(obj);
		_type = obj._type;
	}

	//--------------------------------------------------------------------------------------------------------

	MouseAxisInputItem::~MouseAxisInputItem() {}
}
