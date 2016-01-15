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

#ifndef __CORE_TIMESEQUENCE_H__
#define __CORE_TIMESEQUENCE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Sequences/GenericSequence.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ITimeSequenceAction;

	/**
	 * Esta clase representa una secuencia de acciones basada en el tiempo.
	 */
	class TimeSequence : public GenericSequence<ITimeSequenceAction> {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el tiempo actual acumulado de la secuencia.
		 */
		inline unsigned int getCurrentTime() const { return _currentTime; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicia la ejecución de la secuencia.
		 */
		virtual void start();

		/**
		 * Para la ejecución de la secuencia.
		 */
		virtual void stop();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		TimeSequence(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		TimeSequence(const TimeSequence & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~TimeSequence();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El tiempo actual acumulado de la secuencia.
		 */
		unsigned int _currentTime;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la lógica interna de la secuencia.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		virtual void innerUpdate(unsigned int lastInterval);

		/**
		 * El comparador de elementos del vector de acciones.
		 * @param left El elemento a la derecha de la comparación.
		 * @param right El elemento a la izquierda de la comparación.
		 * @return Devuelve true cuando left < right.
		 */
		static bool vectorComparer(ITimeSequenceAction * left, ITimeSequenceAction * right);
	};
}

#endif
