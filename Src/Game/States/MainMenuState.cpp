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

#include <iostream>

#include "Game/States/MainMenuState.h"

#include "Core/GenericApplication.h"
#include "Core/LocalizationManager.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Core/Scripting/LuabindUtils.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Logic/GameManager.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string MainMenuState::StateName = std::string(MAIN_MENU_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MainMenuState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("MainMenu.layout", "MainMenu")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("MainMenu/NewProfileButton", &MainMenuState::newProfileButton, this);
		SubscribeToClickedEvent("MainMenu/LoadProfileButton", &MainMenuState::loadProfileButton, this);
		SubscribeToClickedEvent("MainMenu/CreditsButton", &MainMenuState::creditsButton, this);
		SubscribeToClickedEvent("MainMenu/OptionsButton", &MainMenuState::optionsButton, this);
		SubscribeToClickedEvent("MainMenu/HelpButton", &MainMenuState::helpButton, this);
		SubscribeToClickedEvent("MainMenu/ExitButton", &MainMenuState::exitButton, this);
		//TODO: Botón de test...
		SubscribeToClickedEvent("MainMenu/TestMissionButton", &MainMenuState::testMissionButton, this);
		//...

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void MainMenuState::release() {
		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void MainMenuState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void MainMenuState::deactivate() {
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void MainMenuState::update(unsigned int lastInterval) {
		//TODO: Completar el método...
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->pushState(CONFIRM_EXIT_STATE_NAME);

		} /*else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_F9)) {
			Core::ScriptingManager::GetInstance()->reloadAndRun();
			std::cout << std::endl;

		} else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_F10)) {
			Core::ScriptingManager::GetInstance()->loadAndRunFile("test1.lua");
			Core::ScriptingManager::GetInstance()->loadAndRunFile("test2.lua");
			if(Core::LocalizationManager::GetInstance()->load("SPANISH_TEXT")) {
				std::cout << Core::LocalizationManager::GetInstance()->get("TXT001") << std::endl;
				std::cout << Core::LocalizationManager::GetInstance()->get("TXT002") << std::endl;
				std::cout << Core::LocalizationManager::GetInstance()->get("TXT003") << std::endl << std::endl;
			} else {
				std::cout << "No se pudo cargar la tabla de texto, puta mierda..." << std::endl;
			}
			std::cout << std::endl;

		} else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_F11)) {
			Core::ScriptObject obj1 = Core::ScriptingManager::GetInstance()->getGlobal("testBool");
			if(obj1.isBoolean()) {
				obj1.setAsBoolean(!obj1.getAsBoolean());
			}
			Core::ScriptObject obj2 = Core::ScriptingManager::GetInstance()->getGlobal("testNumber");
			if(obj2.isNumber()) {
				obj2.setAsInteger(obj2.getAsInteger() + 2);
			}
			Core::ScriptObject obj3 = Core::ScriptingManager::GetInstance()->getGlobal("testString");
			if(obj3.isString()) {
				obj3.setAsString(obj3.getAsString() + "-");
			}
			Core::ScriptObject obj4 = Core::ScriptingManager::GetInstance()->getGlobal("testTable");
			if(obj4.isTable()) {
				obj4["flag"].setAsBoolean(!obj4["flag"].getAsBoolean());
				obj4["number"].setAsInteger(obj4["number"].getAsInteger() + 1);
				obj4["string"].setAsString(obj4["string"].getAsString() + "+");
			}
			std::cout << std::endl;

		} else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_F12)) {
			Core::ScriptObject obj1 = Core::ScriptingManager::GetInstance()->getGlobal("testBool");
			if(obj1.isBoolean()) {
				std::cout << "testBool = " << obj1.getAsBoolean() << std::endl;
			}
			Core::ScriptObject obj2 = Core::ScriptingManager::GetInstance()->getGlobal("testNumber");
			if(obj2.isNumber()) {
				std::cout << "testNumber = " << obj2.getAsInteger() << std::endl;
			}
			Core::ScriptObject obj3 = Core::ScriptingManager::GetInstance()->getGlobal("testString");
			if(obj3.isString()) {
				std::cout << "testString = " << obj3.getAsString() << std::endl;
			}
			Core::ScriptObject obj4 = Core::ScriptingManager::GetInstance()->getGlobal("testTable");
			if(obj4.isTable()) {
				std::cout << "testTable.flag   = " << obj4["flag"].getAsBoolean() << std::endl;
				std::cout << "testTable.number = " << obj4["number"].getAsInteger() << std::endl;
				std::cout << "testTable.string = " << obj4["string"].getAsString() << std::endl;
			}
			luabind::iterator lbtit(obj4.getLuaBindObject()), lbtend;
			std::string auxStr; int auxInt; bool auxBool;
			for(; lbtit != lbtend; ++lbtit) {
				luabind::object objKey = lbtit.key();
				luabind::object objVal = *lbtit;
				if(Core::LuaConvertToString(objKey, auxStr)) {
					std::cout << "objKey:         " << auxStr << std::endl;
				}
				if(Core::LuaConvertToString(objVal, auxStr)) {
					std::cout << "objVal(string): " << auxStr << std::endl;
				} else if(Core::LuaConvertToInteger(objVal, auxInt)) {
					std::cout << "objVal(int):    " << auxInt << std::endl;
				} else if(Core::LuaConvertToBool(objVal, auxBool)) {
					std::cout << "objVal(bool):   " << (auxBool ? "true" : "false") << std::endl;
				}
			}
			std::cout << std::endl;
		} */
		//...
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::newProfileButton(const CEGUI::EventArgs & e) {
		_application->pushState(NEW_PLAYER_PROFILE_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::loadProfileButton(const CEGUI::EventArgs & e) {
		_application->pushState(CHOOSE_PLAYER_PROFILE_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::creditsButton(const CEGUI::EventArgs & e) {
		_application->pushState(CREDITS_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::optionsButton(const CEGUI::EventArgs & e) {
		_application->pushState(OPTIONS_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::helpButton(const CEGUI::EventArgs & e) {
		//TODO: Completar el método...
		//...
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::exitButton(const CEGUI::EventArgs & e) {
		_application->pushState(CONFIRM_EXIT_STATE_NAME);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool MainMenuState::testMissionButton(const CEGUI::EventArgs & e) {
		//TODO: Borrar el método cuando el juego esté más completo...
		Logic::GameManager::GetInstance()->startMission("Mission01.lua");
		return true;
		//...
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	MainMenuState::MainMenuState(Core::GenericApplication * application) : GenericMenuState(application) {}

	//--------------------------------------------------------------------------------------------------------

	MainMenuState::~MainMenuState() {}
}
