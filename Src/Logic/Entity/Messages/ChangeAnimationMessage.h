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

#ifndef __LOGIC_CHANGEANIMATIONMESSAGE_H__
#define __LOGIC_CHANGEANIMATIONMESSAGE_H__

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
	 * Esta clase representa un mensaje para cambiar la animaci�n de una entidad.
	 */
	class ChangeAnimationMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre de la animaci�n.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene el flag de reproducci�n c�clica.
		 */
		inline bool getLoop() const { return _loop; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la animaci�n.
		 * @param loop El flag de reproducci�n c�clica.
		 */
		ChangeAnimationMessage(const std::string & name, bool loop);
		
		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		ChangeAnimationMessage(const ChangeAnimationMessage & obj);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~ChangeAnimationMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre de la animaci�n.
		 */
		std::string _name;

		/**
		 * El flag de reproducci�n c�clica.
		 */
		bool _loop;

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
