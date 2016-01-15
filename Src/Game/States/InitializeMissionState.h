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

//TODO: Completar y comentar el fichero...

#ifndef __GAME_INITIALIZEMISSIONSTATE_H__
#define __GAME_INITIALIZEMISSIONSTATE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Game/GenericMenuState.h"
#include "Core/Resources/ILoadingListener.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class LoadingObserver;
}

//************************************************************************************************************
// CEGUI
//************************************************************************************************************

namespace CEGUI {
	class ProgressBar;
	class Editbox;
	class Window;
}

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	/**
	 * Esta clase representa el estado que se encarga de la inicializaci�n de una misi�n.
	 */
	class InitializeMissionState : public Game::GenericMenuState, public Core::ILoadingListener {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre identificador del estado.
		 */
		static const std::string StateName;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre identificador del estado.
		 */
		inline const std::string & getName() const { return StateName; }

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el estado.
		 * @return Devuelve true si se logra inicializar el estado.
		 */
		virtual bool initialize();

		/**
		 * Finaliza el estado.
		 */
		virtual void release();

		/**
		 * Activa el estado.
		 */
		virtual void activate();

		/**
		 * Desactiva el estado.
		 */
		virtual void deactivate();

		/**
		 * Actualiza la l�gica interna del estado.
		 * @param lastInterval El tiempo total del �ltimo intervalo entre frame y frame.
		 */
		virtual void update(unsigned int lastInterval);

		/**
		 * Delegado que se llama al completarse una operaci�n de carga.
		 * @param sender El observador de la carga que invoca al m�todo.
		 * @param section El identificador de la secci�n actual en el proceso de la carga.
		 * @param operationsCompleted El n�mero de operaciones completadas en la secci�n actual.
		 */
		virtual void loadingUpdated(const Core::LoadingObserver * sender, int section, int operationsCompleted);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		InitializeMissionState(Core::GenericApplication * application);

		/**
		 * Destructor del objeto.
		 */
		virtual ~InitializeMissionState();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El objeto interactivo para indicar el progreso actual dentro del proceso (con una barra).
		 */
		CEGUI::ProgressBar * _loadingBar;

		/**
		 * El objeto interactivo para indicar el progreso actual dentro del proceso (con un porcentaje).
		 */
		CEGUI::Window * _loadingText;
	};
}

#endif
