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
#include <OgreLight.h>
#include <OgreSceneManager.h>

#include "Core/Graphics/LightEntity.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool LightEntity::attachToScene(Scene * scene, GraphicNodeEntity * father) {
		assert(scene && "LightEntity::attachToScene -> The entity must be associated with a scene...");
		// Intentamos añadir el nodo actual a la escena.
		if(GenericGraphicEntity::attachToScene(scene, father)) {
			// Creamos la entidad de luz de Ogre.
			_light = _scene->getSceneManager()->createLight(_name);
			if(_light) {
				// Añadimos la entidad al nodo.
				_entityNode->attachObject(_light);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool LightEntity::deattachFromScene() {
		assert(_scene && "LightEntity::deattachFromScene -> The entity must be associated with a scene...");
		// Borramos la entidad de luz de Ogre.
		if(_light) {
			_scene->getSceneManager()->destroyLight(_light);
			_light = 0;
		}
		// Y por último, intentamos quitar el nodo actual de la escena.
		return GenericGraphicEntity::deattachFromScene();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	LightEntity::LightEntity(const std::string & name) : GenericGraphicEntity(name), _light(0) {}

	//--------------------------------------------------------------------------------------------------------

	LightEntity::LightEntity(const LightEntity & obj) : GenericGraphicEntity(obj) {
		// AVISO: La copia de los siguientes datos puede resultar peliaguda de borrarse el original.
		_light = obj._light;
	}

	//--------------------------------------------------------------------------------------------------------

	LightEntity::~LightEntity() {
		assert(!_scene && "LightEntity::~LightEntity -> You must remove from the scene the entity before delete it...");
	}
}
