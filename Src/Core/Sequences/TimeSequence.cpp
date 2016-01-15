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

#include <algorithm>

#include "Core/Sequences/TimeSequence.h"
#include "Core/Sequences/ITimeSequenceAction.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void TimeSequence::start() {
		// Inicializamos las variables de control de la ejecución.
		GenericSequence::start();
		_currentTime = 0;
		// Ordenamos la secuencia de acciones registradas. 
		std::sort(_actions.begin(), _actions.end(), &(TimeSequence::vectorComparer));
	}

	//--------------------------------------------------------------------------------------------------------

	void TimeSequence::stop() {
		_currentTime = 0;
		GenericSequence::stop();
	}

	//--------------------------------------------------------------------------------------------------------

	void TimeSequence::innerUpdate(unsigned int lastInterval) {
		// Actualizamos el tiempo actual acumulado.
		_currentTime += lastInterval;
		// Comprobamos que no hemos terminado la ejecución y vamos avanzando en la secuencia mientras
		// el siguiente paso a dar esté atrás en el tiempo actual acumulado.
		while(_nextStep < _actions.size() && _actions[_nextStep]->getStartTime() < _currentTime) {
			// Ejecutamos la acción del paso actual y avanzamos al siguiente paso.
			_actions[_nextStep]->execute();
			++_nextStep;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool TimeSequence::vectorComparer(ITimeSequenceAction * left, ITimeSequenceAction * right) {
		return left->getStartTime() < right->getStartTime();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	TimeSequence::TimeSequence(const std::string & name) : GenericSequence(name), _currentTime(0) {}

	//--------------------------------------------------------------------------------------------------------

	TimeSequence::TimeSequence(const TimeSequence & obj) : GenericSequence(obj) {
		_currentTime = obj._currentTime;
	}

	//--------------------------------------------------------------------------------------------------------

	TimeSequence::~TimeSequence() {}
}
