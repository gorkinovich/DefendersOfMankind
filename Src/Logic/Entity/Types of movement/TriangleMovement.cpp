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
 * Esta clase contiene la implementación del tipo de movmiento triangular.
 */

#include "TriangleMovement.h"

namespace Logic
{

	bool TriangleMovement::spawn(Core::InfoTable* info, Core::Entity* owner)
	{
		// TODO
		_moveStep = 0;
		_point1.first = 0.0f; _point1.second = -10.0f;
		_point2.first = 40.0f; _point2.second = -60.0f;
		_point3.first = -40.0f; _point3.second = -60.0f;

		return true;
	}

	//-------------------------------------------

	bool TriangleMovement::activate()
	{
		return true;
	}

	//-------------------------------------------

	void TriangleMovement::calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval)
	{
		// TODO

		/*
		float lastInterval2 = lastInterval * 0.02f;

		float centerAxis1 = 0.0f;
		float centerAxis2 = 0.0f;
		if(actualView==SIDE || actualView==SIDE_ROTATE) {
			centerAxis1 = actionCenter.y;
			centerAxis2 = actionCenter.z;
		}
		else {
			centerAxis1 = actionCenter.x;
			centerAxis2 = actionCenter.y;
		}
		// TODO
		if (_moveStep==0)
		{
			if(posAxis.first < centerAxis1+_point1.first) posAxis.first += 1.0f * lastInterval2;
			if(posAxis.first > centerAxis1+_point1.first) posAxis.first -= 1.0f * lastInterval2;

			if(posAxis.second < centerAxis2+_point1.second) posAxis.second += 1.0f * lastInterval2;
			if(posAxis.second > centerAxis2+_point1.second) posAxis.second -= 1.0f * lastInterval2;

			if((posAxis.first == centerAxis1+_point1.first) && (posAxis.second == centerAxis2+_point1.second)) _moveStep=1;
		}
		else if(_moveStep==1)
		{
			if(posAxis.first < centerAxis1+_point1.first) posAxis.first += 1.0f * lastInterval2;
			if(posAxis.first > centerAxis1+_point1.first) posAxis.first -= 1.0f * lastInterval2;

			if(posAxis.second < centerAxis2+_point1.second) posAxis.second += 1.0f * lastInterval2;
			if(posAxis.second > centerAxis2+_point1.second) posAxis.second -= 1.0f * lastInterval2;

			if((posAxis.first == centerAxis1+_point1.first) && (posAxis.second == centerAxis2+_point1.second)) _moveStep=2;
		}
		else if(_moveStep==2)
		{
			if(posAxis.first < centerAxis1+_point1.first) posAxis.first += 1.0f * lastInterval2;
			if(posAxis.first > centerAxis1+_point1.first) posAxis.first -= 1.0f * lastInterval2;

			if(posAxis.second < centerAxis2+_point1.second) posAxis.second += 1.0f * lastInterval2;
			if(posAxis.second > centerAxis2+_point1.second) posAxis.second -= 1.0f * lastInterval2;

			if((posAxis.first == centerAxis1+_point1.first) && (posAxis.second == centerAxis2+_point1.second)) _moveStep=0;
		}*/
	}

	//---------------------------------------------------------

	bool TriangleMovement::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	//---------------------------------------------------------

	void TriangleMovement::process(const Core::SmartMessage & message)
	{
	}

	//---------------------------------------------------------


} // namespace Logic