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

//TODO: Completar y comentar el fichero...

#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

#include "Logic/Entity/Messages/AvatarWalkMessage.h"
#include "Logic/Entity/Messages/ChangeAnimationMessage.h"
#include "Logic/Entity/Messages/ChangeTransformMessage.h"
#include "Logic/Entity/Messages/ChangeViewMessage.h"
#include "Logic/Entity/Messages/CollisionMessage.h"
#include "Logic/Entity/Messages/CreateChildMessage.h"
#include "Logic/Entity/Messages/DamagedMessage.h"
#include "Logic/Entity/Messages/DeathMessage.h"
#include "Logic/Entity/Messages/EndOfLevelMessage.h"
#include "Logic/Entity/Messages/MoveToMessage.h"
#include "Logic/Entity/Messages/ParticleSystemMessage.h"
#include "Logic/Entity/Messages/ParticleSystemEndMessage.h"
#include "Logic/Entity/Messages/RouteToMessage.h"
#include "Logic/Entity/Messages/SetAngleToRotateMessage.h"
#include "Logic/Entity/Messages/StopAnimationMessage.h"
#include "Logic/Entity/Messages/SwitchMessage.h"
#include "Logic/Entity/Messages/LifeCycleONMessage.h"
#include "Logic/Entity/Messages/LifeCycleOFFMessage.h"
#include "Logic/Entity/Messages/LifeCycleRELEASEMessage.h"
#include "Logic/Entity/Messages/ShowHideEntityMessage.h"
#include "Logic/Entity/Messages/PlaySoundMessage.h"
#include "Logic/Entity/Messages/PauseSoundMessage.h"
#include "Logic/Entity/Messages/PowerUpMessage.h"
#include "Logic/Entity/Messages/StopSoundMessage.h"
#include "Logic/Entity/Messages/PlayerPositionedMessage.h"
#include "Logic/Entity/Messages/PlayerDeadMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantEndMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantAbortMessage.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreateMessage(int type, Core::Object * data,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		return Core::SmartMessage(new Core::Message(type, data, entityTargetName, entityTargetType, componentTargetName));
	}

	//********************************************************************************************************
	// Métodos(General)
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreateUnassignedMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		return CreateMessage(MESSAGE_TYPE_UNASSIGNED, 0, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Métodos(Gráficos)
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreateChangeTransformMessage(const Matrix4 & transform,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new ChangeTransformMessage(transform);
		return CreateMessage(MESSAGE_TYPE_CHANGE_TRANSFORM, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateSetAngleToRotateMessage(float angle,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new SetAngleToRotateMessage(angle);
		return CreateMessage(MESSAGE_TYPE_SET_ANGLE_TO_ROTATE, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateAvatarWalkMessage(const Vector3 & movement,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new AvatarWalkMessage(movement);
		return CreateMessage(MESSAGE_TYPE_AVATAR_WALK, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateChangeAnimationMessage(const std::string & name, bool loop,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new ChangeAnimationMessage(name, loop);
		return CreateMessage(MESSAGE_TYPE_CHANGE_ANIMATION, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateStopAnimationMessage(const std::string & name,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new StopAnimationMessage(name);
		return CreateMessage(MESSAGE_TYPE_STOP_ANIMATION, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateChangeViewMessage(CameraType cameraType,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new ChangeViewMessage(cameraType);
		return CreateMessage(MESSAGE_TYPE_CHANGE_VIEW, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateParticleSystemMessage(const std::string & particleSystemName,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new ParticleSystemMessage(particleSystemName);
		return CreateMessage(MESSAGE_TYPE_PARTICLE_SYSTEM, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateParticleSystemEndMessage(const std::string & particleSystemName,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new ParticleSystemEndMessage(particleSystemName);
		return CreateMessage(MESSAGE_TYPE_PARTICLE_SYSTEM_END, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateShowHideEntityMessage(bool show,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new ShowHideEntityMessage(show);
		return CreateMessage(MESSAGE_TYPE_SHOW_HIDE_ENTITY, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Métodos(Física)
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreateTouchedMessage(const Core::Entity * victim,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new CollisionMessage(const_cast<Core::Entity *>(victim));
		return CreateMessage(MESSAGE_TYPE_TOUCHED, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateUntouchedMessage(const Core::Entity * victim,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new CollisionMessage(const_cast<Core::Entity *>(victim));
		return CreateMessage(MESSAGE_TYPE_UNTOUCHED, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateSwitchMessage(int touched,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new SwitchMessage(touched);
		return CreateMessage(MESSAGE_TYPE_SWITCH, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Métodos(Lógica)
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreateDamagedMessage(float value,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new DamagedMessage(value);
		return CreateMessage(MESSAGE_TYPE_DAMAGED, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateCreateChildMessage(unsigned int generatorId, const std::string childName,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new CreateChildMessage(generatorId, childName);
		return CreateMessage(MESSAGE_TYPE_CREATE_CHILD, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateDeathMessage(float timeToDie,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new DeathMessage(timeToDie);
		return CreateMessage(MESSAGE_TYPE_DEATH, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateEndOfLevelMessage(bool win,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new EndOfLevelMessage(win);
		return CreateMessage(MESSAGE_TYPE_END_OF_LEVEL, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateLifeCycleONMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new LifeCycleONMessage();
		return CreateMessage(MESSAGE_TYPE_LIFE_CYCLE_ON, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateLifeCycleOFFMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new LifeCycleOFFMessage();
		return CreateMessage(MESSAGE_TYPE_LIFE_CYCLE_OFF, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateLifeCycleRELEASEMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new LifeCycleRELEASEMessage();
		return CreateMessage(MESSAGE_TYPE_LIFE_CYCLE_RELEASE, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreatePlayerPositionedMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new PlayerPositionedMessage();
		return CreateMessage(MESSAGE_TYPE_PLAYER_POSITIONED, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreatePlayerDeadMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new PlayerDeadMessage();
		return CreateMessage(MESSAGE_TYPE_PLAYER_DEAD, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------
	
	Core::SmartMessage MessageFactory::CreatePowerUpMessage(PowerUpType powerUp, bool activate, const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new PowerUpMessage(powerUp, activate);
		return CreateMessage(MESSAGE_TYPE_POWER_UP, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------
	
	Core::SmartMessage MessageFactory::CreateGoToVirtualQuadrantMessage(int Q1, int Q2, const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new GoToVirtualQuadrantMessage(Q1, Q2);
		return CreateMessage(MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------
	
	Core::SmartMessage MessageFactory::CreateGoToVirtualQuadrantEndMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new GoToVirtualQuadrantEndMessage();
		return CreateMessage(MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_END, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------
	
	Core::SmartMessage MessageFactory::CreateGoToVirtualQuadrantAbortMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new GoToVirtualQuadrantAbortMessage();
		return CreateMessage(MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_ABORT, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------
	//...

	//********************************************************************************************************
	// Métodos(IA)
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreateRouteToMessage(bool walk, const Vector3 & target,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new RouteToMessage(walk, target);
		return CreateMessage(MESSAGE_TYPE_ROUTE_TO, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateMoveToMessage(int moveType, const Vector3 & target,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new MoveToMessage(moveType, target);
		return CreateMessage(MESSAGE_TYPE_MOVE_TO, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateFinishedRouteMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		return CreateMessage(MESSAGE_TYPE_FINISHED_ROUTE, 0, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateFailedRouteMessage(const char * entityTargetName,
	const char * entityTargetType, const char * componentTargetName) {
		return CreateMessage(MESSAGE_TYPE_FAILED_ROUTE, 0, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Métodos(Sonido)
	//********************************************************************************************************

	Core::SmartMessage MessageFactory::CreatePlaySoundMessage(const std::string& soundName,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new PlaySoundMessage(soundName);
		return CreateMessage(MESSAGE_TYPE_PLAY_SOUND, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreatePauseSoundMessage(const std::string& soundName,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new PauseSoundMessage(soundName);
		return CreateMessage(MESSAGE_TYPE_PAUSE_SOUND, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//--------------------------------------------------------------------------------------------------------

	Core::SmartMessage MessageFactory::CreateStopSoundMessage(const std::string& soundName,
	const char * entityTargetName, const char * entityTargetType, const char * componentTargetName) {
		Core::Object * data = new StopSoundMessage(soundName);
		return CreateMessage(MESSAGE_TYPE_STOP_SOUND, data, entityTargetName, entityTargetType, componentTargetName);
	}

	//...

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************
	
	MessageFactory::MessageFactory() {}
	
	//--------------------------------------------------------------------------------------------------------
	
	MessageFactory::~MessageFactory() {}
}
