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
 * Esta clase contiene la implementación del tipo de movimiento sinusoidal.
 */

#include "SinusoidalMovement.h"
#include "Core/Math.h"

namespace Logic
{

	bool SinusoidalMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// Inicializamos los atributos propios del movimiento en base a los datos del descriptor
		if(info->hasAttribute("velocity") && info->hasAttribute("degrees") && info->hasAttribute("degreesVel")
			&& info->hasAttribute("amplitudeWave") && info->hasAttribute("centerWave") && info->hasAttribute("offset"))
		{
			_vel = info->getAttributeAsFloat("velocity");
			_degrees = info->getAttributeAsFloat("degrees");
			_degreesVel = info->getAttributeAsFloat("degreesVel");
			_amplitudeWave = info->getAttributeAsFloat("amplitudeWave");
			_centerWave = info->getAttributeAsFloat("centerWave");
			_offset = info->getAttributeAsFloat("offset");
			return true;
		}

		return false;
	}

	//-------------------------------------------

	bool SinusoidalMovement::activate()
	{
		return true;
	}

	//-------------------------------------------

	void SinusoidalMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// Dependiendo de la vista actual el centro de la onda cambia
		if(actualView==SIDE || actualView==SIDE_ROTATE)
			_centerWave = actionCenter.y + _offset;
		else
			_centerWave = -actionCenter.x + _offset;

		// Realizamos un paso más del movimiento sinusoidal
		posAxis.first = _centerWave + (sin(Math::FromDegreesToRadians(_degrees)) * _amplitudeWave);
		posAxis.second += _vel * (lastInterval * 0.02f);
		_degrees += _degreesVel * (lastInterval * 0.05f);
		if(_degrees>=360.0f) _degrees = 0.0f;	// El operando módulo no puede ser aplicado con variables en coma flotante
	}

	//---------------------------------------------------------

	bool SinusoidalMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void SinusoidalMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------


} // namespace Logic