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
#include <exception>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "Core/Graphics/GenericGraphicEntity.h"
#include "Core/Graphics/GraphicNodeEntity.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string GenericGraphicEntity::NodeSuffixus = std::string("Node");

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	void GenericGraphicEntity::setTransform(const Matrix4 & value) {
		assert(_entityNode && "GenericGraphicEntity::setTransform -> The entity node has not been created...");
		_entityNode->setPosition(value.getTrans());
		_entityNode->setOrientation(value.extractQuaternion());
	}

	//--------------------------------------------------------------------------------------------------------

	const Vector3 & GenericGraphicEntity::getPosition() const {
		assert(_entityNode && "GenericGraphicEntity::getPosition -> The entity node has not been created...");
		return _entityNode->getPosition();
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericGraphicEntity::setPosition(const Vector3 & value) {
		assert(_entityNode && "GenericGraphicEntity::setPosition -> The entity node has not been created...");
		_entityNode->setPosition(value);
	}

	//--------------------------------------------------------------------------------------------------------

	const Quaternion & GenericGraphicEntity::getOrientation() const {
		assert(_entityNode && "GenericGraphicEntity::getOrientation -> The entity node has not been created...");
		return _entityNode->getOrientation();
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericGraphicEntity::setOrientation(const Quaternion & value) {
		assert(_entityNode && "GenericGraphicEntity::setOrientation -> The entity node has not been created...");
		_entityNode->setOrientation(value);
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericGraphicEntity::setOrientation(const Matrix3 & value) {
		assert(_entityNode && "GenericGraphicEntity::setOrientation -> The entity node has not been created...");
		_entityNode->setOrientation(value);
	}

	//--------------------------------------------------------------------------------------------------------

	const Vector3 & GenericGraphicEntity::getScale() const {
		assert(_entityNode && "GenericGraphicEntity::getScale -> The entity node has not been created...");
		return _entityNode->getScale();
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericGraphicEntity::setScale(const Vector3 & value) {
		assert(_entityNode && "GenericGraphicEntity::setScale -> The entity node has not been created...");
		_entityNode->setScale(value);
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericGraphicEntity::setScale(const float value) {
		assert(_entityNode && "GenericGraphicEntity::setScale -> The entity has not been loaded...");
		_entityNode->setScale(Vector3(value, value, value));
		_entityNode->setInitialState();
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GenericGraphicEntity::attachToScene(Scene * scene, GraphicNodeEntity * father) {
		assert(scene && "GenericGraphicEntity::attachToScene -> The entity must be associated with a scene...");
		// Comprobamos si existe ya un nodo creado en Ogre.
		if(_entityNode) {
			// Comprobamos si está asociado a una escena.
			if(_scene) {
				// Si tiene una escena, comprobamos que corresponda con la nueva.
				return _scene == scene;
			} else {
				// Si no lo está lanzamos una excepción, porque no debería estar un nodo creado y no "tener" escena.
				throw std::exception("GenericGraphicEntity::attachToScene => The node doesn't have an scene...");
			}
		}
		// Si no se cumple nada de lo anterior, pasamos a guardar una referencia a la nueva escena.
		_scene = scene;
		_father = father;
		if(_father) {
			// Si le estamos pasando un padre, comprobamos que tenga un nodo de Ogre.
			if(!_father->_entityNode) {
				_scene = 0;
				_father = 0;
				return false;
			}
			// Si tiene el nodo de Ogre, creamos el nodo dentro del nodo del padre.
			_father->_children.push_back(this);
			_entityNode = _father->_entityNode->createChildSceneNode(_name + NodeSuffixus);
			_fullName = _father->_fullName + GraphicNodeEntity::NodeSeparator + _name;
		} else {
			// Si no le estamos pasando un padre, creamos el nodo en la raíz de la escena.
			_entityNode = _scene->getRootSceneNode()->createChildSceneNode(_name + NodeSuffixus);
			_fullName = _name;
		}
		// Si no se creó el nodo de Ogre avisamos con fallo.
		if(!_entityNode) {
			_entityNode = 0;
			_scene = 0;
			_father = 0;
			_fullName = _name;
			return false;
		}
		// Si todo fue bien, devolvemos true como señal de haber terminado de forma correcta.
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GenericGraphicEntity::deattachFromScene() {
		assert(_scene && "GenericGraphicEntity::deattachFromScene -> The entity must be associated with a scene...");
		if(_entityNode) {
			// Si está asociado a un padre, tendremos que quitar el nodo de ahí.
			if(_father) {
				_father->_children.remove(this);
			}
			// Quitamos del nodo, por precaución, todo posible hijo que le siga colgando.
			_entityNode->detachAllObjects();
			// Destruimos el nodo de Ogre.
			_scene->getSceneManager()->destroySceneNode(_entityNode);
			// Y finalmente ponemos a "cero" la información interna.
			_entityNode = 0;
			_scene = 0;
			_father = 0;
			_fullName = _name;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GenericGraphicEntity::update(float lastInterval) {
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	GenericGraphicEntity::GenericGraphicEntity(const std::string & name)
	: _name(name), _fullName(name), _entityNode(0), _scene(0), _father(0) {}

	//--------------------------------------------------------------------------------------------------------

	GenericGraphicEntity::GenericGraphicEntity(const GenericGraphicEntity & obj) {
		// Copiamos el nombre de la entidad.
		_name = obj._name;
		// AVISO: La copia de los siguientes datos puede resultar peliaguda de borrarse el original.
		_entityNode = obj._entityNode;
		_scene = obj._scene;
	}

	//--------------------------------------------------------------------------------------------------------

	GenericGraphicEntity::~GenericGraphicEntity() {
		assert(!_scene && "GenericGraphicEntity::~GenericGraphicEntity -> You must remove the entity from the scene before delete it...");
	}
}
