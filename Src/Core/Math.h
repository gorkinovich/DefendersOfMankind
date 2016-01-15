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

#ifndef __CORE_MATH_H__
#define __CORE_MATH_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>
#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreRay.h>

//************************************************************************************************************
// Types
//************************************************************************************************************

/**
 * Matriz de 4x4.
 */
typedef Ogre::Matrix4 Matrix4;

/**
 * Matriz de 3x3 para rotaciones.
 */
typedef Ogre::Matrix3 Matrix3;

/**
 * Vector o punto 2D.
 */
typedef Ogre::Vector2 Vector2;

/**
 * Vector o punto 3D.
 */
typedef	Ogre::Vector3 Vector3;

/**
 * Vector o punto 4D.
 */
typedef	Ogre::Vector4 Vector4;

/**
 * Cuaternión. Se usa para calcular rotaciones tridimensionales.
 */
typedef Ogre::Quaternion Quaternion;

/**
 * Rayo.
 */
typedef Ogre::Ray Ray;

//************************************************************************************************************
// Math
//************************************************************************************************************

namespace Math {
	//--------------------------------------------------------------------------------------------------------
	// Constantes
	//--------------------------------------------------------------------------------------------------------

	/**
	 * Constante para representar el número PI.
	 */
	static const float PI = float(4.0 * atan(1.0));

	/**
	 * Constante para pasar de grados a radianes.
	 */
	static const float DEG2RAD = PI / 180.0f;

	/**
	 * Constante para pasar de radianes a grados.
	 */
	static const float RAD2DEG = 180.0f / PI;

	//--------------------------------------------------------------------------------------------------------
	// Funciones
	//--------------------------------------------------------------------------------------------------------

	/**
	 * Convierte un ángulo en grados a radianes.
	 * @param degree El ángulo en grados.
	 * @return El ángulo en radianes.
	 */
	inline float FromDegreesToRadians(float degrees) {
		return degrees * DEG2RAD;
	}

	/**
	 * Convierte un ángulo en radianes a grados.
	 * @param radian El ángulo en radianes.
	 * @return El ángulo en grados.
	 */
	inline float FromRadiansToDegrees(float radians) {
		return radians * RAD2DEG;
	}

	/**
	 * Aplica un giro a una matriz de transformación.
	 * @param turn El giro en radianes.
	 * @param transform La matriz de transformación.
	 */
	inline void Yaw(float turn, Matrix4 & transform) {
		// Primero, se extrae la rotación de la matriz de transformación.
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		// Segundo, se extrae los ángulos del valor de rotación.
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		// Tercero, se obtiene el nuevo ángulo de giro y se actualiza la rotación.
		Ogre::Radian newYaw = yaw + Ogre::Radian(turn);
		rotation.FromEulerAnglesYXZ(newYaw, pitch, roll);
		// Por último, se actualiza la transformación.
		transform = rotation;
	}

	/**
	 * Obtiene el ángulo de giro de una matriz de transformación.
	 * @param transform La matriz de transformación.
	 * @return El ángulo de giro de la entidad.
	 */
	inline float GetYaw(const Matrix4 & transform) {
		// Primero, se extrae la rotación de la matriz de transformación.
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		// Segundo, se extrae los ángulos del valor de rotación.
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		// Por último, se devuelve el ángulo extraido.
		return yaw.valueRadians();
	}

	/**
	 * Cambia el ángulo de giro en una matriz de transformación.
	 * @param turn El ángulo en radianes.
	 * @param transform La matriz de transformación.
	 */
	inline void SetYaw(float turn, Matrix4 & transform) {
		// Primero, se reinicia la matriz de rotación.
		transform = Matrix3::IDENTITY;
		// Y después, se aplica la rotación.
		Yaw(turn, transform);
	}

	/**
	 * Crea un vector unitario de dirección a partir de un angulo de orientación en radianes.
	 * @param orientation La orientación en radianes.
	 * @return El vector unitario en el plano XZ.
	 */
	inline Vector3 GetDirection(float orientation) {
		return Vector3(-sin(orientation), 0, -cos(orientation));
	}

	/**
	 * Crea un vector unitario de dirección en el plano XZ a partir de una matriz de transformación.
	 * @param transform La matriz de transformación.
	 * @return El vector unitario en el plano XZ.
	 */
	inline Vector3 GetDirection(const Matrix4 & transform) {
		return GetDirection(GetYaw(transform));
	}
}

#endif
