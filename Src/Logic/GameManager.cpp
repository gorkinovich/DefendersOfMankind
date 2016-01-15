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

#include <assert.h>
#include <OgreStringConverter.h>

#include "Logic/GameManager.h"

#include "Core/SafeDelete.h"
#include "Core/GenericApplication.h"
#include "Core/Resources/FileSystem.h"
#include "Logic/MissionManager.h"
#include "Logic/Controllers/MusicController.h"
#include "Logic/Controllers/OptionsController.h"
#include "Logic/Controllers/ProfileController.h"
#include "Logic/Data/SpaceMapInfo.h"
#include "Logic/Data/ResearchInfo.h"
#include "Logic/Data/WorkshopInfo.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	GameManager * GameManager::_instance = new GameManager();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	std::string GameManager::getMoneyAsString() const {
		return Ogre::StringConverter::toString(_money);
	}
	
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GameManager::initialize() {
		//TODO: Completar el método...

		// Buscamos el directorio con los datos del jugador.
		_userDirectory = Core::FileSystemGetLocalAppDataFolder();
		if(_userDirectory.size() == 0) return false;

		_userDirectory += "\\MankindDefenders";
		if(Core::FileSystemExistsDirectory(_userDirectory) || Core::FileSystemCreateDirectory(_userDirectory)) {
			_userDirectory += "\\";
		} else {
			return false;
		}

		// Inicializamos los datos del mapa espacial.
		if(!initializeInfo(_spaceMapInfo)) return false;

		// Inicializamos los datos del área de investigación.
		if(!initializeInfo(_researchInfo)) return false;

		// Inicializamos los datos de la tienda.
		if(!initializeInfo(_workshopInfo)) return false;

		// Inicializamos el controlador de la música.
		if(!initializeController(_music)) return false;

		// Inicializamos el controlador de las opciones.
		if(!initializeController(_options)) return false;

		// Inicializamos el controlador de los perfiles.
		if(!initializeController(_profile)) return false;

		// Inicializamos el gestor de las misiones.
		if(!MissionManager::GetInstance()->initialize()) {
			releaseControllersAndInfo();
			return false;
		}

		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	void GameManager::release() {
		//TODO: Completar el método...
		releaseControllersAndInfo();
		MissionManager::GetInstance()->release();
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::startNewGame(GameDifficulty difficulty) {
		//TODO: Completar el método...
		printf("GameManager::startNewGame -> Started...\n");
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::finishCurrentGame() {
		//TODO: Completar el método...
		printf("GameManager::finishCurrentGame -> Finished...\n");
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::loadCurrentGame(const std::string & savefile) {
		//TODO: Completar el método...
		printf("GameManager::loadCurrentGame -> %s\n", savefile.c_str());
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::saveCurrentGame(const std::string & savefile) {
		//TODO: Completar el método...
		printf("GameManager::saveCurrentGame -> %s\n", savefile.c_str());
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::buyPartItem(const std::string & part, const std::string & item) {
		//TODO: Completar el método...
		printf("GameManager::buyPartItem -> %s, %s\n", part.c_str(), item.c_str());
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::selectPartItem(const std::string & part, const std::string & item) {
		//TODO: Completar el método...
		printf("GameManager::selectPartItem -> %s, %s\n", part.c_str(), item.c_str());
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::buyResearch(const std::string & area, const std::string & subsection, unsigned int index) {
		//TODO: Completar el método...
		printf("GameManager::buyResearch -> %s, %s, %u\n", area.c_str(), subsection.c_str(), index);
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool GameManager::startMission(const std::string & file) {
		//TODO: Completar el método...
		printf("GameManager::startMission -> %s\n", file.c_str());
		_lastSelectedMissionFile = file;
		Core::GenericApplication::GetInstance()->pushState(INITIALIZE_MISSION_STATE_NAME);
		return true;
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//--------------------------------------------------------------------------------------------------------

	template<class T>
	bool GameManager::initializeController(T *& victim) {
		// Creamos el nuevo controlador.
		victim = new T();
		// Comprobamos si se ha creado correctamente y si se ha podido inicializar.
		if(!victim || !victim->initialize()) {
			// Si falla borramos todos los controladores y los datos.
			releaseControllersAndInfo();
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	template<class T>
	void GameManager::releaseController(T *& victim) {
		// Si el controlador existe, lo finalizamos y después lo borramos de la memoria.
		if(victim) {
			victim->release();
			delete victim;
			victim = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GameManager::releaseControllers() {
		//TODO: Completar el método...
		releaseController(_music);
		releaseController(_options);
		releaseController(_profile);
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	template<class T>
	bool GameManager::initializeInfo(T *& victim) {
		// Creamos el nuevo objeto con los datos.
		victim = new T();
		// Comprobamos si se ha creado correctamente.
		if(!victim) {
			// Si falla borramos todos los controladores y los datos.
			releaseControllersAndInfo();
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	template<class T>
	void GameManager::releaseInfo(T *& victim) {
		if(victim) {
			delete victim;
			victim = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GameManager::releaseInfo() {
		//TODO: Completar el método...
		releaseInfo(_spaceMapInfo);
		releaseInfo(_researchInfo);
		releaseInfo(_workshopInfo);
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	void GameManager::releaseControllersAndInfo() {
		releaseControllers();
		releaseInfo();
	}

	//--------------------------------------------------------------------------------------------------------

	//...
}
