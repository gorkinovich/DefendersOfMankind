/**
Esta clase representa un "tablero virtual" que divide el plano de acción en diversos cuadrantes.

Dichos "cuadrantes virtuales" los usarán los BTs de los enemigos para saber donde posicionarse según lo que
determine su comportamiento.

Lo que realmente interesa de cada "cuadrante virtual" son las coordenadas de su centro en el plano de acción.

@author Grupo 3
@date Junio 2011
*/

#include "VirtualBoard.h"

#include "Logic/MissionManager.h"
//#include "Core/Math.h"
#include <math.h>


namespace AI
{

	TCenterPos* VirtualBoard::getCenterOfQuadrant(int N, int M, Logic::CameraType actualView)
	{
		// Obtenemos el centro de acción
		Vector3 actionCenter = Logic::MissionManager::GetInstance()->getCenter();

		// Dependiendo de la vista actual... calculamos el centro del cuadrante solicitado
		if(actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
		{
			_centerQuadrant.first  = actionCenter.y + (M * _verticalOffset);
			_centerQuadrant.second = actionCenter.z - (N * _horizontalOffset);
		}			
		else
		{
			_centerQuadrant.first  = -actionCenter.x - (N * _horizontalOffset);
			_centerQuadrant.second = actionCenter.z - (M * _verticalOffset);
		}			

		// Devolvemos la dirección de memoria de la estructura que contiene la posición solicitada
		return &_centerQuadrant;
	}

	// --------------------------------------------------------------------------

	TQuadrant* VirtualBoard::getQuadrantFromPosition(Vector3 pos, Logic::CameraType actualView)
	{
		float value=0;

		// Obtenemos el centro de acción
		Vector3 actionCenter = Logic::MissionManager::GetInstance()->getCenter();

		// Dependiendo de la vista actual... calculamos el cuadrante en el que se encuentra la posición
		if(actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
		{
			value = ((actionCenter.z - pos.z) / _horizontalOffset);
			_actualQuadrant.first = (int) (value>=0 ? floor(value) : ceil(value));

			value = (pos.y - actionCenter.y) / _verticalOffset;
			_actualQuadrant.second = (int) (value>=0 ? floor(value) : ceil(value));
		}			
		else
		{
			value = (pos.x - actionCenter.x) / _horizontalOffset;
			_actualQuadrant.first = (int) (value>=0 ? floor(value) : ceil(value));

			value = ((actionCenter.z - pos.z) / _verticalOffset);
			_actualQuadrant.second = (int) (value>=0 ? floor(value) : ceil(value));
		}			

		// Devolvemos la dirección de memoria de la estructura que contiene la posición solicitada
		return &_actualQuadrant;
	}

}	// namespace AI
