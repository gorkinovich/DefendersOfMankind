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
	 * Esta clase representa una aplicaci�n gen�rica.
	 */
	class GenericApplication {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el estado actual de la aplicaci�n.
		 */
		inline ApplicationState * getCurrentState() const { return _currentState; }

		/**
		 * Obtiene el flag que controla cuando se sale de la aplicaci�n.
		 */
		inline bool getExit() { return _exit; }

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static GenericApplication * GetInstance() {
			return _instance;
		}

		/**
		 * Comunica a la aplicaci�n que se ha de terminar la ejecuci�n.
		 */
		inline void exitRequest() {
			_exit = true;
		}

		/**
		 * Inicializa la aplicaci�n.
		 * @param title El t�tulo del juego.
		 * @param logPath La ruta del log del motor.
		 * @return Devuelve true si se logra inicializar la aplicaci�n.
		 */
		virtual bool initialize(const char * title, const char * logPath = 0);

		/**
		 * Finaliza el aplicaci�n.
		 */
		virtual void release();

		/**
		 * Inicia la ejecuci�n del bucle principal de la aplicaci�n. Para finalizar
		 * su ejecuci�n se debe llamar al m�todo exitRequest().
		 */
		void run();

		/**
		 * Cambia el estado actual (el que est� en la cima de la pila de estados).
		 * @param name El nombre del estado.
		 */
		void changeState(const std::string & name);

		/**
		 * Elimina todos los estados en la pila y a�ade uno nuevo.
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
		 * @remark Si no encuentra el estado que busca, deja el �ltimo que queda.
		 */
		void popToState(const std::string & name);

		/**
		 * Vuelve al estado m�s profundo en la pila de estados.
		 */
		void popToBaseState();

		/**
		 * A�ade un estado en la tabla de estados.
		 * @param name El nombre del estado.
		 * @param victim El estado a a�adir.
		 * @return Devuelve true si la operaci�n se realiz� correctamente.
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
		 * Suspende la ejecuci�n del hilo de la aplicaci�n un tiempo determinado.
		 * @param milliseconds El n�mero de milisegundos a suspender la ejecuci�n.
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
		 * Este tipo representa una enumeraci�n de tipos de cambio de estado.
		 */
		typedef enum {
			SCT_CHANGE, SCT_CLEAN_AND_CHANGE, SCT_PUSH, SCT_POP, SCT_POP_TO_STATE, SCT_POP_TO_BASE, SCT_NONE
		} StateChangeType;

		/**
		 * Este tipo representa una petici�n de cambio de estado.
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
		 * La m�quina de estados de la aplicaci�n.
		 */
		ApplicationStateMachine _fsm;

		/**
		 * El estado actual de la aplicaci�n.
		 */
		ApplicationState * _currentState;

		/**
		 * La petici�n actual de cambio de estado.
		 */
		StateChangeRequest _changeRequest;

		/**
		 * El flag que controla cuando se sale de la aplicaci�n.
		 */
		bool _exit;

		/**
		 * El reloj interno de la aplicaci�n.
		*/
		Clock * _clock;

		/**
		 * El gestor del motor gr�fico.
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
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la l�gica interna de la aplicaci�n.
		 * @param lastInterval El tiempo total del �ltimo intervalo entre frame y frame.
		 */
		inline void update(unsigned int lastInterval);

		/**
		 * Actualiza el cambio de estado tras una petici�n de hacerlo.
		 */
		inline void updateChange();
	};
}

#endif
