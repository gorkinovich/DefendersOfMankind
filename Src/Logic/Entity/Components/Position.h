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

#ifndef __LOGIC_POSITION_H__
#define __LOGIC_POSITION_H__

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	class Position : public Core::Component {
	public:
		ComponentCreateMethod(Position);

		/**
		 * Obtiene la matriz de transformación de la entidad.
		 */
		inline const Matrix4 & getTransform() const { return _transform; }

		/**
		 * Modifica la matriz de transformación de la entidad.
		 */
		void setTransform(const Matrix4 & value);

		/**
		 * Obtiene la posición de la entidad.
		 */
		Vector3 getPosition() const;

		/**
		 * Modifica la posición de la entidad.
		 */
		void setPosition(const Vector3 & value);

		/**
		 * Obtiene la orientación de la entidad.
		 */
		Matrix3 getOrientation() const;

		/**
		 * Obtiene la orientación de la entidad.
		 */
		Quaternion getOrientationAsQuaternion() const;

		/**
		 * Modifica la orientación de la entidad.
		 */
		void setOrientation(const Matrix3 & value);

		/**
		 * Modifica la orientación de la entidad.
		 */
		void setOrientation(float value);

		/**
		 * Modifica la orientación de la entidad.
		 */
		void rotateTo(float angle);

		/**
		 * Obtiene el ángulo de giro de la entidad.
		 */
		float getYaw() const;

		/**
		 * Modifica el ángulo de giro de la entidad.
		 */
		void setYaw(float value);

		/**
		 * Modifica el ángulo de giro de la entidad (sumándole el valor pasado).
		 */
		void yaw(float value);

		static Matrix4 GetTransform(const Core::EntityInfoTable * entityInfo);

		Position(const std::string & name = "Position") : Component(name), _transform(Matrix4::IDENTITY), _angleToReach(0.0f) {}

		virtual ~Position() {}

		/**
		Cambia el ángulo del vector Z en que tendrá que ponerse la entidad.
		@param angle el ángulo en el veector Z hacia el que tendrá que girar la entidad.
		*/
		void changeDestinationAngleZ(float angle) {_angleToReach = angle;}

	protected:

		/**
		 * La matriz de transformación de la entidad.
		 */
		Matrix4 _transform;

		/**
		 * El ángulo que tiene que tomar la entidad.
		 */
		float _angleToReach;

		virtual bool acceptMessage(const Core::SmartMessage & message);

		virtual void processMessage(const Core::SmartMessage & message);

		virtual bool spawn(const Core::EntityInfoTable * entityInfo);
		
		/**
		Método llamado en cada frame que actualiza el estado del componente.<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando está andando o desplazándose lateralmente).
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		 * Envía un mensaje para actualizar, en los componentes de la entidad, cualquier cambio en la
		 * matriz de transformación de la propia entidad.
		 */
		inline void sendChangeTransformMessage();
	};
}

#endif
