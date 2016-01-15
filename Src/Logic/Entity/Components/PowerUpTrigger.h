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

/**
@file PowerUpTrigger.h

Contiene la declaración de un componente que envia un mensaje al jugador con 
un efecto concreto

@see Logic::PowerUpTrigger
@see Core::Component

@author David Rodríguez
@date Junio, 2011
*/
#ifndef __Logic_PowerUpTrigger_H
#define __Logic_PowerUpTrigger_H

#include "Core/Entities/Component.h"
#include "Logic/Entity/Components/PowerUpType.h"

namespace Logic {
	/**
	Este componente procesa mensajes de tipo TOUCHED (indican que la entidad ha 
	sido tocada) para enviar un mensaje a la entidad que tocó.<p>
	
    @ingroup logicGroup
	@author David Rodríguez
	@date Junio, 2010
	*/
	class PowerUpTrigger : public Core::Component
	{
	public:
		ComponentCreateMethod(PowerUpTrigger);

		/**
		Constructor por defecto.
		*/
		PowerUpTrigger() : Component("PowerUpTrigger"), _powerUp(AUTOFIRE) {}

	protected:
		/**
		 * Comprueba si un mensaje es válido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser válido devolverá true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje recién sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Tipo de power up a activar.
		*/
		PowerUpType _powerUp;
	};
}

#endif
