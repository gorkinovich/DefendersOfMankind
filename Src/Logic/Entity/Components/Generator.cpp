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

#include "Logic/Entity/Components/Generator.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/CreateChildMessage.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic
{
	Generator::~Generator()
	{
		for(TChildrenInfoIterator it = _childrenInfo.begin(); it != _childrenInfo.end(); ++it) {
			delete it->second;
		}
		//delete _entityInProgress;
	}

	//---------------------------------------------------------

	bool Generator::spawn(const Core::EntityInfoTable *entityInfo) {

		assert(_owner && "The component does not have an entity...");

		std::stringstream ss;

		//Recogemos el nº de hijos distintos que genera la entidad
		int n = 0;
		ss.str(""); ss << "Generator::children";
		if (entityInfo->hasAttribute(ss.str())) {
			n = entityInfo->getAttributeAsInteger(ss.str());
		}

		//Preparamos la información para cada hijo
		for (int i = 1; i <= n; ++i) {

			//Añadimos la información a la lista de dexcriptores de hijos
			ss.str(""); ss <<_owner->getName() << "Child" << i;
			_childrenInfo[ss.str()] = new Core::EntityInfoTable("");
			TChildrenInfoIterator infoChild = _childrenInfo.find(ss.str());

			//Generator::child# es el comienzo del nombre de todas las variables de este hijo
			std::string tempChildVarBegin;
			ss.str(""); ss << "Generator::child" << i << "::";
			tempChildVarBegin = ss.str();

			//Obtenemos una lista con todos los nombres de los atributos de la entidad
			StringSet paramList;
			entityInfo->getAllAttributes(paramList);

			//Buscamos otros atributos de los hijos
			for(StringSet::iterator it = paramList.begin(); it != paramList.end(); ++it) {
				if (it->find(tempChildVarBegin) == 0) {
					infoChild->second->setAttribute(it->substr(tempChildVarBegin.length()), entityInfo->getAttribute(it->data()));
				}
			}

			
			//Añadimos las variables mínimas que se tienen que definir para todo hijo

			//El tipo de entidad (para cargar el descriptor de LUA adecuado)
			if (!infoChild->second->hasAttribute("type")) {
				delete infoChild->second;	//MEJORAR
				_childrenInfo.erase(infoChild->first);
				break; //Si no encontramos el Type, se sale del bucle
			}

			if (!infoChild->second->hasAttribute("interval")) {
				infoChild->second->setAttribute("interval", "0"); //Por defecto, interval es cero.
			}
			//Cada hijo llevará el control de su tiempo transcurrido
			infoChild->second->setAttribute("lapsed","0");

			if (!infoChild->second->hasAttribute("relativePosition")) {
				//Por defecto, relativePosition es Vector3::ZERO.
				infoChild->second->setAttribute("relativePosition", "0 0 0");
			}
		}
		return true;
	}

	//---------------------------------------------------------

	bool Generator::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_CREATE_CHILD;
	}

	//---------------------------------------------------------

	void Generator::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_CREATE_CHILD:
			{
				const Core::EntityInfoTableNames * attributeNames = Core::EntitiesManager::GetInstance()->getAttributeNames();

				//Procesamos la informacióndel mensaje
				const CreateChildMessage & msgData = message->getDataRefAs<CreateChildMessage>();
				std::string childName = msgData.getChildName();

				for(TChildrenInfoIterator it = _childrenInfo.begin(); it != _childrenInfo.end(); ++it) {
					//Si no se indicó un hijo, se crean todos los hijos
					if (childName.compare("") == 0 || childName.compare(it->first) == 0) {

						// Preparamos las variables a cargar en la entidad
						// Éstas varían en cada generación. Tienen que prepararse aquí
						std::stringstream val;

						//Se genera un nombre que debe ser único
						val << it->second->getType() << "_" << _owner->getEntityId() << "_" << _childCount++;
						it->second->setName(val.str());
						val.str("");

						//Obtenemos el vector de posición en función de la cámara actual
						CameraType camType = MissionManager::GetInstance()->getCameraType();
						Vector3 relativePos = it->second->getAttributeAsVector3("relativePosition");
						if(camType == UPPER || camType == UPPER_ROTATE) {
							float aux = relativePos.y;
							relativePos.y = relativePos.x;
							relativePos.x = -aux;
						}

						//Como la posición del hijo es relativa a la del padre.
						//Se usa la de éste para crear la posición de salida absoluta. 
						Position * positionComponent = _owner->getComponentAs<Position>(attributeNames->position);
						Vector3 position = positionComponent->getPosition() + relativePos;
						it->second->setAttributeAsVector3(attributeNames->position, position);

						//Creamos la entidad
						Core::Entity *entity = Core::EntitiesManager::GetInstance()->createAndActivateEntity(
							Logic::MissionManager::GetInstance()->getWorld(), it->second);

						assert(entity && "No se pudo crear una entidad del mapa");
					}
				}
			}
			//break; //Descomentar cuando haya más opciones
		}
	}

	//---------------------------------------------------------

	void Generator::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);
		bool generate = false;

		//Recorremos la tabla de EntityInfos
		for(TChildrenInfoIterator it = _childrenInfo.begin(); it != _childrenInfo.end(); ++it) {
			if(it->second->hasAttribute("interval") && it->second->getAttributeAsFloat("interval") != 0.0f) {
				//Obtenemos el intervalo y el lapso de tiempo transcurrido
				float interval = it->second->getAttributeAsFloat("interval");
				float lapse = it->second->getAttributeAsFloat("lapsed");

				//Actualizamos valores y si el lapso super al intervalo, generamos el hijo
				lapse += lastInterval;
				if (lapse > interval) {
					lapse -= interval;
					//Cambiar esto para enviar el nombre del hijo a generar
					_owner->sendMessage(MessageFactory::CreateCreateChildMessage(_owner->getEntityId(),it->first));
				}

				//Actualizamos el lapso de tiempo transcurrido
				it->second->setAttributeAsFloat("lapsed",lapse);
			}
		}
	}

//	Vector3 Generator::correctPosition(Vector3 position, int cameraPosition) {
//	}
}