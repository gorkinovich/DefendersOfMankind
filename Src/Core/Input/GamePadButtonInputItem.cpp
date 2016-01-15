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
#include "Core/Input/GamePadButtonInputItem.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GamePadButtonInputItem::changeCondition() const {
		return _currentValue != _previousValue;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValue() {
		_previousValue = _currentValue;
		_updateCurrentValue();
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::callMethod(IGamePadButtonInputActionMethod & method) {
		method.gamePadButtonInputChanged(*this);
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueA() {
		_currentValue = GamePads::GetState(_player).buttons.a;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueB() {
		_currentValue = GamePads::GetState(_player).buttons.b;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueX() {
		_currentValue = GamePads::GetState(_player).buttons.x;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueY() {
		_currentValue = GamePads::GetState(_player).buttons.y;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueLeftShoulder() {
		_currentValue = GamePads::GetState(_player).buttons.leftShoulder;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueRightShoulder() {
		_currentValue = GamePads::GetState(_player).buttons.rightShoulder;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueLeftStick() {
		_currentValue = GamePads::GetState(_player).buttons.leftStick;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueRightStick() {
		_currentValue = GamePads::GetState(_player).buttons.rightStick;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueBack() {
		_currentValue = GamePads::GetState(_player).buttons.back;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueStart() {
		_currentValue = GamePads::GetState(_player).buttons.start;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueUp() {
		_currentValue = GamePads::GetState(_player).dpad.up;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueDown() {
		_currentValue = GamePads::GetState(_player).dpad.down;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueLeft() {
		_currentValue = GamePads::GetState(_player).dpad.left;
	}

	//--------------------------------------------------------------------------------------------------------

	void GamePadButtonInputItem::updateCurrentValueRight() {
		_currentValue = GamePads::GetState(_player).dpad.right;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GamePadButtonInputItem::GamePadButtonInputItem(GamePadButtonElement type, unsigned short player) : _type(type), _player(player) {
		assert(player < PAD_MAX_PLAYERS && "GamePadButtonInputItem::GamePadButtonInputItem -> Player ID invalid...");
		_previousValue = false;
		_currentValue = false;
		switch(_type) {
			default:
			case GamePadButtonInputItemType::A:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueA, this);
				break;
			case GamePadButtonInputItemType::B:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueB, this);
				break;
			case GamePadButtonInputItemType::X:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueX, this);
				break;
			case GamePadButtonInputItemType::Y:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueY, this);
				break;
			case GamePadButtonInputItemType::LEFT_SHOULDER:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueLeftShoulder, this);
				break;
			case GamePadButtonInputItemType::RIGHT_SHOULDER:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueRightShoulder, this);
				break;
			case GamePadButtonInputItemType::LEFT_STICK:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueLeftStick, this);
				break;
			case GamePadButtonInputItemType::RIGHT_STICK:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueRightStick, this);
				break;
			case GamePadButtonInputItemType::BACK:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueBack, this);
				break;
			case GamePadButtonInputItemType::START:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueStart, this);
				break;
			case GamePadButtonInputItemType::UP:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueUp, this);
				break;
			case GamePadButtonInputItemType::DOWN:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueDown, this);
				break;
			case GamePadButtonInputItemType::LEFT:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueLeft, this);
				break;
			case GamePadButtonInputItemType::RIGHT:
				_updateCurrentValue = std::tr1::bind(&GamePadButtonInputItem::updateCurrentValueRight, this);
				break;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadButtonInputItem::GamePadButtonInputItem(const GamePadButtonInputItem & obj) {
		InputItem::copyFrom(obj);
		_type = obj._type;
	}

	//--------------------------------------------------------------------------------------------------------

	GamePadButtonInputItem::~GamePadButtonInputItem() {}
}
