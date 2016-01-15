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

#include "Game/States/ShowStatisticsState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/MissionManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ShowStatisticsState::StateName = std::string(SHOW_STATISTICS_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ShowStatisticsState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ShowStatistics.layout", "ShowStatistics")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ShowStatistics/ReturnButton", &ShowStatisticsState::returnButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_statisticsLabels = Core::GUIManager::GetInstance()->getWindow("ShowStatistics/StatisticsLabels");
		if(!_statisticsLabels) return false;

		_statisticsValues = Core::GUIManager::GetInstance()->getWindow("ShowStatistics/StatisticsValues");
		if(!_statisticsValues) return false;

		_finalPointsLabel = Core::GUIManager::GetInstance()->getWindow("ShowStatistics/FinalPointsLabel");
		if(!_finalPointsLabel) return false;

		_finalPointsValue = Core::GUIManager::GetInstance()->getWindow("ShowStatistics/FinalPointsValue");
		if(!_finalPointsValue) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ShowStatisticsState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_statisticsLabels = 0;
		_statisticsValues = 0;
		_finalPointsLabel = 0;
		_finalPointsValue = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ShowStatisticsState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		// Inicializamos los elementos interactivos de la ventana.
		Logic::MissionManager * missionManager = Logic::MissionManager::GetInstance();
		_statisticsLabels->setText(missionManager->getStatisticsLabels());
		_statisticsValues->setText(missionManager->getStatisticsValues());
		_finalPointsLabel->setText(missionManager->getFinalPointsLabel());
		_finalPointsValue->setText(missionManager->getFinalPointsValue());
	}

	//--------------------------------------------------------------------------------------------------------

	void ShowStatisticsState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ShowStatisticsState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->changeState(RELEASE_MISSION_STATE_NAME);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ShowStatisticsState::returnButton(const CEGUI::EventArgs & e) {
		_application->changeState(RELEASE_MISSION_STATE_NAME);
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ShowStatisticsState::ShowStatisticsState(Core::GenericApplication * application) : GenericMenuState(application),
	_statisticsLabels(0), _statisticsValues(0), _finalPointsLabel(0), _finalPointsValue(0) {}

	//--------------------------------------------------------------------------------------------------------

	ShowStatisticsState::~ShowStatisticsState() {}
}
