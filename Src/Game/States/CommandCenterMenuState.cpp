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

#include "Game/States/CommandCenterMenuState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string CommandCenterMenuState::StateName = std::string(COMMAND_CENTER_MENU_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool CommandCenterMenuState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("CommandCenterMenu.layout", "CommandCenterMenu")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("CommandCenterMenu/SpaceMapButton", &CommandCenterMenuState::spaceMapButton, this);
		SubscribeToClickedEvent("CommandCenterMenu/ResearchAreaButton", &CommandCenterMenuState::researchAreaButton, this);
		SubscribeToClickedEvent("CommandCenterMenu/WorkshopButton", &CommandCenterMenuState::workshopButton, this);
		SubscribeToClickedEvent("CommandCenterMenu/OptionsButton", &CommandCenterMenuState::optionsButton, this);
		SubscribeToClickedEvent("CommandCenterMenu/SaveGameButton", &CommandCenterMenuState::saveGameButton, this);
		SubscribeToClickedEvent("CommandCenterMenu/ExitGameButton", &CommandCenterMenuState::exitGameButton, this);

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void CommandCenterMenuState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void CommandCenterMenuState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void CommandCenterMenuState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void CommandCenterMenuState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->pushState(CONFIRM_EXIT_GAME_STATE_NAME);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommandCenterMenuState::spaceMapButton(const CEGUI::EventArgs & e) {
		_application->pushState(SPACE_MAP_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommandCenterMenuState::researchAreaButton(const CEGUI::EventArgs & e) {
		_application->pushState(RESEARCH_AREA_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommandCenterMenuState::workshopButton(const CEGUI::EventArgs & e) {
		_application->pushState(WORKSHOP_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommandCenterMenuState::optionsButton(const CEGUI::EventArgs & e) {
		_application->pushState(OPTIONS_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommandCenterMenuState::saveGameButton(const CEGUI::EventArgs & e) {
		_application->pushState(SAVE_GAME_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool CommandCenterMenuState::exitGameButton(const CEGUI::EventArgs & e) {
		_application->pushState(CONFIRM_EXIT_GAME_STATE_NAME);
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	CommandCenterMenuState::CommandCenterMenuState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	CommandCenterMenuState::~CommandCenterMenuState() {}
}
