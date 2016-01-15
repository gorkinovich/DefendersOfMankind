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

#include <elements/CEGUISlider.h>

#include "Game/States/SoundOptionsState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Logic/Controllers/OptionsController.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string SoundOptionsState::StateName = std::string(SOUND_OPTIONS_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool SoundOptionsState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("SoundOptions.layout", "SoundOptions")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("SoundOptions/AcceptButton", &SoundOptionsState::acceptButton, this);
		SubscribeToClickedEvent("SoundOptions/CancelButton", &SoundOptionsState::cancelButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_musicVolume = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::Slider>("SoundOptions/MusicSlider");
		if(!_musicVolume) return false;

		_soundsVolume = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::Slider>("SoundOptions/SoundsSlider");
		if(!_soundsVolume) return false;

		_voicesVolume = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::Slider>("SoundOptions/VoicesSlider");
		if(!_voicesVolume) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundOptionsState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_musicVolume = 0;
		_soundsVolume = 0;
		_voicesVolume = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundOptionsState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		// Inicializamos los objetos interactivos de la ventana actual.
		Logic::OptionsController * controller = Logic::GameManager::GetInstance()->getOptions();
		_musicVolume->setCurrentValue(controller->getMusicVolume());
		_soundsVolume->setCurrentValue(controller->getSoundsVolume());
		_voicesVolume->setCurrentValue(controller->getVoicesVolume());
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundOptionsState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void SoundOptionsState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundOptionsState::acceptButton(const CEGUI::EventArgs & e) {
		// Cambiamos las opciones del sonido.
		Logic::GameManager::GetInstance()->getOptions()->changeSoundOptions(
			_musicVolume->getCurrentValue(),
			_soundsVolume->getCurrentValue(),
			_voicesVolume->getCurrentValue()
		);
		// Y volvemos al estado anterior.
		_application->popState();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SoundOptionsState::cancelButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	SoundOptionsState::SoundOptionsState(Core::GenericApplication * application)
	: GenericMenuState(application), _musicVolume(0), _soundsVolume(0), _voicesVolume(0) {}

	//--------------------------------------------------------------------------------------------------------

	SoundOptionsState::~SoundOptionsState() {}
}
