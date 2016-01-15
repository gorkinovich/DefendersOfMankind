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

#include <assert.h>

#include "Core/Input/GamePads.h"
#include "Core/Input/GamePadAxisInputItem.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GamePadAxisInputItem::changeCondition() const {
		return _currentValue != _previousValue;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValue() {
		_previousValue = _currentValue;
		_updateCurrentValue();
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::callMethod(IGamePadAxisInputActionMethod & method) {
		method.gamePadAxisInputChanged(*this);
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValueStickLeftX() {
		_currentValue = (int)GamePads::GetState(_player).leftStick.x;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValueStickLeftY() {
		_currentValue = (int)GamePads::GetState(_player).leftStick.y;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValueStickRightX() {
		_currentValue = (int)GamePads::GetState(_player).rightStick.x;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValueStickRightY() {
		_currentValue = (int)GamePads::GetState(_player).rightStick.y;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValueTriggerLeft() {
		_currentValue = (int)GamePads::GetState(_player).leftTrigger;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadAxisInputItem::updateCurrentValueTriggerRight() {
		_currentValue = GamePads::GetState(_player).rightTrigger;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GamePadAxisInputItem::GamePadAxisInputItem(GamePadAxisElement type, unsigned short player) : _type(type), _player(player) {
		assert(player < PAD_MAX_PLAYERS && "GamePadAxisInputItem::GamePadAxisInputItem -> Player ID invalid...");
		_previousValue = 0;
		_currentValue = 0;
		switch(_type) {
			default:
			case GamePadAxisInputItemType::STICK_LEFT_X:
				_updateCurrentValue = std::tr1::bind(&GamePadAxisInputItem::updateCurrentValueStickLeftX, this);
				break;
			case GamePadAxisInputItemType::STICK_LEFT_Y:
				_updateCurrentValue = std::tr1::bind(&GamePadAxisInputItem::updateCurrentValueStickLeftY, this);
				break;
			case GamePadAxisInputItemType::STICK_RIGHT_X:
				_updateCurrentValue = std::tr1::bind(&GamePadAxisInputItem::updateCurrentValueStickRightX, this);
				break;
			case GamePadAxisInputItemType::STICK_RIGHT_Y:
				_updateCurrentValue = std::tr1::bind(&GamePadAxisInputItem::updateCurrentValueStickRightY, this);
				break;
			case GamePadAxisInputItemType::TRIGGER_LEFT:
				_updateCurrentValue = std::tr1::bind(&GamePadAxisInputItem::updateCurrentValueTriggerLeft, this);
				break;
			case GamePadAxisInputItemType::TRIGGER_RIGHT:
				_updateCurrentValue = std::tr1::bind(&GamePadAxisInputItem::updateCurrentValueTriggerRight, this);
				break;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadAxisInputItem::GamePadAxisInputItem(const GamePadAxisInputItem & obj) {
		InputItem::copyFrom(obj);
		_type = obj._type;
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadAxisInputItem::~GamePadAxisInputItem() {}
}
