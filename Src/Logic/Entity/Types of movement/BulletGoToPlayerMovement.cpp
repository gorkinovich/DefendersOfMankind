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
 * Esta clase representa un tipo de movimiento rectilíneo, moviendo la entidad hacia donde se encuentraba el
 * jugador (al crearse la entidad "bala") en base a un vector dirección.
 */

#include "BulletGoToPlayerMovement.h"

#include "Core/Entities/World.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/MissionManager.h"

#include <math.h>

namespace Logic
{

	bool BulletGoToPlayerMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// Guardamos el puntero de la entidad propietaria del movimiento (ya que en éste tipo de movimiento si 
		// es necesaria para usos futuros).
		_owner = owner;

		// Inicializamos los atributos propios del movimiento en base a los datos del descriptor
		if(info->hasAttribute("velocityAxis1") && info->hasAttribute("velocityAxis2"))
		{
			_velAxis1 = info->getAttributeAsFloat("velocityAxis1");
			_velAxis2 = info->getAttributeAsFloat("velocityAxis2");
			return true;
		}

		return false;
	}

	//-------------------------------------------

	bool BulletGoToPlayerMovement::activate()
	{
		if (!_initialized)
		{
			// Obtenemos la posición actual del jugador
			Core::Entity* player = _owner->getWorld()->getEntityByName("Jugador1");
			assert(player && "BulletGoToPlayerMovement::activate --> Entidad Jugador no encontrada.");
			Position* playerPositionComponent = player->getComponentAs<Position>("Position");
			assert(playerPositionComponent && "BulletGoToPlayerMovement::activate --> Componente <Position> del jugador no válido.");
			Vector3 playerPos = playerPositionComponent->getPosition();

			_dir.first = 0.0f;
			_dir.second = 0.0f;

			// Obtenemos la posición actual de la entidad
			Vector3 entityPos = _owner->getComponentAs<Position>("Position")->getPosition();

			// Calculamos el vector director
			CameraType actualView = Logic::MissionManager::GetInstance()->getCameraType();
			if (actualView==SIDE || actualView==SIDE_ROTATE)
			{
				_dir.first = playerPos.y - entityPos.y;
			}
			else
			{
				_dir.first = entityPos.x - playerPos.x;
			}
			_dir.second = playerPos.z - entityPos.z;

			
			// Normalizamos el vector director
			float m = sqrt( (_dir.first*_dir.first)+(_dir.second*_dir.second) );
			_dir.first = _dir.first/m;
			_dir.second = _dir.second/m;

			_dir.first = (_dir.first * _velAxis1);
			_dir.second = (_dir.second * _velAxis2);

			_dir.second += -Logic::MissionManager::GetInstance()->getSpeed();

			_initialized = true;
		}

		return true;
	}	

	//-----------------------------------------------

	void BulletGoToPlayerMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// Realizamos un paso más del movimiento rectilíneo
		posAxis.first +=  (_dir.first) * (lastInterval);
		posAxis.second += (_dir.second) * (lastInterval);
	}

	//---------------------------------------------------------

	bool BulletGoToPlayerMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void BulletGoToPlayerMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------


} // namespace Logic