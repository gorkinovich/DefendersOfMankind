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
@file KillEntities.cpp

Componente encargado de enviar un mensaje de tipo LIFE_CYCLE_ON a toda entidad que entra en el volumen de colisión
de la entidad propietaria del componente (caja de la muerte).
A su vez envía un mensaje de tipo LIFE_CYCLE_RELEASE a toda entidad que sale de dicho volumen de colisión.


@see Logic::KillEntities
@see Core::Component

@author Grupo 3
@date Abril, 2011
*/

#include <assert.h>

#include "Logic/Entity/Components/KillEntities.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool KillEntities::spawn(const Core::EntityInfoTable *entityInfo)
	{
		assert(_owner && "The component does not have an entity...");

		// Obtenemos las dimensiones del "cubo de la muerte"
		if(entityInfo->hasAttribute("physic_dimensions")) {
			_dim = entityInfo->getAttributeAsVector3("physic_dimensions");
		}

		return true;
	}
	
	//---------------------------------------------------------

	bool KillEntities::activate()
	{
		// Obtenemos el centro de la acción
		Vector3 pos = Logic::MissionManager::GetInstance()->getCenter();

		// Posicionamos correctamente el cubo con respecto a la acción
		pos.y = pos.y - (_dim.y/2);
		_positionComponent = _owner->getComponentAs<Position>("Position");
		_positionComponent->setPosition(pos);

		return true;
	}
	
	//---------------------------------------------------------

	void KillEntities::deactivate()
	{
	}
	
	//---------------------------------------------------------

	bool KillEntities::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_TOUCHED ||
			message->getType() == MESSAGE_TYPE_UNTOUCHED;
	}
	
	//---------------------------------------------------------

	void KillEntities::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_TOUCHED:
			{
				// Activar la entidad
				Core::Entity* victim = message->getDataRefAs<CollisionMessage>().getVictim();
				if(victim != _lastVictim2)	// HACK: para evitar múltiples mensajes repetidos
				{							// Cuando encuentre el fallo lo quitaré
					//printf("Entrada: %i\n", (int) victim);
					victim->sendMessage(MessageFactory::CreateLifeCycleONMessage());
					_lastVictim2 = victim;
				}	
			}
			break;

		case MESSAGE_TYPE_UNTOUCHED:
			{
				// Eliminar entidad
				const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
				Core::Entity* victim = msgData.getVictim();
				if(!victim->getComponentAs<GeneralData>("GeneralData")->isPlayer())
				{
					if(victim != _lastVictim)	// HACK: para evitar múltiples mensajes repetidos
					{							// Cuando encuentre el fallo lo quitaré
						//printf("Salida/muerte: %i\n", (int) victim);
						victim->sendMessage(MessageFactory::CreateLifeCycleRELEASEMessage());
						_lastVictim = victim;
					}				
				}
			}
			break;
		}
	}

	//----------------------------------------------------------

	void KillEntities::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		// Obtenemos el centro de la acción
		Vector3 pos = Logic::MissionManager::GetInstance()->getCenter();

		// Posicionamos correctamente el cubo con respecto a la acción
		pos.y = pos.y - (_dim.y/2);
		_positionComponent->setPosition(pos);
		
	}
}
