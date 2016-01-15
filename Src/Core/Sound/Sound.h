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

#ifndef __CORE_SOUND_H__
#define __CORE_SOUND_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

//************************************************************************************************************
// FMOD
//************************************************************************************************************

namespace FMOD {
	class System;
	class Channel;
	class Sound;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class SoundManager;

	/**
	 * Esta clase representa un sonido con el que el gestor de sonido pueda trabajar.
	 */
	class Sound {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre del fichero de audio.
		 */
		inline const std::string & getFileName() const { return _fileName; }

		/**
		 * Obtiene el nombre del grupo al que pertenecerá el sonido.
		 */
		inline const std::string & getGroupName() const { return _groupName; }

		/**
		 * Obtiene si se está actualmente reproduciendo el sonido.
		 */
		bool isPlaying() const;

		/**
		 * Obtiene si se está actualmente pausado el sonido.
		 */
		bool isPaused() const;

		/**
		 * Obtiene el volumen actual del sonido.
		 */
		float getVolume() const;

		/**
		 * Modifica el volumen actual del sonido.
		 */
		void setVolume(float value);

		/**
		 * Obtiene si el sonido está en modo "mute".
		 */
		bool getMute() const;

		/**
		 * Modifica si el sonido está en modo "mute".
		 */
		void setMute(bool value);

		/**
		 * Obtiene el "pan" actual del sonido.
		 */
		float getPan() const;

		/**
		 * Modifica el "pan" actual del sonido.
		 */
		void setPan(float value);

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Reproduce el sonido.
		 * @return Devuelve true cuando la operación se realiza correctamente.
		 */
		bool play();

		/**
		 * Pausa el sonido.
		 * @return Devuelve true cuando la operación se realiza correctamente.
		 */
		bool pause();

		/**
		 * Para el sonido.
		 * @return Devuelve true cuando la operación se realiza correctamente.
		 */
		bool stop();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Sound(const Sound & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Sound();

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre del fichero de audio.
		 */
		std::string _fileName;

		/**
		 * El nombre del grupo al que pertenecerá el sonido.
		 */
		std::string _groupName;

		/**
		 * El buffer interno con el sonido.
		 */
		FMOD::Sound * _buffer;

		/**
		 * El canal donde se reproduce el sonido.
		 */
		FMOD::Channel * _channel;

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * El gestor del motor de sonido.
		 */
		static SoundManager * _soundManager;

		/**
		 * Construye un nuevo objeto.
		 */
		Sound(const std::string & fileName, const std::string & groupName, FMOD::Sound * buffer);

		friend class Core::SoundManager;
	};
}

#endif
