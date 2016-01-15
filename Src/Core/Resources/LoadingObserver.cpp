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

#include "Core/Resources/LoadingObserver.h"
#include "Core/Resources/ILoadingListener.h"
#include "Core/Clock.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/Input/InputManager.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Sound/SoundManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos est�ticos
	//********************************************************************************************************

	LoadingObserver * LoadingObserver::_instance = new LoadingObserver();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	void LoadingObserver::setNumberOfSections(unsigned int value) {
		// Borramos y establecemos el tama�o de la tabla.
		_operationsBySector.clear();
		_operationsBySector.resize(value);
		// Inicializamos todas las secciones con al menos una operaci�n.
		for(unsigned int i = 0; i < value; ++i) {
			_operationsBySector[i] = 1;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void LoadingObserver::setNumberOfOperations(unsigned int section, unsigned int value) {
		// Comprobamos que la secci�n est� dentro de la tabla.
		if(_operationsBySector.size() > section) {
			// Si lo est� asignamos el valor a la secci�n indicada.
			_operationsBySector[section] = value;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool LoadingObserver::isLoadingFinished() const {
		// Se ha terminado cuando la variable de control de las secciones indique que se han completado
		// todas las secciones registradas en el proceso de carga.
		return _currentSection >= _operationsBySector.size();
	}

	//********************************************************************************************************
	// M�todos
	//********************************************************************************************************

	void LoadingObserver::startLoading(unsigned int numberOfSections, ILoadingListener * listener) {
		// Guardamos el listener recibido.
		if(listener) _listener = listener;
		// Inicializamos la tabla de secciones.
		setNumberOfSections(numberOfSections);
		// Inicializamos las variables de control del proceso.
		_currentSection = 0;
		_currentOperation = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void LoadingObserver::operationFinished() {
		// Comprobamos que no se haya terminado el proceso.
		if(_operationsBySector.size() > _currentSection) {
			// Avanzamos en una operaci�n el proceso.
			++_currentOperation;
			// Comprobamos si hemos llegado al final de la secci�n actual.
			if(_operationsBySector[_currentSection] <= _currentOperation) {
				// De haber llegadoo al final avanzamos en una secci�n el proceso.
				++_currentSection;
				_currentOperation = 0;
			}
			// Y por �ltimo comunicamos el avance actual del proceso.
			if(_listener) {
				_listener->loadingUpdated(this, _currentSection, _currentOperation);
			}
			// Actualiza la l�gica interna de la aplicaci�n cuando se est� en un proceso de carga.
			update();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void LoadingObserver::endLoading() {
		// Borramos el listener que tuvieramos almacenado.
		_listener = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void LoadingObserver::update() {
		if(_clock) {
			// Actualizamos el reloj para obtener el intervalo de tiempo entre frame y frame.
			_clock->update();
			// Actualizamos el estado de la entrada.
			InputManager::GetInstance()->update();
			// Actualizamos el estado del sonido.
			SoundManager::GetInstance()->update();
			// Actualizamos el estado del motor de script.
			ScriptingManager::GetInstance()->update();
			// Actualizamos el estado de los gr�ficos.
			GraphicsManager::GetInstance()->update(((float)_clock->getLastInterval()) / 1000.0f);
		}
	}
}
