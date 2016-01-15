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

#include <assert.h>

#include "Logic/Entity/Components/StateMachineExecutor.h"

#include "Core/Data/EntityInfoTable.h"

namespace Logic
{
	bool StateMachineExecutor::spawn(const Core::EntityInfoTable *entityInfo)
	{
		assert(_owner && "The component does not have an entity...");

		std::string smName = "";

		if(entityInfo->hasAttribute("behavior")) {
			smName.append(entityInfo->getAttribute("behavior"));
		}

		if (smName.compare("")) {
			if (_currentStateMachine != 0) {
				delete _currentStateMachine;
			}

			// Saca una instancia de la m�quina de estado de la factor�a
			_currentStateMachine = AI::CStateMachineFactory::getStateMachine(smName, _owner);
	}

		// Obtiene el nombre de la m�quina de estado 
		if(entityInfo->hasAttribute("behavior")) {
			std::string smName = entityInfo->getAttribute("behavior");
			if (_currentStateMachine != 0) delete _currentStateMachine;
			// Saca una instancia de la m�quina de estado de la factor�a
			_currentStateMachine = AI::CStateMachineFactory::getStateMachine(smName, _owner);
		}
		return true;
	}

	//---------------------------------------------------------

	void StateMachineExecutor::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		// PR�CTICA IA
		// En cada tick del ejecutor de m�quinas de estado tenemos que 
		// realizar 2 acciones principales:
		// 1. Actualizar la m�quina de estado.
		// 1.1. Si la m�quina cambia de estado reseteamos la acci�n que 
		//		est�bamos ejecutando hasta ahora para que se pueda volver
		//		a ejecutar y cambiamos la acci�n latente actual por la del 
		//		nuevo estado.
		// 2. Ejecutar la acci�n latente correspondiente al estado actual

		if (_currentStateMachine != 0) {
			// Si cambiamos de nodo
			if (_currentStateMachine->update()) {
				// Dejamos la acci�n anterior lista para que pueda
				// volver a ser ejecutada
				if (_currentAction != 0)
					_currentAction->reset();
				// Sacamos la nueva acci�n
				_currentAction = _currentStateMachine->getCurrentNode();
			}
			if (_currentAction != 0)
				_currentAction->update();
		}
	}

	//---------------------------------------------------------

	bool StateMachineExecutor::acceptMessage(const Core::SmartMessage & message)
	{
		// PR�CTICA IA
		// El m�todo accept delega en el m�todo accept de la acci�n latente actual
		if (_currentAction != 0)
			return _currentAction->accept(message);
		return false;
	}

	//---------------------------------------------------------

	void StateMachineExecutor::processMessage(const Core::SmartMessage & message)
	{
		// PR�CTICA IA
		// El m�todo process delega en el m�todo process de la acci�n latente actual
		if (_currentAction != 0)
			_currentAction->process(message);
	}
}