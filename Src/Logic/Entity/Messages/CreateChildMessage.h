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

#ifndef __LOGIC_CREATECHILDMESSAGE_H__
#define __LOGIC_CREATECHILDMESSAGE_H__

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
	 * Esta clase representa un mensaje para crear una entidad hija en un generador.
	 */
	class CreateChildMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el identificador del generador.
		 */
		inline unsigned int getGeneratorId() const { return _generatorId; }

		/**
		 * Obtiene el nombre del jhijo a generar.
		 */
		std::string getChildName() const { return _childName; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 * @param generatorId El identificador del generador.
		 * @param childName El nombre del hijo a generar.
		 */
		CreateChildMessage(unsigned int generatorId, std::string childName);
		
		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		CreateChildMessage(const CreateChildMessage & obj);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~CreateChildMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * El identificador del generador.
		 */
		unsigned int _generatorId;

		/**
		 * El nombre del hijo a generar.
		 */
		std::string _childName;

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
