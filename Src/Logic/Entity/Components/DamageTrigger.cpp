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
Contiene la implementación del componente que envia un mensaje DAMAGED cuando su 
entidad es tocada. El mensaje se envía a la entidad que se ha tocado.
*/

#include <assert.h>

#include "Logic/Entity/Components/DamageTrigger.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool DamageTrigger::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		if(entityInfo->hasAttribute("damage")) {
			_damage = entityInfo->getAttributeAsFloat("damage");
		}

		return true;
	}

	//---------------------------------------------------------

	bool DamageTrigger::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_TOUCHED;
	}
	
	//---------------------------------------------------------

	void DamageTrigger::processMessage(const Core::SmartMessage & message)
	{
		// Cuando la entidad propietaria de éste componente ha sido tocada...
		switch(message->getType())
		{
		case MESSAGE_TYPE_TOUCHED:
			// ... envía un mensaje de daño a la entidad que la tocó
			{
				const CollisionMessage & msgData = message->getDataRefAs<CollisionMessage>();
				Core::Entity * victim = msgData.getVictim();
				victim->sendMessage(MessageFactory::CreateDamagedMessage(_damage));
			}
			break;
		}
	}
}
