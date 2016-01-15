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

#include <elements/CEGUIItemEntry.h>
#include <elements/CEGUIItemListbox.h>

#include "Game/States/ChoosePlayerProfileState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Logic/Controllers/ProfileController.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ChoosePlayerProfileState::StateName = std::string(CHOOSE_PLAYER_PROFILE_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ChoosePlayerProfileState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ChoosePlayerProfile.layout", "ChoosePlayerProfile")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ChoosePlayerProfile/AcceptButton", &ChoosePlayerProfileState::acceptButton, this);
		SubscribeToClickedEvent("ChoosePlayerProfile/CancelButton", &ChoosePlayerProfileState::cancelButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_profilesList = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::ItemListbox>("ChoosePlayerProfile/ProfilesList");
		if(!_profilesList) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ChoosePlayerProfileState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_profilesList = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ChoosePlayerProfileState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		// Recorremos la lista de nombres de los perfiles para añadirlos al menú.
		Core::GUIManager * gui = Core::GUIManager::GetInstance();
		const Core::StringList & names = Logic::GameManager::GetInstance()->getProfile()->getProfilesNames();
		Core::StringList::const_iterator i = names.begin();
		Core::StringList::const_iterator end = names.end();
		CEGUI::ItemEntry * victim = 0;
		std::string listItemName;
		for(; i != end; ++i) {
			// Creamos el objeto interactivo a añadir en la lista de perfiles.
			listItemName = std::string("ChoosePlayerProfile/ProfilesList/") + (*i);
			victim = dynamic_cast<CEGUI::ItemEntry *>(gui->createWindow("MankindDefenders/ListboxItem", listItemName));
			if(victim) {
				// Inicializamos el objeto interactivo a añadir en la lista de perfiles.
				victim->setAlwaysOnTop(true);
				victim->setFont("DejaVuSans-10");
				victim->setText(i->c_str());
				// Y finalmente lo añadimos a la lista de perfiles.
				_profilesList->addItem(victim);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ChoosePlayerProfileState::deactivate() {
		// Borramos el contenido del objeto interactivo para seleccionar el perfil a cargar.
		_profilesList->resetList();
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ChoosePlayerProfileState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ChoosePlayerProfileState::acceptButton(const CEGUI::EventArgs & e) {
		// Comprobamos que se ha seleccionado algún elemento de la lista.
		if(_profilesList->getLastSelectedItem()) {
			// Obtenemos el nombre elegido por el jugador.
			std::string name = _profilesList->getLastSelectedItem()->getText().c_str();
			// Intentamos cargar el perfil en el juego.
			Logic::ProfileController * controller = Logic::GameManager::GetInstance()->getProfile();
			if(controller->loadPlayerProfile(name)) {
				// Si se logra cargar, cambiamos al menú del jugador actual.
				_application->pushState(MAIN_PLAYER_MENU_STATE_NAME);
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ChoosePlayerProfileState::cancelButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ChoosePlayerProfileState::ChoosePlayerProfileState(Core::GenericApplication * application)
	: GenericMenuState(application), _profilesList(0) {}

	//--------------------------------------------------------------------------------------------------------

	ChoosePlayerProfileState::~ChoosePlayerProfileState() {}
}
