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

/**
@file SteeringMovement.h

Contiene la declaraci�n de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cin�ticos o din�micos.

@author Gonzalo Fl�rez
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
	Acepta mensajes del tipo MOVE_TO. Los par�metros relevantes del mensaje
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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::Entity). Toma del mapa los atributos
		speed, angularSpeed, accel y angularAccel, que indican los valores m�ximos 
		de velocidad y aceleraci�n lineales y angulares.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable * entityInfo);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente. <p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		 * Comprueba si un mensaje es v�lido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser v�lido devolver� true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje reci�n sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

	private:
		/** 
		Valores m�ximos de velocidades y aceleraciones.
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
		Instancia de un movimiento de giro que se utilizar� para mantener la direcci�n.
		*/
		AI::IMovement* _yaw;

		/**
		Propiedades actuales del movimiento. En esta variable se almacenan las velocidades
		actuales, que ser�n consultadas por los movimientos din�micos
		*/
		AI::IMovement::DynamicMovement _currentProperties;

		/**
		Env�a un mensaje para cambiar la animaci�n actual.
		@param animation Nueva animaci�n.
		*/
		void sendAnimationMessage(std::string animation);
	};
}

#endif
