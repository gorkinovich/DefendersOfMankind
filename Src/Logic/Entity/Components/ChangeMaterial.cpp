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
Contiene la declaración del componente que controla el cambio del material de la entidad en tiempo real.
Para ello acepta y procesa mensajes de tipo SWITCH.
*/

#include <assert.h>
#include <OgreEntity.h>
#include <OgreString.h>
#include <OgreSubEntity.h>

#include "Logic/Entity/Components/ChangeMaterial.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Graphics/GraphicEntity.h"
#include "Logic/Entity/Components/Graphics.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/SwitchMessage.h"

namespace Logic 
{
	ChangeMaterial::~ChangeMaterial()
	{
		// Borramos la información de las tablas
		_origMaterials.clear();
		_modifiedMaterials.clear();
	}

	//---------------------------------------------------------

	bool ChangeMaterial::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		_entityInfo = entityInfo;
		return true;
	}
	
	//---------------------------------------------------------

	bool ChangeMaterial::activate()
	{
		Graphics * graphicsComponent = _owner->getComponentAs<Graphics>("Graphics");
		assert(_entityInfo && graphicsComponent && "La entidad necesariamente debe tener un componente grafico");

		// Rellenamos las tablas con la información de los materiales
		Ogre::String name;
		std::stringstream ss;
		std::string str;

		//Recorremos la tabla de materiales de todas las subentidades
		int n = graphicsComponent->getGraphicsEntity()->getEntity()->getNumSubEntities();
		for (int i = 0; i<n; ++i)
		{
			// Rellenamos la tabla de los materiales originales
			name = graphicsComponent->getGraphicsEntity()->getEntity()->getSubEntity(i)->getMaterialName();
			_origMaterials[i] = name;

			// Rellenamos la tabla de los materiales nuevos
			ss.clear();
			ss << "NewMaterial" << i;
			ss >> str; // Construimos el nombre de la propiedad a buscar
			if(_entityInfo->hasAttribute(str)) {
				_modifiedMaterials[i] = _entityInfo->getAttribute(str);
			}
		}

		return true;
	}
	
	//---------------------------------------------------------

	void ChangeMaterial::deactivate()
	{
	}

	//---------------------------------------------------------

	bool ChangeMaterial::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_SWITCH;
	}
	
	//---------------------------------------------------------

	void ChangeMaterial::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_SWITCH:
			{
				//printf("MATERIAL !!!!\n");
				Graphics * graphicsComponent = _owner->getComponentAs<Graphics>("Graphics");
				int n = graphicsComponent->getGraphicsEntity()->getEntity()->getNumSubEntities();
				TMaterialTableIterator it;

				int value = message->getDataRefAs<SwitchMessage>().getTouched();
				if (value==1)	// Dentro de la entidad enemiga (materiales con shader)
				{			
					// Cambiamos el material de cada subentidad
					for (int i = 0; i<n; i++)
					{
						it = _modifiedMaterials.find(i);
						if (it != _modifiedMaterials.end())	// Si existe...
						{
							graphicsComponent->getGraphicsEntity()->
								getEntity()->getSubEntity(i)->setMaterialName(it->second);
						}
					}
				}
				else	// Fuera de la entidad enemiga (materiales originales)
				{
					// Cambiamos el material de cada subentidad
					for (int i = 0; i<n; i++)
					{
						it = _origMaterials.find(i);
						if (it != _origMaterials.end())	// Si existe...
						{
							graphicsComponent->getGraphicsEntity()->
								getEntity()->getSubEntity(i)->setMaterialName(it->second);
						}
					}
				}
			}
			break;
		}
	}
}
