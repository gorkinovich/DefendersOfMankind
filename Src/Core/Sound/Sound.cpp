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

#include <assert.h>
#include <OgreLog.h>
#include <fmod.hpp>
#include <fmod_errors.h>

#include "Core/Sound/Sound.h"
#include "Core/Sound/SoundManager.h"
#include "Core/BaseManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	std::string GetStringFromFmodError(const std::string & method, FMOD_RESULT result);

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	SoundManager * Sound::_soundManager = 0;

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	bool Sound::isPlaying() const {
		if(_channel) {
			bool value;
			FMOD_RESULT result = _channel->isPlaying(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::isPlaying", result));
				return false;
			}
			return value;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Sound::isPaused() const {
		if(_channel) {
			bool value;
			FMOD_RESULT result = _channel->getPaused(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::isPaused", result));
				return false;
			}
			return value;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	float Sound::getVolume() const {
		if(_channel) {
			float value;
			FMOD_RESULT result = _channel->getVolume(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::getVolume", result));
				return 0.0f;
			}
			return value;
		}
		return 0.0f;
	}

	//--------------------------------------------------------------------------------------------------------

	void Sound::setVolume(float value) {
		FMOD_RESULT result = _channel->setVolume(value);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::setVolume", result));
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool Sound::getMute() const {
		if(_channel) {
			bool value;
			FMOD_RESULT result = _channel->getMute(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::getMute", result));
				return false;
			}
			return value;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void Sound::setMute(bool value) {
		FMOD_RESULT result = _channel->setMute(value);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::setMute", result));
		}
	}

	//--------------------------------------------------------------------------------------------------------

	float Sound::getPan() const {
		if(_channel) {
			float value;
			FMOD_RESULT result = _channel->getPan(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::getPan", result));
				return 0.0f;
			}
			return value;
		}
		return 0.0f;
	}

	//--------------------------------------------------------------------------------------------------------

	void Sound::setPan(float value) {
		FMOD_RESULT result = _channel->setPan(value);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::setPan", result));
		}
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool Sound::play() {
		assert(_soundManager && "Sound::play -> Sound manager not initialized...");
		FMOD_RESULT result;
		// Comprobamos primero si el sonido está pausado para continuar su reproducción.
		if(isPaused()) {
			result = _channel->setPaused(false);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::play", result));
				return false;
			}
			return true;
		}
		// Intentamos empezar la reproducción del sonido, pidiendo un canal para ello.
		result = _soundManager->_system->playSound(FMOD_CHANNEL_FREE, _buffer, false, &_channel);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::play", result));
			return false;
		}
		// Intentamos asignar el canal obtenido a un grupo determinado.
		if(_soundManager->containsGroup(_groupName)) {
			result = _channel->setChannelGroup(_soundManager->_groupsTable[_groupName].channel);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::play", result));
				return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Sound::pause() {
		assert(_soundManager && "Sound::pause -> Sound manager not initialized...");
		// Intentamos pausar la reproducción del sonido.
		FMOD_RESULT result = _channel->setPaused(true);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::pause", result));
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Sound::stop() {
		assert(_soundManager && "Sound::stop -> Sound manager not initialized...");
		// Intentamos parar la reproducción del sonido.
		FMOD_RESULT result = _channel->stop();
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("Sound::stop", result));
			return false;
		}
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Sound::Sound(const std::string & fileName, const std::string & groupName, FMOD::Sound * buffer)
	: _fileName(fileName), _groupName(groupName), _buffer(buffer), _channel(0) {}

	//--------------------------------------------------------------------------------------------------------

	Sound::Sound(const Sound & obj) {
		_fileName = obj._fileName;
		_groupName = obj._groupName;
		_buffer = obj._buffer;
		_channel = obj._channel;
	}

	//--------------------------------------------------------------------------------------------------------

	Sound::~Sound() {
		if(isPlaying()) {
			stop();
		}
	}
}
