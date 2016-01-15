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
Contiene la implementación del componente que controla la vida de una entidad.
*/

#include <assert.h>

#include "Logic/Entity/Components/Life.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/MissionManager.h"
#include "Logic/HUDController.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Messages/DamagedMessage.h"
#include "Logic/Entity/Messages/PowerUpMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool Life::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		if(entityInfo->hasAttribute("life")) {
			_maxLife = entityInfo->getAttributeAsFloat("life");
			_life = _maxLife;
		} else {
			_life = 100.0f;		// Por defecto un valor de 100
			_maxLife = 100.0f;
		}

		// Si el propietario del componente es el jugador, inicializamos el HUD adecuadamente
		_isPlayer = _owner->getComponentAs<GeneralData>("GeneralData")->isPlayer();
		if(_isPlayer)
		{
			MissionManager::GetInstance()->getHUDController()->updateLifeBar(_life);
			MissionManager::GetInstance()->getHUDController()->updateLifeCounter(_playerLifeCounter);
		}
		// Comprobamos si la entidad propietaria del componente es una bala (enemiga o jugador) o un jefe final de nivel
		else if (_owner->getType() == "Bullet" || _owner->getType() == "BulletBoss1" || _owner->getType() == "BulletBoss2") {
			_isBullet = true; }
		else if (_owner->getType() == "Bullet2" || _owner->getType() == "PowerBullet") {
			_isPlayerBullet = true; }
		else if (_owner->getType() == "BossLevel1" || _owner->getType() == "BossLevel2") {
			_isBoss = true; }
		

		return true;
	}
	
	//---------------------------------------------------------

	bool Life::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_DAMAGED ||
			message->getType() == MESSAGE_TYPE_POWER_UP;
	}
	
	//---------------------------------------------------------

	void Life::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_DAMAGED:
			// Disminuimos la vida de la entidad si no está en modo invincibilidad
			if (!_invincibility){
				_life -= message->getDataRefAs<DamagedMessage>().getValue();
				// Mostramos un SP de chispazos para mostrar feedback de daño recibido
				if (!_isBullet && !_isPlayerBullet && !_isBoss) {
					_owner->sendMessage(MessageFactory::CreateParticleSystemMessage("Chispas"));
				}
				else if (_isBoss) {
					_owner->sendMessage(MessageFactory::CreateParticleSystemMessage("BigChispas"));
				}
			}

			//==================================================================================
			// Referente al jugador:
			//==================================================================================
			// Si el jugador es quién ha recibido el daño... actualizamos el HUD			
			if (_isPlayer) MissionManager::GetInstance()->getHUDController()->updateLifeBar(_life);

			// Si han matado al jugador...
			if (_life<=0 && _isPlayer) {

				if (_playerLifeCounter>=0)		// Y todavía le quedan vidas...
				{
					// Restauramos la cantidad de vida al completo, le restamos una vida y actualizamos el HUD
					_life = _maxLife;
					_playerLifeCounter--;
					MissionManager::GetInstance()->getHUDController()->updateLifeBar(_life);
					if (_playerLifeCounter>=0) MissionManager::GetInstance()->getHUDController()->updateLifeCounter(_playerLifeCounter);
					//printf("Player lives = %i\n", _playerLifeCounter);

					// Enviamos un mensaje de PLAYER_DEAD
					_owner->sendMessage(MessageFactory::CreatePlayerDeadMessage());

				} else {						// Si ya no le quedan vidas...

					// Enviamos un mensaje de PLAYER_DEAD					
					_owner->sendMessage(MessageFactory::CreatePlayerDeadMessage());
				}
			}
			//==================================================================================
			// Referente a las balas:
			//==================================================================================
			// Si ha perdido toda su vida y se trata de una bala del jugador... pasamos a su estado OFF
			else if ((_life <= 0) && (!_dead) && (_isPlayerBullet))
			{
				_owner->sendMessage(MessageFactory::CreateLifeCycleOFFMessage());
				_dead = true;
			}
			// Si ha perdido toda su vida y se trata de una bala enemiga... la liberamos directamente
			else if ((_life <= 0) && (!_dead) && (_isBullet))
			{
				_owner->sendMessage(MessageFactory::CreateLifeCycleRELEASEMessage());
				_dead = true;
			}

			//==================================================================================
			// Referente al resto de entidades:
			//==================================================================================
			// Si ha perdido toda su vida... pasamos a un estado de "muriendo" (OFF)
			else if ((_life <= 0) && (!_dead))
			{
				_owner->sendMessage(MessageFactory::CreateLifeCycleOFFMessage());				
				_dead = true;
			}			

			break;

		case MESSAGE_TYPE_POWER_UP:
			if ((message->getDataRefAs<PowerUpMessage>().getPowerUp() == INVINCIBILITY)||
				(message->getDataRefAs<PowerUpMessage>().getPowerUp() == BERSERKER)){
				if (message->getDataRefAs<PowerUpMessage>().getActivate()){
					//Activar invincibilidad
					_invincibility = true;
				}else{
					//Desactivar invincibilidad
					_invincibility = false;
				}
			}
			if ((message->getDataRefAs<PowerUpMessage>().getPowerUp() == HEAL)||
				(message->getDataRefAs<PowerUpMessage>().getPowerUp() == BERSERKER)){
				if (message->getDataRefAs<PowerUpMessage>().getActivate()){
					//Activar autocura
					_autoHeal = true;
					_actualHealTime = 0;
				}else{
					//Desactivar autocura
					_autoHeal = false;
					_actualHealTime = 0;
				}
			}
			break;
		}
	}

	//---------------------------------------------------------

	void Life::update(unsigned int lastInterval){
		Component::update(lastInterval);
		//Si tenemos activado el autoheal, subimos la vida cada cierto tiempo.
		if (_autoHeal){
			if (_healInterval<_actualHealTime){
				_actualHealTime = 0;
				if (_life < _maxLife){
					_life += 1;
					MissionManager::GetInstance()->getHUDController()->updateLifeBar(_life);
				}
			}else{
				_actualHealTime += lastInterval;
			}
		}
	}
}
