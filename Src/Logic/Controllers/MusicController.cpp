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

#include "Logic/Controllers/MusicController.h"

#include "Core/SafeDelete.h"
#include "Core/Sound/Sound.h"
#include "Core/Sound/SoundManager.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string MusicController::MusicGroupName = std::string("music");

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	float MusicController::getSongVolume() const {
		return _soundManager->getGroupVolume(MusicGroupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::setSongVolume(float value) {
		_soundManager->setGroupVolume(MusicGroupName, value);
	}

	//--------------------------------------------------------------------------------------------------------

	bool MusicController::getSongMute() const {
		return _soundManager->getGroupMute(MusicGroupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::setSongMute(bool value) {
		_soundManager->setGroupMute(MusicGroupName, value);
	}

	//--------------------------------------------------------------------------------------------------------

	float MusicController::getFadeSpeed() const {
		return _soundManager->getGroupMuteFadeSpeed(MusicGroupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::setFadeSpeed(float value) {
		_soundManager->setGroupMuteFadeSpeed(MusicGroupName, value);
	}

	//--------------------------------------------------------------------------------------------------------

	bool MusicController::getSongPause() const {
		return _soundManager->getGroupPause(MusicGroupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::setSongPause(bool value) {
		_soundManager->setGroupPause(MusicGroupName, value);
	}

	//--------------------------------------------------------------------------------------------------------

	bool MusicController::isSongPlaying() const {
		return _currentSong ? _currentSong->isPlaying() : false;
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MusicController::initialize() {
		_soundManager->addGroup(MusicGroupName);
		_currentSongPath = "";
		_currentSong = 0;
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::release() {
		unloadSong();
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::loadSong(const std::string & path, bool loop) {
		// Comprobamos que la ruta tenga al menos algo.
		if(path.size() > 0) {
			// Descargamos la canción que estaba previamente cargada.
			unloadSong();
			// Guardamos la ruta y obtenemos el objeto de sonido para trabajar con él.
			_currentSongPath = path;
			_currentSong = _soundManager->loadMusic(_currentSongPath, MusicGroupName, loop);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::unloadSong() {
		// Borramos el objeto de sonido actual.
		SafeDelete(_currentSong);

		// Y si tenemos una ruta válida, descargamos el buffer de sonido asociado.
		if(_currentSongPath.size() > 0) {
			_soundManager->unloadSound(_currentSongPath);
			_currentSongPath = "";
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::playSong() {
		if(_currentSong) {
			_currentSong->play();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void MusicController::stopSong() {
		if(_currentSong) {
			_currentSong->stop();
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	MusicController::MusicController() : _currentSong(0) {
		_soundManager = Core::SoundManager::GetInstance();
	}

	//--------------------------------------------------------------------------------------------------------

	MusicController::~MusicController() {}
}
