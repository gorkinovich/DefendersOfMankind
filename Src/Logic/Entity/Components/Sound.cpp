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

/**
Contiene la implementación del componente que controla los sonidos que genera la entidad.
*/

#include <assert.h>

#include "Logic/Entity/Components/Sound.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/PlaySoundMessage.h"
#include "Logic/Entity/Messages/PauseSoundMessage.h"
#include "Logic/Entity/Messages/StopSoundMessage.h"

#include "Core/Sound/SoundManager.h"
#include "Logic/MissionManager.h"

namespace Logic
{

	//---------------------------------------------------------

	Sound::~Sound()
	{	
		// Si hay algún sonido... lo liberamos
		TSoundsMapIterator it = _soundsMap.begin();
		TSoundsMapIterator end = _soundsMap.end();
		for (it; it!=end; ++it)
		{
			// Innecesario, se hace al llamar al destructor del sonido
			//if(it->second->isPlaying())
			//	it->second->stop();

			delete it->second;
			it->second = 0;
		}

		// Limpiamos la tabla
		_soundsMap.clear();
	}

	//---------------------------------------------------------

	bool Sound::spawn(const Core::EntityInfoTable *entityInfo)
	{
		assert(_owner && "Sound::The component does not have an entity...");
		
		// Precargamos los sonidos que usará la entidad para evitar un retraso in-game
		// ===========================================================================

		// Leemos del mapa cada sonido que podrá reproducir la entidad
		int n = 0;
		if (entityInfo->hasAttribute("NumberOfSounds")) {
			n = entityInfo->getAttributeAsInteger("NumberOfSounds");
		}
			
		for (int i=1; i<=n; ++i)
		{
			std::stringstream ss;
			std::string str, soundName;

			// Construimos el nombre de la propiedad a buscar
			ss.clear(); ss << "SoundName" << i; ss >> str;

			// Precargamos el sonido y lo registramos para descargarlo al finalizar la misión
			// Nota: si ya está precargado devuelve "true" igualmente
			if (entityInfo->hasAttribute(str)) {
				soundName.append(entityInfo->getAttribute(str));
			}

			if(soundName.compare("") != 0 && Core::SoundManager::GetInstance()->preloadSound(soundName, false)) {
				MissionManager::GetInstance()->RegisterUnLoadMissionSound(soundName);
			} else {
				return false; //Si falla un sonido se termina la carga y se devuelve FALSE
			}
		}

		//Si todo ha ido bien, se devuelve true
		return true;
	}
	
	//---------------------------------------------------------

	bool Sound::activate()
	{
		return true;
	}

	//---------------------------------------------------------

	void Sound::deactivate()
	{
		// Si hay algún sonido reproduciendose... lo paramos
		TSoundsMapIterator it = _soundsMap.begin();
		TSoundsMapIterator end = _soundsMap.end();
		for (it; it!=end; ++it)
		{
			if(it->second->isPlaying())
				it->second->stop();
		}
	}

	//---------------------------------------------------------

	bool Sound::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_PLAY_SOUND ||
				message->getType() == MESSAGE_TYPE_PAUSE_SOUND ||
				message->getType() == MESSAGE_TYPE_STOP_SOUND;
	}
	
	//---------------------------------------------------------

	void Sound::processMessage(const Core::SmartMessage & message)
	{
		std::string soundName;

		switch(message->getType())
		{
			// Creamos y reproducimos el sonido en cuestión
			case MESSAGE_TYPE_PLAY_SOUND:
			{
				soundName = message->getDataRefAs<PlaySoundMessage>().getSoundName();
				Core::Sound* soundPointer = Core::SoundManager::GetInstance()->loadSound(soundName, false);
				if(soundPointer)
				{
					// Si ya existe un sonido igual en el mapa, lo liberamos de forma instantánea
					if(_soundsMap[soundName] != 0)
					{
						delete _soundsMap[soundName];
						_soundsMap[soundName] = 0;
					}

					_soundsMap[soundName] = soundPointer;	// Guardamos la información en la tabla
					soundPointer->play();					
				}				
			}
			break;

			// Pausamos el sonido en cuestión
			case MESSAGE_TYPE_PAUSE_SOUND:
			{
				soundName = message->getDataRefAs<PauseSoundMessage>().getSoundName();
				TSoundsMapIterator it = _soundsMap.find(soundName);
				if(it!=_soundsMap.end())	// Si existe el sonido en cuestión... lo pausamos
				{
					it->second->pause();
				}
			}
			break;

			// Paramos la reproducción del sonido en cuestión
			case MESSAGE_TYPE_STOP_SOUND:
			{
				soundName = message->getDataRefAs<PauseSoundMessage>().getSoundName();
				TSoundsMapIterator it = _soundsMap.find(soundName);
				if(it!=_soundsMap.end())	// Si existe el sonido, paramos su reproducción
				{
					it->second->stop();
				}				
			}
			break;
		}
	}

}
