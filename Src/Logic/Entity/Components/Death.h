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
@file Death.h

Contiene la declaración del componente que inicia la destrucción (retrasada) de la entidad padre.
Procesa mensajes de tipo DEATH.

@see Logic::Death
@see Core::Component

@author Grupo 3
@date Abril, 2011
*/
#ifndef __Logic_Death_H
#define __Logic_Death_H

#include "Core/Entities/Component.h"

namespace Logic {
	/**
	Este componente controla la destrucción (retrasada) de la entidad padre.

    @ingroup logicGroup
	@author Grupo 3
	@date Abril, 2011
	*/
	class Death : public Core::Component
	{
	public:
		ComponentCreateMethod(Death);

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		Death() : Component("Death"), _die(false), _timeToDie(0.0f), _dying(false) {}

		/**
		Devuelve si la entidad está muerta
		*/
		bool isDead() {return _die;}

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
		Método llamado en cada frame que actualiza el estado del componente.
		Se encarga de decrementar el tiempo de vida de la entidad y liberarla en su momento.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Indica si la entidad ya fue puesta en cola para ser eliminada
		*/
		bool _die;

		/**
		Tiempo de vida hasta que la entidad sea puesta en la cola de eliminación
		*/
		float _timeToDie;

		/**
		Indica si la entidad ya fue puesta en cola para ser eliminada
		*/
		bool _dying;
	};
}

#endif
