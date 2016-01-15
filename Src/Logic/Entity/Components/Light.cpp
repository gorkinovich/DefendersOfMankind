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
#include <OgreLight.h>

#include "Logic/Entity/Components/Light.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"
#include "Core/Graphics/Scene.h"
#include "Core/Graphics/LightEntity.h"
#include "Core/XML/TypeOfLights.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/ChangeTransformMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool Light::acceptMessage(const Core::SmartMessage & message) {
		return message->getType() == MESSAGE_TYPE_CHANGE_TRANSFORM;
	}

	//--------------------------------------------------------------------------------------------------------

	void Light::processMessage(const Core::SmartMessage & message) {
		switch(message->getType()) {
		case MESSAGE_TYPE_CHANGE_TRANSFORM:
			_lightEntity->setTransform(message->getDataRefAs<ChangeTransformMessage>().getTransform());
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool Light::spawn(const Core::EntityInfoTable * info) {
		assert(_owner && "Light::spawn -> The component does not have an entity...");
		_scene = _owner->getWorld()->getScene();

		_lightEntity = createLightEntity(info);
		if(!_lightEntity) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	Core::LightEntity * Light::createLightEntity(const Core::EntityInfoTable * info) {
		Core::LightEntity * victim = new Core::LightEntity(info->getName());
		if(!_scene->addEntity(victim)) return 0;

		Ogre::Light * light = victim->getLight();

		if(info->hasAttribute("Light.Type")) {
			std::string ligthType = info->getAttribute("Light.Type");
			if(ligthType == XML_LIGHT_TYPE_POINT) {
				light->setType(Ogre::Light::LT_POINT);
			} else if(ligthType == XML_LIGHT_TYPE_DIRECTIONAL) {
				light->setType(Ogre::Light::LT_DIRECTIONAL);
			} else if(ligthType == XML_LIGHT_TYPE_SPOT) {
				light->setType(Ogre::Light::LT_SPOTLIGHT);
			} else if(ligthType == XML_LIGHT_TYPE_RADPOINT) {
				light->setType(Ogre::Light::LT_POINT);
			}

			if(info->hasAttribute("Light.Visible"))
				light->setVisible(info->getAttributeAsBool("Light.Visible"));

			if(info->hasAttribute("Light.CastShadows"))
				light->setCastShadows(info->getAttributeAsBool("Light.CastShadows"));

			if(info->hasAttribute("Light.Position"))
				light->setPosition(info->getAttributeAsVector3("Position"));

			if(info->hasAttribute("Light.Direction"))
				light->setDirection(info->getAttributeAsVector3("Light.Direction"));

			if(info->hasAttribute("Light.ColourDiffuse"))
				light->setDiffuseColour(info->getAttributeAsColourValue("Light.ColourDiffuse"));

			if(info->hasAttribute("Light.ColourSpecular"))
				light->setSpecularColour(info->getAttributeAsColourValue("Light.ColourSpecular"));

			if(info->hasAttribute("Light.SpotlightRangeInner") && info->hasAttribute("Light.SpotlightRangeOuter") &&
				info->hasAttribute("Light.SpotlightRangeFalloff")) {
				float inner = info->getAttributeAsFloat("Light.SpotlightRangeInner");
				float outer = info->getAttributeAsFloat("Light.SpotlightRangeOuter");
				float falloff = info->getAttributeAsFloat("Light.SpotlightRangeFalloff");
				light->setSpotlightRange(Ogre::Angle(inner), Ogre::Angle(outer), falloff);
			}

			if(info->hasAttribute("Light.AttenuationRange") && info->hasAttribute("Light.AttenuationConstant") &&
				info->hasAttribute("Light.AttenuationLinear") && info->hasAttribute("Light.AttenuationQuadratic")) {
				float range = info->getAttributeAsFloat("Light.AttenuationRange");
				float constant = info->getAttributeAsFloat("Light.AttenuationConstant");
				float linear = info->getAttributeAsFloat("Light.AttenuationLinear");
				float quadratic = info->getAttributeAsFloat("Light.AttenuationQuadratic");
				light->setAttenuation(range, constant, linear, quadratic);
			}
		}

		return victim;
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	Light::Light() : Component("Light"), _lightEntity(0), _scene(0) {}

	//--------------------------------------------------------------------------------------------------------

	Light::~Light() {
		if(_lightEntity) {
			_scene->removeEntity(_lightEntity);
			delete _lightEntity;
			_lightEntity = 0;
		}
	}
}
