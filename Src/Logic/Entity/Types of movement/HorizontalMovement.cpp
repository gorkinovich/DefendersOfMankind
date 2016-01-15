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
 * Esta clase contiene la implementación del tipo de movimiento horizontal.
 */

#include "HorizontalMovement.h"

namespace Logic
{

	bool HorizontalMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// Inicializamos los atributos propios del movimiento en base a los datos del descriptor
		if(info->hasAttribute("velocity"))
		{
			_vel = info->getAttributeAsFloat("velocity");
			return true;
		}

		return false;
	}

	//-------------------------------------------

	bool HorizontalMovement::activate()
	{
		return true;
	}

	//-----------------------------------------------

	void HorizontalMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// Realizamos un paso más del movimiento horizontal
		posAxis.second += _vel * (lastInterval*0.05f);
	}

	//---------------------------------------------------------

	bool HorizontalMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void HorizontalMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------


} // namespace Logic