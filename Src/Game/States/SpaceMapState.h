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

#ifndef __GAME_SPACEMAPSTATE_H__
#define __GAME_SPACEMAPSTATE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>
#include <string>

#include "Game/GenericMenuState.h"

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
	 * Esta clase representa el estado que se encarga de elegir la pr�xima misi�n a realizar en la partida.
	 */
	class SpaceMapState : public Game::GenericMenuState {
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
		SpaceMapState(Core::GenericApplication * application);

		/**
		 * Destructor del objeto.
		 */
		virtual ~SpaceMapState();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La lista de botones para acceder a las misiones.
		 */
		std::vector<CEGUI::PushButton *> _missionButtons;

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "SpaceMap/Mission".
		 */
		bool missionButton(const CEGUI::EventArgs & e);

		/**
		 * Delegado que gestiona el evento de pulsar el bot�n "BackButton".
		 */
		bool backButton(const CEGUI::EventArgs & e);
	};
}

#endif
