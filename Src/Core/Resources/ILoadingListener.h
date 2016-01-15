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

#ifndef __CORE_ILOADINGLISTENER_H__
#define __CORE_ILOADINGLISTENER_H__

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class LoadingObserver;

	/**
	 * Esta interfaz representa un listener para poder estar al tanto de como est� yendo la carga.
	 */
	class ILoadingListener {
	public:
		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Delegado que se llama al completarse una operaci�n de carga.
		 * @param sender El observador de la carga que invoca al m�todo.
		 * @param section El identificador de la secci�n actual en el proceso de la carga.
		 * @param operationsCompleted El n�mero de operaciones completadas en la secci�n actual.
		 */
		virtual void loadingUpdated(const LoadingObserver * sender, int section, int operationsCompleted) = 0;

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~ILoadingListener() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ILoadingListener() {}
	};
}

#endif
