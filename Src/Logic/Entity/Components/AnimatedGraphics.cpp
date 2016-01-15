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
Contiene la implementación del componente que controla la representación
gráfica de una entidad estática.
*/

#include <assert.h>

#include "Logic/Entity/Components/AnimatedGraphics.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/Graphics/Scene.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/ChangeAnimationMessage.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/StopAnimationMessage.h"

namespace Logic 
{
	Core::GraphicEntity* AnimatedGraphics::createGraphicsEntity(const Core::EntityInfoTable *entityInfo)
	{
		_animatedGraphicsEntity = new Core::AnimatedEntity(_owner->getName(), _model);
		if(!_scene->addEntity(_animatedGraphicsEntity)) return 0;

		_animatedGraphicsEntity->setTransform(Position::GetTransform(entityInfo));
		
		if(entityInfo->hasAttribute("defaultAnimation"))
		{
			_defaultAnimation = entityInfo->getAttribute("defaultAnimation");
			_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
			_animatedGraphicsEntity->setObserver(this);
		}

		float scale = 1.0;
		const Core::EntityInfoTableNames * attributeNames = Core::EntitiesManager::GetInstance()->getAttributeNames();
		if (entityInfo->hasAttribute("scale")) {
			scale = entityInfo->getAttributeAsFloat("scale");
		} else if(entityInfo->hasAttribute(attributeNames->scale)) {
			scale = entityInfo->getAttributeAsFloat(attributeNames->scale);
		}
		_animatedGraphicsEntity->setScale(scale);

		return _animatedGraphicsEntity;
	}
	
	//---------------------------------------------------------

	bool AnimatedGraphics::acceptMessage(const Core::SmartMessage & message)
	{
		return Graphics::acceptMessage(message) ||
			message->getType() == MESSAGE_TYPE_CHANGE_ANIMATION ||
			message->getType() == MESSAGE_TYPE_STOP_ANIMATION;
	}
	
	//---------------------------------------------------------

	void AnimatedGraphics::processMessage(const Core::SmartMessage & message)
	{
		Graphics::processMessage(message);

		switch(message->getType())
		{
		case MESSAGE_TYPE_CHANGE_ANIMATION:
			// Paramos todas las animaciones antes de poner una nueva.
			// Un control más sofisticado debería permitir interpolación
			// de animaciones. DoM no lo plantea.
			{
			const ChangeAnimationMessage & cam = message->getDataRefAs<ChangeAnimationMessage>();
			_animatedGraphicsEntity->stopAllAnimations();
			_animatedGraphicsEntity->setAnimation(cam.getName(), cam.getLoop());
			}
			break;
		case MESSAGE_TYPE_STOP_ANIMATION:
			{
			const StopAnimationMessage & sam = message->getDataRefAs<StopAnimationMessage>();
			_animatedGraphicsEntity->stopAnimation(sam.getName());
			}
			break;
		}
	}
	
	//---------------------------------------------------------
	
	void AnimatedGraphics::animationFinished(const std::string &animation)
	{
		// Si acaba una animación y tenemos una por defecto la ponemos
		_animatedGraphicsEntity->stopAllAnimations();
		_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
	}
}
