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

/**
@file BifurcationTrigger.h

Contiene la declaraci�n de un componente que cambia el centro de la acci�n al ser tocado. 
El mensaje se env�a a la c�mara.

@see Logic::BifurcationTrigger
@see Core::Component

@author David Rodr�guez
@date Abril, 2011
*/
#ifndef __Logic_BifurcationTrigger_H
#define __Logic_BifurcationTrigger_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	/**
	Este componente crea un trigger que ante el contacto modifica 
	el centro de la c�mara, abriendo un nuevo camino.
	
    @ingroup logicGroup
	@author David Llans� Garc�a
	@date Octubre, 2010
	*/
	class BifurcationTrigger : public Core::Component
	{
	public:
		ComponentCreateMethod(BifurcationTrigger);

		/**
		Constructor por defecto.
		*/
		BifurcationTrigger() : Component("BifurcationTrigger"), _newCenter(Vector3::ZERO) {}

	protected:
		/**
		 * Comprueba si un mensaje es v�lido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser v�lido devolver� true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje reci�n sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Centro al que se cambia.
		*/
		Vector3 _newCenter;
	};
}

#endif
