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

#ifndef __Logic_HUDController_H
#define __Logic_HUDController_H

namespace CEGUI
{
	class Window;
}


namespace Logic
{
	// Gestiona la actualizaci�n del HUD
	class HUDController
	{
	public:

		/**
		 *	Constructor.
		 */
		HUDController ();

		/**
		 *	Destructor.
		 */
		~HUDController();

		/**
		 *	Activa la la clase, muestra el HUD.
		 */
		void activate();

		/**
		 *	Desactiva la la clase, oculta el HUD.
		 */
		void deactivate();

		/**
		 *	Cambia el texto del campo bonificaci�n.
		 */
		void setScore(unsigned int);

		/**
		 *	Actualiza la visualizaci�n de la barra de vida.
		 */
		void updateLifeBar(float);

		/**
		* Actualiza la visualizaci�n del n�mero de vidas restantes
		*/
		void updateLifeCounter(unsigned short n);

		// Establece el �rea que corresponda...
		void setAreaOfLifeBar();		// ... para la barra de vida
		void setAreaOfLifeCounter();	// ... para el contador de vidas restantes

		/**
		* Actualiza la informaci�n de debug (FPS y n�mero de tri�ngulos)
		*/
		void updateInfoDebug(float fps, unsigned int t);

		/**
		* Muestra o no la ventana de informaci�n de debug
		*/
		void showInfoDebug(bool show);


	protected:

		/**
		Ventana de juego.
		*/
		CEGUI::Window* _gameWindow;

		/**
		Ventana que muestra la bonificaci�n actual.
		*/
		CEGUI::Window* _scoreWindow;

		/**
		Ventanas que forman la barra de vida del jugador.
		*/
		CEGUI::Window* _lifeBar[20];

		/**
		Ventanas para mostrar el n�mero de vidas restantes
		*/
		CEGUI::Window* _nLife[3];

		/**
		Relaci�n de aspecto
		*/
		float _ratio;

		/**
		Ventana que muestra la informaci�n de debug (FPS y n�mero de tri�ngulos)
		*/
		CEGUI::Window* _infoDebugWindow;
		


	}; // class HUDController

} // namespace GUI

#endif // __GUI_HUDController_H
