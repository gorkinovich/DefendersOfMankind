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

#include "Core/Graphics/GraphicNodeEntity.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string GraphicNodeEntity::NodeSeparator = std::string(".");

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GraphicNodeEntity::attachToScene(Scene * scene, GraphicNodeEntity * father) {
		// Añadimos el nodo actual a la escena.
		return GenericGraphicEntity::attachToScene(scene, father);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicNodeEntity::deattachFromScene() {
		// Quitamos todas las entidades hijas del nodo actual.
		GenericGraphicEntityList::iterator end = _children.end();
		for(GenericGraphicEntityList::iterator i = _children.begin(); i != end; ++i) {
			if(!(*i)->deattachFromScene()) return false;
		}
		// Y por último, intentamos quitar el nodo actual de la escena.
		return GenericGraphicEntity::deattachFromScene();
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicNodeEntity::update(float lastInterval) {
		// Actualizamos todas las entidades hijas del nodo actual.
		GenericGraphicEntityList::iterator end = _children.end();
		for(GenericGraphicEntityList::iterator i = _children.begin(); i != end; ++i) {
			(*i)->update(lastInterval);
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GraphicNodeEntity::GraphicNodeEntity(const std::string & name) : GenericGraphicEntity(name) {}

	//--------------------------------------------------------------------------------------------------------

	GraphicNodeEntity::GraphicNodeEntity(const GraphicNodeEntity & obj) : GenericGraphicEntity(obj) {
		_children = obj._children;
	}

	//--------------------------------------------------------------------------------------------------------

	GraphicNodeEntity::~GraphicNodeEntity() {
		_children.clear();
	}
}
