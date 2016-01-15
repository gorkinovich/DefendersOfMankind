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
 * Esta clase contiene la implementación del tipo de movimiento rectilíneo.
 */

#include "RectilinearMovement.h"

namespace Logic
{

	bool RectilinearMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// Inicializamos los atributos propios del movimiento en base a los datos del descriptor
		if(info->hasAttribute("DirAxis1") && info->hasAttribute("DirAxis2"))
		{
			_dir.first = info->getAttributeAsFloat("DirAxis1");
			_dir.second = info->getAttributeAsFloat("DirAxis2");
			return true;
		}

		return false;
	}

	//-------------------------------------------

	bool RectilinearMovement::activate()
	{
		return true;
	}	

	//-----------------------------------------------

	void RectilinearMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// Realizamos un paso más del movimiento rectilíneo
		posAxis.first += _dir.first * (lastInterval*0.05f);
		posAxis.second += _dir.second * (lastInterval*0.05f);
	}

	//---------------------------------------------------------

	bool RectilinearMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void RectilinearMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------


} // namespace Logic