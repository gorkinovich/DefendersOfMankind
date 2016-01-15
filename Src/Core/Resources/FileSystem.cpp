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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ShlObj.h>

#include "Core/Resources/FileSystem.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	std::string FileSystemGetFolder(int csidl) {
		char buffer[MAX_PATH];
		if(SHGetSpecialFolderPathA(0, buffer, csidl, false)) {
			return std::string(buffer);
		}
		return std::string("");
	}

	//--------------------------------------------------------------------------------------------------------

	std::string FileSystemGetUserFolder() {
		return FileSystemGetFolder(CSIDL_PROFILE);
	}

	//--------------------------------------------------------------------------------------------------------

	std::string FileSystemGetDocumentsFolder() {
		return FileSystemGetFolder(CSIDL_PERSONAL);
	}

	//--------------------------------------------------------------------------------------------------------

	std::string FileSystemGetRoamingAppDataFolder() {
		return FileSystemGetFolder(CSIDL_APPDATA);
	}

	//--------------------------------------------------------------------------------------------------------

	std::string FileSystemGetLocalAppDataFolder() {
		return FileSystemGetFolder(CSIDL_LOCAL_APPDATA);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool FileSystemExistsDirectory(const std::string & path) {
		DWORD attributes = GetFileAttributesA(path.c_str());
		return (attributes != INVALID_FILE_ATTRIBUTES) && ((attributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
	}

	//--------------------------------------------------------------------------------------------------------

	bool FileSystemCreateDirectory(const std::string & path) {
		return CreateDirectoryA(path.c_str(), 0) ? true : false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool FileSystemRemoveDirectory(const std::string & path) {
		return RemoveDirectoryA(path.c_str()) ? true : false;
	}
}
