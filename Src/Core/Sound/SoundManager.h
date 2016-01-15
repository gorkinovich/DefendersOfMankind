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

#ifndef __CORE_SOUNDMANAGER_H__
#define __CORE_SOUNDMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <string>

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define MAX_SOUND_CHANNELS 300

//************************************************************************************************************
// FMOD
//************************************************************************************************************

namespace FMOD {
	class Sound;
	class System;
	class ChannelGroup;
	class SoundGroup;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Sound;

	/**
	 * Esta clase representa al gestor del motor de sonido.
	 */
	class SoundManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el grupo por defecto al que asignar los nuevos sonidos creados.
		 */
		inline const std::string & getDefaultGroup() const { return _defaultGroup; }

		/**
		 * Modifica el grupo por defecto al que asignar los nuevos sonidos creados.
		 */
		inline void setDefaultGroup(const std::string & value) { _defaultGroup = value; }

		/**
		 * Obtiene el volumen actual de un grupo.
		 */
		float getGroupVolume(const std::string & name) const;

		/**
		 * Modifica el volumen actual de un grupo.
		 */
		void setGroupVolume(const std::string & name, float value);

		/**
		 * Obtiene si un grupo está en modo "mute".
		 */
		bool getGroupMute(const std::string & name) const;

		/**
		 * Modifica si un grupo está en modo "mute".
		 */
		void setGroupMute(const std::string & name, bool value);

		/**
		 * Obtiene la velocidad de fade en el "mute" de un grupo.
		 * @remark La "velocidad" consiste en el tiempo que tarda en ir de un estado a otro en segundos.
		 */
		float getGroupMuteFadeSpeed(const std::string & name) const;

		/**
		 * Modifica la velocidad de fade en el "mute" de un grupo.
		 * @remark La "velocidad" consiste en el tiempo que tarda en ir de un estado a otro en segundos.
		 */
		void setGroupMuteFadeSpeed(const std::string & name, float value);

		/**
		 * Obtiene si un grupo está en pausado o no.
		 */
		bool getGroupPause(const std::string & name) const;

