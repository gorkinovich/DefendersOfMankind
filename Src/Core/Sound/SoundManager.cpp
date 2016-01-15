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

#include <sstream>
#include <exception>
#include <OgreLog.h>
#include <fmod.hpp>
#include <fmod_errors.h>

#include "Core/Sound/SoundManager.h"
#include "Core/Sound/Sound.h"
#include "Core/BaseManager.h"
#include "Core/Resources/ResourcesManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	std::string GetStringFromFmodError(const std::string & method, FMOD_RESULT result) {
		std::stringstream stream;
		stream << method << " -> FMOD error " << result << ": " << FMOD_ErrorString(result);
		return stream.str();
	}

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	SoundManager * SoundManager::_instance = new SoundManager();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	float SoundManager::getGroupVolume(const std::string & name) const {
		if(containsGroup(name)) {
			const Group & victim = _groupsTable.find(name)->second;
			float value;
			FMOD_RESULT result = victim.channel->getVolume(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::getGroupVolume", result));
				return 0.0f;
			}
			return value;
		}
		return 0.0f;
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundManager::setGroupVolume(const std::string & name, float value) {
		if(containsGroup(name)) {
			Group & victim = _groupsTable[name];
			FMOD_RESULT result = victim.channel->setVolume(value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::setGroupVolume", result));
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::getGroupMute(const std::string & name) const {
		if(containsGroup(name)) {
			const Group & victim = _groupsTable.find(name)->second;
			bool value;
			FMOD_RESULT result = victim.channel->getMute(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::getGroupMute", result));
				return false;
			}
			return value;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundManager::setGroupMute(const std::string & name, bool value) {
		if(containsGroup(name)) {
			Group & victim = _groupsTable[name];
			FMOD_RESULT result = victim.channel->setMute(value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::setGroupMute", result));
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	float SoundManager::getGroupMuteFadeSpeed(const std::string & name) const {
		if(containsGroup(name)) {
			const Group & victim = _groupsTable.find(name)->second;
			float value;
			FMOD_RESULT result = victim.sound->getMuteFadeSpeed(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::getGroupMuteFadeSpeed", result));
				return 0.0f;
			}
			return value;
		}
		return 0.0f;
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundManager::setGroupMuteFadeSpeed(const std::string & name, float value) {
		if(containsGroup(name)) {
			Group & victim = _groupsTable[name];
			FMOD_RESULT result = victim.sound->setMuteFadeSpeed(value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::setGroupMuteFadeSpeed", result));
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::getGroupPause(const std::string & name) const {
		if(containsGroup(name)) {
			const Group & victim = _groupsTable.find(name)->second;
			bool value;
			FMOD_RESULT result = victim.channel->getPaused(&value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::getGroupPause", result));
				return false;
			}
			return value;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundManager::setGroupPause(const std::string & name, bool value) {
		if(containsGroup(name)) {
			Group & victim = _groupsTable[name];
			FMOD_RESULT result = victim.channel->setPaused(value);
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::setGroupPause", result));
			}
		}
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool SoundManager::initialize() {
		FMOD_RESULT result;

		// Creamos el gestor FMOD del motor de sonido.
		result = FMOD::System_Create(&_system);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::initialize", result));
			return false;
		}

		// Inicializamos el gestor FMOD del motor de sonido.
		result = _system->init(MAX_SOUND_CHANNELS, FMOD_INIT_NORMAL, 0);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::initialize", result));
			return false;
		}

		// Configuramos el resto del gestor.
		result = _system->getMasterChannelGroup(&(_masterGroup.channel));
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::initialize", result));
			return false;
		}
		result = _system->getMasterSoundGroup(&(_masterGroup.sound));
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::initialize", result));
			return false;
		}
		_defaultGroup = "default";
		_groupsTable[_defaultGroup] = _masterGroup;

		// Actualizamos la referencia común a todos los sonidos, al gestor actual.
		Sound::_soundManager = this;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundManager::release() {
		// Quitamos la referencia común a todos los sonidos, al gestor actual.
		Sound::_soundManager = 0;

		// Eliminamos todos los buffers de sonido del gestor.
		clearAllSounds();

		// Eliminamos todos los grupos del gestor.
		clearAllGroups();

		// Liberamos el gestor FMOD del motor de sonido.
		FMOD_RESULT result;
		result = _system->release();
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::release", result));
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundManager::update() {
		// Actualizamos el gestor FMOD del motor de sonido.
		FMOD_RESULT result;
		result = _system->update();
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::containsGroup(const std::string & name) const {
		return _groupsTable.count(name) > 0;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::addGroup(const std::string & name) {
		if(!containsGroup(name)) {
			FMOD_RESULT result;
			Group victim;

			// Creamos el grupo de canales.
			result = _system->createChannelGroup(name.c_str(), &(victim.channel));
			if(result != FMOD_OK) {
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::addGroup", result));
				return false;
			}

			// Creamos el grupo de sonidos.
			result = _system->createSoundGroup(name.c_str(), &(victim.sound));
			if(result != FMOD_OK) {
				victim.channel->release();
				BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::addGroup", result));
				return false;
			}

			// Añadimos el grupo a la tabla.
			_groupsTable[name] = victim;

			// Asignamos el grupo actual como el grupo por defecto si no ha sido asignado previamente.
			if(_groupsTable.size() == 1 && _defaultGroup.size() == 0) {
				_defaultGroup = name;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::removeGroup(const std::string & name) {
		GroupsTable::iterator victim = _groupsTable.find(name);
		if(victim != _groupsTable.end()) {
			FMOD_RESULT result;

			// Eliminamos el grupo de canales.
			if(_masterGroup.channel != victim->second.channel) {
				result = victim->second.channel->release();
				if(result != FMOD_OK) {
					BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::removeGroup", result));
					return false;
				}
			}

			// Eliminamos el grupo de sonidos.
			if(_masterGroup.sound != victim->second.sound) {
				result = victim->second.sound->release();
				if(result != FMOD_OK) {
					BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::removeGroup", result));
					return false;
				}
			}

			// Eliminamos el grupo de la tabla.
			_groupsTable.erase(victim);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::clearAllGroups() {
		// Recorremos entera la tabla de grupos.
		GroupsTable::iterator i = _groupsTable.begin();
		GroupsTable::iterator end = _groupsTable.end();
		while(i != end) {
			// Cogemos el identificador del grupo y lo mandamos borrar.
			std::string victim = i->first;
			++i;
			if(!removeGroup(victim)) return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::stopGroup(const std::string & name) {
		// Buscamos el grupo que necesitamos para la operación.
		GroupsTable::iterator victim = _groupsTable.find(name);
		if(victim == _groupsTable.end()) return false;

		// Intentamos parar la reproducción del grupo.
		FMOD_RESULT result = victim->second.channel->stop();
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::stopGroup", result));
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::pauseGroup(const std::string & name) {
		// Buscamos el grupo que necesitamos para la operación.
		GroupsTable::iterator victim = _groupsTable.find(name);
		if(victim == _groupsTable.end()) return false;

		// Intentamos pausar la reproducción del grupo.
		FMOD_RESULT result = victim->second.channel->setPaused(true);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::pauseGroup", result));
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::unpauseGroup(const std::string & name) {
		// Buscamos el grupo que necesitamos para la operación.
		GroupsTable::iterator victim = _groupsTable.find(name);
		if(victim == _groupsTable.end()) return false;

		// Intentamos reanudar la reproducción del grupo.
		FMOD_RESULT result = victim->second.channel->setPaused(false);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::unpauseGroup", result));
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::stopAllGroups() {
		GroupsTable::iterator i = _groupsTable.begin();
		GroupsTable::iterator end = _groupsTable.end();
		bool result = true;
		for(; i != end; ++i) {
			result = stopGroup(i->first) && result;
		}
		return result;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::pauseAllGroups() {
		GroupsTable::iterator i = _groupsTable.begin();
		GroupsTable::iterator end = _groupsTable.end();
		bool result = true;
		for(; i != end; ++i) {
			result = pauseGroup(i->first) && result;
		}
		return result;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::unpauseAllGroups() {
		GroupsTable::iterator i = _groupsTable.begin();
		GroupsTable::iterator end = _groupsTable.end();
		bool result = true;
		for(; i != end; ++i) {
			result = unpauseGroup(i->first) && result;
		}
		return result;
	}

	//--------------------------------------------------------------------------------------------------------

	Sound * SoundManager::loadSound(const std::string & fileName, const std::string & groupName, bool loop) {
		// Comprobamos si hay algún sonido precargado. Si no lo está, intentamos precargarlo.
		if(_soundsTable.count(fileName) > 0 || preloadSound(fileName, groupName, loop)) {
			// Y si está o se logra precargar, mandamos crear el sonido que lo encapsule.
			return createSound(fileName);
		} else {
			return 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	Sound * SoundManager::loadMusic(const std::string & fileName, const std::string & groupName, bool loop) {
		// Comprobamos si hay algún sonido precargado. Si no lo está, intentamos precargarlo.
		if(_soundsTable.count(fileName) > 0 || preloadMusic(fileName, groupName, loop)) {
			// Y si está o se logra precargar, mandamos crear el sonido que lo encapsule.
			return createSound(fileName);
		} else {
			return 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::preloadSound(const std::string & fileName, const std::string & groupName, bool loop) {
		// Comprobamos que no exista ya el buffer en la tabla de sonidos.
		if(_soundsTable.count(fileName) > 0) return true;

		// Comprobamos si existe el grupo al que queremos asignar el sonido.
		if(!containsGroup(groupName)) {
			BaseManager::GetInstance()->getOgreLog()->logMessage("SoundManager::preloadSound -> Invalid group...");
			return false;
		}

		// Obtenemos la ruta completa para poder cargar el sonido.
		std::string fullPath;
		if(!ResourcesManager::GetInstance()->getFullPath(fileName, fullPath)) {
			BaseManager::GetInstance()->getOgreLog()->logMessage("SoundManager::preloadSound -> Invalid path...");
			return false;
		}

		// Definimos las variables con las que crear el sonido.
		FMOD_RESULT result;
		FMOD::Sound * buffer = 0;
		FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE : FMOD_2D | FMOD_HARDWARE;

		// Intentamos crear y cargar un sonido.
		result = _system->createSound(fullPath.c_str(), mode, 0, &buffer);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::preloadSound", result));
			return false;
		}

		// Creamos y devolvemos el objeto con el sonido cargado.
		return addSoundBuffer(fileName, groupName, buffer);
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::preloadMusic(const std::string & fileName, const std::string & groupName, bool loop) {
		// Comprobamos que no exista ya el buffer en la tabla de sonidos.
		if(_soundsTable.count(fileName) > 0) return true;

		// Comprobamos si existe el grupo al que queremos asignar el sonido.
		if(!containsGroup(groupName)) {
			BaseManager::GetInstance()->getOgreLog()->logMessage("SoundManager::preloadMusic -> Invalid group...");
			return false;
		}

		// Obtenemos la ruta completa para poder cargar el sonido.
		std::string fullPath;
		if(!ResourcesManager::GetInstance()->getFullPath(fileName, fullPath)) {
			BaseManager::GetInstance()->getOgreLog()->logMessage("SoundManager::preloadMusic -> Invalid path...");
			return false;
		}

		// Definimos las variables con las que crear el sonido.
		FMOD_RESULT result;
		FMOD::Sound * buffer = 0;
		FMOD_MODE mode = loop ? FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE : FMOD_2D | FMOD_HARDWARE;

		// Intentamos crear y cargar un sonido.
		result = _system->createStream(fullPath.c_str(), mode, 0, &buffer);
		if(result != FMOD_OK) {
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::preloadMusic", result));
			return false;
		}

		// Creamos y devolvemos el objeto con el sonido cargado.
		return addSoundBuffer(fileName, groupName, buffer);
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::unloadSound(const std::string & fileName) {
		SoundsTable::iterator victim = _soundsTable.find(fileName);
		if(victim != _soundsTable.end()) {
			FMOD_RESULT result;

			// Eliminamos el sonido de la memoria.
			if(victim->second.buffer) {
				result = victim->second.buffer->release();
				if(result != FMOD_OK) {
					BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::unloadSound", result));
					return false;
				}
			}

			// Eliminamos el grupo de la tabla.
			_soundsTable.erase(victim);
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::clearAllSounds() {
		// Recorremos entera la tabla de buffers.
		SoundsTable::iterator i = _soundsTable.begin();
		SoundsTable::iterator end = _soundsTable.end();
		while(i != end) {
			// Cogemos el identificador del buffer y lo mandamos borrar.
			std::string victim = i->first;
			++i;
			if(!unloadSound(victim)) return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	Sound * SoundManager::createSound(const std::string & fileName) {
		// Buscamos el buffer de sonido en la tabla.
		SoundsTable::iterator victim = _soundsTable.find(fileName);
		if(victim != _soundsTable.end()) {
			// Creamos y devolvemos el objeto con el sonido cargado.
			return new Sound(fileName, victim->second.groupName, victim->second.buffer);
		} else {
			return 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundManager::addSoundBuffer(const std::string & fileName, const std::string & groupName, FMOD::Sound * buffer) {
		// Asignamos el sonido creado al grupo indicado.
		Group & group = _groupsTable[groupName];
		FMOD_RESULT result = buffer->setSoundGroup(group.sound);
		if(result != FMOD_OK) {
			buffer->release();
			BaseManager::GetInstance()->getOgreLog()->logMessage(GetStringFromFmodError("SoundManager::addSoundBuffer", result));
			return false;
		}

		// Creamos el nodo donde almacenar el buffer de sonido.
		SoundBuffer victim;
		victim.groupName = groupName;
		victim.buffer = buffer;

		// Añadimos el sonido a la tabla.
		_soundsTable[fileName] = victim;

		return true;
	}
}
