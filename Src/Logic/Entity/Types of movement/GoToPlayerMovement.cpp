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
* Esta clase representa un tipo de movimiento que constantemente se dirige hacia la posición actual del jugador.
*/
#include <assert.h>

#include "GoToPlayerMovement.h"

//#include "Logic/MissionManager.h"
#include "Core/Entities/World.h"
#include "Logic/Entity/Messages/MessageFactory.h"


namespace Logic
{

	bool GoToPlayerMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// Guardamos el puntero de la entidad propietaria del movimiento (ya que en éste tipo de movimiento si 
		// es necesaria para usos futuros).
		_owner = owner;

		// Obtenemos los datos leidos del descriptor
		if(info->hasAttribute("velocity") && info->hasAttribute("verticalVelocity") && info->hasAttribute("playerTarget"))
		{
			_vel = info->getAttributeAsFloat("velocity");
			_velVert = info->getAttributeAsFloat("verticalVelocity");
			_playerTarget = info->getAttributeAsInteger("playerTarget");
			assert((_playerTarget==1 || _playerTarget==2)  && "GoToPlayerMovement::spawn --> Identificador del jugador a seguir no válido.");
			return true;
		}

		return false;
	}

	//-----------------------------------------------

	bool GoToPlayerMovement::activate()
	{
		Core::Entity* player=0;

		// Obtenemos la entidad "Jugador" a seguir
		if (_playerTarget==2)
		{
			 player = _owner->getWorld()->getEntityByName("Jugador2");
			// Si el jugador2 no existe o esta muerto, seguimos al jugador 1.
			if(player==0) player = _owner->getWorld()->getEntityByName("Jugador1");
		}
		else
		{
			player = _owner->getWorld()->getEntityByName("Jugador1");
		}
		assert(player && "GoToPlayerMovement::activate --> Entidad Jugador no encontrada.");

		// Obtenemos la entidad "Jugador"	(de MISSIONMANAGER !!)
		//Core::Entity* player = MissionManager::GetInstance()->getPlayer();
		//assert(player && "GoToPlayerMovement::activate --> Entidad Jugador1 no encontrada.");

		// Obtenemos su componente de posición
		_playerPositionComponent = player->getComponentAs<Position>("Position");
		assert(_playerPositionComponent && "GoToPlayerMovement::activate --> Componente <Position> del Jugador1 no válido.");

		return true;
	}

	//-----------------------------------------------

	void GoToPlayerMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// Obtenemos la posición actual del jugador
		Vector3 playerPos = _playerPositionComponent->getPosition();

		// Dependiendo de la vista actual...
		if(actualView==SIDE || actualView==SIDE_ROTATE)
		{
			posAxis.first>playerPos.y ? posAxis.first-=(float) (_velVert * (lastInterval*0.02)) : posAxis.first+=(float) (_velVert * (lastInterval*0.02));
		}
		else
		{
			posAxis.first>-playerPos.x ? posAxis.first-=(float) (_velVert * (lastInterval*0.02)) : posAxis.first+=(float) (_velVert * (lastInterval*0.02));
		}

		posAxis.second>playerPos.z ? _owner->sendMessage(MessageFactory::CreateLifeCycleOFFMessage()) : posAxis.second+=(float) (_vel * (lastInterval*0.02));
	}

	//---------------------------------------------------------

	bool GoToPlayerMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void GoToPlayerMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------

} // namespace Logic