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

#ifndef __CORE_GENERICSEQUENCE_H__
#define __CORE_GENERICSEQUENCE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>

#include "Core/Sequences/ISequence.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una secuencia de acciones genérica.
	 */
	template<class T>
	class GenericSequence : public ISequence {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre de la secuencia.
		 */
		virtual const std::string & getName() const { return _name; }

		/**
		 * Obtiene si la secuencia se está ejecutando.
		 */
		virtual bool isPlaying() const { return _started; }

		/**
		 * Obtiene si la secuencia ha terminado.
		 */
		virtual bool isFinished() const { return !_started; }

		/**
		 * Obtiene el próximo paso a ejecutar en la secuencia de acciones.
		 */
		unsigned int getNextStep() const { return _nextStep; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade una acción a la secuencia.
		 * @param action La acción a añadir.
		 * @remark La acción no se añade de forma ordenada, el vector se ordena en el método start().
		 * @remark Si se está ejecutando la secuencia no se podrá realizar la operación.
		 */
		void addAction(T * action) {
			// Comprobamos que no se esté ejecutando la secuencia para realizar la operación.
			if(!_started) {
				// Añadimos la acción al vector.
				_actions.push_back(action);
			}
		}

		/**
		 * Elimina una acción de la secuencia.
		 * @param action La acción a añadir.
		 * @remark Elimina de la memoria la acción borrada.
		 * @remark Si se está ejecutando la secuencia no se podrá realizar la operación.
		 */
		void removeAction(T * action) {
			// Comprobamos que no se esté ejecutando la secuencia para realizar la operación.
			if(!_started) {
				// Recorremos la secuencia de acciones registradas.
				SequenceActionVector::iterator i = _actions.begin();
				SequenceActionVector::iterator end = _actions.end();
				for(; i != end; ++i) {
					// Comprobamos si la acción corresponde con la que queremos borrar.
					if(*i == action) {
						// Borramos la acción de la memoria y del vector.
						delete action;
						_actions.erase(i);
						return;
					}
				}
			}
		}

		/**
		 * Elimina todas las acciones de la secuencia.
		 * @remark Elimina de la memoria las acciones borradas.
		 * @remark Si se está ejecutando la secuencia no se podrá realizar la operación.
		 */
		void removeAllActions() {
			// Comprobamos que no se esté ejecutando la secuencia para realizar la operación.
			if(!_started) {
				// Recorremos la secuencia de acciones registradas.
				SequenceActionVector::iterator i = _actions.begin();
				SequenceActionVector::iterator end = _actions.end();
				SequenceActionVector::iterator victim;
				while(i != end) {
					// Borramos la acción de la memoria.
					victim = i++;
					delete *victim;
					// Borramos la acción del vector.
					_actions.erase(victim);
				}
			}
		}

		/**
		 * Inicia la ejecución de la secuencia.
		 */
		virtual void start() {
			_nextStep = 0;
			_started = true;
		}

		/**
		 * Para la ejecución de la secuencia.
		 */
		virtual void stop() {
			_nextStep = 0;
			_started = false;
		}

		/**
		 * Actualiza la lógica interna de la secuencia.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		virtual void update(unsigned int lastInterval) {
			// Comprobamos que no hemos terminado la ejecución.
			if(_started && _nextStep < _actions.size()) {
				// Actualizamos la lógica interna de la secuencia.
				innerUpdate(lastInterval);
				// Si hemos llegado al final marcamos como terminada la ejecución.
				if(_nextStep >= _actions.size()) {
					_started = false;
				}
			}
		}

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la secuencia.
		 */
		GenericSequence(const std::string & name) : _name(name), _started(false), _nextStep(0) {}

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		GenericSequence(const GenericSequence & obj) {
			_name = obj._name;
			_nextStep = obj._nextStep;
			_actions = obj._actions;
			_started = obj._started;
		}

		/**
		 * Destructor del objeto.
		 */
		virtual ~GenericSequence() {
			removeAllActions();
		}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un vector de acciones.
		 */
		typedef std::vector<T *> SequenceActionVector;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre de la secuencia.
		 */
		std::string _name;

		/**
		 * El flag que indica si se ha iniciado la ejecución de la secuencia.
		 */
		bool _started;

		/**
		 * El próximo paso a ejecutar en la secuencia de acciones.
		 */
		unsigned int _nextStep;

		/**
		 * La secuencia de acciones ordenada por tiempo de activación.
		 */
		SequenceActionVector _actions;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la lógica interna de la secuencia.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		virtual void innerUpdate(unsigned int lastInterval) = 0;
	};
}

#endif