		/**
		 * Modifica si un grupo está en pausado o no.
		 */
		void setGroupPause(const std::string & name, bool value);

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static SoundManager * GetInstance() {
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

		/**
		 * Actualiza el estado del gestor.
		 */
		void update();

		/**
		 * Comprueba si un grupo está registrado o no.
		 * @param name El nombre identificador del grupo.
		 * @return Devuelve true si se encuentra algún grupo.
		 */
		bool containsGroup(const std::string & name) const;

		/**
		 * Crea y añade un grupo al gestor.
		 * @param name El nombre identificador del grupo.
		 * @return Devuelve true si se logra añadir el grupo correctamente.
		 */
		bool addGroup(const std::string & name);

		/**
		 * Elimina un grupo del gestor.
		 * @param name El nombre identificador del grupo.
		 * @return Devuelve true si se logra borrar el grupo correctamente.
		 */
		bool removeGroup(const std::string & name);

		/**
		 * Elimina todos los grupos del gestor.
		 * @return Devuelve true si se logra borrar todos los grupos correctamente.
		 */
		bool clearAllGroups();

		/**
		 * Para la reproducción de un grupo de canales.
		 * @param name El nombre identificador del grupo.
		 * @return Devuelve true si se logra parar el grupo correctamente.
		 */
		bool stopGroup(const std::string & name);

		/**
		 * Pausa la reproducción de un grupo de canales.
		 * @param name El nombre identificador del grupo.
		 * @return Devuelve true si se logra pausar el grupo correctamente.
		 */
		bool pauseGroup(const std::string & name);

		/**
		 * Reanuda la reproducción de un grupo de canales.
		 * @param name El nombre identificador del grupo.
		 * @return Devuelve true si se logra reanudar el grupo correctamente.
		 */
		bool unpauseGroup(const std::string & name);

		/**
		 * Para la reproducción de todos los grupos de canales.
		 * @return Devuelve true si se logra parar todos los grupos correctamente.
		 */
		bool stopAllGroups();

		/**
		 * Pausa la reproducción de todos los grupos de canales.
		 * @return Devuelve true si se logra pausar todos los grupos correctamente.
		 */
		bool pauseAllGroups();

		/**
		 * Reanuda la reproducción de todos los grupos de canales.
		 * @return Devuelve true si se logra reanudar todos los grupos correctamente.
		 */
		bool unpauseAllGroups();

		/**
		 * Carga un fichero de audio como un sonido normal.
		 * @param fileName El nombre del fichero de audio.
		 * @param loop El flag de reproducción cíclica.
		 * @return El objeto con el sonido cargado.
		 */
		inline Sound * loadSound(const std::string & fileName, bool loop = true) {
			return loadSound(fileName, _defaultGroup, loop);
		}

		/**
		 * Carga un fichero de audio como un sonido de música.
		 * @param fileName El nombre del fichero de audio.
		 * @param loop El flag de reproducción cíclica.
		 * @return El objeto con el sonido cargado.
		 */
		inline Sound * loadMusic(const std::string & fileName, bool loop = true) {
			return loadMusic(fileName, _defaultGroup, loop);
		}

		/**
		 * Carga un fichero de audio como un sonido normal.
		 * @param fileName El nombre del fichero de audio.
		 * @param groupName El nombre del grupo al que pertenecerá el sonido.
		 * @param loop El flag de reproducción cíclica.
		 * @return El objeto con el sonido cargado.
		 */
		Sound * loadSound(const std::string & fileName, const std::string & groupName, bool loop = true);

		/**
		 * Carga un fichero de audio como un sonido de música.
		 * @param fileName El nombre del fichero de audio.
		 * @param groupName El nombre del grupo al que pertenecerá el sonido.
		 * @param loop El flag de reproducción cíclica.
		 * @return El objeto con el sonido cargado.
		 */
		Sound * loadMusic(const std::string & fileName, const std::string & groupName, bool loop = true);

		/**
		 * Precarga un fichero de audio como un sonido normal.
		 * @param fileName El nombre del fichero de audio.
		 * @param loop El flag de reproducción cíclica.
		 * @return Devuelve true si se logra precargar el sonido antes.
		 */
		inline bool preloadSound(const std::string & fileName, bool loop = true) {
			return preloadSound(fileName, _defaultGroup, loop);
		}

		/**
		 * Precarga un fichero de audio como un sonido de música.
		 * @param fileName El nombre del fichero de audio.
		 * @param loop El flag de reproducción cíclica.
		 * @return Devuelve true si se logra precargar el sonido antes.
		 */
		inline bool preloadMusic(const std::string & fileName, bool loop = true) {
			return preloadMusic(fileName, _defaultGroup, loop);
		}

		/**
		 * Precarga un fichero de audio como un sonido normal.
		 * @param fileName El nombre del fichero de audio.
		 * @param groupName El nombre del grupo al que pertenecerá el sonido.
		 * @param loop El flag de reproducción cíclica.
		 * @return Devuelve true si se logra precargar el sonido antes.
		 */
		bool preloadSound(const std::string & fileName, const std::string & groupName, bool loop = true);

		/**
		 * Precarga un fichero de audio como un sonido de música.
		 * @param fileName El nombre del fichero de audio.
		 * @param groupName El nombre del grupo al que pertenecerá el sonido.
		 * @param loop El flag de reproducción cíclica.
		 * @return Devuelve true si se logra precargar el sonido antes.
		 */
		bool preloadMusic(const std::string & fileName, const std::string & groupName, bool loop = true);

		/**
		 * Descarga y elimina un buffer de audio.
		 * @param victim El sonido a descargar.
		 */
		bool unloadSound(const std::string & fileName);

		/**
		 * Elimina todos los buffers de audio del gestor.
		 * @return Devuelve true si se logra borrar todos los buffers correctamente.
		 */
		bool clearAllSounds();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~SoundManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa un grupo de canales y sonidos.
		 */
		typedef struct {
			FMOD::ChannelGroup * channel;
			FMOD::SoundGroup * sound;
		} Group;

		/**
		 * Este tipo representa una tabla de grupos de canales y de sonidos.
		 */
		typedef std::map<std::string, Group> GroupsTable;

		/**
		 * Este tipo representa un buffer de sonido.
		 */
		typedef struct {
			std::string groupName;
			FMOD::Sound * buffer;
		} SoundBuffer;

		/**
		 * Este tipo representa una tabla de sonidos.
		 */
		typedef std::map<std::string, SoundBuffer> SoundsTable;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static SoundManager * _instance;

		/**
		 * El gestor FMOD del motor de sonido.
		 */
		FMOD::System * _system;

		/**
		 * La tabla de grupos en el gestor.
		 */
		GroupsTable _groupsTable;

		/**
		 * La tabla de sonidos del gestor.
		 */
		SoundsTable _soundsTable;

		/**
		 * El grupo por defecto al que asignar los nuevos sonidos creados.
		 */
		std::string _defaultGroup;

		/**
		 * El grupo maestro del motor de sonido.
		 */
		Group _masterGroup;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un objeto sonido con el que el gestor de sonido pueda trabajar.
		 * @param fileName El nombre del fichero de audio.
		 * @return El objeto con el sonido cargado.
		 */
		inline Sound * createSound(const std::string & fileName);

		/**
		 * Añade y registra un buffer de sonido para guardarlo en la tabla de sonidos del gestor.
		 * @param fileName El nombre del fichero de audio.
		 * @param groupName El nombre del grupo al que pertenecerá el sonido.
		 * @param buffer El buffer con el sonido.
		 * @return Devuelve true si se logra registrar el sonido en el gestor.
		 */
		inline bool addSoundBuffer(const std::string & fileName, const std::string & groupName, FMOD::Sound * buffer);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		SoundManager() : _system(0) {
			_masterGroup.channel = 0;
			_masterGroup.sound = 0;
		}

		friend class Core::Sound;
	};
}

#endif
