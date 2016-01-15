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

#ifndef __CORE_FILESYSTEM_H__
#define __CORE_FILESYSTEM_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Obtiene la ruta del directorio del usuario.
	 */
	std::string FileSystemGetUserFolder();

	/**
	 * Obtiene la ruta del directorio "Mis Documentos" del usuario.
	 */
	std::string FileSystemGetDocumentsFolder();

	/**
	 * Obtiene la ruta del directorio con los datos compartidos de las aplicaciones del usuario.
	 */
	std::string FileSystemGetRoamingAppDataFolder();

	/**
	 * Obtiene la ruta del directorio con los datos locales de las aplicaciones del usuario.
	 */
	std::string FileSystemGetLocalAppDataFolder();

	/**
	 * Comprueba si existe un directorio.
	 * @param path La ruta del directorio.
	 * @return Devuelve true si existe el directorio indicado.
	 */
	bool FileSystemExistsDirectory(const std::string & path);

	/**
	 * Crea un nuevo directorio.
	 * @param path La ruta del directorio.
	 * @return Devuelve true si se crea el directorio indicado.
	 * @remark Si existe el directorio devuelve false.
	 */
	bool FileSystemCreateDirectory(const std::string & path);

	/**
	 * Borra un directorio.
	 * @param path La ruta del directorio.
	 * @return Devuelve true si se borra el directorio indicado.
	 */
	bool FileSystemRemoveDirectory(const std::string & path);
}

#endif
