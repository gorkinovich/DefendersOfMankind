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

#ifndef __LOGIC_PROFILECONTROLLER_H__
#define __LOGIC_PROFILECONTROLLER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Types/StdTypes.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class GameManager;

	/**
	 * Esta clase representa el controlador de los perfiles del juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class ProfileController {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la lista de nombres de los perfiles.
		 */
		inline const Core::StringList & getProfilesNames() const { return _profilesNames; }

		/**
		 * Obtiene la lista de nombres de las partidas.
		 */
		inline const Core::StringList & getSavefilesList() const { return _savefilesList; }

		/**
		 * Obtiene el directorio donde se salva la información del perfil.
		 */
		inline const std::string & getProfileDirectory() const { return _profileDirectory; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el controlador.
		 * @return Devuelve true si se logra inicializar el controlador.
		 */
		bool initialize();

		/**
		 * Finaliza el controlador.
		 */
		void release();

		/**
		 * Añade un perfil nuevo al juego.
		 * @param name El nombre del nuevo perfil.
		 * @return Devuelve true si logra crear el perfil o si ya existía.
		 */
		bool addNewPlayerProfile(const std::string & name);

		/**
		 * Carga un perfil en el juego.
		 * @param name El nombre del nuevo perfil.
		 * @return Devuelve true si logra cargar el perfil.
		 */
		bool loadPlayerProfile(const std::string & name);

		/**
		 * Sale del perfil actualmente cargado.
		 */
		void exitCurrentProfile();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La lista de nombres de los perfiles.
		 */
		Core::StringList _profilesNames;

		/**
		 * La lista de nombres de las partidas.
		 */
		Core::StringList _savefilesList;

		/**
		 * El directorio donde se salva la información del perfil.
		 */
		std::string _profileDirectory;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Carga el contenido de un fichero dentro de una lista de cadenas.
		 * @param filePath La ruta del fichero a cargar.
		 * @param victimList La lista de cadenas donde meter el contenido del fichero.
		 * @return Devuelve true si se logra llevar la carga correctamente.
		 */
		bool loadStringListFromFile(const std::string & filePath, Core::StringList & victimList);

		/**
		 * Salva el contenido de una lista de cadenas en un fichero.
		 * @param filePath La ruta del fichero a salvar.
		 * @param victimList La lista de cadenas que salvar.
		 * @return Devuelve true si se logra salvar la lista correctamente.
		 */
		bool saveStringListIntoFile(const std::string & filePath, Core::StringList & victimList);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		ProfileController();

		/**
		 * Destructor del objeto.
		 */
		virtual ~ProfileController();

		friend class Logic::GameManager;
	};
}

#endif
