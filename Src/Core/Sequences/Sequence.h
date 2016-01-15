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

#ifndef __CORE_SEQUENCE_H__
#define __CORE_SEQUENCE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Sequences/GenericSequence.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ISequenceAction;

	/**
	 * Esta clase representa una secuencia de acciones.
	 */
	class Sequence : public GenericSequence<ISequenceAction> {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Sequence(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Sequence(const Sequence & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Sequence();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la lógica interna de la secuencia.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		virtual void innerUpdate(unsigned int lastInterval);
	};
}

#endif
