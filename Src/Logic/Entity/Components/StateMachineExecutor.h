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
@file StateMachineExecutor.h

Contiene la declaraci�n de la clase StateMachineExecutor, que se encarga de
ejecutar m�quinas de estado de la clase CStateMachine.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#pragma once

#ifndef __Logic_StateMachineExecutor_H
#define __Logic_StateMachineExecutor_H

#include "Core/Entities/Component.h"
#include "AI/StateMachine.h"

namespace Logic {
	/**
	Componente que se encarga de ejecutar m�quinas de estado.
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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::Entity). Toma del mapa el atributo
		behavior, que indica el nombre de la m�quina de estado a ejecutar.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		<p>
		Este m�todo actualiza la m�quina de estado. Si hay un cambio de estado, 
		se actualiza el valor del atributo _currentAction, que es el que contiene
		la acci�n latente que se est� ejecutando. Por �ltimo, se llama al tick de
		la acci�n latente para que avance su ejecuci�n.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

	private:
		/**
		Almacena la m�quina de estado que se est� ejecutando
		*/
		AI::CStateMachine<AI::CLatentAction> * _currentStateMachine;

		/**
		Acci�n que se est� ejecutando.
		*/
		AI::CLatentAction* _currentAction;
	};
}

#endif
