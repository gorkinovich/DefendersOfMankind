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
@file SwitchPosition.h

Contiene la declaración del componente que controla el movimiento de
una entidad que tiene dos estado (posiciones) para ir de una a otra.

@see Logic::SwitchPosition
@see Core::Component

@author David Llansó
@date Octubre, 2010
*/
#ifndef __Logic_SwitchPosition_H
#define __Logic_SwitchPosition_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	/**
	Este componente controla el movimiento de una entidad que tiene dos estados 
	(posiciones) y la mueve de uno a otro.<p>
	Las posiciones entre las que se transita pueden configurarse desde el mapa.
	De la misma manera se puede estableces el atributo "loop" que mantendrá constante
	las transiciones. El atributo "speed" determina la velocidad del movimiento.<p>
	Recibe mensajes de tipo "SWITCH" para transitar de un estado a otro en caso de
	que no se encuentre en loop. El atributo "_int" del mensaje indica el estado
	al que se debe mover la entidad.
	
    @ingroup logicGroup

	@author David Llansó García
	@date Octubre, 2010
	*/
	class SwitchPosition : public Core::Component
	{
	public:
		ComponentCreateMethod(SwitchPosition);

		/**
		Constructor por defecto.
		*/
		SwitchPosition();

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
		Mueve el componente hacia la posición de destino. Una vez la alcance se para
		(loop = false) o empieza a moverse hacia la otra posición (loop = true).
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Posición inicial (_position[0]) y final (_position[1]).
		*/
		Vector3 _position[2];
	
		/**
		Posición hacia la que nos estamos moviendo.
		*/
		Vector3 _targetPosition;

		/**
		Atributo que indica la magnitud de velocidad de la entidad.
		*/
		float _speed;
		
		/**
		Atributo que indica si estamos constantemente moviendo de un punto a otro.
		*/
		bool _loop;
	};
}

#endif
