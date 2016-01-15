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
 * Esta clase contiene la implementación del tipo de movimiento arriba-abajo.
 */

#include "UpDownMovement.h"
#include "Core/Math.h"

namespace Logic
{

	bool UpDownMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// Inicializamos los atributos propios del movimiento en base a los datos del descriptor
		if(info->hasAttribute("velocity") && info->hasAttribute("maxDistance") && info->hasAttribute("direction") 
				&& info->hasAttribute("staticOffset") && info->hasAttribute("approachVel"))
		{
			_vel = info->getAttributeAsFloat("velocity");
			_maxDistance = info->getAttributeAsFloat("maxDistance");
			_direction = (DirectionType) info->getAttributeAsInteger("direction");
			_staticOffset = info->getAttributeAsFloat("staticOffset");
			_approachVel = 	info->getAttributeAsFloat("approachVel");
			return true;
		}

		return false;
	}

	//-------------------------------------------

	bool UpDownMovement::activate()
	{
		return true;
	}

	//-------------------------------------------

	void UpDownMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		float lastInterval2 = lastInterval * 0.02f;

		// Dependiendo de la vista actual el eje a considerar cambia
		float centerMovement = 0.0f;
		if(actualView==SIDE || actualView==SIDE_ROTATE)
			centerMovement = actionCenter.y;
		else
			centerMovement = -actionCenter.x;

		// Realizamos un paso más del movimiento horizontal
		if (_direction==UP_LEFT)
		{
			if(posAxis.first < centerMovement+_maxDistance) posAxis.first += _vel * lastInterval2;
			else _direction=DOWN_RIGHT;	// Si llegamos al límite cambiamos el sentido del movimiento
		}
		else
		{
			if(posAxis.first > centerMovement-_maxDistance) posAxis.first -= _vel * lastInterval2;
			else _direction=UP_LEFT;
		}

		// Aproximamos la entidad hasta una cierta distancia del centro de acción, o  bien la mantenemos estatica si ya ha llegado
		if (posAxis.second < actionCenter.z-_staticOffset) posAxis.second -= _approachVel * lastInterval2;
		else posAxis.second -= 5.0f * lastInterval2;	// TODO: leer parametro de velocidad
	}

	//---------------------------------------------------------

	bool UpDownMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void UpDownMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------


} // namespace Logic