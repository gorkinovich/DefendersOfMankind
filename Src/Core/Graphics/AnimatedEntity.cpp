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
#include <OgreEntity.h>
#include <OgreAnimationState.h>

#include "Core/Graphics/AnimatedEntity.h"
#include "Core/Graphics/Scene.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool AnimatedEntity::setAnimation(const std::string & name, bool loop) {
		assert(_entity && "AnimatedEntity::setAnimation -> The entity does not exist...");
		// Primero preguntamos si la entidad tiene la animación que le estamos pidiendo.
		if(!_entity->getAllAnimationStates()->hasAnimationState(name)) {
			return false;
		}
		// Obtenemos el gestor interno de la animación de la entidad.
		_currentAnimation = _entity->getAnimationState(name);
		// Activamos la animación y configuramos si es cíclica o no.
		_currentAnimation->setEnabled(true);
		_currentAnimation->setLoop(loop);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool AnimatedEntity::stopAnimation(const std::string & name) {
		assert(_entity && "AnimatedEntity::stopAnimation -> The entity does not exist...");
		// Primero preguntamos si la entidad tiene la animación que le estamos pidiendo.
		if(!_entity->getAllAnimationStates()->hasAnimationState(name)) {
			return false;
		}
		// Obtenemos el gestor interno de la animación de la entidad.
		Ogre::AnimationState * victim = _entity->getAnimationState(name);
		// Paramos la animación.
		victim->setEnabled(false);
		// En caso de que la animación actual sea la que acabamos de parar, ya no
		// necesitaremos la referencia interna que guardabamos para la actualización.
		if(victim == _currentAnimation) {
			_currentAnimation = 0;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void AnimatedEntity::stopAllAnimations() {
		assert(_entity && "AnimatedEntity::stopAllAnimations -> The entity does not exist...");
		// Primero preguntamos si la entidad tiene alguna animación activada.
		Ogre::AnimationStateSet * animationStates = _entity->getAllAnimationStates();
		if(animationStates->hasEnabledAnimationState()) {
			Ogre::AnimationState * victim;
			// Obtenemos el iterador de todas las animaciones activas dentro de la entidad.
			Ogre::ConstEnabledAnimationStateIterator i = animationStates->getEnabledAnimationStateIterator();
			// Recorremos todas las animaciones activas, para pararlas una por una.
			while(i.hasMoreElements()) {
				victim = i.getNext();
				victim->setEnabled(false);
			}
			// Y borramos cualquier posible referencia a una animación activa.
			_currentAnimation = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void AnimatedEntity::update(float lastInterval) {
		// Comprobamos primero si hay alguna animación activada.
		if(_currentAnimation) {
			// Si lo hay, actualizamos su estado interno.
			_currentAnimation->addTime(lastInterval);
			// Tras la actualización, comprobamos si la animación ha terminado para poder avisar
			// al observador que pudiera estar registrado, que la animación ha terminado.
			if(_observer && _currentAnimation->hasEnded()) {
				_observer->animationFinished(_currentAnimation->getAnimationName());
			}
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	AnimatedEntity::AnimatedEntity(const std::string & name, const std::string & mesh)
	: GraphicEntity(name, mesh), _observer(0), _currentAnimation(0) {}

	//--------------------------------------------------------------------------------------------------------

	AnimatedEntity::AnimatedEntity(const AnimatedEntity & obj) : GraphicEntity(obj) {
		_observer = obj._observer;
		_currentAnimation = obj._currentAnimation;
	}

	//--------------------------------------------------------------------------------------------------------

	AnimatedEntity::~AnimatedEntity() {}
}
