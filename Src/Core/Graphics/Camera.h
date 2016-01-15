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

#ifndef __CORE_CAMERA_H__
#define __CORE_CAMERA_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Math.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class Camera;
	class SceneNode;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;

	/**
	 * Esta clase representa una cámara dentro de una escena cualquiera.
	 */
	class Camera {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * Sufijo que lleva el nombre del nodo de la camara creado para Ogre.
		 */
		static const std::string NodeSuffixus;

		/**
		 * Sufijo que lleva el nombre la camara creada para Ogre.
		 */
		static const std::string EntitySuffixus;

		/**
		 * Valor por defecto del la distancia del plano cercano de renderizado.
		 */
		static const float NearClipDistance;

		/**
		 * Valor por defecto del la distancia del plano lejano de renderizado.
		 */
		static const float FarClipDistance;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre de la cámara.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene el nodo de escena de la cámara.
		 */
		inline Ogre::SceneNode * getSceneNode() { return _sceneNode; }

		/**
		 * Obtiene el controlador de Ogre de la cámara.
		 */
		inline Ogre::Camera * getCamera() { return _camera; }

		/**
		 * Modifica la transformación de la cámara.
		 */
		void setTransform(const Matrix4 & value);

		/**
		 * Obtiene la posición de la cámara.
		 */
		const Vector3 & getPosition() const;

		/**
		 * Modifica la posición de la cámara.
		 */
		void setPosition(const Vector3 & value);

		/**
		 * Obtiene la orientación de la cámara.
		 */
		const Quaternion & getOrientation() const;

		/**
		 * Modifica la orientación de la cámara.
		 */
		void setOrientation(const Quaternion & value);

		/**
		 * Modifica la orientación de la cámara.
		 */
		void setOrientation(const Matrix3 & value);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la cámara.
		 * @param scene La escena a la que la cámara pertenece.
		 */
		Camera(const std::string & name, Scene * scene);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Camera(const Camera & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Camera();

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre de la cámara.
		 */
		std::string _name;

		/**
		 * El nodo de Ogre donde está la cámara.
		 */
		Ogre::SceneNode * _sceneNode;

		/**
		 * El controlador de Ogre para la cámara.
		 */
		Ogre::Camera * _camera;

		/**
		 * La escena a la que la cámara pertenece.
		 */
		Scene * _scene;
	};
}

#endif
