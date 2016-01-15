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
#include <exception>
#include <OgreConfigFile.h>
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreResourceBackgroundQueue.h>

#include "Core/Resources/ResourcesManager.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define RESOURCES_CFG "resources.cfg"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// ResourcesManagerListener
	//********************************************************************************************************

	/**
	 * Esta clase representa al encargado de recibir los eventos de la carga de recursos.
	 */
	class ResourcesManagerListener : public Ogre::ResourceBackgroundQueue::Listener {
	public:
		/**
		 * Recibe la información sobre una operación completada.
		 * @param ticket El identificador de la operación.
		 * @param result El resultado de la operación.
		 */
		virtual void operationCompleted(Ogre::BackgroundProcessTicket ticket, const Ogre::BackgroundProcessResult & result) {
		}
	};

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	ResourcesManager * ResourcesManager::_instance = new ResourcesManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ResourcesManager::initialize() {
		// Obtenemos punteros a los singletones de Ogre, para poder trabajar con ellos más adelante.
		_resourceGroupManager = Ogre::ResourceGroupManager::getSingletonPtr();
		_resourceBackgroundQueue = Ogre::ResourceBackgroundQueue::getSingletonPtr();
		// Cargamos las rutas indicadas en el fichero de configuración para la localización de recursos.
		loadLocations();
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::release() {
	}

	//--------------------------------------------------------------------------------------------------------
	
	void ResourcesManager::createGroup(const std::string & groupName, bool inGlobalPool) {
		assert(_resourceGroupManager && "ResourcesManager::createGroup -> The resource group manager has not been created...");
		_resourceGroupManager->createResourceGroup(groupName, inGlobalPool);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::removeGroup(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::removeGroup -> The resource group manager has not been created...");
		_resourceGroupManager->destroyResourceGroup(groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::clearGroup(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::clearGroup -> The resource group manager has not been created...");
		_resourceGroupManager->clearResourceGroup(groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::initialiseGroup(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::initialiseGroup -> The resource group manager has not been created...");
		_resourceGroupManager->initialiseResourceGroup(groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::initialiseAllGroups() {
		assert(_resourceGroupManager && "ResourcesManager::initialiseAllGroups -> The resource group manager has not been created...");
		_resourceGroupManager->initialiseAllResourceGroups();
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::loadGroup(const std::string & groupName, bool loadMainResources, bool loadWorldGeom) {
		assert(_resourceGroupManager && "ResourcesManager::loadGroup -> The resource group manager has not been created...");
		_resourceGroupManager->loadResourceGroup(groupName, loadMainResources, loadWorldGeom);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::unloadGroup(const std::string & groupName, bool reloadableOnly) {
		assert(_resourceGroupManager && "ResourcesManager::unloadGroup -> The resource group manager has not been created...");
		_resourceGroupManager->unloadResourceGroup(groupName, reloadableOnly);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::isGroupInitialised(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::isGroupInitialised -> The resource group manager has not been created...");
		return _resourceGroupManager->isResourceGroupInitialised(groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::isGroupLoaded(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::isGroupLoaded -> The resource group manager has not been created...");
		return _resourceGroupManager->isResourceGroupLoaded(groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::groupExists(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::groupExists -> The resource group manager has not been created...");
		return _resourceGroupManager->resourceGroupExists(groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::addLocation(const std::string & path, const std::string & pathType) {
		assert(_resourceGroupManager && "ResourcesManager::addLocation -> The resource group manager has not been created...");
		_resourceGroupManager->addResourceLocation(path, pathType);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::addLocation(const std::string & path, const std::string & pathType, const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::addLocation -> The resource group manager has not been created...");
		_resourceGroupManager->addResourceLocation(path, pathType, groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::removeLocation(const std::string & path) {
		assert(_resourceGroupManager && "ResourcesManager::removeLocation -> The resource group manager has not been created...");
		_resourceGroupManager->removeResourceLocation(path);
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::removeLocation(const std::string & path, const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::removeLocation -> The resource group manager has not been created...");
		_resourceGroupManager->removeResourceLocation(path, groupName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::fileExists(const std::string & fileName) {
		assert(_resourceGroupManager && "ResourcesManager::fileExists -> The resource group manager has not been created...");
		return _resourceGroupManager->resourceExistsInAnyGroup(fileName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::fileExists(const std::string & fileName, const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::fileExists -> The resource group manager has not been created...");
		return _resourceGroupManager->resourceExists(groupName, fileName);
	}

	//--------------------------------------------------------------------------------------------------------

	std::vector<std::string> ResourcesManager::listResources(const std::string & groupName, bool showDirs) {
		assert(_resourceGroupManager && "ResourcesManager::listResources -> The resource group manager has not been created...");
		Ogre::StringVectorPtr lrlPtr = _resourceGroupManager->listResourceNames(groupName, showDirs);
		Ogre::StringVector & lrl = *lrlPtr;
		return std::vector<std::string>(lrl.begin(), lrl.end());
	}

	//--------------------------------------------------------------------------------------------------------

	std::vector<std::string> ResourcesManager::listLocations(const std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::listLocations -> The resource group manager has not been created...");
		Ogre::StringVectorPtr lrlPtr = _resourceGroupManager->listResourceLocations(groupName);
		Ogre::StringVector & lrl = *lrlPtr;
		return std::vector<std::string>(lrl.begin(), lrl.end());
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::getGroupName(const std::string & fileName, std::string & groupName) {
		assert(_resourceGroupManager && "ResourcesManager::getGroupName -> The resource group manager has not been created...");
		// Comprobamos que exista el fichero en algún grupo.
		if(_resourceGroupManager->resourceExistsInAnyGroup(fileName)) {
			// Si existe, buscamos el nombre del grupo que estamos buscando.
			groupName = _resourceGroupManager->findGroupContainingResource(fileName);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool ResourcesManager::getFullPath(const std::string & fileName, std::string & fullPath) {
		assert(_resourceGroupManager && "ResourcesManager::fileExists -> The resource group manager has not been created...");
		// Comprobamos que exista el fichero en algún grupo.
		if(_resourceGroupManager->resourceExistsInAnyGroup(fileName)) {
			// Si existe, buscamos el nombre del grupo.
			std::string groupName = _resourceGroupManager->findGroupContainingResource(fileName);
			// Entonces buscamos el fichero dentro del grupo, sin buscar recursivamente en los directorios.
			Ogre::FileInfoListPtr list = _resourceGroupManager->findResourceFileInfo(groupName, fileName);
			if(list->size() > 0) {
				// Si se ha encontrado algo, se toma los diferentes fragmentos de la ruta, se pegan y se devuelve.
				Ogre::FileInfo & info = *(list->begin());
				fullPath = info.archive->getName() + std::string("/") + info.path + fileName;
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::loadMeshFile(const std::string & fileName) {
		std::string groupName;
		// Buscamos el grupo del fichero que queremos cargar.
		if(getGroupName(fileName, groupName)) {
			// Y tras encontrarlo cargamos el fichero con su gestor específico.
			Ogre::MeshManager::getSingleton().load(fileName, groupName);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::loadLocations() {
		assert(_resourceGroupManager && "ResourcesManager::loadLocations -> The resource group manager has not been created...");
		// Cargamos las rutas indicadas en el fichero de configuración para la localización de recursos.
		Ogre::ConfigFile configFile;
		configFile.load(RESOURCES_CFG);
		// Echamos un ojo a todos los grupos dentro del archivo y los vamos añadiendo.
		Ogre::ConfigFile::SectionIterator section = configFile.getSectionIterator();
		std::string groupName, pathType, path;
		while(section.hasMoreElements()) {
			groupName = section.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap * paths = section.getNext();
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i = paths->begin();
			while(i != paths->end()) {
				pathType = i->first;
				path = i->second;
				_resourceGroupManager->addResourceLocation(path, pathType, groupName);
				++i;
			}
		}
	}

	//********************************************************************************************************
	// Métodos experimentales del gestor de carga de recursos en el background
	//********************************************************************************************************

	void ResourcesManager::backgroundInitialiseGroup(const std::string & groupName) {
		// NOTA: Este método está sin completar dada la falta de documentación clara en Ogre sobre la
		//       carga de recursos en segundo plano, así que no se debe usar esta función de momento.
		assert(_resourceBackgroundQueue && "ResourcesManager:: -> The resource background queue has not been created...");
		Ogre::BackgroundProcessTicket ticket = _resourceBackgroundQueue->initialiseResourceGroup(groupName, _listener);
		throw std::exception("ResourcesManager::backgroundInitialiseGroup => Method not implemented...");
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::backgroundInitialiseAllGroups() {
		// NOTA: Este método está sin completar dada la falta de documentación clara en Ogre sobre la
		//       carga de recursos en segundo plano, así que no se debe usar esta función de momento.
		assert(_resourceBackgroundQueue && "ResourcesManager:: -> The resource background queue has not been created...");
		Ogre::BackgroundProcessTicket ticket = _resourceBackgroundQueue->initialiseAllResourceGroups(_listener);
		throw std::exception("ResourcesManager::backgroundInitialiseAllGroups => Method not implemented...");
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::backgroundPrepareGroup(const std::string & groupName) {
		// NOTA: Este método está sin completar dada la falta de documentación clara en Ogre sobre la
		//       carga de recursos en segundo plano, así que no se debe usar esta función de momento.
		assert(_resourceBackgroundQueue && "ResourcesManager:: -> The resource background queue has not been created...");
		Ogre::BackgroundProcessTicket ticket = _resourceBackgroundQueue->prepareResourceGroup(groupName, _listener);
		throw std::exception("ResourcesManager::backgroundPrepareGroup => Method not implemented...");
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::backgroundLoadGroup(const std::string & groupName) {
		// NOTA: Este método está sin completar dada la falta de documentación clara en Ogre sobre la
		//       carga de recursos en segundo plano, así que no se debe usar esta función de momento.
		assert(_resourceBackgroundQueue && "ResourcesManager:: -> The resource background queue has not been created...");
		Ogre::BackgroundProcessTicket ticket = _resourceBackgroundQueue->loadResourceGroup(groupName, _listener);
		throw std::exception("ResourcesManager::backgroundLoadGroup => Method not implemented...");
	}

	//--------------------------------------------------------------------------------------------------------

	void ResourcesManager::backgroundUnloadGroup(const std::string & groupName) {
		// NOTA: Este método está sin completar dada la falta de documentación clara en Ogre sobre la
		//       carga de recursos en segundo plano, así que no se debe usar esta función de momento.
		assert(_resourceBackgroundQueue && "ResourcesManager:: -> The resource background queue has not been created...");
		Ogre::BackgroundProcessTicket ticket = _resourceBackgroundQueue->unloadResourceGroup(groupName, _listener);
		throw std::exception("ResourcesManager::backgroundUnloadGroup => Method not implemented...");
	}
}
