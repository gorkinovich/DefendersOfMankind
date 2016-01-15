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

#ifndef __CORE_IMMUTABLEENTITY_H__
#define __CORE_IMMUTABLEENTITY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Graphics/GraphicEntity.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;

	/**
	 * Esta clase representa una entidad gr�fica inmutable dentro de una escena.
	 */
	class ImmutableEntity : public GraphicEntity {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 * @param mesh El nombre del modelo que debe cargarse.
		 */
		ImmutableEntity(const std::string & name, const std::string & mesh);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 * @remark El constructor copia crea una copia nueva, los punteros del objeto origen se conservan,
		 *         con lo que existe el peligro de borrar el original sin que la copia se entere.
		 */
		ImmutableEntity(const ImmutableEntity & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~ImmutableEntity();

	protected:
		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * A�ade la entidad a la geometr�a inmutable de la escena. Al hacerlo, se quita la entidad de la
		 * escena para no pintarla dos veces.
		 * @return Devuelve true si se crea correctamente la geometr�a inmutable.
		 * @remarks Una vez a�adida la entidad a la geometr�a inmutable, las modificaciones posteriores hechas en
		 *          los atributos de la clase GraphicsEntity no tendr�n efecto en lo que se podr� ver en la escena.
		 *          Por ello dichos cambios han de hacerse antes de invocar a este m�todo. Se mantendr� no obstante
		 *          las estructuras de las entidades din�micas de Ogre para futuras cargas en otras escenas.
		 */
		bool addToImmutableGeometry();

		friend class Core::Scene;
	};
}

#endif
