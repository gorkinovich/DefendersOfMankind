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

#include "Game/States/ChooseDifficultyLevelState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ChooseDifficultyLevelState::StateName = std::string(CHOOSE_DIFFICULTY_LEVEL_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ChooseDifficultyLevelState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ChooseDifficultyLevel.layout", "ChooseDifficultyLevel")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ChooseDifficultyLevel/EasyButton", &ChooseDifficultyLevelState::easyButton, this);
		SubscribeToClickedEvent("ChooseDifficultyLevel/NormalButton", &ChooseDifficultyLevelState::normalButton, this);
		SubscribeToClickedEvent("ChooseDifficultyLevel/HardButton", &ChooseDifficultyLevelState::hardButton, this);
		SubscribeToClickedEvent("ChooseDifficultyLevel/BackButton", &ChooseDifficultyLevelState::backButton, this);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ChooseDifficultyLevelState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ChooseDifficultyLevelState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ChooseDifficultyLevelState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ChooseDifficultyLevelState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ChooseDifficultyLevelState::easyButton(const CEGUI::EventArgs & e) {
		if(Logic::GameManager::GetInstance()->startNewGame(Logic::GameManager::EasyDifficulty)) {
			_application->changeState(INITIALIZE_GAME_STATE_NAME);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ChooseDifficultyLevelState::normalButton(const CEGUI::EventArgs & e) {
		if(Logic::GameManager::GetInstance()->startNewGame(Logic::GameManager::NormalDifficulty)) {
			_application->changeState(INITIALIZE_GAME_STATE_NAME);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ChooseDifficultyLevelState::hardButton(const CEGUI::EventArgs & e) {
		if(Logic::GameManager::GetInstance()->startNewGame(Logic::GameManager::HardDifficulty)) {
			_application->changeState(INITIALIZE_GAME_STATE_NAME);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ChooseDifficultyLevelState::backButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ChooseDifficultyLevelState::ChooseDifficultyLevelState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	ChooseDifficultyLevelState::~ChooseDifficultyLevelState() {}
}
