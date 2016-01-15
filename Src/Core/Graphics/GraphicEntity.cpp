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
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "Core/Graphics/GraphicEntity.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	bool GraphicEntity::getVisible() {
		assert(_entity && "GraphicEntity::getVisible -> The entity has not been loaded...");
		return _entity->isVisible();
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicEntity::setVisible(bool value) {
		assert(_entity && "GraphicEntity::setVisible -> The entity has not been loaded...");
		_entity->setVisible(value);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GraphicEntity::attachToScene(Scene * scene, GraphicNodeEntity * father) {
		assert(scene && "GraphicEntity::attachToScene -> The entity must be associated with a scene...");
		// Comprobamos si la entidad está ya cargada.
		if(_loaded) {
			// Si la entidad está cargada en otra escena lanzamos falso.
			return _scene == scene;
		} else {
			// Si no está cargada forzamos su carga.
			return GenericGraphicEntity::attachToScene(scene, father) && load();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicEntity::deattachFromScene() {
		assert(_scene && "GraphicEntity::deattachFromScene -> The entity must be associated with a scene...");
		// Si la entidad no está cargada no se puede quitar de una escena. Ya que no pertenecerá a ninguna.
		if(!_loaded) {
			return false;
		} else {
			// Si la entidad está cargada forzamos su descarga.
			unload();
			return GenericGraphicEntity::deattachFromScene();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicEntity::load() {
		try {
			// Creamos primero la entidad de Ogre.
			_entity = _scene->getSceneManager()->createEntity(_name, _mesh);
			if(_entity) {
				// Añadimos la entidad al nodo.
				_entityNode->attachObject(_entity);
				// Y marcamos la entidad como cargada.
				_loaded = true;
				return true;
			} else {
				return false;
			}
		} catch(...) {
			// Si algo falla quitamos la entidad de la escena.
			deattachFromScene();
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicEntity::unload() {
		// Destruimos la entidad de Ogre de existir.
		if(_entity) {
			_scene->getSceneManager()->destroyEntity(_entity);
			_entity = 0;
		}
		// Y marcamos la entidad como descargada.
		_loaded = false;
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicEntity::update(float lastInterval) {
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GraphicEntity::GraphicEntity(const std::string & name, const std::string & mesh)
	: GenericGraphicEntity(name), _mesh(mesh), _entity(0), _loaded(false) {}

	//--------------------------------------------------------------------------------------------------------

	GraphicEntity::GraphicEntity(const GraphicEntity & obj) : GenericGraphicEntity(obj) {
		// Copiamos el nombre del modelo.
		_mesh = obj._mesh;
		// AVISO: La copia de los siguientes datos puede resultar peliaguda de borrarse el original.
		_entity = obj._entity;
		_loaded = obj._loaded;
	}

	//--------------------------------------------------------------------------------------------------------

	GraphicEntity::~GraphicEntity() {
		assert(!_scene && "GraphicEntity::~GraphicEntity -> You must remove from the scene the entity before delete it...");
	}
}
