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

#ifndef __LOGIC_ROUTETOMESSAGE_H__
#define __LOGIC_ROUTETOMESSAGE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Object.h"
#include "Core/Math.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	/**
	 * Esta clase representa un mensaje para indicar el destino final de la ruta.
	 */
	class RouteToMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el flag para indicar si se está en movimiento o no.
		 */
		inline bool getWalk() const { return _walk; }

		/**
		 * Obtiene el destino del movimiento.
		 */
		inline const Vector3 & getTarget() const { return _target; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 * @param walk El flag para indicar si se está en movimiento o no.
		 * @param target El destino del movimiento.
		 */
		RouteToMessage(bool walk, const Vector3 & target);
		
		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		RouteToMessage(const RouteToMessage & obj);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~RouteToMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El flag para indicar si se está en movimiento o no.
		 */
		bool _walk;

		/**
		 * El destino del movimiento.
		 */
		Vector3 _target;

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

#endif
