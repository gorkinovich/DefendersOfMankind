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
@file PowerUpController.cpp

Controlador del estado de los power ups activados en el jugador.

@see Logic::PowerUpController
@see Core::Component

@author Grupo 3
@date Junio, 2011
*/

#include <assert.h>

#include "Logic/Entity/Components/PowerUpController.h"
#include "Logic/Entity/Messages/PowerUpMessage.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/MessageFactory.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"

namespace Logic 
{
	bool PowerUpController::spawn(const Core::EntityInfoTable *entityInfo)
	{
		assert(_owner && "The component does not have an entity...");

		// Tiempo de vida del efecto de los power ups (10 segundos)
		_powerUpTotalTime = 10000;
		return true;
	}
	
	//---------------------------------------------------------

	bool PowerUpController::activate()
	{
		return true;
	}
	
	//---------------------------------------------------------

	void PowerUpController::deactivate()
	{
	}
	
	//---------------------------------------------------------

	bool PowerUpController::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_POWER_UP;
	}
	
	//---------------------------------------------------------

	void PowerUpController::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_POWER_UP:
			{
				if (message->getDataRefAs<PowerUpMessage>().getActivate()){
					PowerUpType type = message->getDataRefAs<PowerUpMessage>().getPowerUp();
					switch (type){
						case AUTOFIRE:			// La nave dispara automáticamente
							_autoFireTime = 0;
							_autoFire = true;
							break;

						case INVINCIBILITY:		// No se recibe ningún daño
							_invincibilityTime = 0;
							_invincibility = true;
							// Mostramos el SP de "Shield"
							_owner->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("Shield"));
							break;

						case SPEEDUP:			// Aumenta la velocidad de movimiento
							_superSpeedTime = 0;
							_superSpeed = true;
							// Mostramos el SP de "Turbo"
							_owner->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("Turbo"));
							break;

						case HEAL:				// Recupera vida progresivamente
							_autoHealTime = 0;
							_autoHeal = true;
							// Mostramos el SP de "AutoHeal"
							_owner->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("AutoHeal"));
							break;

						case DAMAGEUP:			// Los disparos hacen el doble de daño
							_damageUpTime = 0;
							_damageUp = true;
							break;

						case BERSERKER:			// Todos los anteriores a la vez
							_autoFireTime = 0;
							_autoFire = true;
							_invincibilityTime = 0;
							_invincibility = true;
							_superSpeedTime = 0;
							_superSpeed = true;
							_autoHealTime = 0;
							_autoHeal = true;
							_damageUpTime = 0;
							_damageUp = true;
							// Mostramos el SP de "Berserker"
							_owner->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("Berserker"));
							break;
						default:
							break;
					}
				}
			}
			break;
		}
	}

	//----------------------------------------------------------

	void PowerUpController::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);
		
		if(_autoFire){
			_autoFireTime += lastInterval;
			if (_autoFireTime >= _powerUpTotalTime){
				_autoFireTime = 0;
				_autoFire = false;
				//Eliminar efecto
				_owner->sendMessage(MessageFactory::CreatePowerUpMessage(AUTOFIRE, false));
			}
		}

		if(_invincibility){
			_invincibilityTime += lastInterval;
			if (_invincibilityTime >= _powerUpTotalTime){
				_invincibilityTime = 0;
				_invincibility = false;
				//Eliminar efecto
				_owner->sendMessage(MessageFactory::CreatePowerUpMessage(INVINCIBILITY, false));
			}
		}

		if(_superSpeed){
			_superSpeedTime += lastInterval;
			if (_superSpeedTime >= _powerUpTotalTime){
				_superSpeedTime = 0;
				_superSpeed = false;
				//Eliminar efecto
				_owner->sendMessage(MessageFactory::CreatePowerUpMessage(SPEEDUP, false));
			}
		}

		if(_autoHeal){
			_autoHealTime += lastInterval;
			if (_autoHealTime >= _powerUpTotalTime){
				_autoHealTime = 0;
				_autoHeal = false;
				//Eliminar efecto
				_owner->sendMessage(MessageFactory::CreatePowerUpMessage(HEAL, false));
			}
		}

		if(_damageUp){
			_damageUpTime += lastInterval;
			if (_damageUpTime >= _powerUpTotalTime){
				_damageUpTime = 0;
				_damageUp = false;
				//Eliminar efecto
				_owner->sendMessage(MessageFactory::CreatePowerUpMessage(DAMAGEUP, false));
			}
		}

	}
}
