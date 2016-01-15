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
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "Core/BaseManager.h"
#include "Core/Graphics/Camera.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	const std::string Camera::NodeSuffixus = std::string("Node");
	const std::string Camera::EntitySuffixus = std::string("Camera");
	const float Camera::NearClipDistance = 10.0f;
	const float Camera::FarClipDistance = 9000.0f;

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	void Camera::setTransform(const Matrix4 & value) {
		assert(_sceneNode && "Camera::setTransform -> The scene node has not been created...");
		_sceneNode->setPosition(value.getTrans());
		_sceneNode->setOrientation(value.extractQuaternion());
	}

	//--------------------------------------------------------------------------------------------------------

	const Vector3 & Camera::getPosition() const {
		assert(_sceneNode && "Camera::getPosition -> The scene node has not been created...");
		return _sceneNode->getPosition();
	}

	//--------------------------------------------------------------------------------------------------------

	void Camera::setPosition(const Vector3 & value) {
		assert(_sceneNode && "Camera::setPosition -> The scene node has not been created...");
		_sceneNode->setPosition(value);
	}

	//--------------------------------------------------------------------------------------------------------

	const Quaternion & Camera::getOrientation() const {
		assert(_sceneNode && "Camera::getOrientation -> The scene node has not been created...");
		return _sceneNode->getOrientation();
	}

	//--------------------------------------------------------------------------------------------------------

	void Camera::setOrientation(const Quaternion & value) {
		assert(_sceneNode && "Camera::setOrientation -> The scene node has not been created...");
		_sceneNode->setOrientation(value);
	}

	//--------------------------------------------------------------------------------------------------------

	void Camera::setOrientation(const Matrix3 & value) {
		assert(_sceneNode && "Camera::setOrientation -> The scene node has not been created...");
		_sceneNode->setOrientation(value);
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Camera::Camera(const std::string & name, Scene * scene) {
		assert(scene && "Camera::Camera -> The camera must be associated with a scene...");
		// Asignamos el nombre de la cámara y la escena a la que pertenecerá.
		_name = name + EntitySuffixus;
		_scene = scene;

		// Creamos el nodo que va a contener la entidad de la cámara, que colgará de la raíz de la escena.
		_sceneNode = _scene->getSceneManager()->getRootSceneNode()->createChildSceneNode(_name + NodeSuffixus);

		// Creamos la entidad de la cámara.
		_camera = scene->getSceneManager()->createCamera(_name);

		// Configuramos el intervalo de distancias que la cámara va a abarcar.
		_camera->setNearClipDistance(NearClipDistance);
		_camera->setFarClipDistance(FarClipDistance);

		// Comprobamos si la tarjeta soporta renderizar con el "plano lejano" en el infinito.
		if(BaseManager::GetInstance()->isInfiniteFarPlaneSupported()) {
			// Si lo soporta configuramos el "plano lejano" para que esté en el infinito.
			_camera->setFarClipDistance(0);
		}

		// Finalmente añadimos la cámara al nodo que hemos creado.
		_sceneNode->attachObject(_camera);
	}

	//--------------------------------------------------------------------------------------------------------

	Camera::Camera(const Camera & obj) {
		_name = "";
		_sceneNode = 0;
		_camera = 0;
		_scene = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	Camera::~Camera() {
		// Eliminamos todas las entidades que cuelgan del nodo.
		_sceneNode->detachAllObjects();
		// Y luego destruimos los elementos del grafo de escena.
		_scene->getSceneManager()->destroyCamera(_camera);
		_scene->getSceneManager()->destroySceneNode(_sceneNode);
	}
}
