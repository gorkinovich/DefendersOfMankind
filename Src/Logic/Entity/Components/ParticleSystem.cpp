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
Contiene la declaración del componente que controla los sistemas de partículas (SP) de la entidad.
Recibe y procesa mensajes de tipo PARTICLE_SYSTEM.
*/

#include <assert.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

#include "Logic/Entity/Components/ParticleSystem.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Graphics/GraphicEntity.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/Graphics/Scene.h"
#include "Logic/Entity/Components/Graphics.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/ParticleSystemMessage.h"

namespace Logic 
{
	ParticleSystem::~ParticleSystem()
	{
		// Si existe algún sistema de partículas...
		if(_particleSystemList.size()>0)
		{
			// Recorremos la lista y liberamos cada uno de los nodos
			TParticleSystemListIterator it;
			for (it=_particleSystemList.begin(); it!=_particleSystemList.end(); ++it)
				releaseParticleSystem(*it);
			
			// Borramos toda la lista
			_particleSystemList.clear();
		}

		// Borramos toda la tabla
		_particleSystemTable.clear();
	}
	
	//---------------------------------------------------------

	bool ParticleSystem::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		if(_owner->getType().compare("PowerBullet") == 0)
			printf("");
		assert(_owner && "The component does not have an entity...");		

		int n = 0;

		// Rellenamos la tabla con los datos de los sistemas de partículas que tendrá la entidad
		if(entityInfo->hasAttribute("NumberOfPS")) {
			n = entityInfo->getAttributeAsInteger("NumberOfPS");
		} else {
			return false;
		}

		std::stringstream ss; std::string str, str2;

		for (int i=0; i<n; i++) {
			// Construimos los nombres de la propiedad a buscar
			ss.clear(); ss << "PSName" << i+1; ss >> str;
			ss.clear(); ss << "PSTimeToLife" << i+1; ss >> str2;
			if(entityInfo->hasAttribute(str) && entityInfo->hasAttribute(str2)) {
				_particleSystemTable[entityInfo->getAttribute(str)] = entityInfo->getAttributeAsFloat(str2);
			}
		}

		return true;
	}

	//---------------------------------------------------------

	bool ParticleSystem::activate()
	{
		// Obtenemos el nodo de escena de la entidad
		Graphics * graphicsComponent = _owner->getComponentAs<Graphics>("Graphics");
		assert (graphicsComponent && "La entidad necesariamente debe tener un componente grafico !!");
		_entitySceneNode = graphicsComponent->getGraphicsEntity()->getSceneNode();
		// Obtenemos el manager de escena
		_sceneManager = Core::GraphicsManager::GetInstance()->getCurrentScene()->getSceneManager();
		// Obtenemos el manager de los sistemas de partículas (Particle Universe)
		_particleManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();		
		
		return true;
	}
	
	//---------------------------------------------------------

	bool ParticleSystem::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM;
	}
	
	//---------------------------------------------------------

	void ParticleSystem::processMessage(const Core::SmartMessage & message)
	{
		switch(message->getType())
		{
		case MESSAGE_TYPE_PARTICLE_SYSTEM:
			{
				// Obtenemos el nombre que especifica el sistema de partículas a crear
				std::string name = message->getDataRefAs<ParticleSystemMessage>().getParticleSystemName();
				// Creamos el sistema de partículas
				createParticleSystem(name);
			}
			break;
		}
	}

	//----------------------------------------------------------

	void ParticleSystem::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		// Si existe algun sistema de partículas...
		if(_particleSystemList.size()>0)
		{	
			// Actualizamos su tiempo de vida
			TParticleSystemListIterator it;
			it = _particleSystemList.begin();
			while (it != _particleSystemList.end())
			{
				(*it)->_timeToLife -= lastInterval;
				// Lo liberamos en caso de ser necesario
				if ( (*it)->_timeToLife <= 0)
				{
					// Notificamos el fín del sistema de partículas y lo liberamos
					_owner->sendMessage(MessageFactory::CreateParticleSystemEndMessage((*it)->_name));
					releaseParticleSystem(*it);
					it = _particleSystemList.erase(it);
				}
				else ++it;
			}
		}
	}

	//------------------------------------------

	bool ParticleSystem::createParticleSystem(const std::string &name)
	{
		TNode* node = new TNode;
		node->_name = name;

		// Construimos un nombre único para el sistema de partículas (completamente necesario en el caso
		// de que la entidad muestre simultáneamente dos mismos SP)
		std::stringstream ss; std::string str;
		TParticleSystemTableIterator it = _particleSystemTable.find(name);
		ss.clear(); ss << it->first << _owner << _idPS++; ss >> str;

		// Creamos el sistema de partículas
		//node->_particleSystem = Core::GraphicsManager::GetInstance()->getCurrentScene()->getSceneManager()->createParticleSystem(str, it->first);
		node->_particleSystem = _particleManager->createParticleSystem(str, name, _sceneManager);

		// Lo enlazamos al nodo de escena padre
		_entitySceneNode->attachObject(node->_particleSystem);

		// Establecemos su tiempo de vida
		node->_timeToLife = it->second;

		// Finalmente añadimos el nodo a la lista
		_particleSystemList.push_back(node);

		// Preparamos y mostramos el SP
		node->_particleSystem->prepare();
		node->_particleSystem->start();

	
		return true;
	}

	//------------------------------------------

	bool ParticleSystem::releaseParticleSystem(TNode * & node)
	{
		if (node->_particleSystem)
		{
			// Paramos el SP
			node->_particleSystem->stop();

			// Desenlazamos el sistema de partículas del nodo de escena padre
			Ogre::SceneNode * sceneNode = node->_particleSystem->getParentSceneNode();
			if(sceneNode) sceneNode->detachObject(node->_particleSystem);

			// Liberamos el sistema de partículas
			//Core::GraphicsManager::GetInstance()->getCurrentScene()->getSceneManager()->destroyParticleSystem(node->_particleSystem);
			_particleManager->destroyParticleSystem(node->_particleSystem, _sceneManager);
			node->_particleSystem = 0;

			// Borramos el nodo
			delete node;
			node = 0;

			return true;
		}
		return false;
	}
}
