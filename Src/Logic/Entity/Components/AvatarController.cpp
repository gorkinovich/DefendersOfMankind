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

/** 
Contiene la implementación del componente que controla el movimiento de la entidad.
*/


#include <assert.h>

#include "Logic/Entity/Components/AvatarController.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Input/InputListenersManager.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/CameraType.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Components/PhysicCharacter.h"
#include "Logic/Entity/Components/PowerUpController.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/PowerUpMessage.h"
#include "Logic/Entity/Messages/SetAngleToRotateMessage.h"

namespace Logic 
{
	bool AvatarController::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		if(entityInfo->hasAttribute("speed")) {	
			_speed = entityInfo->getAttributeAsFloat("speed");
		}
		
		Vector3 center = Logic::MissionManager::GetInstance()->getCenter();
		Position * positionComponent = _owner->getComponentAs<Position>("Position");
		Vector3 newPosition = center + _offset;
		positionComponent->setPosition(newPosition);

		return true;
	}
	
	//---------------------------------------------------------

	bool AvatarController::activate()
	{
		float dist = Logic::MissionManager::GetInstance()->getDistance();
		_limitX = dist * 0.5f;
		_limitY = dist * 0.3f;
		_limitZ = dist * 0.5f;

		// Si somos el jugador nos registramos para que nos informen
		// de los movimientos que devemos realizar.
		if(_owner->getComponentAs<GeneralData>("GeneralData")->isPlayer()) {
			Core::InputListenersManager * ilm = Core::InputListenersManager::GetInstance();
			ilm->addKeyPressedDelegate(this, CreateKeyboardDelegate(&AvatarController::keyPressed, this));
			ilm->addKeyReleasedDelegate(this, CreateKeyboardDelegate(&AvatarController::keyReleased, this));
			ilm->addGamePadAxisDelegate(this, CreateGamePadDelegate(&AvatarController::gamePadAxis, this));
			ilm->addGamePadPressedDelegate(this, CreateGamePadDelegate(&AvatarController::gamePadPressed, this));
			ilm->addGamePadReleasedDelegate(this, CreateGamePadDelegate(&AvatarController::gamePadReleased, this));
			
		}
		return true;
	}
	
	//---------------------------------------------------------

	void AvatarController::deactivate()
	{
		// Si somos el jugador evitamos que se nos siga informando.
		if(_owner->getComponentAs<GeneralData>("GeneralData")->isPlayer()) {
			Core::InputListenersManager * ilm = Core::InputListenersManager::GetInstance();
			ilm->removeKeyPressedDelegate(this);
			ilm->removeKeyReleasedDelegate(this);
			ilm->removeGamePadAxisDelegate(this);
			ilm->removeGamePadPressedDelegate(this);
			ilm->removeGamePadReleasedDelegate(this);
		}
	}
	
	//---------------------------------------------------------

	void AvatarController::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		// Si nos estamos desplazando calculamos la próxima posición
		// Calculamos si hay vectores de dirección de avance y strafe,
		// hayamos la dirección de la suma y escalamos según la
		// velocidad y el tiempo transcurrido.
		CameraType cam = Logic::MissionManager::GetInstance()->getCameraType();
		Vector3 center = Logic::MissionManager::GetInstance()->getCenter();
		Position * positionComponent = _owner->getComponentAs<Position>("Position");
		PhysicCharacter * physicComponent = _owner->getComponentAs<PhysicCharacter>("PhysicCharacter");
		Vector3 actPosition = positionComponent->getPosition();

		if(((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE))&& (actPosition.x != center.x)){
			_travelTime += lastInterval;
			Vector3 direction(Vector3::ZERO);
			direction.x -= (actPosition.x - center.x);
			if (_travelTime >= 1000){
				_travelTime = 0.0f;
			}else{
				direction*= ((Ogre::Real)lastInterval*(Ogre::Real)0.001);
			}
			
			_owner->sendMessage(MessageFactory::CreateAvatarWalkMessage(direction));

			positionComponent->setPosition(actPosition + direction);

		}else if (((cam == Logic::UPPER)||(cam == Logic::UPPER_ROTATE))&& (actPosition.y != center.y)){
			_travelTime += lastInterval;
			Vector3 direction(Vector3::ZERO);
			direction.y -= (actPosition.y - center.y);
			if (_travelTime >= 1000){
				_travelTime = 0.0f;
			}else{
				direction*= ((Ogre::Real)lastInterval*(Ogre::Real)0.001);
			}
			
			_owner->sendMessage(MessageFactory::CreateAvatarWalkMessage(direction));

			positionComponent->setPosition(actPosition + direction);
		}

		//Si no se pulsa ninguna de las teclas de movimiento, se gira la nave para que parezca estabilizada
		if(((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE) && !_up && !_down)
		|| ((cam == Logic::UPPER)||(cam == Logic::UPPER_ROTATE) && !_left && !_right)) {
			positionComponent->changeDestinationAngleZ(0.0f);
			_owner->sendMessage(MessageFactory::CreateSetAngleToRotateMessage(0.0f));
		}

		if(_up || _down || _left || _right || _fire || _autoFire) {
			Vector3 direction(Vector3::ZERO);

			if(_up)
			{
				if((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE)) {
					if (actPosition.y<center.y+_limitY) {
						direction += Vector3::UNIT_Y;
						positionComponent->changeDestinationAngleZ(45.0f);
//						_owner->sendMessage(MessageFactory::CreateSetAngleToRotateMessage(45.0f));
					}
				} else if((cam == Logic::UPPER)||(cam == Logic::UPPER_ROTATE)) {
					if(cam == Logic::UPPER) {
						if(actPosition.z>center.z-_limitY) {
							direction -= Vector3::UNIT_Z;
						}
					} else {
						if(actPosition.z>center.z-_limitZ) {
							direction -= Vector3::UNIT_Z;
						}
					}
				}
			}

			if(_down)
			{
				if((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE)) {
					if(actPosition.y>center.y-_limitY) {
						direction -= Vector3::UNIT_Y;
						positionComponent->changeDestinationAngleZ(-45.0f);
//						_owner->sendMessage(MessageFactory::CreateSetAngleToRotateMessage(-45.0f));
					}
				} else if((cam == Logic::UPPER)||(cam == Logic::UPPER_ROTATE)) {
					if(cam == Logic::UPPER) {
						if(actPosition.z<center.z+_limitY){
							direction += Vector3::UNIT_Z;
						}
					} else {
						if(actPosition.z<center.z+_limitZ) {
							direction += Vector3::UNIT_Z;
						}
					}
				}
			}

			if(_left)
			{
				if((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE)) {
					if(cam == Logic::SIDE) {
						if(actPosition.z<center.z+_limitZ) {
							direction += Vector3::UNIT_Z;
						}
					} else {
						if(actPosition.z<center.z+_limitZ) {
							direction += Vector3::UNIT_Z;
						}
					}
				} else if((cam == Logic::UPPER)||(cam == Logic::UPPER_ROTATE)) {
					if(actPosition.x>center.x-_limitX) {
						direction -= Vector3::UNIT_X;
						positionComponent->changeDestinationAngleZ(45.0f);
//						_owner->sendMessage(MessageFactory::CreateSetAngleToRotateMessage(45.0f));
					}
				}
			}

			if(_right)
			{
				if((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE)) {
					if(cam == Logic::SIDE) {
						if(actPosition.z>center.z-_limitZ) {
							direction -= Vector3::UNIT_Z;
						}
					} else {
						if(actPosition.z>center.z-_limitZ) {
							direction -= Vector3::UNIT_Z;
						}
					}
				} else if((cam == Logic::UPPER)||(cam == Logic::UPPER_ROTATE)) {
					if(actPosition.x<center.x+_limitX) {
						direction += Vector3::UNIT_X;
						positionComponent->changeDestinationAngleZ(-45.0f);
//						_owner->sendMessage(MessageFactory::CreateSetAngleToRotateMessage(-45.0f));
					}
				}
			}
			std::stringstream ss;

			if (_autoFire){
				if (_fireTime>=50){
					_fireTime =0;
					if(!Logic::MissionManager::GetInstance()->getPlayer()->getComponentAs<Logic::PowerUpController>("PowerUpController")->getDamageUp()) {
						ss.str(""); ss <<_owner->getName() << "Child1";
						std::cout << ss.str() << std::endl;
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
						ss.str(""); ss <<_owner->getName() << "Child2";
						std::cout << ss.str() << std::endl;
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
					} else {
						ss.str(""); ss <<_owner->getName() << "Child3";
						std::cout << ss.str() << std::endl;
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
						ss.str(""); ss <<_owner->getName() << "Child4";
						std::cout << ss.str() << std::endl;
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
					}
				}else{
					_fireTime += lastInterval;
				}
			}else{
				if(_fire)
				{
					if(!Logic::MissionManager::GetInstance()->getPlayer()->getComponentAs<Logic::PowerUpController>("PowerUpController")->getDamageUp()) {
						ss.str(""); ss <<_owner->getName() << "Child1";
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
						ss.str(""); ss <<_owner->getName() << "Child2";
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
					} else {	//Creamos las balas de mayor daño
						ss.str(""); ss <<_owner->getName() << "Child3";
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
						ss.str(""); ss <<_owner->getName() << "Child4";
						_owner->sendMessage(MessageFactory::CreateCreateChildMessage(0, ss.str()));
					}
					_fire = false;
				}
			}

			direction *= lastInterval * _speed;

			//Si tenemos activado el powerup, aumentamos la velocidad
			if (_speedUp){
				direction *= 2.0f;
			}

			//Enviar un mensaje para que el componente físico mueva el personaje
			//_owner->sendMessage(MessageFactory::CreateAvatarWalkMessage(direction));
			physicComponent->setMovement(direction);
			
			_offset += direction;	
		}

		//Si estamos moviéndonos por una bifurcación, la nave queda inclinada
		if(Logic::MissionManager::GetInstance()->getBifurcation()) {
			if((cam == Logic::SIDE)||(cam == Logic::SIDE_ROTATE)) {
				if(Logic::MissionManager::GetInstance()->getBifurcationDirection().y > 0) {
					positionComponent->changeDestinationAngleZ(45.0f);
				} else {
					positionComponent->changeDestinationAngleZ(-45.0f);
				}
			} else {
				if(Logic::MissionManager::GetInstance()->getBifurcationDirection().x < 0) {
					positionComponent->changeDestinationAngleZ(45.0f);
				} else {
					positionComponent->changeDestinationAngleZ(-45.0f);
				}
			}
		}

		//Vector3 newPosition = center + _offset;//positionComponent->getPosition() + direction;
		//physicComponent->setMovement(Vector3::UNIT_Z * (-0.1f) * (Ogre::Real)lastInterval);
		//positionComponent->setPosition(newPosition);
		/*printf("Offset X: %f; Y: %f; Z: %f\n", _offset.x, _offset.y, _offset.z);
		printf("Center X: %f; Y: %f; Z: %f\n", center.x, center.y, center.z);
		printf("Position X: %f; Y: %f; Z: %f\n", newPosition.x, newPosition.y, newPosition.z);*/
	}

	//--------------------------------------------------------------------------------------------------------

	bool AvatarController::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_POWER_UP;
	}
	
	//--------------------------------------------------------------------------------------------------------

	void AvatarController::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_POWER_UP:
			{
				if ((message->getDataRefAs<PowerUpMessage>().getPowerUp() == SPEEDUP)||
					(message->getDataRefAs<PowerUpMessage>().getPowerUp() == BERSERKER)){
					if (message->getDataRefAs<PowerUpMessage>().getActivate()){
						_speedUp = true;
					}else{
						_speedUp = false;
					}
				}
				if ((message->getDataRefAs<PowerUpMessage>().getPowerUp() == AUTOFIRE)||
					(message->getDataRefAs<PowerUpMessage>().getPowerUp() == BERSERKER)){
					if (message->getDataRefAs<PowerUpMessage>().getActivate()){
						_autoFire = true;
					}else{
						_autoFire = false;
					}
				}
				if ((message->getDataRefAs<PowerUpMessage>().getPowerUp() == DAMAGEUP)||
					(message->getDataRefAs<PowerUpMessage>().getPowerUp() == BERSERKER)){
					if (message->getDataRefAs<PowerUpMessage>().getActivate()){
						_damageUp = true;
					}else{
						_damageUp = false;
					}
				}
			}
			break;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool AvatarController::keyPressed(Core::KeyCode key) {
		switch(key) {
		case Core::Key::KEY_LEFT:
			_left = true;
			break;
		case Core::Key::KEY_RIGHT:
			_right = true;
			break;
		case Core::Key::KEY_UP:
			_up = true;
			break;
		case Core::Key::KEY_DOWN:
			_down = true;
			break;
		case Core::Key::KEY_RCONTROL:
		case Core::Key::KEY_LCONTROL:
			_fire = true;
			break;
		default:
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool AvatarController::keyReleased(Core::KeyCode key) {
		switch(key) {
		case Core::Key::KEY_LEFT:
			_left = false;
			break;
		case Core::Key::KEY_RIGHT:
			_right = false;
			break;
		case Core::Key::KEY_UP:
			_up = false;
			break;
		case Core::Key::KEY_DOWN:
			_down = false;
			break;
		case Core::Key::KEY_RCONTROL:
		case Core::Key::KEY_LCONTROL:
			_fire = false;
			break;
		case Core::Key::KEY_N1:
			//Logic::MissionManager::GetInstance()->getCamera()->sendMessage(MessageFactory::CreateChangeViewMessage(SIDE));
			break;
		case Core::Key::KEY_N2:
			//Logic::MissionManager::GetInstance()->getCamera()->sendMessage(MessageFactory::CreateChangeViewMessage(SIDE_ROTATE));
			break;
		case Core::Key::KEY_N3:
			//Logic::MissionManager::GetInstance()->getCamera()->sendMessage(MessageFactory::CreateChangeViewMessage(UPPER));
			break;
		case Core::Key::KEY_N4:
			//Logic::MissionManager::GetInstance()->getCamera()->sendMessage(MessageFactory::CreateChangeViewMessage(UPPER_ROTATE));
			break;
		default:
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool AvatarController::gamePadAxis(const Core::GamePadState & state, unsigned short player) {
		if(player == PAD_PLAYER1) {
			bool moved = false;
			if(state.leftStick.x > 0) {
				_right = true;
				moved = true;
			} else if(state.leftStick.x < 0) {
				_left = true;
				moved = true;
			} else {
				_right = false;
				_left = false;
			}
			if(state.leftStick.y > 0) {
				_up = true;
				moved = true;
			} else if(state.leftStick.y < 0) {
				_down = true;
				moved = true;
			} else {
				_up = false;
				_down = false;
			}
			return moved;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool AvatarController::gamePadPressed(const Core::GamePadState & state, unsigned short player) {
		if(player == PAD_PLAYER1) {
			if(state.buttons.a) {
				_fire = true;
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool AvatarController::gamePadReleased(const Core::GamePadState & state, unsigned short player) {
		if(player == PAD_PLAYER1) {
			if(!state.buttons.a) {
				_fire = false;
				return true;
			}
		}
		return false;
	}
}
