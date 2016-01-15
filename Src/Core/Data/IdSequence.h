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

#ifndef __CORE_IDSEQUENCE_H__
#define __CORE_IDSEQUENCE_H__

//************************************************************************************************************
// Include
//************************************************************************************************************

#include "Core/IdType.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una secuencia de identificadores.
	 * @remark Los identificadores serán positivos distintos de cero.
	 */
	class IdSequence {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		enum {
			Unassigned = ID_TYPE_UNASSIGNED, // Valor para indicar un ID no asignado.
			FirstId    = ID_TYPE_FIRST       // Valor del primer ID en una secuencia.
		};

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el siguiente identificador dentro de la secuencia.
		 */
		IdType getNextId();

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Reinicia la secuencia.
		 */
		void reset();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		IdSequence();

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		IdSequence(const IdSequence & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~IdSequence();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El siguiente identificador dentro de la secuencia.
		 */
		IdType _nextId;
	};
}

#endif
