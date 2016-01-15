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

#include "Logic/Entity/Components/Position.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Logic/Entity/Messages/ChangeTransformMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/SetAngleToRotateMessage.h"

namespace Logic {

	void Position::setTransform(const Matrix4 & value) {
		_transform = value;
		sendChangeTransformMessage();
	}

	//--------------------------------------------------------------------------------------------------------

	Vector3 Position::getPosition() const {
		return _transform.getTrans();
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::setPosition(const Vector3 & value) {
		_transform.setTrans(value);
		sendChangeTransformMessage();
	}

	//--------------------------------------------------------------------------------------------------------

	Matrix3 Position::getOrientation() const {
		Matrix3 orientation;
		_transform.extract3x3Matrix(orientation);
		return orientation;
	}

	//--------------------------------------------------------------------------------------------------------

	Quaternion Position::getOrientationAsQuaternion() const {
		return _transform.extractQuaternion();
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::setOrientation(const Matrix3 & value) {
		_transform = value;
		sendChangeTransformMessage();
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::setOrientation(float value) {
		Quaternion orientationQuaternion = Quaternion(Ogre::Degree((Ogre::Real)value), Vector3::UNIT_Z);
		Matrix3 orientationM3;
		orientationQuaternion.ToRotationMatrix(orientationM3);
		setOrientation(orientationM3);
	}

	//--------------------------------------------------------------------------------------------------------

	float Position::getYaw() const {
		return Math::GetYaw(_transform);
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::setYaw(float value) {
		Math::SetYaw(value, _transform);
		sendChangeTransformMessage();
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::yaw(float value) {
		Math::Yaw(value, _transform);
		sendChangeTransformMessage();
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::sendChangeTransformMessage() {
		_owner->sendMessage(MessageFactory::CreateChangeTransformMessage(_transform), this);
	}

	//--------------------------------------------------------------------------------------------------------

	Matrix4 Position::GetTransform(const Core::EntityInfoTable * entityInfo) {

		Matrix4 transform = Matrix4::IDENTITY;
		const Core::EntityInfoTableNames * attributeNames = Core::EntitiesManager::GetInstance()->getAttributeNames();

		if(entityInfo->hasAttribute("position")) {
			transform.setTrans(entityInfo->getAttributeAsVector3("position"));
		} else if(entityInfo->hasAttribute(attributeNames->position)) {
			transform.setTrans(entityInfo->getAttributeAsVector3(attributeNames->position));
		}

		if(entityInfo->hasAttribute("rotation")) {
			transform.makeTransform(transform.getTrans(), Vector3::UNIT_SCALE, entityInfo->getAttributeAsQuaternion("rotation"));
		} else if(entityInfo->hasAttribute(attributeNames->orientation)) {
			transform.makeTransform(transform.getTrans(), Vector3::UNIT_SCALE, entityInfo->getAttributeAsQuaternion(attributeNames->orientation));
		}

		return transform;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Position::spawn(const Core::EntityInfoTable * entityInfo) {
		assert(_owner && "The component does not have an entity...");
		_transform = GetTransform(entityInfo);
		sendChangeTransformMessage();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool Position::acceptMessage(const Core::SmartMessage & message) {
		return message->getType() == MESSAGE_TYPE_CHANGE_TRANSFORM
			|| message->getType() == MESSAGE_TYPE_SET_ANGLE_TO_ROTATE;
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::processMessage(const Core::SmartMessage & message) {
		switch(message->getType()) {
		case MESSAGE_TYPE_CHANGE_TRANSFORM:
			_transform = message->getDataRefAs<ChangeTransformMessage>().getTransform();
			break;
		case MESSAGE_TYPE_SET_ANGLE_TO_ROTATE:
			_angleToReach = message->getDataRefAs<SetAngleToRotateMessage>().getAngle();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Position::update(unsigned int lastInterval) {
		if(_owner->getType().compare("Player") == 0) {
			//Recogemos el ángulo actual sobre el eje Z en grados y la velocidad de giro
			float angleZ = getOrientationAsQuaternion().getRoll().valueDegrees();
			float giro = 0.5f * lastInterval;

			//Giramos la entidad hacia la orientación que debe
			if(_angleToReach < angleZ) {
				angleZ = (angleZ - giro > _angleToReach) ? angleZ - giro : _angleToReach;
				setOrientation(angleZ);
			} else if (_angleToReach > angleZ) {
				angleZ = (angleZ + giro < _angleToReach) ? angleZ + giro : _angleToReach;
				setOrientation(angleZ);
			}
		}
	}
}
