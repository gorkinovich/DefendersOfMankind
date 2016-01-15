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
#include <OgreSceneNode.h>
#include <OgreStaticGeometry.h>

#include "Core/Graphics/ImmutableEntity.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ImmutableEntity::addToImmutableGeometry() {
		// Si tenemos creado un nodo de Ogre vamos a seguir con el proceso.
		if(_entityNode) {
			// Añadimos la información del nodo a la geometría inmutable de la escena. Como no permite
			// modificaciones, toda ella está al mismo nivel en su nodo de geometría inmutable.
			_scene->getImmutableGeometry()->addSceneNode(_entityNode);
			// Borramos toda la información del nodo, para que no se pinte dos veces los modelos.
			_entityNode->detachAllObjects();
			return true;
		}
		return false;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ImmutableEntity::ImmutableEntity(const std::string & name, const std::string & mesh)
	: GraphicEntity(name, mesh) {}

	//--------------------------------------------------------------------------------------------------------

	ImmutableEntity::ImmutableEntity(const ImmutableEntity & obj) : GraphicEntity(obj) {}

	//--------------------------------------------------------------------------------------------------------

	ImmutableEntity::~ImmutableEntity() {}
}
