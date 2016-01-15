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

#include <CEGUIWindow.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreRenderWindow.h>

#include "Core/GenericApplication.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/GUI/GUIManager.h"
#include "Core/IdType.h"
#include "Core/Input/Keyboard.h"
#include "Core/Graphics/TerrainManager.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"

#include "Game/StatesNames.h"
#include "Application/GameState.h"

#include "Physics/Server.h"
#include "Logic/Entity/Components/Death.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Components/PhysicCharacter.h"
#include "Logic/GameManager.h"
#include "Logic/MissionManager.h"
#include "Logic/HUDController.h"

//************************************************************************************************************
// Application
//************************************************************************************************************

namespace Application {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************
	
	bool GameState::initialize() {
		//TODO: Completar el método...

		_terrain = 0;
		_renderWin = 0;
		_viewDebugInfo = false;
		_time = 0;
		
		// Obtenemos la ventana de renderizado para acceder a los FPS
		_renderWin = Core::GraphicsManager::GetInstance()->getRenderWindow();
		_terrain = Core::TerrainManager::GetInstance()->getTerrainGroup();

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GameState::release() {
		//TODO: Completar el método...
		
		//Descargamos el mapa entero y todos los elementos cargados en él.
		Logic::MissionManager::GetInstance()->UnLoadMissionSounds();
		Logic::MissionManager::GetInstance()->unloadLevel();
		Core::EntitiesManager::GetInstance()->cleanEntitiesInfo();
		Core::EntitiesManager::GetInstance()->getBlueprints().clear();

		// Liberamos la escena física.
		Physics::CServer::getSingletonPtr()->destroyScene();
	}

	//--------------------------------------------------------------------------------------------------------

	void GameState::activate() {
		//TODO: Completar el método...
		
		Logic::MissionManager::GetInstance()->activateMap();
		_map = Logic::MissionManager::GetInstance()->getWorld();

		// Activamos la ventana del HUD
		Logic::MissionManager::GetInstance()->getHUDController()->activate();

		// Activamos la ventana que nos muestra el tiempo transcurrido.
		//Core::GUIManager::GetInstance()->setRootWindow(_timeWindow);
		//_timeWindow->setVisible(true);
		//_timeWindow->activate();
	}

	//--------------------------------------------------------------------------------------------------------

	void GameState::deactivate() {
		//TODO: Completar el método...
		
		// Desactivamos la ventana de tiempo.
		//_timeWindow->deactivate();
		//_timeWindow->setVisible(false);

		// Desactivamos la ventana del HUD
		Logic::MissionManager::GetInstance()->getHUDController()->deactivate();

		// Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador.
		Logic::MissionManager::GetInstance()->deactivateMap();
	}

	//--------------------------------------------------------------------------------------------------------

	void GameState::update(unsigned int lastInterval) {
		//TODO: Completar el método...

		//Vector3 nextPos(_terrain->getOrigin());
		if (!Logic::MissionManager::GetInstance()->getBifurcation()){
			Vector3 nextPos(Logic::MissionManager::GetInstance()->getGameCamera()->getCenter());
			float speed = Logic::MissionManager::GetInstance()->getSpeed();
			nextPos.z -= speed * lastInterval;

			Logic::MissionManager::GetInstance()->setCenter(nextPos);//Logic::MissionManager::GetInstance()->getPlayer()->getComponentAs<Logic::Position>("Position")->getPosition());
			Logic::MissionManager::GetInstance()->getPlayer()->getComponentAs<Logic::PhysicCharacter>("PhysicCharacter")->setMovement(Vector3(0,0,-speed * lastInterval));
		}else{
			Vector3 step(Logic::MissionManager::GetInstance()->bifurcationStep(lastInterval));
			Logic::MissionManager::GetInstance()->setCenter(Logic::MissionManager::GetInstance()->getGameCamera()->getCenter() + step);
			Logic::MissionManager::GetInstance()->getPlayer()->getComponentAs<Logic::PhysicCharacter>("PhysicCharacter")->setMovement(step);
		}

		// Entrada del teclado
		if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_ESCAPE)) {
			// Establecemos el nuevo estado
			_application->pushState(MISSION_MENU_STATE_NAME);

		} /* else if(Core::Keyboard::IsKeyReleased(Core::Key::KEY_F12)) {
			_viewDebugInfo = !_viewDebugInfo;
			Logic::MissionManager::GetInstance()->getHUDController()->showInfoDebug(_viewDebugInfo);
		} */

		Logic::MissionManager::GetInstance()->prepareUpdate(lastInterval);

		// Simulación física
		Physics::CServer::getSingletonPtr()->update(lastInterval*0.001f);

		// Actualizamos la lógica de juego.
		Logic::MissionManager::GetInstance()->update(lastInterval);

		_time += lastInterval;

		//std::stringstream text;
		//text << "Time: " << _time/1000;
		//_timeWindow->setText(text.str());

		// Otenemos los frames por segundo
		if(_viewDebugInfo) {
			Ogre::RenderTarget::FrameStats info = _renderWin->getStatistics();
			Logic::MissionManager::GetInstance()->getHUDController()->updateInfoDebug(info.lastFPS, (unsigned int) info.triangleCount);
		}

		// Mostramos la puntuación actual
		Logic::MissionManager::GetInstance()->getHUDController()->setScore((unsigned int) Logic::MissionManager::GetInstance()->getActualBonus());	//_time/1000);

		//Comprobamos si el jugador ha muerto. En ese caso, GAME OVER
		if (Logic::MissionManager::GetInstance()->getPlayer()
		&&  Logic::MissionManager::GetInstance()->getPlayer()->getComponentAs<Logic::Death>("Death")->isDead()) {
			_application->changeState(MISSION_FAILED_STATE_NAME);
		}

		/*
		Core::Entity * player = Logic::MissionManager::GetInstance()->getPlayer();
		if(player) {
			Logic::Death * compDeath = player->getComponentAs<Logic::Death>("Death");
			if(compDeath && compDeath->isDead()) {
			}
		}
		//*/

		//Comprobamos si se ha llegado al final del nivel.
		if(Logic::MissionManager::GetInstance()->getEndOfLevel()) {
			_application->changeState(SHOW_STATISTICS_STATE_NAME);
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GameState::GameState(Core::GenericApplication * application) : ApplicationState(application),
	_terrain(0), _renderWin(0), _viewDebugInfo(false), _time(0) {
	}

	//--------------------------------------------------------------------------------------------------------

	GameState::~GameState() {
	}
}
