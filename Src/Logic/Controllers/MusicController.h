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

#ifndef __LOGIC_MUSICCONTROLLER_H__
#define __LOGIC_MUSICCONTROLLER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class SoundManager;
	class Sound;
}

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class GameManager;

	/**
	 * Esta clase representa el controlador de la música para el juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class MusicController {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * Nombre del grupo de la música dentro del gestor del motor de sonido.
		 */
		static const std::string MusicGroupName;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la ruta de la canción actual.
		 */
		inline const std::string & getCurrentSongPath() const { return _currentSongPath; }

		/**
		 * Obtiene el volumen actual de la música.
		 */
		float getSongVolume() const;

		/**
		 * Modifica el volumen actual de la música.
		 */
		void setSongVolume(float value);

		/**
		 * Obtiene si la música está en modo "mute".
		 */
		bool getSongMute() const;

		/**
		 * Modifica si la música está en modo "mute".
		 */
		void setSongMute(bool value);

		/**
		 * Obtiene la velocidad de fade en el "mute" de la música.
		 * @remark La "velocidad" consiste en el tiempo que tarda en ir de un estado a otro en segundos.
		 */
		float getFadeSpeed() const;

		/**
		 * Modifica la velocidad de fade en el "mute" de la música.
		 * @remark La "velocidad" consiste en el tiempo que tarda en ir de un estado a otro en segundos.
		 */
		void setFadeSpeed(float value);

		/**
		 * Obtiene si la música está en pausada o no.
		 */
		bool getSongPause() const;

		/**
		 * Modifica si la música está en pausada o no.
		 */
		void setSongPause(bool value);

		/**
		 * Obtiene si se está actualmente reproduciendo la canción.
		 */
		bool isSongPlaying() const;

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
		 * Carga una canción.
		 * @param fileName El nombre del fichero de audio.
		 * @param loop El flag de reproducción cíclica.
		 */
		void loadSong(const std::string & path, bool loop = true);

		/**
		 * Descarga una canción.
		 */
		void unloadSong();

		/**
		 * Reproduce la canción.
		 */
		void playSong();

		/**
		 * Para la canción.
		 */
		void stopSong();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El gestor del motor de sonido.
		 */
		Core::SoundManager * _soundManager;

		/**
		 * La ruta de la canción actual.
		 */
		std::string _currentSongPath;

		/**
		 * La canción actual.
		 */
		Core::Sound * _currentSong;

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		MusicController();

		/**
		 * Destructor del objeto.
		 */
		virtual ~MusicController();

		friend class Logic::GameManager;
	};
}

#endif
