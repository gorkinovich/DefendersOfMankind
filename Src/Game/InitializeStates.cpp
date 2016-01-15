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

#include "Game/DoMApplication.h"

#include "Game/States/InitializeState.h"
#include "Game/States/MainMenuState.h"
#include "Game/States/NewPlayerProfileState.h"
#include "Game/States/ChoosePlayerProfileState.h"
#include "Game/States/ConfirmExitState.h"
#include "Game/States/ReleaseState.h"
#include "Game/States/CreditsState.h"

#include "Game/States/MainPlayerMenuState.h"
#include "Game/States/ChooseDifficultyLevelState.h"
#include "Game/States/LoadGameState.h"
#include "Game/States/OptionsState.h"
#include "Game/States/GameplayOptionsState.h"
#include "Game/States/GraphicsOptionsState.h"
#include "Game/States/SoundOptionsState.h"
#include "Game/States/ConfirmExitProfileState.h"

#include "Game/States/InitializeGameState.h"
#include "Game/States/CommandCenterMenuState.h"
#include "Game/States/SpaceMapState.h"
#include "Game/States/ResearchAreaState.h"
#include "Game/States/WorkshopState.h"
#include "Game/States/SaveGameState.h"
#include "Game/States/ConfirmExitGameState.h"
#include "Game/States/ReleaseGameState.h"

#include "Game/States/InitializeMissionState.h"
#include "Game/States/MissionState.h"
#include "Game/States/CutsceneState.h"
#include "Game/States/MissionMenuState.h"
#include "Game/States/ConfirmExitMissionState.h"
#include "Game/States/MissionFailedState.h"
#include "Game/States/ShowStatisticsState.h"
#include "Game/States/ReleaseMissionState.h"

//TODO: Comprobar qué includes sí se están usando de verdad...
#include "Application/GameState.h"
//...

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool DoMApplication::initializeStates() {
		//TODO: Añadir los nuevos estados en esta zona...
		addToTable("GameState2", new Application::GameState(this));
		//...

		// Añadimos los estados usados por el juego a la tabla de estados de la aplicación.
		easyAddToTable<Game::InitializeState>();
		easyAddToTable<Game::MainMenuState>();
		easyAddToTable<Game::NewPlayerProfileState>();
		easyAddToTable<Game::ChoosePlayerProfileState>();
		easyAddToTable<Game::ConfirmExitState>();
		easyAddToTable<Game::ReleaseState>();
		easyAddToTable<Game::CreditsState>();

		easyAddToTable<Game::MainPlayerMenuState>();
		easyAddToTable<Game::ChooseDifficultyLevelState>();
		easyAddToTable<Game::LoadGameState>();
		easyAddToTable<Game::OptionsState>();
		easyAddToTable<Game::GameplayOptionsState>();
		easyAddToTable<Game::GraphicsOptionsState>();
		easyAddToTable<Game::SoundOptionsState>();
		easyAddToTable<Game::ConfirmExitProfileState>();

		easyAddToTable<Game::InitializeGameState>();
		easyAddToTable<Game::CommandCenterMenuState>();
		easyAddToTable<Game::SpaceMapState>();
		easyAddToTable<Game::ResearchAreaState>();
		easyAddToTable<Game::WorkshopState>();
		easyAddToTable<Game::SaveGameState>();
		easyAddToTable<Game::ConfirmExitGameState>();
		easyAddToTable<Game::ReleaseGameState>();

		easyAddToTable<Game::InitializeMissionState>();
		easyAddToTable<Game::MissionState>();
		easyAddToTable<Game::CutsceneState>();
		easyAddToTable<Game::MissionMenuState>();
		easyAddToTable<Game::ConfirmExitMissionState>();
		easyAddToTable<Game::MissionFailedState>();
		easyAddToTable<Game::ShowStatisticsState>();
		easyAddToTable<Game::ReleaseMissionState>();
		
		// Añadimos a la pila el estado inicial.
		pushState(Game::InitializeState::StateName);

		// Actualizamos internamente el cambio al estado que hemos pedido
		updateChange();

		// Y comprobamos que el cambio se ha realizado.
		return _currentState != 0;
	}
}
