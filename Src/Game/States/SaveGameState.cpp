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

#include <elements/CEGUIEditbox.h>
#include <elements/CEGUIItemEntry.h>
#include <elements/CEGUIItemListbox.h>

#include "Game/States/SaveGameState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/ItemListboxEvents.h"
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

	const std::string SaveGameState::StateName = std::string(SAVE_GAME_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool SaveGameState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("SaveGame.layout", "SaveGame")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToItemListboxSelectionChangedEvent("SaveGame/SavefilesList", &SaveGameState::savefileSelected, this);
		SubscribeToClickedEvent("SaveGame/SaveButton", &SaveGameState::saveButton, this);
		SubscribeToClickedEvent("SaveGame/CancelButton", &SaveGameState::cancelButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_savefile = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::Editbox>("SaveGame/Savefile");
		if(!_savefile) return false;

		_savefilesList = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::ItemListbox>("SaveGame/SavefilesList");
		if(!_savefilesList) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void SaveGameState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_savefile = 0;
		_savefilesList = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void SaveGameState::activate() {
		// Activamos la ventana del estado.
		activateWindow();

		// Recorremos la lista de partidas guardadas para añadirlas al menú.
		Core::GUIManager * gui = Core::GUIManager::GetInstance();
		const Core::StringList & names = Logic::GameManager::GetInstance()->getProfile()->getSavefilesList();
		Core::StringList::const_iterator i = names.begin();
		Core::StringList::const_iterator end = names.end();
		CEGUI::ItemEntry * victim = 0;
		std::string listItemName;
		for(; i != end; ++i) {
			// Creamos el objeto interactivo a añadir en la lista de partidas.
			listItemName = std::string("SaveGame/SavefilesList/") + (*i);
			victim = dynamic_cast<CEGUI::ItemEntry *>(gui->createWindow("MankindDefenders/ListboxItem", listItemName));
			if(victim) {
				// Inicializamos el objeto interactivo a añadir en la lista de partidas.
				victim->setAlwaysOnTop(true);
				victim->setFont("DejaVuSans-10");
				victim->setText(i->c_str());
				// Y finalmente lo añadimos a la lista de partidas.
				_savefilesList->addItem(victim);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void SaveGameState::deactivate() {
		// Borramos el contenido del objeto interactivo para seleccionar el perfil a cargar.
		_savefilesList->resetList();
		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void SaveGameState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			_application->popState();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SaveGameState::savefileSelected(const CEGUI::EventArgs & e) {
		// Comprobamos que se ha seleccionado algún elemento de la lista.
		if(_savefilesList->getLastSelectedItem()) {
			// Y lo ponemos en la caja de texto donde se introduce el nombre de la partida.
			_savefile->setText(_savefilesList->getLastSelectedItem()->getText());
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SaveGameState::saveButton(const CEGUI::EventArgs & e) {
		// Obtenemos el nombre de la partida.
		std::string name = _savefile->getText().c_str();
		// Comprobamos que el nombre sea válido.
		if(name.size() > 0) {
			// Intentamos guardar la partida del juego.
			if(Logic::GameManager::GetInstance()->saveCurrentGame(name)) {
				// Si se logra cargar, cambiamos al inicializador de la partida.
				_application->popState();
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SaveGameState::cancelButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	SaveGameState::SaveGameState(Core::GenericApplication * application)
	: GenericMenuState(application), _savefile(0), _savefilesList(0) {}

	//--------------------------------------------------------------------------------------------------------

	SaveGameState::~SaveGameState() {}
}
