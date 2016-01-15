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

//TODO: Este estado ser� borrado en el futuro...

#ifndef __APPLICATION_GAMESTATE_H__
#define __APPLICATION_GAMESTATE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/ApplicationState.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class TerrainGroup;
	class RenderWindow;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class World;
}

//************************************************************************************************************
// Application
//************************************************************************************************************

namespace Application {
	/**
	 * Esta clase representa el estado de la aplicaci�n que gestiona la misi�n actual.
	 */
	class GameState : public Core::ApplicationState {
	public:
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
		GameState(Core::GenericApplication * application);
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~GameState();
		
	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * El controlador del terreno en la escena.
		 */
		Ogre::TerrainGroup * _terrain;

		/**
		 * Ventana de renderizado (para obtener los frames por segundo)
		 */
		Ogre::RenderWindow* _renderWin;

		/**
		 * ...
		 */
		bool _viewDebugInfo;

		/**
		 * ...
		 */
		float _time;

	private:
		Core::World * _map;
	};
}

#endif
