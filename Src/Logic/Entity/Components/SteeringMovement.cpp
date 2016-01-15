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
 * Contiene la declaraci�n de la clase CSteringMovement. Se encarga de
 * mover un avatar utilizando movimientos cin�ticos o din�micos.
 */

#include <assert.h>

#include "Logic/Entity/Components/SteeringMovement.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/MoveToMessage.h"

namespace Logic {

	SteeringMovement::~SteeringMovement() {
		if(_currentMovement) delete _currentMovement;
		if(_yaw) delete _yaw;
	}

	//---------------------------------------------------------

	bool SteeringMovement::spawn(const Core::EntityInfoTable * entityInfo) {
		assert(_owner && "The component does not have an entity...");
		if(entityInfo->hasAttribute("speed"))
			_maxLinearSpeed = entityInfo->getAttributeAsFloat("speed");
		if(entityInfo->hasAttribute("angularSpeed"))
			_maxAngularSpeed = entityInfo->getAttributeAsFloat("angularSpeed");
		if(entityInfo->hasAttribute("accel"))
			_maxLinearAccel = entityInfo->getAttributeAsFloat("accel");
		if(entityInfo->hasAttribute("angularAccel"))
			_maxAngularAccel = entityInfo->getAttributeAsFloat("angularAccel");

		_yaw = AI::IMovement::getMovement(
			AI::IMovement::MOVEMENT_KINEMATIC_ALIGN_TO_SPEED, _maxLinearSpeed,
			_maxAngularSpeed, _maxLinearAccel, _maxAngularAccel);
		_yaw->setEntity(_owner);

		return true;
	}

	//---------------------------------------------------------

	void SteeringMovement::update(unsigned int lastInterval) {
		Component::update(lastInterval);

		// PR�CTICA IA
		// En cada tick tenemos que:
		// Comprobar si hay que cambiar de movimiento o destino
		//		Si es as�, sacar el nuevo movimiento de la factor�a (puede ser NULL ==> parado)
		//		Asignarle el nuevo destino y la entidad
		//		Si tiene que cambiar la animaci�n notificarlo con un mensaje

		// Si tenemos que movernos
		//		Invocar al m�todo move del movimiento actual. Las velocidades actuales se guardan en _currentProperties
		//		Calcular la nueva posici�n y notificarla a la f�sica para que nos mueva
		//		Calcular la nueva rotaci�n y actualizarla en la propia entidad con el m�todo setYaw
		//		Actualizar las velocidades usando la aceleraci�n

		// Comprobamos si hay que cambiar de movimiento o destino
		if(_movType != _currentMovementType || _currentTarget != _target) {
			if(_currentMovement != 0) {
				delete _currentMovement;
			}
			_currentMovementType = _movType;
			_currentTarget = _target;
			_currentMovement = AI::IMovement::getMovement(_currentMovementType, _maxLinearSpeed,
				_maxAngularSpeed, _maxLinearAccel, _maxAngularAccel);
			// Si hay un nuevo movimiento
			if (_currentMovement != 0) {
				// Ajustamos el target
				_arrived = false;
				_currentMovement->setEntity(_owner);
				_currentMovement->setTarget(_currentTarget);
				// Y la animaci�n
				sendAnimationMessage("walk");
			} else {
				// Si no hay movimiento paramos la animaci�n
				sendAnimationMessage("idle");
			}
		}

		// Si nos estamos desplazando calculamos la pr�xima posici�n
		if (!_arrived && _currentMovement != 0) {
			Position * positionComponent = _owner->getComponentAs<Position>("Position");
			_arrived = positionComponent->getPosition().positionEquals(_target);
			_currentMovement->move(lastInterval, _currentProperties);
			// Aplicamos la rotaci�n
			_yaw->move(lastInterval, _currentProperties);

			// Enviar un mensaje para que el componente f�sico mueva el personaje
			_owner->sendMessage(MessageFactory::CreateAvatarWalkMessage(
				_currentProperties.linearSpeed * (Ogre::Real)lastInterval), this);
			// Aplicar la rotaci�n
			//_owner->yaw(_owner->getYaw() - out.targetYaw);
			// En este caso suponemos que la entidad siempre se mueve hacia adelante, 
			// as� que tomamos la direcci�n del vector de velocidad.
			//_owner->setYaw(atan2(-message._vector3.x, -message._vector3.z));
			positionComponent->setYaw(positionComponent->getYaw() +
				(float)(_currentProperties.angularSpeed * (double)lastInterval));

			// Acelerar
			_currentProperties.linearSpeed += _currentProperties.linearAccel * (Ogre::Real)lastInterval;
			// Clipping
			double speedValue = _currentProperties.linearSpeed.length();
			if (speedValue > _maxLinearSpeed) {
				_currentProperties.linearSpeed *= (Ogre::Real)((double)_maxLinearSpeed / speedValue);
			}

			_currentProperties.angularSpeed += _currentProperties.angularAccel * lastInterval;
			if (_currentProperties.angularSpeed > _maxAngularSpeed) 
				_currentProperties.angularSpeed =
					(double)(Ogre::Math::Sign((Ogre::Real)_currentProperties.angularSpeed) *
					(Ogre::Real)_maxAngularSpeed);
		}
	}

	//---------------------------------------------------------

	void SteeringMovement::sendAnimationMessage(std::string animation) {
		_owner->sendMessage(MessageFactory::CreateChangeAnimationMessage(animation, true), this);
	}

	//---------------------------------------------------------

	bool SteeringMovement::acceptMessage(const Core::SmartMessage & message) {
		return message->getType() == MESSAGE_TYPE_MOVE_TO;
	}

	//---------------------------------------------------------

	void SteeringMovement::processMessage(const Core::SmartMessage & message) {
		switch(message->getType()) {
		case MESSAGE_TYPE_MOVE_TO:
			// Anotamos el vector de desplazamiento para usarlo posteriormente en 
			// el m�todo tick. De esa forma, si recibimos varios mensajes AVATAR_MOVE
			// en el mismo ciclo s�lo tendremos en cuenta el �ltimo.
			const MoveToMessage & msg = message->getDataRefAs<MoveToMessage>();
			_target = msg.getTarget();
			_movType = msg.getMoveType();
			break;
		}
	}
}
