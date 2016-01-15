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

#ifndef __GAME_DOMAPPLICATION_H__
#define __GAME_DOMAPPLICATION_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/GenericApplication.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define TITLE "Defenders of Mankind v0.4a"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	/**
	 * Esta clase representa la aplicaci�n DoM, que hereda de GenericApplication para arrancar la base
	 * del motor de juego. En esta clase, entre otras cosas se inicializar� la l�gica del juego y se
	 * crear�n los estados que se van a usar en la aplicaci�n.
	 */
	class DoMApplication : public Core::GenericApplication {
	public:
		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Inicializa la aplicaci�n.
		 * @return Devuelve true si se logra inicializar la aplicaci�n.
		 */
		virtual bool initialize();

		/**
		 * Finaliza el aplicaci�n.
		 */
		virtual void release();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 */
		DoMApplication();

		/**
		 * Destructor del objeto.
		 */
		virtual ~DoMApplication();

	protected:
		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * A�ade un estado en la tabla de estados de forma sencilla.
		 */
		template<class T>
		void easyAddToTable() {
			addToTable(T::StateName, new T(this));
		}

		/**
		 * Inicializa los estados de la aplicaci�n.
		 * @return Devuelve true si se logra inicializar los estados.
		 */
		bool initializeStates();
	};
}

#endif
