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

#ifndef __LOGIC_POSITION_H__
#define __LOGIC_POSITION_H__

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	class Position : public Core::Component {
	public:
		ComponentCreateMethod(Position);

		/**
		 * Obtiene la matriz de transformaci�n de la entidad.
		 */
		inline const Matrix4 & getTransform() const { return _transform; }

		/**
		 * Modifica la matriz de transformaci�n de la entidad.
		 */
		void setTransform(const Matrix4 & value);

		/**
		 * Obtiene la posici�n de la entidad.
		 */
		Vector3 getPosition() const;

		/**
		 * Modifica la posici�n de la entidad.
		 */
		void setPosition(const Vector3 & value);

		/**
		 * Obtiene la orientaci�n de la entidad.
		 */
		Matrix3 getOrientation() const;

		/**
		 * Obtiene la orientaci�n de la entidad.
		 */
		Quaternion getOrientationAsQuaternion() const;

		/**
		 * Modifica la orientaci�n de la entidad.
		 */
		void setOrientation(const Matrix3 & value);

		/**
		 * Modifica la orientaci�n de la entidad.
		 */
		void setOrientation(float value);

		/**
		 * Modifica la orientaci�n de la entidad.
		 */
		void rotateTo(float angle);

		/**
		 * Obtiene el �ngulo de giro de la entidad.
		 */
		float getYaw() const;

		/**
		 * Modifica el �ngulo de giro de la entidad.
		 */
		void setYaw(float value);

		/**
		 * Modifica el �ngulo de giro de la entidad (sum�ndole el valor pasado).
		 */
		void yaw(float value);

		static Matrix4 GetTransform(const Core::EntityInfoTable * entityInfo);

		Position(const std::string & name = "Position") : Component(name), _transform(Matrix4::IDENTITY), _angleToReach(0.0f) {}

		virtual ~Position() {}

		/**
		Cambia el �ngulo del vector Z en que tendr� que ponerse la entidad.
		@param angle el �ngulo en el veector Z hacia el que tendr� que girar la entidad.
		*/
		void changeDestinationAngleZ(float angle) {_angleToReach = angle;}

	protected:

		/**
		 * La matriz de transformaci�n de la entidad.
		 */
		Matrix4 _transform;

		/**
		 * El �ngulo que tiene que tomar la entidad.
		 */
		float _angleToReach;

		virtual bool acceptMessage(const Core::SmartMessage & message);

		virtual void processMessage(const Core::SmartMessage & message);

		virtual bool spawn(const Core::EntityInfoTable * entityInfo);
		
		/**
		M�todo llamado en cada frame que actualiza el estado del componente.<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando est� andando o desplaz�ndose lateralmente).
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		 * Env�a un mensaje para actualizar, en los componentes de la entidad, cualquier cambio en la
		 * matriz de transformaci�n de la propia entidad.
		 */
		inline void sendChangeTransformMessage();
	};
}

#endif
