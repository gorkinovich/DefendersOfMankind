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

#ifndef __CORE_ISEQUENCEACTION_H__
#define __CORE_ISEQUENCEACTION_H__

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta interfaz representa una acción genérica en una secuencia.
	 */
	class ISequenceAction {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Ejecuta la acción.
		 */
		virtual void execute() = 0;

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~ISequenceAction() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ISequenceAction() {}
	};
}

#endif
