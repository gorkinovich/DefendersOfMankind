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

#include <OgreStringConverter.h>
#include <elements/CEGUIListboxTextItem.h>
#include <elements/CEGUIMultiColumnList.h>

#include "Game/States/WorkshopState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/MultiColumnListEvents.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Logic/Data/WorkshopInfo.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string WorkshopState::StateName = std::string(WORKSHOP_STATE_NAME);

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool WorkshopState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("Workshop.layout", "Workshop")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToMultiColumnListSelectionChangedEvent("Workshop/Dialog/Parts", &WorkshopState::partSelected, this);
		SubscribeToClickedEvent("Workshop/PartButton1", &WorkshopState::partButton, this);
		SubscribeToClickedEvent("Workshop/PartButton2", &WorkshopState::partButton, this);
		SubscribeToClickedEvent("Workshop/PartButton3", &WorkshopState::partButton, this);
		SubscribeToClickedEvent("Workshop/PartButton4", &WorkshopState::partButton, this);
		SubscribeToClickedEvent("Workshop/HelpButton", &WorkshopState::helpButton, this);
		SubscribeToClickedEvent("Workshop/BackButton", &WorkshopState::backButton, this);
		SubscribeToClickedEvent("Workshop/Dialog/BuyButton", &WorkshopState::dialogBuyButton, this);
		SubscribeToClickedEvent("Workshop/Dialog/SelectButton", &WorkshopState::dialogSelectButton, this);
		SubscribeToClickedEvent("Workshop/Dialog/BackButton", &WorkshopState::dialogBackButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_mainPanel = Core::GUIManager::GetInstance()->getWindow("Workshop/MainPanel");
		if(!_mainPanel) return false;

		_dialogPanel = Core::GUIManager::GetInstance()->getWindow("Workshop/PartsDialog");
		if(!_dialogPanel) return false;

		_parts = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::MultiColumnList>("Workshop/Dialog/Parts");
		if(!_parts) return false;

		_properties = Core::GUIManager::GetInstance()->getWindow("Workshop/Dialog/Properties");
		if(!_properties) return false;

		_money = Core::GUIManager::GetInstance()->getWindow("Workshop/Dialog/Money");
		if(!_money) return false;

		_part1 = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>("Workshop/PartButton1");
		if(!_part1) return false;

		_part2 = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>("Workshop/PartButton2");
		if(!_part2) return false;

		_part3 = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>("Workshop/PartButton3");
		if(!_part3) return false;

		_part4 = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>("Workshop/PartButton4");
		if(!_part4) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_mainPanel = 0;
		_dialogPanel = 0;
		_parts = 0;
		_properties = 0;
		_money = 0;
		_part1 = 0;
		_part2 = 0;
		_part3 = 0;
		_part4 = 0;

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
		showMainPanel();

		// Inicializamos los elementos interactivos de la ventana.
		Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
		_part1->setText(gameManager->getWorkshopInfo()->findPart(_part1->getName().c_str()).name);
		_part2->setText(gameManager->getWorkshopInfo()->findPart(_part2->getName().c_str()).name);
		_part3->setText(gameManager->getWorkshopInfo()->findPart(_part3->getName().c_str()).name);
		_part4->setText(gameManager->getWorkshopInfo()->findPart(_part4->getName().c_str()).name);
		_money->setText(gameManager->getMoneyAsString());
		_parts->addColumn("Name", 0, CEGUI::UDim(0.5f, 0.0f));
		_parts->addColumn("Status", 1, CEGUI::UDim(0.5f, 0.0f));
		_parts->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
		_parts->setSortDirection(CEGUI::ListHeaderSegment::None);
		_properties->setText("");
		_lastSelectedPart = "";
		_lastSelectedItem = "";
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopState::deactivate() {
		// Finalizamos los elementos interactivos de la ventana.
		_parts->resetList();
		_parts->removeColumnWithID(0);
		_parts->removeColumnWithID(1);

		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			if(_dialogPanel->isVisible()) {
				showMainPanel();
			} else {
				_application->popState();
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopState::showMainPanel() {
		_dialogPanel->setVisible(false);
		_mainPanel->setVisible(true);
	}

	//--------------------------------------------------------------------------------------------------------

	void WorkshopState::showDialogPanel() {
		_mainPanel->setVisible(false);
		_dialogPanel->setVisible(true);
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::partSelected(const CEGUI::EventArgs & e) {
		if(_parts->getFirstSelectedItem()) {
			std::string selectedItemText = _parts->getFirstSelectedItem()->getText().c_str();
			Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
			Logic::WorkshopInfo::PartInfo & info = gameManager->getWorkshopInfo()->findPart(_lastSelectedPart);
			Logic::WorkshopInfo::ComponentInfoVector::iterator i = info.components.begin();
			Logic::WorkshopInfo::ComponentInfoVector::iterator end = info.components.end();
			for(; i != end; ++i) {
				if(selectedItemText == i->name) {
					_properties->setText(i->description);
					_lastSelectedItem = i->name;
					break;
				}
			}
		} else {
			_lastSelectedItem = "";
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::partButton(const CEGUI::EventArgs & e) {
		if(typeid(CEGUI::WindowEventArgs) == typeid(e)) {
			const CEGUI::WindowEventArgs & wea = dynamic_cast<const CEGUI::WindowEventArgs &>(e);
			_lastSelectedPart = wea.window->getName().c_str();
			Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
			if(gameManager->getWorkshopInfo()->containsPart(_lastSelectedPart)) {
				_parts->resetList();
				Logic::WorkshopInfo::PartInfo & info = gameManager->getWorkshopInfo()->findPart(_lastSelectedPart);
				Logic::WorkshopInfo::ComponentInfoVector::iterator i = info.components.begin();
				Logic::WorkshopInfo::ComponentInfoVector::iterator end = info.components.end();
				CEGUI::ListboxTextItem * item = 0;
				for(unsigned int j = 0; i != end; ++i, ++j) {
					_parts->addRow();
					item = new CEGUI::ListboxTextItem(i->name);
					item->setSelectionColours(CEGUI::colour(0.0f, 0.6f, 0.0f));
					item->setSelectionBrushImage("MultiColumnSelector", "Selector");
					_parts->setItem(item, 0, j);
					item = new CEGUI::ListboxTextItem(
						(i->buyed ? (i->selected ? "Selected": "") : Ogre::StringConverter::toString(i->cost))
					);
					item->setSelectionColours(CEGUI::colour(0.0f, 0.6f, 0.0f));
					item->setSelectionBrushImage("MultiColumnSelector", "Selector");
					_parts->setItem(item, 1, j);
				}
				_properties->setText("");
				_money->setText(gameManager->getMoneyAsString());
				showDialogPanel();
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::helpButton(const CEGUI::EventArgs & e) {
		//TODO: Completar el método...
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::backButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::dialogBuyButton(const CEGUI::EventArgs & e) {
		if(Logic::GameManager::GetInstance()->buyPartItem(_lastSelectedPart, _lastSelectedItem)) {
			Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
			Logic::WorkshopInfo::PartInfo & info = gameManager->getWorkshopInfo()->findPart(_lastSelectedPart);
			Logic::WorkshopInfo::ComponentInfoVector::iterator i = info.components.begin();
			Logic::WorkshopInfo::ComponentInfoVector::iterator end = info.components.end();
			for(unsigned int j = 0; i != end; ++i, ++j) {
				if(_lastSelectedItem == i->name) {
					_money->setText(gameManager->getMoneyAsString());
					_parts->getItemAtGridReference(CEGUI::MCLGridRef(j, 1))->setText("");
					_parts->invalidate();
					break;
				}
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::dialogSelectButton(const CEGUI::EventArgs & e) {
		if(Logic::GameManager::GetInstance()->selectPartItem(_lastSelectedPart, _lastSelectedItem)) {
			showMainPanel();
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool WorkshopState::dialogBackButton(const CEGUI::EventArgs & e) {
		showMainPanel();
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	WorkshopState::WorkshopState(Core::GenericApplication * application) : GenericMenuState(application),
	_mainPanel(0), _dialogPanel(0), _parts(0), _properties(0), _money(0), _part1(0), _part2(0), _part3(0), _part4(0) {}

	//--------------------------------------------------------------------------------------------------------

	WorkshopState::~WorkshopState() {}
}
