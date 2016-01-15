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

/**
@file SteeringMovement.h

Contiene la declaración de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cinéticos o dinámicos.

@author Gonzalo Flórez
@date Diciembre, 2010
*/
#pragma once

#ifndef __Logic_SteeringMovement_H
#define __Logic_SteeringMovement_H

#include "Core/Entities/Component.h"
#include "AI/Movement.h"

namespace Logic {
	/**
	Componente que se encarga de trasladar una entidad de un punto a otro
	usando SteeringMovements. 
	Acepta mensajes del tipo MOVE_TO. Los parámetros relevantes del mensaje
	son el _vector, que indica el destino del movimiento, y el _int que indica 
	el tipo de movimiento (ver los tipos en IMovement).
	*/
	class SteeringMovement : public Core::Component {
	public:
		ComponentCreateMethod(SteeringMovement);

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		SteeringMovement() : Component("SteeringMovement"), _arrived(false), _maxLinearSpeed(0.05f),
		_maxAngularSpeed(0.01f), _maxLinearAccel(0.001f), _maxAngularAccel(0.001f), _currentMovement(0),
		_currentMovementType(AI::IMovement::MOVEMENT_NONE), _yaw(0) {};

		/**
		Destructor
		*/
		~SteeringMovement();

	protected:
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::Entity). Toma del mapa los atributos
		speed, angularSpeed, accel y angularAccel, que indican los valores máximos 
		de velocidad y aceleración lineales y angulares.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable * entityInfo);

		/**
		Método llamado en cada frame que actualiza el estado del componente. <p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		 * Comprueba si un mensaje es válido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser válido devolverá true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje recién sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

	private:
		/** 
		Valores máximos de velocidades y aceleraciones.
		*/
		float _maxLinearSpeed, _maxAngularSpeed, _maxLinearAccel, _maxAngularAccel;

		/**
		Este campo indica si se ha alcanzado el objetivo
		*/
		bool _arrived;

		/**
		Destino del movimiento.
		*/
		Vector3 _currentTarget, _target;

		/**
		Tipo de movimiento.
		*/
		int _currentMovementType, _movType;

		/**
		Instancia del movimiento actual.
		*/
		AI::IMovement* _currentMovement;

		/**
		Instancia de un movimiento de giro que se utilizará para mantener la dirección.
		*/
		AI::IMovement* _yaw;

		/**
		Propiedades actuales del movimiento. En esta variable se almacenan las velocidades
		actuales, que serán consultadas por los movimientos dinámicos
		*/
		AI::IMovement::DynamicMovement _currentProperties;

		/**
		Envía un mensaje para cambiar la animación actual.
		@param animation Nueva animación.
		*/
		void sendAnimationMessage(std::string animation);
	};
}

#endif
