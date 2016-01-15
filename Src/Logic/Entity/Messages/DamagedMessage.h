//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
//************************************************************************************************************

#ifndef __LOGIC_DAMAGEDMESSAGE_H__
#define __LOGIC_DAMAGEDMESSAGE_H__

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
	 * Esta clase representa un mensaje para infligir da�o a una entidad.
	 */
	class DamagedMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la cantidad de da�o infligido.
		 */
		inline float getValue() const { return _value; }


		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 * @param value La cantidad de da�o infligido.
		 * @param damageTarget El tipo del objetivo del da�o.
		 */
		DamagedMessage(float value);
		
		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		DamagedMessage(const DamagedMessage & obj);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~DamagedMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * La cantidad de da�o infligido.
		 */
		float _value;


		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Copia el contenido de un objeto en el actual.
		 * @param obj El objeto a copiar.
		 */
		virtual void copyFrom(const Core::Object & obj);
	};
}

#endif
