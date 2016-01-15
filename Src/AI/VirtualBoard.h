/**
Esta clase representa un "tablero virtual" que divide el plano de acción en diversos cuadrantes.

Dichos "cuadrantes virtuales" los usarán los BTs de los enemigos para saber donde posicionarse según lo que
determine su comportamiento.

Lo que realmente interesa de cada "cuadrante virtual" son las coordenadas de su centro en el plano de acción.

@author Grupo 3
@date Junio 2011
*/


#ifndef __AI_VIRTUALBOARD_H__
#define __AI_VIRTUALBOARD_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************
#include <utility>

#include "Logic/Entity/Components/CameraType.h"
#include "Core/Math.h"

//************************************************************************************************************
// AI
//************************************************************************************************************

namespace AI
{

	// Definimos una estructura de tipo par que contendrá la posición del centro del cuadrante solicitado.
	typedef std::pair<float, float> TCenterPos;

	// Definimos una estructura de tipo par que indicará en que cuadrante se encuentra la posición indicada.
	typedef std::pair<int, int> TQuadrant;


	class VirtualBoard
	{
	public:

		/*
		Constructor.
		*/
		VirtualBoard() : _horizontalOffset(20.0f), _verticalOffset(20.0f) {}

		/*
		Destructor
		*/
		~VirtualBoard() {}

		/*
		Método para obtener la posición del centro del cuadrante solicitado.
		@param N Posición del cuadrante.
		@param M Posición del cuadrante.
		@param actualView Vista actual del juego.
		@return TCenterPos Puntero a la estructura que contiene la posición del centro del cuadrante en el plano de acción.
		*/
		TCenterPos* getCenterOfQuadrant(int N, int M, Logic::CameraType actualView);

		/*
		Método para obtener el cuadrante en el que se encuentra una posición pasada por parámetro.
		@param pos Posición sobre la que se quiere saber su cuadrante.
		@param actualView Vista actual del juego.
		@return TQuadrant Puntero a la estructura que indica el cuadrante en el que se encuentra la posición.
		*/
		TQuadrant* getQuadrantFromPosition(Vector3 pos, Logic::CameraType actualView);
 
		/*
		Métodos para establecer los desplazamientos de cada eje.
		*/
		inline void setHorizontalOffset (float value) { _horizontalOffset = value; }
		inline void setVerticalOffset (float value) { _verticalOffset = value; }

		
	private:

		// Desplazamientos entre los centros de los cuadrantes
		float _horizontalOffset;
		float _verticalOffset;

		// Estructura de tipo par que contendrá la posición del centro del cuadrante solicitado		
		TCenterPos _centerQuadrant;

		// Estructura de tipo par que indicará en que cuadrante se encuentra la posición indicada
		TQuadrant _actualQuadrant;

	};

}	// namespace AI

#endif	// __AI_VIRTUALBOARD_H__
