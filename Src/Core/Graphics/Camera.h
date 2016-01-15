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
	 * Esta clase representa una c�mara dentro de una escena cualquiera.
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
		 * Obtiene el nombre de la c�mara.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene el nodo de escena de la c�mara.
		 */
		inline Ogre::SceneNode * getSceneNode() { return _sceneNode; }

		/**
		 * Obtiene el controlador de Ogre de la c�mara.
		 */
		inline Ogre::Camera * getCamera() { return _camera; }

		/**
		 * Modifica la transformaci�n de la c�mara.
		 */
		void setTransform(const Matrix4 & value);

		/**
		 * Obtiene la posici�n de la c�mara.
		 */
		const Vector3 & getPosition() const;

		/**
		 * Modifica la posici�n de la c�mara.
		 */
		void setPosition(const Vector3 & value);

		/**
		 * Obtiene la orientaci�n de la c�mara.
		 */
		const Quaternion & getOrientation() const;

		/**
		 * Modifica la orientaci�n de la c�mara.
		 */
		void setOrientation(const Quaternion & value);

		/**
		 * Modifica la orientaci�n de la c�mara.
		 */
		void setOrientation(const Matrix3 & value);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la c�mara.
		 * @param scene La escena a la que la c�mara pertenece.
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
		 * El nombre de la c�mara.
		 */
		std::string _name;

		/**
		 * El nodo de Ogre donde est� la c�mara.
		 */
		Ogre::SceneNode * _sceneNode;

		/**
		 * El controlador de Ogre para la c�mara.
		 */
		Ogre::Camera * _camera;

		/**
		 * La escena a la que la c�mara pertenece.
		 */
		Scene * _scene;
	};
}

#endif
