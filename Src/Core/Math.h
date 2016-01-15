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
 * Cuaterni�n. Se usa para calcular rotaciones tridimensionales.
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
	 * Constante para representar el n�mero PI.
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
	 * Convierte un �ngulo en grados a radianes.
	 * @param degree El �ngulo en grados.
	 * @return El �ngulo en radianes.
	 */
	inline float FromDegreesToRadians(float degrees) {
		return degrees * DEG2RAD;
	}

	/**
	 * Convierte un �ngulo en radianes a grados.
	 * @param radian El �ngulo en radianes.
	 * @return El �ngulo en grados.
	 */
	inline float FromRadiansToDegrees(float radians) {
		return radians * RAD2DEG;
	}

	/**
	 * Aplica un giro a una matriz de transformaci�n.
	 * @param turn El giro en radianes.
	 * @param transform La matriz de transformaci�n.
	 */
	inline void Yaw(float turn, Matrix4 & transform) {
		// Primero, se extrae la rotaci�n de la matriz de transformaci�n.
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		// Segundo, se extrae los �ngulos del valor de rotaci�n.
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		// Tercero, se obtiene el nuevo �ngulo de giro y se actualiza la rotaci�n.
		Ogre::Radian newYaw = yaw + Ogre::Radian(turn);
		rotation.FromEulerAnglesYXZ(newYaw, pitch, roll);
		// Por �ltimo, se actualiza la transformaci�n.
		transform = rotation;
	}

	/**
	 * Obtiene el �ngulo de giro de una matriz de transformaci�n.
	 * @param transform La matriz de transformaci�n.
	 * @return El �ngulo de giro de la entidad.
	 */
	inline float GetYaw(const Matrix4 & transform) {
		// Primero, se extrae la rotaci�n de la matriz de transformaci�n.
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		// Segundo, se extrae los �ngulos del valor de rotaci�n.
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		// Por �ltimo, se devuelve el �ngulo extraido.
		return yaw.valueRadians();
	}

	/**
	 * Cambia el �ngulo de giro en una matriz de transformaci�n.
	 * @param turn El �ngulo en radianes.
	 * @param transform La matriz de transformaci�n.
	 */
	inline void SetYaw(float turn, Matrix4 & transform) {
		// Primero, se reinicia la matriz de rotaci�n.
		transform = Matrix3::IDENTITY;
		// Y despu�s, se aplica la rotaci�n.
		Yaw(turn, transform);
	}

	/**
	 * Crea un vector unitario de direcci�n a partir de un angulo de orientaci�n en radianes.
	 * @param orientation La orientaci�n en radianes.
	 * @return El vector unitario en el plano XZ.
	 */
	inline Vector3 GetDirection(float orientation) {
		return Vector3(-sin(orientation), 0, -cos(orientation));
	}

	/**
	 * Crea un vector unitario de direcci�n en el plano XZ a partir de una matriz de transformaci�n.
	 * @param transform La matriz de transformaci�n.
	 * @return El vector unitario en el plano XZ.
	 */
	inline Vector3 GetDirection(const Matrix4 & transform) {
		return GetDirection(GetYaw(transform));
	}
}

#endif
