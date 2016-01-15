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

#ifndef __CORE_GENERICTIMESEQUENCEACTION_H__
#define __CORE_GENERICTIMESEQUENCEACTION_H__

//************************************************************************************************************
// Include
//************************************************************************************************************

#include "Core/Sequences/ITimeSequenceAction.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase abstracta representa una acción genérica en una secuencia basada en el tiempo.
	 */
	class GenericTimeSequenceAction : public ITimeSequenceAction {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la marca de tiempo donde la acción se activa.
		 */
		virtual unsigned int getStartTime() const { return _startTime; }

		/**
		 * Modifica la marca de tiempo donde la acción se activa.
		 */
		inline void setStartTime(unsigned int value) { _startTime = value; }

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~GenericTimeSequenceAction() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La marca de tiempo donde la acción se activa.
		 */
		unsigned int _startTime;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param startTime La marca de tiempo donde la acción se activa.
		 */
		GenericTimeSequenceAction(unsigned int startTime) : _startTime(startTime) {}

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		GenericTimeSequenceAction(const GenericTimeSequenceAction & obj) : _startTime(obj._startTime) {}
	};
}

#endif
