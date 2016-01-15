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
Contiene la declaración del componente que inicia la destrucción (retrasada) de la entidad padre.
Procesa mensajes de tipo DEATH.
*/

#include <assert.h>

#include "Logic/Entity/Components/Death.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/DeathMessage.h"

namespace Logic 
{
	bool Death::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		return true;
	}
	
	//---------------------------------------------------------

	bool Death::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_DEATH;
	}
	
	//---------------------------------------------------------

	void Death::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_DEATH:
			_timeToDie = message->getDataRefAs<DeathMessage>().getTimeToDie();
			_dying = true;
			break;
		}
	}

	//----------------------------------------------------------

	void Death::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		if (_dying)
		{
			if(_timeToDie > 0)
			{
				_timeToDie -= lastInterval;
			}
			else if(_die == false)
			{
				if(_owner->getComponentAs<GeneralData>("GeneralData")->isPlayer()) {
					printf("Player dead !!\n");
					//GOTO GAMEOVERSTATE
				} else {
					Core::EntitiesManager::GetInstance()->deferredDeleteEntity(_owner);
					//printf("Muerte !!\n");
					_dying = false;
				}

				_die = true;
			}
		}
	}
}
