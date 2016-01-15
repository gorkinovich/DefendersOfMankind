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

#ifndef __GAME_GENERICMENUSTATE_H__
#define __GAME_GENERICMENUSTATE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>
#include "Core/ApplicationState.h"

//************************************************************************************************************
// CEGUI
//************************************************************************************************************

namespace CEGUI {
	class Window;
}

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	/**
	 * Esta clase representa un estado genérico de los menús de la aplicación.
	 */
	class GenericMenuState : public Core::ApplicationState {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Inicializa la ventana del estado.
		 * @param fileName El nombre del fichero con el objeto ventana.
		 * @param windowName El nombre del objeto ventana.
		 * @return Devuelve true si se logra inicializar la ventana.
		 */
		bool initializeWindow(const std::string & fileName, const std::string & windowName);

		/**
		 * Finaliza la ventana del estado.
		 */
		void releaseWindow();

		/**
		 * Activa la ventana del estado.
		 * @param showMouse El flag encargado de mostrar el cursor del ratón o no.
		 * @param updateGraphics Flag para indicar si se debe actualizar el motor gráfico o no.
		 */
		void activateWindow(bool showMouse = true, bool updateGraphics = false);

		/**
		 * Desactiva la ventana del estado.
		 * @param hideMouse El flag encargado de ocultar el cursor del ratón o no.
		 */
		void deactivateWindow(bool hideMouse = true);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 */
		GenericMenuState(Core::GenericApplication * application);

		/**
		 * Destructor del objeto.
		 */
		virtual ~GenericMenuState();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * El objeto raíz que representa la "ventana" de menú que CEGUI mostrará.
		 */
		CEGUI::Window * _window;
	};
}

#endif
