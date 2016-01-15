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

#ifndef __LOGIC_MESSAGEFACTORY_H__
#define __LOGIC_MESSAGEFACTORY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Math.h"
#include "Core/Entities/Message.h"
#include "Logic/Entity/Components/CameraType.h"
#include "Logic/Entity/Components/PowerUpType.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Entity;
}

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	/**
	 * Esta clase representa una factoría de mensajes.
	 */
	class MessageFactory {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo Message.
		 * @param type El tipo del mensaje.
		 * @param data Los datos del mensaje.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateMessage(int type, Core::Object * data,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		//----------------------------------------------------------------------------------------------------
		// Métodos(General)
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_UNASSIGNED.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateUnassignedMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos(Gráficos)
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_CHANGE_TRANSFORM.
		 * @param transform La transformación final de la entidad.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateChangeTransformMessage(const Matrix4 & transform,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_SET_ANGLE_TO_ROTATE.
		 * @param angle El ángulo al que deberá girar la nave.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateSetAngleToRotateMessage(float angle,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_AVATAR_WALK.
		 * @param movement El vector de avance de la entidad.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateAvatarWalkMessage(const Vector3 & movement,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_CHANGE_ANIMATION.
		 * @param name El nombre de la animación.
		 * @param loop El flag de reproducción cíclica.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateChangeAnimationMessage(const std::string & name, bool loop,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_STOP_ANIMATION.
		 * @param name El nombre de la animación.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateStopAnimationMessage(const std::string & name,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_CHANGE_VIEW.
		 * @param cameraType El tipo de camara a la que cambiar.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateChangeViewMessage(CameraType cameraType,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_PARTICLE_SYSTEM.
		 * @param particleSystemName El nombre del sistema de partículas.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateParticleSystemMessage(const std::string & particleSystemName,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_PARTICLE_SYSTEM_END.
		 * @param particleSystemName El nombre del sistema de partículas.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateParticleSystemEndMessage(const std::string & particleSystemName,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_SHOW_HIDE_ENTITY.
		 * @param show Booleano que indica si se debe mostrar u ocultar.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateShowHideEntityMessage(bool show,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos(Física)
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_TOUCHED.
		 * @param victim La entidad contra la que se interactua.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateTouchedMessage(const Core::Entity * victim,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_UNTOUCHED.
		 * @param victim La entidad contra la que se interactua.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateUntouchedMessage(const Core::Entity * victim,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_SWITCH.
		 * @param touched El flag que indica si la colisión está o no produciéndose.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateSwitchMessage(int touched,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos(Lógica)
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_DAMAGED.
		 * @param value La cantidad de daño infligido.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateDamagedMessage(float value,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_CREATE_CHILD.
		 * @param generatorId El identificador del generador.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateCreateChildMessage(unsigned int generatorId, const std::string childName,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_DEATH.
		 * @param timeToDie La cantidad de tiempo que queda antes de morir la entidad.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateDeathMessage(float timeToDie,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_END_OF_LEVEL.
		 * @param win El flag para indicar si el jugador ha terminado la partida venciendo.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateEndOfLevelMessage(bool win,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_END_OF_LEVEL.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateLifeCycleONMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_END_OF_LEVEL.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateLifeCycleOFFMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_END_OF_LEVEL.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateLifeCycleRELEASEMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_PLAYER_POSITIONED.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreatePlayerPositionedMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_PLAYER_DEAD.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreatePlayerDeadMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_POWER_UP.
		 * @param powerUp El Tipo de power Up
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreatePowerUpMessage(PowerUpType powerUp, bool activate, const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT.
		 * @param Q1 Indica la posición en el eje 1 del cuadrante virtual objetivo.
		 * @param Q2 Indica la posición en el eje 2 del cuadrante virtual objetivo.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateGoToVirtualQuadrantMessage(int Q1, int Q2, const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);


		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_END.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateGoToVirtualQuadrantEndMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_ABORT.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateGoToVirtualQuadrantAbortMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);


		//----------------------------------------------------------------------------------------------------
		// Métodos(IA)
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_ROUTE_TO.
		 * @param walk El flag para indicar si se está en movimiento o no.
		 * @param target El destino del movimiento.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateRouteToMessage(bool walk, const Vector3 & target,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_MOVE_TO.
		 * @param moveType El tipo de movimiento.
		 * @param target El destino del movimiento.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateMoveToMessage(int moveType, const Vector3 & target,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_FINISHED_ROUTE.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateFinishedRouteMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_FAILED_ROUTE.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateFailedRouteMessage(const char * entityTargetName = 0,
			const char * entityTargetType = 0, const char * componentTargetName = 0);

		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos(Sonido)
		//----------------------------------------------------------------------------------------------------

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_PLAY_SOUND.
		 * @param soundName El nombre del archivo de sonido.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreatePlaySoundMessage(const std::string & soundName,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_PAUSE_SOUND.
		 * @param soundName El nombre del archivo de sonido.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreatePauseSoundMessage(const std::string & soundName,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

				/**
		 * Crea un nuevo puntero inteligente de tipo MESSAGE_TYPE_STOP_SOUND.
		 * @param soundName El nombre del archivo de sonido.
		 * @param entityTargetName El nombre de la entidad destino.
		 * @param entityTargetType El tipo de la entidad destino.
		 * @param componentTargetName El nombre del componente destino.
		 * @return El nuevo mensaje creado.
		 */
		static Core::SmartMessage CreateStopSoundMessage(const std::string & soundName,
			const char * entityTargetName = 0, const char * entityTargetType = 0, const char * componentTargetName = 0);

		//...


	private:
		//----------------------------------------------------------------------------------------------------
		// Constructor y destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 */
		MessageFactory();
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~MessageFactory();
	};
}

#endif
