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

#ifndef __GAME_WORKSHOPSTATE_H__
#define __GAME_WORKSHOPSTATE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Game/GenericMenuState.h"

//************************************************************************************************************
// CEGUI
//************************************************************************************************************

namespace CEGUI {
	class EventArgs;
	class MultiColumnList;
	class PushButton;
	class Window;
}

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	/**
	 * Esta clase representa el estado que se encarga de gestionar la tienda de la partida.
	 */
	class WorkshopState : public Game::GenericMenuState {
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
		// Métodos
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
		 * Actualiza la lógica interna del estado.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		virtual void update(unsigned int lastInterval);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		WorkshopState(Core::GenericApplication * application);

		/**
		 * Destructor del objeto.
		 */
		virtual ~WorkshopState();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El objeto interactivo para controlar al panel principal.
		 */
		CEGUI::Window * _mainPanel;

		/**
		 * El objeto interactivo para controlar el panel del cuadro de diálogo principal.
		 */
		CEGUI::Window * _dialogPanel;

		/**
		 * El objeto interactivo para indicar en una lista los componentes a elegir para la parte seleccionada.
		 */
		CEGUI::MultiColumnList * _parts;

		/**
		 * El objeto interactivo para conocer las propiedades del componente seleccionado.
		 */
		CEGUI::Window * _properties;

		/**
		 * El objeto interactivo para indicar el dinero total del jugador.
		 */
		CEGUI::Window * _money;

		/**
		 * El objeto interactivo para seleccionar una de las partes de la nave.
		 */
		CEGUI::PushButton * _part1;

		/**
		 * El objeto interactivo para seleccionar una de las partes de la nave.
		 */
		CEGUI::PushButton * _part2;

		/**
		 * El objeto interactivo para seleccionar una de las partes de la nave.
		 */
		CEGUI::PushButton * _part3;

		/**
		 * El objeto interactivo para seleccionar una de las partes de la nave.
		 */
		CEGUI::PushButton * _part4;

		/**
		 * La última parte seleccionada.
		 */
		std::string _lastSelectedPart;

		/**
		 * El último item seleccionado.
		 */
		std::string _lastSelectedItem;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Muestra el panel principal.
		 */
		void showMainPanel();

		/**
		 * Muestra el diálogo principal.
		 */
		void showDialogPanel();

		/**
		 * Delegado que gestiona el evento de seleccionar un elemento en "Parts".
		 */
		bool partSelected(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar alguno de los botones "PartButton".
		 */
		bool partButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el botón "HelpButton".
		 */
		bool helpButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el botón "BackButton".
		 */
		bool backButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el botón "BuyButton".
		 */
		bool dialogBuyButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el botón "SelectButton".
		 */
		bool dialogSelectButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el botón "BackButton".
		 */
		bool dialogBackButton(const CEGUI::EventArgs & e);
	};
}

#endif
