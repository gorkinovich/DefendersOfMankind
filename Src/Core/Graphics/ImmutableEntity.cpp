//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
	// M�todos
	//********************************************************************************************************

	bool ImmutableEntity::addToImmutableGeometry() {
		// Si tenemos creado un nodo de Ogre vamos a seguir con el proceso.
		if(_entityNode) {
			// A�adimos la informaci�n del nodo a la geometr�a inmutable de la escena. Como no permite
			// modificaciones, toda ella est� al mismo nivel en su nodo de geometr�a inmutable.
			_scene->getImmutableGeometry()->addSceneNode(_entityNode);
			// Borramos toda la informaci�n del nodo, para que no se pinte dos veces los modelos.
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
