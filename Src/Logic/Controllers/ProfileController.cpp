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

#include <string>
#include <fstream>
#include <algorithm>

#include "Logic/Controllers/ProfileController.h"

#include "Core/Resources/FileSystem.h"
#include "Logic/GameManager.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define MAX_BUFFER_SIZE 300

#define PROFILES_FILE_PATH  std::string("profiles.data")
#define SAVEFILES_FILE_PATH std::string("savefiles.data")

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ProfileController::initialize() {
		_profilesNames.clear();
		_savefilesList.clear();
		_profileDirectory = "";

		const std::string & userDir = GameManager::GetInstance()->getUserDirectory();
		const std::string profilesPath = userDir + PROFILES_FILE_PATH;
		if(!loadStringListFromFile(profilesPath, _profilesNames)) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ProfileController::release() {
		if(_profileDirectory.size() > 0) {
			exitCurrentProfile();
		}

		const std::string & userDir = GameManager::GetInstance()->getUserDirectory();
		const std::string profilesPath = userDir + PROFILES_FILE_PATH;
		saveStringListIntoFile(profilesPath, _profilesNames);

		_profileDirectory = "";
		_savefilesList.clear();
		_profilesNames.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	bool ProfileController::addNewPlayerProfile(const std::string & name) {
		Core::StringList::iterator victim = std::find(_profilesNames.begin(), _profilesNames.end(), name);
		if(victim == _profilesNames.end()) {
			const std::string & userDir = GameManager::GetInstance()->getUserDirectory();
			const std::string finalDir = userDir + name;
			if(!Core::FileSystemExistsDirectory(finalDir) && !Core::FileSystemCreateDirectory(finalDir)) {
				printf("ProfileController::addNewPlayerProfile -> Can't create the profile directory...");
				return false;
			}
			_profilesNames.push_back(name);
		}
		return loadPlayerProfile(name);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ProfileController::loadPlayerProfile(const std::string & name) {
		Core::StringList::iterator victim = std::find(_profilesNames.begin(), _profilesNames.end(), name);
		if(victim == _profilesNames.end()) return false;

		const std::string & userDir = GameManager::GetInstance()->getUserDirectory();
		_profileDirectory = userDir + name + "\\";

		const std::string savefilesPath = _profileDirectory + SAVEFILES_FILE_PATH;
		if(!loadStringListFromFile(savefilesPath, _savefilesList)) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ProfileController::exitCurrentProfile() {
		const std::string savefilesPath = _profileDirectory + SAVEFILES_FILE_PATH;
		saveStringListIntoFile(savefilesPath, _savefilesList);

		_profileDirectory = "";
		_savefilesList.clear();
	}

	//--------------------------------------------------------------------------------------------------------

	bool ProfileController::loadStringListFromFile(const std::string & filePath, Core::StringList & victimList) {
		char buffer[MAX_BUFFER_SIZE];
		std::string victim;
		std::ifstream input;

		input.open(filePath.c_str(), std::ios::in | std::ios::binary);

		while(input.good()) {
			memset(buffer, 0, MAX_BUFFER_SIZE);
			input.getline(buffer, MAX_BUFFER_SIZE, '\n');
			victim = "";
			for(unsigned int i = 0; buffer[i] != 0; ++i) {
				if(buffer[i] != '\n' && buffer[i] != '\r') {
					victim += buffer[i];
				}
			}
			if(victim.size() > 0) {
				victimList.push_back(victim);
			}
		}

		input.close();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ProfileController::saveStringListIntoFile(const std::string & filePath, Core::StringList & victimList) {
		std::ofstream output;
		output.open(filePath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

		if(output.good()) {
			Core::StringList::iterator i = victimList.begin();
			Core::StringList::iterator end = victimList.end();
			for(; i != end; ++i) {
				output << (*i) << "\n";
			}
		}

		output.close();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ProfileController::ProfileController() {}

	//--------------------------------------------------------------------------------------------------------

	ProfileController::~ProfileController() {}
}
