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
Contiene la implementación del componente que controla la cámara gráfica de una escena.
*/

#include <assert.h>

#include "Logic/Entity/Components/Camera.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"
#include "Core/Graphics/Scene.h"
#include "Core/Graphics/Camera.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Messages/ChangeViewMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	Camera::Camera() : Component("Camera"), _graphicsCamera(0), _target(0), _distance(10.0f),
	_height(7.0f), _targetDistance(180.0f), _targetHeight(3.0f), _center(0, 0, 0),
	_type(SIDE), _moving(false), _interpolating(false), _travelTime(0), _interpTime(0), 
	_interpTotalTime(2.0f) {}
	
	//---------------------------------------------------------

	bool Camera::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		//Obtenemos la cámara de la escena
		_graphicsCamera = _owner->getWorld()->getScene()->getCamera();
		if(!_graphicsCamera) return false;

		if(entityInfo->hasAttribute("distance")) {
			_distance = entityInfo->getAttributeAsFloat("distance");
		}
			if(entityInfo->hasAttribute("height")) {
			_height = entityInfo->getAttributeAsFloat("height");
		}
			if(entityInfo->hasAttribute("targetDistance")) {
			_targetDistance = entityInfo->getAttributeAsFloat("targetDistance");
		}
			if(entityInfo->hasAttribute("targetHeight")) {
			_targetHeight = entityInfo->getAttributeAsFloat("targetHeight");
		}
			if(entityInfo->hasAttribute("center")) {
			_center = entityInfo->getAttributeAsVector3("center");
		}

		MissionManager::GetInstance()->setCameraType(Logic::SIDE);
		MissionManager::GetInstance()->setCenter(_center);
		MissionManager::GetInstance()->setDistance(_targetDistance);
		MissionManager::GetInstance()->setGameCamera(this);

		return true;
	}
	
	//---------------------------------------------------------

	bool Camera::activate()
	{
		setCamera();
		_target = MissionManager::GetInstance()->getPlayer();
		return true;
	}
	
	//---------------------------------------------------------

	void Camera::deactivate()
	{
		_target = 0;
	}
	
	//---------------------------------------------------------

	Vector3 Camera::getCenter()
	{
		return _center;
	}

	//---------------------------------------------------------

	void Camera::setCenter(/*Vector3 c*/)
	{
		/*if (!_interpolating){
			_center = c;
			MissionManager::GetInstance()->setCenter(_center);
		}*/
		_center = MissionManager::GetInstance()->getCenter();
	}

	//---------------------------------------------------------
	
	CameraType Camera::getType()
	{
		return _type;
	}

	//---------------------------------------------------------

	void Camera::setType(CameraType t)
	{
		_type = t;
	}

	//---------------------------------------------------------

	float Camera::getDistance()
	{
		return _targetDistance;
	}

	//---------------------------------------------------------

	void Camera::setCamera()
	{
		switch (_type){
			case SIDE: 
				_actPosition = Vector3(_targetDistance + _center.x, _center.y, _center.z); // 180,0,0
				_actRoll = Quaternion(1.0f, 0.0f, 1.0f, 0.0f); // 1,0,1,0
				_graphicsCamera->setPosition(_actPosition);
				_graphicsCamera->setOrientation(_actRoll);
				break;
			case SIDE_ROTATE:
				_actPosition = Vector3(_targetDistance + _center.x, _center.y, _targetDistance + _center.z); // 180,0,180
				_actRoll = Quaternion(1.0f, 0.0f, 0.5f, 0.0f); // 1,0,0.5,0
				_graphicsCamera->setPosition(_actPosition);
				_graphicsCamera->setOrientation(_actRoll);
				break;
			case UPPER:
				_actPosition = Vector3(_center.x, _targetDistance + _center.y, _center.z); // 0,180,0
				_actRoll = Quaternion(1.0f, -1.0f, 0.0f, 0.0f); // 1,-1,0,0
				_graphicsCamera->setPosition(_actPosition);
				_graphicsCamera->setOrientation(_actRoll);
				break;
			case UPPER_ROTATE:
				_actPosition = Vector3(_center.x, _targetDistance + _center.y, _targetDistance + _center.z); // 0,180,180
				_actRoll = Quaternion(1.0f, -0.5f, 0.0f, 0.0f); // 1,-0.5,0,0
				_graphicsCamera->setPosition(_actPosition);
				_graphicsCamera->setOrientation(_actRoll);
				break;
		}
	}

	//---------------------------------------------------------

	void Camera::moveCamera(CameraType t)
	{
		switch (t){
			case SIDE:
				_type = SIDE;
				MissionManager::GetInstance()->setCameraType(SIDE);
				_destination = Vector3(_targetDistance + _center.x, _center.y, _center.z);
				_destRotation = Quaternion(1.0f, 0.0f, 1.0f, 0.0f);
				_moving = true;
				break;

			case SIDE_ROTATE:
				_type = SIDE_ROTATE;
				MissionManager::GetInstance()->setCameraType(SIDE_ROTATE);
				_destination = Vector3(_targetDistance + _center.x, _center.y, _targetDistance + _center.z);
				_destRotation = Quaternion(1.0f, 0.0f, 0.5f, 0.0f);
				_moving = true;
				break;

			case UPPER:
				_type = UPPER;
				MissionManager::GetInstance()->setCameraType(UPPER);
				_destination = Vector3(_center.x, _targetDistance + _center.y, _center.z);
				_destRotation = Quaternion(1.0f, -1.0f, 0.0f, 0.0f);
				_moving = true;
				break;

			case UPPER_ROTATE:
				_type = UPPER_ROTATE;
				MissionManager::GetInstance()->setCameraType(UPPER_ROTATE);
				_destination = Vector3(_center.x, _targetDistance + _center.y, _targetDistance + _center.z);
				_destRotation = Quaternion(1.0f, -0.5f, 0.0f, 0.0f);
				_moving = true;
				break;
		}
		float iter = 100.0f;
		const Vector3 & position = _graphicsCamera->getPosition();
		_direction = _destination - position; //Vector3(_destination->x-position.x, _destination->y-position.y, _destination->z-position.z);
		_origin = _graphicsCamera->getPosition();
		_origCenter = _center;
		_origRotation = _graphicsCamera->getOrientation();
		_travelTime = 0;
	}

	//---------------------------------------------------------

	void Camera::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);
		
		if (_interpolating){
			//En el caso de estar haciendo una bifurcación, interpolamos el centro
			if (_interpTime >= _interpTotalTime){
				_interpolating = false;
				_center = _destCenter;
				MissionManager::GetInstance()->setCenter(_center);
			}else{
				Ogre::Real auxFactor = ((float)_interpTime * 0.001f);
				Vector3 direction(_destCenter.x - _oldCenter.x, _destCenter.y - _oldCenter.y, _destCenter.z - _oldCenter.z);
				_center = (_oldCenter + direction * auxFactor);
				MissionManager::GetInstance()->setCenter(_center);
				_interpTime += lastInterval;
			}
		}else{
			//Si no, actualizamos el centro
			setCenter();
		}

		if (_moving){
			const Vector3 & nuPosition = _graphicsCamera->getPosition();
			Vector3 direction(_destination.x - nuPosition.x, _destination.y - nuPosition.y, _destination.z - nuPosition.z);
			if (_travelTime >= 1000){
				_moving = false;
				setCamera();
			}else{
				Ogre::Real auxFactor = (float)_travelTime * 0.001f;
				_graphicsCamera->setPosition((_origin + _direction * auxFactor)- _origCenter + _center);
				_graphicsCamera->setOrientation(Quaternion::Slerp(auxFactor, _origRotation, _destRotation, true));
				_travelTime += lastInterval;
			}
		}else{
			setCamera();
		}
	}

	//---------------------------------------------------------

	bool Camera::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_CHANGE_VIEW;
	}

	//---------------------------------------------------------

	void Camera::processMessage(const Core::SmartMessage & message)
	{
		if (message->getType() == MESSAGE_TYPE_CHANGE_VIEW){
			const ChangeViewMessage & cv = message->getDataRefAs<ChangeViewMessage>();
			moveCamera(cv.getCameraType());

			//Next block of code is for testing camera changes. Uncomment if you need to.
			/*switch (_type){
			case SIDE:
				moveCamera(SIDE_ROTATE);
				break;
			case SIDE_ROTATE:
				moveCamera(UPPER);
				break;
			case UPPER:
				moveCamera(UPPER_ROTATE);
				break;
			case UPPER_ROTATE:
				moveCamera(SIDE);
				break;
			}*/

			/*float iter = 100.0f;
			const Vector3 & position = _graphicsCamera->getPosition();
			_direction = _destination - position;
			_origin = _graphicsCamera->getPosition();
			_origRotation = _graphicsCamera->getCamera()->getOrientation();
			_travelTime = 0;*/
		}
	}

	//---------------------------------------------------------

	void Camera::interpolateCenter(Vector3 newCenter, float travelTime){
		if (!_interpolating){
			_oldCenter = _center;
			_destCenter = newCenter;
			_interpTime = 0;
			_interpTotalTime = travelTime*1000;
			_interpolating = true;
		}
	}

	Camera::~Camera() {}
}
