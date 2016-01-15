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

#include "Game/States/ResearchAreaState.h"

#include "Core/GenericApplication.h"
#include "Core/GUI/WindowEvents.h"
#include "Core/Input/Keyboard.h"
#include "Logic/GameManager.h"
#include "Logic/Data/ResearchInfo.h"
#include "Game/StatesNames.h"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string ResearchAreaState::StateName = std::string(RESEARCH_AREA_STATE_NAME);

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	unsigned int ResearchAreaState::getPreviousAreaIndex() {
		unsigned int size = _areasNames.size();
		return size ? ((_currentArea ? _currentArea : size) - 1) : 0;
	}

	//--------------------------------------------------------------------------------------------------------

	unsigned int ResearchAreaState::getNextAreaIndex() {
		unsigned int size = _areasNames.size();
		return size ? ((_currentArea + 1) % size) : 0;
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ResearchAreaState::initialize() {
		// Inicializamos la ventana del estado.
		if(!initializeWindow("ResearchArea.layout", "ResearchArea")) return false;

		// Configuramos los eventos asociados a los botones de la ventana.
		SubscribeToClickedEvent("ResearchArea/LeftButton", &ResearchAreaState::leftButton, this);
		SubscribeToClickedEvent("ResearchArea/RightButton", &ResearchAreaState::rightButton, this);
		SubscribeToClickedEvent("ResearchArea/HelpButton", &ResearchAreaState::helpButton, this);
		SubscribeToClickedEvent("ResearchArea/BackButton", &ResearchAreaState::backButton, this);
		SubscribeToClickedEvent("ResearchArea/Dialog/BuyButton", &ResearchAreaState::dialogBuyButton, this);
		SubscribeToClickedEvent("ResearchArea/Dialog/CancelButton", &ResearchAreaState::dialogCancelButton, this);
		
		SubscribeToClickedEvent("ResearchArea/LeftResearch1", &ResearchAreaState::leftResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/LeftResearch2", &ResearchAreaState::leftResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/LeftResearch3", &ResearchAreaState::leftResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/LeftResearch4", &ResearchAreaState::leftResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/MiddleResearch1", &ResearchAreaState::middleResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/MiddleResearch2", &ResearchAreaState::middleResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/MiddleResearch3", &ResearchAreaState::middleResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/MiddleResearch4", &ResearchAreaState::middleResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/RightResearch1", &ResearchAreaState::rightResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/RightResearch2", &ResearchAreaState::rightResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/RightResearch3", &ResearchAreaState::rightResearchButton, this);
		SubscribeToClickedEvent("ResearchArea/RightResearch4", &ResearchAreaState::rightResearchButton, this);

		// Obtenemos los objetos interactivos de la ventana actual.
		_mainPanel = Core::GUIManager::GetInstance()->getWindow("ResearchArea/MainPanel");
		if(!_mainPanel) return false;

		_dialogPanel = Core::GUIManager::GetInstance()->getWindow("ResearchArea/BuyDialog");
		if(!_dialogPanel) return false;

		_leftButton = Core::GUIManager::GetInstance()->getWindow("ResearchArea/LeftButton");
		if(!_leftButton) return false;

		_areaTitle = Core::GUIManager::GetInstance()->getWindow("ResearchArea/AreaTitle");
		if(!_areaTitle) return false;

		_rightButton = Core::GUIManager::GetInstance()->getWindow("ResearchArea/RightButton");
		if(!_rightButton) return false;

		_money = Core::GUIManager::GetInstance()->getWindow("ResearchArea/Money");
		if(!_money) return false;

		_dialogTitle = Core::GUIManager::GetInstance()->getWindow("ResearchArea/Dialog/Title");
		if(!_dialogTitle) return false;

		_dialogCost = Core::GUIManager::GetInstance()->getWindow("ResearchArea/Dialog/Cost");
		if(!_dialogCost) return false;

		_dialogMoney = Core::GUIManager::GetInstance()->getWindow("ResearchArea/Dialog/Money");
		if(!_dialogMoney) return false;

		std::string auxName, auxIndex;
		for(unsigned int i = 0; i < MAX_RESEARCH_BUTTONS; ++i) {
			auxIndex = ('1' + i);
			auxName = std::string("ResearchArea/LeftResearch") + auxIndex;
			_leftResearch[i] = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>(auxName);
			if(!_leftResearch[i]) return false;

			auxName = std::string("ResearchArea/MiddleResearch") + auxIndex;
			_middleResearch[i] = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>(auxName);
			if(!_middleResearch[i]) return false;

			auxName = std::string("ResearchArea/RightResearch") + auxIndex;
			_rightResearch[i] = Core::GUIManager::GetInstance()->getWindowAs<CEGUI::PushButton>(auxName);
			if(!_rightResearch[i]) return false;
		}

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::release() {
		// Eliminamos las referencias a los objetos interactivos de la ventana actual.
		_mainPanel = 0;
		_dialogPanel = 0;
		_leftButton = 0;
		_areaTitle = 0;
		_rightButton = 0;
		_money = 0;
		_dialogTitle = 0;
		_dialogCost = 0;
		_dialogMoney = 0;
		for(unsigned int i = 0; i < MAX_RESEARCH_BUTTONS; ++i) {
			_leftResearch[i] = 0;
			_middleResearch[i] = 0;
			_rightResearch[i] = 0;
		}

		// Liberamos la ventana del estado.
		releaseWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::activate() {
		// Activamos la ventana del estado.
		activateWindow();
		showMainPanel();

		// Inicializamos los elementos interactivos de la ventana.
		Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
		Logic::ResearchInfo * researchs = gameManager->getResearchInfo();
		Logic::ResearchInfo::AreaInfoTable::iterator i = researchs->getAreasBegin();
		Logic::ResearchInfo::AreaInfoTable::iterator end = researchs->getAreasEnd();
		for(; i != end; ++i) {
			_areasNames.push_back(i->second.name);
		}
		_currentArea = 0;
		updateAreaData();
		_money->setText(gameManager->getMoneyAsString());
		_dialogTitle->setText("");
		_dialogCost->setText("");
		_dialogMoney->setText(gameManager->getMoneyAsString());
		_currentSubarea = 0;
		_currentResearch = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::deactivate() {
		// Finalizamos los elementos interactivos de la ventana.
		_areasNames.clear();

		// Desactivamos la ventana del estado.
		deactivateWindow();
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::update(unsigned int lastInterval) {
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			if(_dialogPanel->isVisible()) {
				showMainPanel();
			} else {
				_application->popState();
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::showMainPanel() {
		_dialogPanel->setVisible(false);
		_mainPanel->setVisible(true);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::showDialogPanel() {
		_mainPanel->setVisible(false);
		_dialogPanel->setVisible(true);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::updateAreaData() {
		Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
		Logic::ResearchInfo * researchs = gameManager->getResearchInfo();
		unsigned int previousArea = getPreviousAreaIndex();
		unsigned int nextArea = getNextAreaIndex();
		std::string currentAreaName = _areasNames[_currentArea];
		_leftButton->setText(_areasNames[previousArea]);
		_areaTitle->setText(_areasNames[_currentArea]);
		_rightButton->setText(_areasNames[nextArea]);

		if(researchs->containsArea(currentAreaName)) {
			Logic::ResearchInfo::AreaInfo & area = researchs->findArea(currentAreaName);
			unsigned int sizeLeft = area.left.size();
			unsigned int sizeMiddle = area.middle.size();
			unsigned int sizeRight = area.right.size();
			for(unsigned int i = 0; i < MAX_RESEARCH_BUTTONS; ++i) {
				if(i < sizeLeft) {
					_leftResearch[i]->setVisible(true);
					_leftResearch[i]->setText(area.left[i].name);
					_leftResearch[i]->setEnabled(!area.left[i].buyed && (i > 0 ? area.left[i - 1].buyed : true));
				} else {
					_leftResearch[i]->setVisible(false);
				}
				if(i < sizeMiddle) {
					_middleResearch[i]->setVisible(true);
					_middleResearch[i]->setText(area.middle[i].name);
					_middleResearch[i]->setEnabled(!area.middle[i].buyed && (i > 0 ? area.middle[i - 1].buyed : true));
				} else {
					_middleResearch[i]->setVisible(false);
				}
				if(i < sizeRight) {
					_rightResearch[i]->setVisible(true);
					_rightResearch[i]->setText(area.right[i].name);
					_rightResearch[i]->setEnabled(!area.right[i].buyed && (i > 0 ? area.right[i - 1].buyed : true));
				} else {
					_rightResearch[i]->setVisible(false);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ResearchAreaState::updateAndShowDialogPanel() {
		if(_currentResearch < MAX_RESEARCH_BUTTONS && _currentSubarea < 3) {
			Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
			Logic::ResearchInfo * researchs = gameManager->getResearchInfo();
			std::string currentAreaName = _areasNames[_currentArea];
			if(researchs->containsArea(currentAreaName)) {
				Logic::ResearchInfo::AreaInfo & area = researchs->findArea(currentAreaName);
				std::string title = "";
				std::string cost = "";
				switch(_currentSubarea) {
					case 0:
						title = area.left[_currentResearch].name;
						cost = Ogre::StringConverter::toString(area.left[_currentResearch].cost);
						break;
					case 1:
						title = area.middle[_currentResearch].name;
						cost = Ogre::StringConverter::toString(area.middle[_currentResearch].cost);
						break;
					case 2:
						title = area.right[_currentResearch].name;
						cost = Ogre::StringConverter::toString(area.right[_currentResearch].cost);
						break;
				}
				_dialogTitle->setText(title);
				_dialogCost->setText(cost);
				_dialogMoney->setText(gameManager->getMoneyAsString());
				showDialogPanel();
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::leftButton(const CEGUI::EventArgs & e) {
		_currentArea = getPreviousAreaIndex();
		updateAreaData();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::rightButton(const CEGUI::EventArgs & e) {
		_currentArea = getNextAreaIndex();
		updateAreaData();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::helpButton(const CEGUI::EventArgs & e) {
		//TODO: Completar el método...
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::backButton(const CEGUI::EventArgs & e) {
		_application->popState();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::dialogBuyButton(const CEGUI::EventArgs & e) {
		if(_currentResearch < MAX_RESEARCH_BUTTONS && _currentSubarea < 3) {
			Logic::GameManager * gameManager = Logic::GameManager::GetInstance();
			std::string area = _areasNames[_currentArea];
			std::string subsection = "";
			switch(_currentSubarea) {
				case 0: subsection = "left"; break;
				case 1: subsection = "middle"; break;
				case 2: subsection = "right"; break;
			}
			if(area.size() > 0 && subsection.size() > 0 &&
			   gameManager->buyResearch(area, subsection, _currentResearch)) {
				showMainPanel();
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::dialogCancelButton(const CEGUI::EventArgs & e) {
		showMainPanel();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::leftResearchButton(const CEGUI::EventArgs & e) {
		if(typeid(CEGUI::WindowEventArgs) == typeid(e)) {
			const CEGUI::WindowEventArgs & wea = dynamic_cast<const CEGUI::WindowEventArgs &>(e);
			_currentSubarea = 0;
			for(_currentResearch = 0; _currentResearch < MAX_RESEARCH_BUTTONS; ++_currentResearch) {
				if(_leftResearch[_currentResearch]->getName() == wea.window->getName()) {
					break;
				}
			}
			updateAndShowDialogPanel();
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::middleResearchButton(const CEGUI::EventArgs & e) {
		if(typeid(CEGUI::WindowEventArgs) == typeid(e)) {
			const CEGUI::WindowEventArgs & wea = dynamic_cast<const CEGUI::WindowEventArgs &>(e);
			_currentSubarea = 1;
			for(_currentResearch = 0; _currentResearch < MAX_RESEARCH_BUTTONS; ++_currentResearch) {
				if(_middleResearch[_currentResearch]->getName() == wea.window->getName()) {
					break;
				}
			}
			updateAndShowDialogPanel();
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResearchAreaState::rightResearchButton(const CEGUI::EventArgs & e) {
		if(typeid(CEGUI::WindowEventArgs) == typeid(e)) {
			const CEGUI::WindowEventArgs & wea = dynamic_cast<const CEGUI::WindowEventArgs &>(e);
			_currentSubarea = 2;
			for(_currentResearch = 0; _currentResearch < MAX_RESEARCH_BUTTONS; ++_currentResearch) {
				if(_rightResearch[_currentResearch]->getName() == wea.window->getName()) {
					break;
				}
			}
			updateAndShowDialogPanel();
		}
		return true;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ResearchAreaState::ResearchAreaState(Core::GenericApplication * application) : GenericMenuState(application),
	_mainPanel(0), _dialogPanel(0), _leftButton(0), _areaTitle(0), _rightButton(0), _money(0), _dialogTitle(0),
	_dialogCost(0), _dialogMoney(0), _currentArea(0), _currentSubarea(0), _currentResearch(0) {
		for(unsigned int i = 0; i < MAX_RESEARCH_BUTTONS; ++i) {
			_leftResearch[i] = 0;
			_middleResearch[i] = 0;
			_rightResearch[i] = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	ResearchAreaState::~ResearchAreaState() {}
}
