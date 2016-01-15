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

//TODO: Completar y comentar el fichero...

#ifndef __LOGIC_LIFECYCLEONMESSAGE_H__
#define __LOGIC_LIFECYCLEONMESSAGE_H__

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
	 * Esta clase representa un mensaje para ...???
	 */
	class LifeCycleONMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 * @param particleSystemName El nombre del sistema de part�culas.
		 */
		LifeCycleONMessage();
		
		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		LifeCycleONMessage(const LifeCycleONMessage & obj);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~LifeCycleONMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

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
