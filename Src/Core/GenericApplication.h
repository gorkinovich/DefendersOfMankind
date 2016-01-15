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

#ifndef __CORE_GENERICAPPLICATION_H__
#define __CORE_GENERICAPPLICATION_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/ApplicationStateMachine.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Clock;
	class InputManager;
	class GraphicsManager;
	class SoundManager;
	class ScriptingManager;

	/**
	 * Esta clase representa una aplicación genérica.
	 */
	class GenericApplication {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el estado actual de la aplicación.
		 */
		inline ApplicationState * getCurrentState() const { return _currentState; }

		/**
		 * Obtiene el flag que controla cuando se sale de la aplicación.
		 */
		inline bool getExit() { return _exit; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static GenericApplication * GetInstance() {
			return _instance;
		}

		/**
		 * Comunica a la aplicación que se ha de terminar la ejecución.
		 */
		inline void exitRequest() {
			_exit = true;
		}

		/**
		 * Inicializa la aplicación.
		 * @param title El título del juego.
		 * @param logPath La ruta del log del motor.
		 * @return Devuelve true si se logra inicializar la aplicación.
		 */
		virtual bool initialize(const char * title, const char * logPath = 0);

		/**
		 * Finaliza el aplicación.
		 */
		virtual void release();

		/**
		 * Inicia la ejecución del bucle principal de la aplicación. Para finalizar
		 * su ejecución se debe llamar al método exitRequest().
		 */
		void run();

		/**
		 * Cambia el estado actual (el que está en la cima de la pila de estados).
		 * @param name El nombre del estado.
		 */
		void changeState(const std::string & name);

		/**
		 * Elimina todos los estados en la pila y añade uno nuevo.
		 * @param name El nombre del estado.
		 */
		void cleanAndChangeState(const std::string & name);

		/**
		 * Introduce un nuevo estado en la pila de estados.
		 * @param name El nombre del estado.
		 */
		void pushState(const std::string & name);

		/**
		 * Vuelve al estado anterior en la pila de estados.
		 */
		void popState();

		/**
		 * Vuelve al estado anterior en la pila de estados.
		 * @param name El nombre del estado al que volver.
		 * @remark Si no encuentra el estado que busca, deja el último que queda.
		 */
		void popToState(const std::string & name);

		/**
		 * Vuelve al estado más profundo en la pila de estados.
		 */
		void popToBaseState();

		/**
		 * Añade un estado en la tabla de estados.
		 * @param name El nombre del estado.
		 * @param victim El estado a añadir.
		 * @return Devuelve true si la operación se realizó correctamente.
		 */
		bool addToTable(const std::string & name, ApplicationState * victim);

		/**
		 * Borra un estado de la tabla de estados.
		 * @param name El nombre del estado.
		 */
		void removeFromTable(const std::string & name);

		/**
		 * Limpia la tabla de estados.
		 */
		void clearTable();

		/**
		 * Limpia la pila de estados.
		 */
		void clearStack();

		/**
		 * Suspende la ejecución del hilo de la aplicación un tiempo determinado.
		 * @param milliseconds El número de milisegundos a suspender la ejecución.
		 */
		void sleep(unsigned int milliseconds);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		GenericApplication();

		/**
		 * Destructor del objeto.
		 */
		virtual ~GenericApplication();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una enumeración de tipos de cambio de estado.
		 */
		typedef enum {
			SCT_CHANGE, SCT_CLEAN_AND_CHANGE, SCT_PUSH, SCT_POP, SCT_POP_TO_STATE, SCT_POP_TO_BASE, SCT_NONE
		} StateChangeType;

		/**
		 * Este tipo representa una petición de cambio de estado.
		 */
		typedef struct {
			std::string nextState;
			StateChangeType changeType;
		} StateChangeRequest;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static GenericApplication * _instance;

		/**
		 * La máquina de estados de la aplicación.
		 */
		ApplicationStateMachine _fsm;

		/**
		 * El estado actual de la aplicación.
		 */
		ApplicationState * _currentState;

		/**
		 * La petición actual de cambio de estado.
		 */
		StateChangeRequest _changeRequest;

		/**
		 * El flag que controla cuando se sale de la aplicación.
		 */
		bool _exit;

		/**
		 * El reloj interno de la aplicación.
		*/
		Clock * _clock;

		/**
		 * El gestor del motor gráfico.
		 */
		GraphicsManager * _graphics;

		/**
		 * El gestor del motor de entrada.
		 */
		InputManager * _input;

		/**
		 * El gestor del motor de sonido.
		 */
		SoundManager * _sound;

		/**
		 * El gestor del motor de scripting.
		 */
		ScriptingManager * _scripting;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la lógica interna de la aplicación.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		inline void update(unsigned int lastInterval);

		/**
		 * Actualiza el cambio de estado tras una petición de hacerlo.
		 */
		inline void updateChange();
	};
}

#endif
