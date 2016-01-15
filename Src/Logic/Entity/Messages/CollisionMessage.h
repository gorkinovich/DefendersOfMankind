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

#ifndef __LOGIC_COLLISIONMESSAGE_H__
#define __LOGIC_COLLISIONMESSAGE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Object.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Entity;
}

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	/**
	 * Esta clase representa un mensaje para indicar contra qu� entidad se ha colisionado o dejado de colisionar.
	 */
	class CollisionMessage : public Core::Object {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la entidad v�ctima de la colisi�n.
		 */
		inline Core::Entity * getVictim() const { return _victim; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param victim La entidad contra la que se interactua.
		 */
		CollisionMessage(Core::Entity * victim);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		CollisionMessage(const CollisionMessage & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~CollisionMessage();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La entidad v�ctima de la colisi�n.
		 */
		Core::Entity * _victim;

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
