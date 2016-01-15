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
@file StateMachineExecutor.h

Contiene la declaración de la clase StateMachineExecutor, que se encarga de
ejecutar máquinas de estado de la clase CStateMachine.

@author Gonzalo Flórez
@date Diciembre, 2010
*/
#pragma once

#ifndef __Logic_StateMachineExecutor_H
#define __Logic_StateMachineExecutor_H

#include "Core/Entities/Component.h"
#include "AI/StateMachine.h"

namespace Logic {
	/**
	Componente que se encarga de ejecutar máquinas de estado.
	*/
	class StateMachineExecutor : public Core::Component
	{
	public:
		ComponentCreateMethod(StateMachineExecutor);

		/**
		Constructor
		*/
		StateMachineExecutor() : Component("StateMachineExecutor"), _currentStateMachine(0), _currentAction(0) {}

		/**
		Destructor
		*/
		~StateMachineExecutor() {
			if (_currentStateMachine != 0) delete _currentStateMachine;
		}

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
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::Entity). Toma del mapa el atributo
		behavior, que indica el nombre de la máquina de estado a ejecutar.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Este método actualiza la máquina de estado. Si hay un cambio de estado, 
		se actualiza el valor del atributo _currentAction, que es el que contiene
		la acción latente que se está ejecutando. Por último, se llama al tick de
		la acción latente para que avance su ejecución.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

	private:
		/**
		Almacena la máquina de estado que se está ejecutando
		*/
		AI::CStateMachine<AI::CLatentAction> * _currentStateMachine;

		/**
		Acción que se está ejecutando.
		*/
		AI::CLatentAction* _currentAction;
	};
}

#endif
