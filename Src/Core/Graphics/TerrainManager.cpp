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

#include <assert.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreTerrainMaterialGeneratorA.h>
#include <OgreResourceGroupManager.h>

#include "Core/SafeDelete.h"
#include "Core/Graphics/TerrainManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	TerrainManager * TerrainManager::_instance = new TerrainManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool TerrainManager::initialize() {
		assert(!_terrainGlobalOptions && "TerrainManager::initialize -> A terrain global options exists...");
		_isInitialized = true;
		_terrainGlobalOptions = OGRE_NEW Ogre::TerrainGlobalOptions();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool TerrainManager::initialize(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize) {
		return initialize() && initializeTerrainGroup(sceneManager, terrainSize, worldSize);
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::release() {
		_isInitialized = false;
		SafeDelete(_terrainGroup);
		SafeDelete(_terrainGlobalOptions);
	}

	//--------------------------------------------------------------------------------------------------------

	bool TerrainManager::reset(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize) {
		release();
		return initialize(sceneManager, terrainSize, worldSize);
	}

	//--------------------------------------------------------------------------------------------------------

	bool TerrainManager::initializeTerrainGroup(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize) {
		assert(!_terrainGroup && "TerrainManager::initializeTerrainGroup -> A terrain group exists...");
		if(sceneManager) {
			_terrainGroup = OGRE_NEW Ogre::TerrainGroup(sceneManager, Ogre::Terrain::ALIGN_X_Z, terrainSize, worldSize);
			return true;
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::releaseTerrainGroup() {
		SafeDelete(_terrainGroup);
	}

	//--------------------------------------------------------------------------------------------------------

	bool TerrainManager::resetTerrainGroup(Ogre::SceneManager * sceneManager, int terrainSize, float worldSize) {
		releaseTerrainGroup();
		return initializeTerrainGroup(sceneManager, terrainSize, worldSize);
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::update() {
		assert(_terrainGroup && "TerrainManager::update -> The terrain group have not been created...");
		_terrainGroup->update();
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::configureTerrainGroup(const std::string & groupName, const Vector3 & origin) {
		assert(_terrainGroup && "TerrainManager::configureTerrainGroup -> The terrain group have not been created...");
		_terrainGroup->setResourceGroup(groupName);
		_terrainGroup->setOrigin(origin);
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::defineTerrain(long x, long y, const std::string & fileName) {
		assert(_terrainGroup && "TerrainManager::defineTerrain -> The terrain group have not been created...");
		if(Ogre::ResourceGroupManager::getSingleton().resourceExists(_terrainGroup->getResourceGroup(), fileName)) {
			_terrainGroup->defineTerrain(x, y, fileName);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::loadAllTerrains(bool synchronous) {
		assert(_terrainGroup && "TerrainManager::loadAllTerrains -> The terrain group have not been created...");
		_terrainGroup->loadAllTerrains(synchronous);
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::freeTemporaryResources() {
		assert(_terrainGroup && "TerrainManager::freeTemporaryResources -> The terrain group have not been created...");
		_terrainGroup->freeTemporaryResources();
	}

	//--------------------------------------------------------------------------------------------------------

	void TerrainManager::removeAllTerrains() {
		if(_isInitialized && _terrainGroup) {
			_terrainGroup->removeAllTerrains();
		}
	}
}
