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

#ifndef __LOGIC_GAMEMANAGER_H__
#define __LOGIC_GAMEMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Types/StdTypes.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class MusicController;
	class OptionsController;
	class ProfileController;
	class SpaceMapInfo;
	class ResearchInfo;
	class WorkshopInfo;

	/**
	 * Esta clase representa al gestor base del juego.
	 */
	class GameManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Este tipo representa una enumeración de tipos de dificultad del juego.
		 */
		typedef enum {
			EasyDifficulty, NormalDifficulty, HardDifficulty
		} GameDifficulty;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el controlador de la música.
		 */
		inline MusicController * getMusic() { return _music; }

		/**
		 * Obtiene el controlador de las opciones.
		 */
		inline OptionsController * getOptions() { return _options; }

		/**
		 * Obtiene el controlador de los perfiles.
		 */
		inline ProfileController * getProfile() { return _profile; }

		/**
		 * Obtiene los datos relativos al mapa espacial del juego.
		 */
		inline SpaceMapInfo * getSpaceMapInfo() { return _spaceMapInfo; }

		/**
		 * Obtiene los datos relativos al área de investigación del juego.
		 */
		inline ResearchInfo * getResearchInfo() { return _researchInfo; }

		/**
		 * Obtiene los datos relativos a la tienda del juego.
		 */
		inline WorkshopInfo * getWorkshopInfo() { return _workshopInfo; }

		/**
		 * Obtiene el dinero actual que tiene el jugador.
		 */
		inline unsigned int getMoney() const { return _money; }

		/**
		 * Obtiene el dinero actual que tiene el jugador.
		 */
		std::string getMoneyAsString() const;

		/**
		 * Obtiene el directorio donde se salva la información del jugador.
		 */
		inline const std::string & getUserDirectory() const { return _userDirectory; }

		/**
		 * Obtiene la última misión seleccionada.
		 */
		inline const std::string & getLastSelectedMissionFile() const { return _lastSelectedMissionFile; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static GameManager * GetInstance() {
			return _instance;
		}

		/**
		 * Inicializa el gestor.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize();

		/**
		 * Finaliza el gestor.
		 */
		void release();

		//...
		bool startNewGame(GameDifficulty difficulty);
		bool finishCurrentGame();
		bool loadCurrentGame(const std::string & savefile);
		bool saveCurrentGame(const std::string & savefile);
		bool buyPartItem(const std::string & part, const std::string & item);
		bool selectPartItem(const std::string & part, const std::string & item);
		bool buyResearch(const std::string & area, const std::string & subsection, unsigned int index);
		bool startMission(const std::string & file);
		//...

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~GameManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static GameManager * _instance;

		/**
		 * El controlador de la música.
		 */
		MusicController * _music;

		/**
		 * El controlador de las opciones.
		 */
		OptionsController * _options;

		/**
		 * El controlador de los perfiles.
		 */
		ProfileController * _profile;

		/**
		 * Los datos relativos al mapa espacial del juego.
		 */
		SpaceMapInfo * _spaceMapInfo;

		/**
		 * Los datos relativos al área de investigación del juego.
		 */
		ResearchInfo * _researchInfo;

		/**
		 * Los datos relativos a la tienda del juego.
		 */
		WorkshopInfo * _workshopInfo;

		/**
		 * El dinero actual que tiene el jugador.
		 */
		unsigned int _money;

		/**
		 * El directorio donde se salva la información del jugador.
		 */
		std::string _userDirectory;

		/**
		 * La última misión seleccionada.
		 */
		std::string _lastSelectedMissionFile;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa un controlador del gestor.
		 * @param victim El controlador.
		 * @return Devuelve true si se logra inicializar el controlador.
		 */
		template<class T>
		inline bool initializeController(T *& victim);

		/**
		 * Finaliza un controlador del gestor.
		 * @param victim El controlador.
		 */
		template<class T>
		inline void releaseController(T *& victim);

		/**
		 * Finaliza todos los controladores del gestor.
		 */
		void releaseControllers();

		/**
		 * Inicializa unos datos del gestor.
		 * @param victim Los datos.
		 * @return Devuelve true si se logra inicializar los datos.
		 */
		template<class T>
		inline bool initializeInfo(T *& victim);

		/**
		 * Finaliza unos datos del gestor.
		 * @param victim Los datos.
		 */
		template<class T>
		inline void releaseInfo(T *& victim);

		/**
		 * Finaliza todos los datos del gestor.
		 */
		void releaseInfo();

		/**
		 * Finaliza todos los controladores y los datos del gestor.
		 */
		void releaseControllersAndInfo();

		//...

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 */
		GameManager() : _music(0), _options(0), _profile(0),
		_spaceMapInfo(0), _researchInfo(0), _workshopInfo(0), _money(0) {}
	};
}

#endif
