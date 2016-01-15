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
Contiene la implementación del componente que controla la representación gráfica de la entidad.
*/

#include <assert.h>
#include <OgreEntity.h>

#include "Logic/Entity/Components/Graphics.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"
#include "Core/Graphics/GraphicEntity.h"
#include "Core/Graphics/ImmutableEntity.h"
#include "Core/Graphics/Scene.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/ChangeTransformMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/ShowHideEntityMessage.h"

namespace Logic 
{
	Graphics::~Graphics() 
	{
		if(_graphicsEntity)
		{
			_scene->removeEntity(_graphicsEntity);
			delete _graphicsEntity;
			_graphicsEntity = 0;
		}
	}
	
	//---------------------------------------------------------

	bool Graphics::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		_scene = _owner->getWorld()->getScene();

		const Core::EntityInfoTableNames * attributeNames = Core::EntitiesManager::GetInstance()->getAttributeNames();
		if(entityInfo->hasAttribute("model")) {
			_model = entityInfo->getAttribute("model");
		} else if(entityInfo->hasAttribute(attributeNames->graphicMeshFile)) {
			_model = entityInfo->getAttribute(attributeNames->graphicMeshFile);
		}

		_graphicsEntity = createGraphicsEntity(entityInfo);

		if(!_graphicsEntity) return false;

		if(entityInfo->hasAttribute(attributeNames->graphicCastShadows)) {
			_graphicsEntity->getEntity()->setCastShadows(entityInfo->getAttributeAsBool(attributeNames->graphicCastShadows));
		}
		if(entityInfo->hasAttribute(attributeNames->graphicMaterialFile)) {
			std::string materialFile = entityInfo->getAttribute(attributeNames->graphicMaterialFile);
			if(materialFile.size() > 0) {
				_graphicsEntity->getEntity()->setMaterialName(materialFile);
			}
		}

		return true;
	}

	//---------------------------------------------------------

	Core::GraphicEntity* Graphics::createGraphicsEntity(const Core::EntityInfoTable *entityInfo)
	{
		const Core::EntityInfoTableNames * attributeNames = Core::EntitiesManager::GetInstance()->getAttributeNames();

		bool isStatic = false;
		if(entityInfo->hasAttribute("static")) {
			isStatic = entityInfo->getAttributeAsBool("static");
		} else if(entityInfo->hasAttribute(attributeNames->graphicStatic)) {
			isStatic = entityInfo->getAttributeAsBool(attributeNames->graphicStatic);
		}

		Ogre::Vector3 scale;
		scale.x = 1.0; scale.y = 1.0; scale.z = 1.0;
		if(entityInfo->hasAttribute("scale")) {
			scale = entityInfo->getAttributeAsVector3("scale");
		} else if(entityInfo->hasAttribute(attributeNames->scale)) {
			scale = entityInfo->getAttributeAsVector3(attributeNames->scale);
		}

		// SkyBox: verificamos que se trata de una entidad "mundo"
		if(entityInfo->getAttribute("type")=="World")
		{
			bool skyBox_enable = false;
			if(entityInfo->hasAttribute("skyBox_enable"))
				skyBox_enable = entityInfo->getAttributeAsBool("skyBox_enable");

			if(skyBox_enable)
			{				
				std::string skyBox_material = "";
				if(entityInfo->hasAttribute("skyBox_material"))
					skyBox_material = entityInfo->getAttribute("skyBox_material");

				float skyBox_distance = 5000;
				if(entityInfo->hasAttribute("skyBox_distance"))
					skyBox_distance = entityInfo->getAttributeAsFloat("skyBox_distance");

				bool skyBox_paintBefore = true;
				if(entityInfo->hasAttribute("skyBox_paintBefore"))
					skyBox_paintBefore = entityInfo->getAttributeAsBool("skyBox_paintBefore");
				
				// Mostramos la skybox
				_scene->showSkyBox(skyBox_enable, skyBox_material, skyBox_distance, skyBox_paintBefore);			
			}
		}

		_graphicsEntity = isStatic ?
			new Core::ImmutableEntity(_owner->getName(), _model) :
			new Core::GraphicEntity(_owner->getName(), _model);
		if(!_scene->addEntity(_graphicsEntity)) return 0;

		_graphicsEntity->setScale(scale);
		_graphicsEntity->setTransform(Position::GetTransform(entityInfo));

		return _graphicsEntity;
	}
	
	//---------------------------------------------------------

	bool Graphics::acceptMessage(const Core::SmartMessage & message)
	{
		return (message->getType() == MESSAGE_TYPE_CHANGE_TRANSFORM || message->getType() == MESSAGE_TYPE_SHOW_HIDE_ENTITY);
	}
	
	//---------------------------------------------------------

	void Graphics::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
			case MESSAGE_TYPE_CHANGE_TRANSFORM:
			{
				_graphicsEntity->setTransform(message->getDataRefAs<ChangeTransformMessage>().getTransform());
				break;
			}
			case MESSAGE_TYPE_SHOW_HIDE_ENTITY:
			{
				_graphicsEntity->setVisible(message->getDataRefAs<ShowHideEntityMessage>().getShowHideParameter());
				break;
			}
		}
	}
}
