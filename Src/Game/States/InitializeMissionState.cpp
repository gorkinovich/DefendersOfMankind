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

//TODO: Completar y comentar el fichero...

#include <CEGUIWindow.h>
#include <elements/CEGUIProgressBar.h>
#include <OgreStringConverter.h>

#include "Game/States/InitializeMissionState.h"

#include "Core/GenericApplication.h"
#include "Core/Entities/LoadingSections.h"
#include "Core/GUI/GUIManager.h"
#include "Core/Input/Keyboard.h"
#include "Core/Resources/LoadingObserver.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Physics/Server.h"
#include "Logic/GameManager.h"
#include "Logic/MissionManager.h"
#include "Logic/Controllers/MusicController.h"
#include "Game/StatesNames.h"

#include "Physics/Server.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string InitializeMissionState::StateName = std::string(INITIALIZE_MISSION_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InitializeMissionState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("InitializeMission.layout", "InitializeMission")) return false;

		// Obtenemos los objetos interactivos de la ventana actual.
		_loadingBar = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::ProgressBar>("InitializeMission/LoadingBar");
		if(!_loadingBar) return false;
		
		_loadingText = Core::GUIManager::GetInstance()->getWindow("InitializeMission/LoadingText");
		if(!_loadingText) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeMissionState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_loadingBar = 0;
		_loadingText = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeMissionState::activate() {
		// Activamos la ventana del estado.
		activateWindow(false, true);

		// Inicializamos los elementos interactivos de la ventana.
		_loadingBar->setProgress(0.0f);
		_loadingText->setText("0%");

		Core::LoadingObserver * loadingObserver = Core::LoadingObserver::GetInstance();
		loadingObserver->setNumberOfOperations(LOADING_SECTION_INITIALIZE, 1);
		loadingObserver->startLoading(NUMBER_OF_LOADING_SECTIONS, this);

		std::string file = Logic::GameManager::GetInstance()->getLastSelectedMissionFile();
		Physics::CServer::getSingletonPtr()->createScene();
		loadingObserver->operationFinished();
		Core::ScriptingManager::GetInstance()->loadAndRunFile(file);
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeMissionState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeMissionState::update(unsigned int lastInterval) {
		//TODO: Completar el método...
		if(Core::LoadingObserver::GetInstance()->isLoadingFinished()) {
			Core::LoadingObserver::GetInstance()->endLoading();
			Logic::MissionManager::GetInstance()->startLevel();
			//_application->changeState(MISSION_STATE_NAME);
			_application->changeState("GameState2");
			Logic::GameManager::GetInstance()->getMusic()->loadSong("GameMusic.mp3");
			Logic::GameManager::GetInstance()->getMusic()->playSong();
		}
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	void InitializeMissionState::loadingUpdated(const Core::LoadingObserver * sender, int section, int operationsCompleted) {
		//TODO: Completar el método...
		Core::LoadingObserver * loadingObserver = Core::LoadingObserver::GetInstance();
		float bigMark = (float)section / (float)loadingObserver->getNumberOfSections();
		float lowMark = 0.0f;
		float mark = bigMark + lowMark;
		
		_loadingBar->setProgress(mark);
		_loadingText->setText(Ogre::StringConverter::toString(mark * 100.0f) + std::string("%"));
		//...
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	InitializeMissionState::InitializeMissionState(Core::GenericApplication * application)
	: GenericMenuState(application), _loadingBar(0), _loadingText(0) {}

	//--------------------------------------------------------------------------------------------------------

	InitializeMissionState::~InitializeMissionState() {}
}
