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

#ifndef __LOGIC_GOTOVIRTUALQUADRANTMESSAGE_H__
#define __LOGIC_GOTOVIRTUALQUADRANTMESSAGE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Core/Object.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	/**
	 * Esta clase representa un mensaje que indica el "cuadrante virtual" objetivo al que debe moverse la entidad.
	 */
	class GoToVirtualQuadrantMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		// Métodos para obtener el cuadrante objetivo
		inline int getTargetQuadrant1() const { return _Q1; }
		inline int getTargetQuadrant2() const { return _Q2; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 * @param Q1 Indica la posición en el eje 1 del cuadrante objetivo.
		 * @param Q2 Indica la posición en el eje 2 del cuadrante objetivo.
		 */
		GoToVirtualQuadrantMessage(int Q1, int Q2);
		
		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		GoToVirtualQuadrantMessage(const GoToVirtualQuadrantMessage & obj);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~GoToVirtualQuadrantMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------
		
		/*
		Cuadrante objetivo
		*/
		int _Q1, _Q2;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Copia el contenido de un objeto en el actual.
		 * @param obj El objeto a copiar.
		 */
		virtual void copyFrom(const Core::Object & obj);
	};
}

#endif	// __LOGIC_GOTOVIRTUALQUADRANTMESSAGE_H__
