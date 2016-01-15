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

#ifndef __GAME_RESEARCHAREASTATE_H__
#define __GAME_RESEARCHAREASTATE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>
#include <string>

#include "Game/GenericMenuState.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define MAX_RESEARCH_BUTTONS 4

//************************************************************************************************************
// CEGUI
//************************************************************************************************************

namespace CEGUI {
	class EventArgs;
	class PushButton;
	class Window;
}

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	/**
	 * Esta clase representa el estado que se encarga de gestionar la investigaci�n de la partida.
	 */
	class ResearchAreaState : public Game::GenericMenuState {
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

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ResearchAreaState(Core::GenericApplication * application);

		/**
		 * Destructor del objeto.
		 */
		virtual ~ResearchAreaState();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El objeto interactivo para controlar al panel principal.
		 */
		CEGUI::Window * _mainPanel;

		/**
		 * El objeto interactivo para controlar el panel del cuadro de di�logo principal.
		 */
		CEGUI::Window * _dialogPanel;

		/**
		 * El objeto interactivo para indicar el nombre del �rea anterior.
		 */
		CEGUI::Window * _leftButton;

		/**
		 * El objeto interactivo para indicar el nombre del �rea actual.
		 */
		CEGUI::Window * _areaTitle;

		/**
		 * El objeto interactivo para indicar el nombre del �rea siguiente.
		 */
		CEGUI::Window * _rightButton;

		/**
		 * El objeto interactivo para indicar el dinero que tiene el jugador.
		 */
		CEGUI::Window * _money;

		/**
		 * El objeto interactivo para indicar el nombre de la investigaci�n seleccionada.
		 */
		CEGUI::Window * _dialogTitle;

		/**
		 * El objeto interactivo para indicar el coste de la investigaci�n seleccionada.
		 */
		CEGUI::Window * _dialogCost;

		/**
		 * El objeto interactivo para indicar en el panel de confirmaci�n el dinero que tiene el jugador.
		 */
		CEGUI::Window * _dialogMoney;

		/**
		 * El objeto interactivo para seleccionar una de las investigaciones de una rama izquierda.
		 */
		CEGUI::PushButton * _leftResearch[MAX_RESEARCH_BUTTONS];

		/**
		 * El objeto interactivo para seleccionar una de las investigaciones de una rama central.
		 */
		CEGUI::PushButton * _middleResearch[MAX_RESEARCH_BUTTONS];

		/**
		 * El objeto interactivo para seleccionar una de las investigaciones de una rama derecha.
		 */
		CEGUI::PushButton * _rightResearch[MAX_RESEARCH_BUTTONS];

		/**
		 * El �rea de investigaci�n actual.
		 */
		unsigned int _currentArea;

		/**
		 * Los nombres de las �reas actuales en el juego.
		 */
		std::vector<std::string> _areasNames;

		/**
		 * La rama de investigaci�n actual.
		 * @remark Valores: 0 (left), 1 (middle) y 2 (right).
		 */
		unsigned int _currentSubarea;

		/**
		 * La investigaci�n actual.
		 */
		unsigned int _currentResearch;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el �ndice anterior del �rea de investigaci�n actual.
		 */
		unsigned int getPreviousAreaIndex();

		/**
		 * Obtiene el �ndice siguiente del �rea de investigaci�n actual.
		 */
		unsigned int getNextAreaIndex();

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Muestra el panel principal.
		 */
		void showMainPanel();

		/**
		 * Muestra el di�logo principal.
		 */
		void showDialogPanel();

		/**
		 * Actualiza los datos del �rea actual.
		 */
		void updateAreaData();

		/**
		 * Actualiza y muestra los datos del panel de confirmaci�n.
		 */
		void updateAndShowDialogPanel();

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "LeftButton".
		 */
		bool leftButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "RightButton".
		 */
		bool rightButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "HelpButton".
		 */
		bool helpButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "BackButton".
		 */
		bool backButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "Dialog/BuyButton".
		 */
		bool dialogBuyButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "Dialog/CancelButton".
		 */
		bool dialogCancelButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "LeftResearch".
		 */
		bool leftResearchButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "MiddleResearch".
		 */
		bool middleResearchButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "RightResearch".
		 */
		bool rightResearchButton(const CEGUI::EventArgs & e);
	};
}

#endif
