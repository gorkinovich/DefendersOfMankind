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
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreStaticGeometry.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>

#include "Core/BaseManager.h"
#include "Core/Graphics/Scene.h"
#include "Core/Graphics/Camera.h"
#include "Core/Graphics/AnimatedEntity.h"
#include "Core/Graphics/ImmutableEntity.h"
#include "Core/Graphics/GraphicsManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	Ogre::SceneNode * Scene::getRootSceneNode() {
		return _sceneManager->getRootSceneNode();
	}

	//--------------------------------------------------------------------------------------------------------

	Ogre::ColourValue Scene::getBackgroundColour() const {
		return _backgroundColour;
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::setBackgroundColour(const Ogre::ColourValue & value) {
		_backgroundColour = value;
		if(_viewport) _viewport->setBackgroundColour(_backgroundColour);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool Scene::addEntity(GenericGraphicEntity * entity, GraphicNodeEntity * father) {
		assert(entity && "Scene::addEntity -> The entity parameter can't be NULL...");
		// Añadimos la entidad al grafo de escena.
		if(!entity->attachToScene(this, father)) {
			return false;
		}
		// Registramos la entidad en la tabla de entidades.
		_entities[entity->getFullName()] = entity;
		// Registramos la entidad en la lista que sea necesaria.
		if(ImmutableEntity * immutableVictim = dynamic_cast<ImmutableEntity *>(entity)) {
			_immutableEntities.push_back(immutableVictim);
		} else if(AnimatedEntity * animatedVictim = dynamic_cast<AnimatedEntity *>(entity)) {
			_updateableEntities.push_back(animatedVictim);
		}
		// Y devolvemos que todo ha ido perfectamente.
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::removeEntity(GenericGraphicEntity * entity) {
		assert(entity && "Scene::removeEntity -> The entity parameter can't be NULL...");
		// Quitamos la entidad del grafo de escena.
		entity->deattachFromScene();
		// Eliminamos la entidad de la tabla de entidades.
		GenericGraphicEntityTable::iterator victim = _entities.find(entity->getFullName());
		if(victim != _entities.end()) {
			_entities.erase(victim);
		}
		// Eliminamos la entidad de la lista en la que esté registrada.
		if(ImmutableEntity * immutableVictim = dynamic_cast<ImmutableEntity *>(entity)) {
			_immutableEntities.remove(immutableVictim);
		} else if(AnimatedEntity * animatedVictim = dynamic_cast<AnimatedEntity *>(entity)) {
			_updateableEntities.remove(animatedVictim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::showSkyBox(bool enable, const std::string & material, float distance, bool paintBefore) {
		_sceneManager->setSkyBox(enable, material, distance, paintBefore);
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::moveTerrain(const Vector3 & offset) {
		_terrain->setOrigin(_terrain->getOrigin() + offset);
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::activate() {
		// Construimos la geometría inmutable.
		buildImmutableGeometry();
		// Creamos el viewport para la escena.
		_viewport = GraphicsManager::GetInstance()->getRenderWindow()->addViewport(_camera->getCamera());
		if(_viewport) _viewport->setBackgroundColour(_backgroundColour);
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::deactivate() {
		// Borramos la geometría inmutable de la escena.
		if(_immutableGeometry) {
			_sceneManager->destroyStaticGeometry(_immutableGeometry);
			_immutableGeometry = 0;
		}
		// Borramos el viewport de la escena.
		if(_viewport) {
			GraphicsManager::GetInstance()->getRenderWindow()->removeViewport(_viewport->getZOrder());
			_viewport = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::update(float lastInterval) {
		// Recorremos la lista de entidades que requieren ser actualizadas.
		GenericGraphicEntityList::iterator end = _updateableEntities.end();
		for(GenericGraphicEntityList::iterator i = _updateableEntities.begin(); i != end; ++i) {
			// Actualizamos la entidad pasándole el último intervalo de tiempo.
			(*i)->update(lastInterval);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Scene::buildImmutableGeometry() {
		// Comprobamos que la geometría inmutable no esté previamente creada y que haya geometría para añadir.
		if(!_immutableGeometry && !_immutableEntities.empty()) {
			// Creamos el controlador del terreno en la escena.
			_immutableGeometry = _sceneManager->createStaticGeometry("StaticGeometry");
			// Recorremos la lista de entidades inmutables.
			ImmutableEntityList::iterator end = _immutableEntities.end();
			for(ImmutableEntityList::iterator i = _immutableEntities.begin(); i != end; ++i) {
				// Añadimos la entidad al gestor de la geometría inmutable.
				(*i)->addToImmutableGeometry();
			}
			// Y finalmente mandamos construir la geometría inmutable.
			_immutableGeometry->build();
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Scene::Scene(const std::string & name) : _name(name), _root(0), _sceneManager(0), _viewport(0),
	_backgroundColour(0.0f, 0.0f, 0.0f, 1.0f), _camera(0), _terrain(0), _immutableGeometry(0) {
		// Asignamos el nombre de la escena.
		_name = name;
		// Guardamos el gestor Ogre de la aplicación, para crear el gestor Ogre de la escena.
		_root = BaseManager::GetInstance()->getOgreRoot();
		_sceneManager = _root->createSceneManager(Ogre::ST_INTERIOR, _name);
		// Creamos la cámara de la escena.
		_camera = new Camera(_name, this);
	}

	//--------------------------------------------------------------------------------------------------------

	Scene::~Scene() {
		// Desactivamos la escena.
		deactivate();
		// Borramos la cámara de la escena.
		delete _camera;
		// Destruimos el gestor Ogre de la escena.
		_root->destroySceneManager(_sceneManager);
		// Borramos las colecciones de datos.
		_entities.clear();
		_updateableEntities.clear();
		_immutableEntities.clear();
	}

	//********************************************************************************************************
	// Operadores
	//********************************************************************************************************

	GenericGraphicEntity * Scene::operator [](const std::string & index) {
		GenericGraphicEntityTable::iterator victim = _entities.find(index);
		if(victim != _entities.end()) {
			return victim->second;
		} else {
			return 0;
		}
	}
}
