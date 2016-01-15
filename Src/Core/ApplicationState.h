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

#ifndef __CORE_APPLICATIONSTATE_H__
#define __CORE_APPLICATIONSTATE_H__

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class GenericApplication;
	class BaseManager;

	/**
	 * Esta clase abstracta representa un estado genérico de la aplicación.
	 */
	class ApplicationState {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el estado.
		 * @return Devuelve true si se logra inicializar el estado.
		 */
		virtual bool initialize() { return true; }

		/**
		 * Finaliza el estado.
		 */
		virtual void release() {}

		/**
		 * Activa el estado.
		 */
		virtual void activate() {}

		/**
		 * Desactiva el estado.
		 */
		virtual void deactivate() {}

		/**
		 * Actualiza la lógica interna del estado.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		virtual void update(unsigned int lastInterval) {}

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~ApplicationState();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La aplicación a la que pertenece el estado.
		 */
		GenericApplication * _application;

		/**
		 * El gestor del nucleo del motor.
		 */
		BaseManager * _baseManager;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ApplicationState(GenericApplication * application);
	};
}

#endif
