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
* Esta clase representa un tipo de movimiento se dirige hacia el centro de un cuadrante virtual objetivo.
*/
#include <assert.h>

#include "GoToQuadrantMovement.h"

#include "Logic/MissionManager.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantEndMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantAbortMessage.h"

#include "Logic/Entity/Components/CameraType.h"


namespace Logic
{

	bool GoToQuadrantMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		_owner = owner;

		// Obtenemos los datos leidos del descriptor
		if(info->hasAttribute("velocity"))
		{
			_vel = info->getAttributeAsFloat("velocity");

			// Por defecto el cuadrante virtual objetivo es el (0,0) (centro de la acción)
			_quadrantTarget.first = 0;
			_quadrantTarget.second = 0;

			return true;
		}

		return false;
	}

	//-----------------------------------------------

	bool GoToQuadrantMovement::activate()
	{
		return true;
	}

	//-----------------------------------------------

	void GoToQuadrantMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// Obtenemos el centro del cuadrante objetivo
		AI::TCenterPos* targetPos = _virtualBoard.getCenterOfQuadrant(_quadrantTarget.first, _quadrantTarget.second, actualView);

		// Indicamos un valor epsilon para detectar si la entidad ha llegado al objetivo
		float epsilon = 1.0f;

		// Vector estático (velocidad de la acción)
		_dirStatic.first = 0.0f;
		_dirStatic.second = -Logic::MissionManager::GetInstance()->getSpeed();

		// Reseteamos el vector director
		_dir.first = 0.0f;
		_dir.second = 0.0f;

		// Si está llendo hacia el cuadrante objetivo...
		if(!_isStatic)
		{
			// Calculamos el vector director dependiendo de la vista actual
			if(actualView==SIDE || actualView==SIDE_ROTATE)
			{
				_dir.first = targetPos->first - posAxis.first;
			}
			else
			{
				_dir.first = targetPos->first - posAxis.first;
			}
			_dir.second = targetPos->second - posAxis.second;

			// Lo normalizamos y multiplicamos por la velocidad de movimiento
			float m = sqrt( (_dir.first*_dir.first)+(_dir.second*_dir.second) );
			_dir.first = _dir.first/m;
			_dir.second = _dir.second/m;

			_dir.first *= _vel;
			_dir.second *= _vel;

			// Se lo sumamos al vector estático
			_dirStatic.first += _dir.first;
			_dirStatic.second += _dir.second;

			// Comprobamos si la entidad ha llegado al objetivo y debe realizar un movimiento estático
			float rangeAxis1;
			if(actualView==SIDE || actualView==SIDE_ROTATE)
			{
				rangeAxis1 = abs(posAxis.first-targetPos->first);
			}
			else
			{
				rangeAxis1 = abs(posAxis.first-targetPos->first);
			}
			float rangeAxis2 = abs(posAxis.second-targetPos->second);
			if (rangeAxis1<epsilon && rangeAxis2<epsilon)
			{
				// Ha llegado al objetivo, luego enviamos un msg indicando que ya se ha llegado al cuadrante objetivo
				_isStatic = true;	// Hacemos que únicamente tenga un movimiento estático
				_owner->sendMessage(MessageFactory::CreateGoToVirtualQuadrantEndMessage());
				//printf("llegado\n");
			}

		}


		// Aplicamos el movimiento
		if(actualView==SIDE || actualView==SIDE_ROTATE)
		{
			posAxis.first += _dirStatic.first * lastInterval;
		}
		else
		{
			posAxis.first += _dirStatic.first * lastInterval;
		}
		posAxis.second += _dirStatic.second * lastInterval;

		
	}

	//---------------------------------------------------------

	bool GoToQuadrantMovement::accept(const Core::SmartMessage & message)
	{
		return (message->getType() == MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT || message->getType() == MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_ABORT);
	}
	
	//---------------------------------------------------------

	void GoToQuadrantMovement::process(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
			// Cambiamos el cuadrante objetivo
			case MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT:
				{
					_quadrantTarget.first  = message->getDataRefAs<GoToVirtualQuadrantMessage>().getTargetQuadrant1();
					_quadrantTarget.second = message->getDataRefAs<GoToVirtualQuadrantMessage>().getTargetQuadrant2();
					_isStatic = false;
				}
				break;

			// Abortamos el movimiento hacia el cuadrante objetivo
			case MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_ABORT:
				{
					_isStatic = true;
				}
				break;
		}

	}

	//---------------------------------------------------------


} // namespace Logic