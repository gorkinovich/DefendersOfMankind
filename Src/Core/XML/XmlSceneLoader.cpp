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
#include <OgreLog.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreColourValue.h>
#include <OgreSceneManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreTerrainMaterialGeneratorA.h>

#include "Core/XML/XmlSceneLoader.h"
#include "Core/XML/XmlNodeUtil.h"
#include "Core/XML/EntityInfoTableNames.h"
#include "Core/XML/TypeOfLights.h"
#include "Core/Entities/LoadingSections.h"
#include "Core/Graphics/Scene.h"
#include "Core/Graphics/Camera.h"
#include "Core/Graphics/TerrainManager.h"
#include "Core/Graphics/LightEntity.h"
#include "Core/Graphics/AnimatedEntity.h"
#include "Core/Graphics/ImmutableEntity.h"
#include "Core/Graphics/GraphicNodeEntity.h"
#include "Core/Resources/LoadingObserver.h"
#include "Core/Resources/ResourcesManager.h"
#include "Core/Data/EntityInfoTable.h"
#include "Core/Data/ComponentInfoTable.h"
#include "Core/BaseManager.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define XML_ENV_BASE_FACTOR     9
#define XML_NODES_BASE_FACTOR   1
#define XML_TERRAIN_BASE_FACTOR 2

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool XmlSceneLoader::parse(const std::string & fileName, Scene * scene,
	GraphicNodeEntity * fatherNode, const std::string & nodePraefixus) {
		ResourcesManager * resourcesManager = ResourcesManager::GetInstance();
		// Primero intentamos obtener el grupo en el que está el fichero que queremos cargar.
		if(resourcesManager->getGroupName(fileName, _fileGroupName)) {
			// Configuramos las variables globales al proceso de carga.
			_log = BaseManager::GetInstance()->getOgreLog();
			_scene = scene;
			_sceneManager = _scene->getSceneManager();
			_fatherNode = fatherNode;
			_nodePraefixus = nodePraefixus;
			_entityInProgress = 0;

			// Creamos y cargamos el documento xml a través del gestor de recursos de Ogre.
			rapidxml::xml_document<> document;
			Ogre::DataStreamPtr stream = resourcesManager->getResourceGroupManager()->openResource(fileName, _fileGroupName);
			char * streamData = strdup(stream->getAsString().c_str());
			document.parse<0>(streamData);

			// Pedimos el nodo raíz del documento.
			rapidxml::xml_node<> * rootNode = document.first_node("scene");

			// Hacemos una pequeña comprobación para validar que el fichero es del tipo correcto.
			if(XmlNodeGetAttribute(rootNode, "formatVersion", "") == "") {
				_log->logMessage("XmlSceneLoader::parse -> Invalid .scene file...");
				delete streamData;
				return false;
			}

			// Configuramos el proceso de carga.
			configureLoadingObserver(rootNode);

			// Mandamos procesar el nodo raíz del documento.
			processScene(rootNode);

			// Finalmente borramos la copia que hicimos del fichero de texto y salimos del método.
			delete streamData;
			return true;

		} else {
			_sceneManager = 0;
			_scene = 0;
			_fatherNode = 0;
			_nodePraefixus = "";
			_fileGroupName = "";
			_entityInProgress = 0;
			_loadingObserver = 0;
			return false;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::configureLoadingObserver(rapidxml::xml_node<> * rootNode) {
		// Definimos las variables auxiliares para poder configurar del gestor del proceso de carga.
		unsigned int nodeOps = 0;
		unsigned int terrainOps = 0;
		rapidxml::xml_node<> * element = 0;

		// Contabilizamos el número de operaciones en la sección de nodos.
		element = rootNode->first_node("nodes");
		if(element) {
			element = element->first_node("node");
			while(element) {
				++nodeOps;
				element = element->next_sibling("node");
			}
		}

		// Contabilizamos el número de operaciones en la sección de terrenos.
		element = rootNode->first_node("terrain");
		if(element) {
			element = element->first_node("terrainPages");
			if(element) {
				element = element->first_node("terrainPage");
				while(element) {
					++terrainOps;
					element = element->next_sibling("terrainPage");
				}
			}
		}

		// Configuramos las secciones en el proceso de carga que tienen que ver con el XML.
		_loadingObserver = LoadingObserver::GetInstance();
		_loadingObserver->setNumberOfOperations(LOADING_SECTION_XML_ENV, XML_ENV_BASE_FACTOR);
		_loadingObserver->setNumberOfOperations(LOADING_SECTION_XML_NODES, XML_NODES_BASE_FACTOR + nodeOps);
		_loadingObserver->setNumberOfOperations(LOADING_SECTION_XML_TERRAIN, XML_TERRAIN_BASE_FACTOR + terrainOps);
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processScene(rapidxml::xml_node<> * rootNode) {
#ifdef _DEBUG
		// Registramos que estamos procesando un fichero de DotScene de la versión que sea.
		std::string version = XmlNodeGetAttribute(rootNode, "formatVersion", "unknown");
		std::string message = "Parsing DotScene file with version " + version;
		_log->logMessage(message);
#endif

		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "environment".
		element = rootNode->first_node("environment");
		if(element) processEnvironment(element);

		// Comprobamos si existe el nodo "nodes".
		element = rootNode->first_node("nodes");
		if(element) processNodes(element);

		// Comprobamos si existe el nodo "terrain".
		element = rootNode->first_node("terrain");
		if(element) processTerrain(element);
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processEnvironment(rapidxml::xml_node<> * xmlNode) {
		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "scenemanager".
		element = xmlNode->first_node("scenemanager");
		if(element) processSceneManager(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "colourAmbient".
		element = xmlNode->first_node("colourAmbient");
		if(element) {
			_sceneManager->setAmbientLight(XmlNodeParseColour(element));
			
			// Si el gestor del terreno no está inicializado, lo inicializamos.
			TerrainManager * terrainManager = TerrainManager::GetInstance();
			if(!terrainManager->isInitialized()) terrainManager->initialize();

			// Configuramos las opciones por defecto para los terrenos.
			Ogre::TerrainGlobalOptions * tgo = terrainManager->getTerrainGlobalOptions();
			tgo->setCompositeMapAmbient(_sceneManager->getAmbientLight());
		}
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "skyBox".
		element = xmlNode->first_node("skyBox");
		if(element) processSkyBox(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "skyDome".
		element = xmlNode->first_node("skyDome");
		if(element) processSkyDome(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "skyPlane".
		element = xmlNode->first_node("skyPlane");
		if(element) processSkyPlane(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "fog".
		element = xmlNode->first_node("fog");
		if(element) processFog(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "clipping".
		element = xmlNode->first_node("clipping");
		if(element) processClipping(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "viewport".
		element = xmlNode->first_node("viewport");
		if(element) processViewport(element);
		_loadingObserver->operationFinished();

		// Comprobamos si existe el nodo "camera".
		element = xmlNode->first_node("camera");
		if(element) processCamera(element);
		_loadingObserver->operationFinished();
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processNodes(rapidxml::xml_node<> * xmlNode) {
		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "position".
		element = xmlNode->first_node("position");
		if(element) {
			_fatherNode->getSceneNode()->setPosition(XmlNodeParseVector3(element));
			_fatherNode->getSceneNode()->setInitialState();
		}

		// Comprobamos si existe el nodo "rotation".
		element = xmlNode->first_node("rotation");
		if(element) {
			_fatherNode->getSceneNode()->setOrientation(XmlNodeParseQuaternion(element));
			_fatherNode->getSceneNode()->setInitialState();
		}

		// Comprobamos si existe el nodo "scale".
		element = xmlNode->first_node("scale");
		if(element) {
			_fatherNode->getSceneNode()->setScale(XmlNodeParseVector3(element));
			_fatherNode->getSceneNode()->setInitialState();
		}
		_loadingObserver->operationFinished();

		// Recorremos los nodos "node".
		element = xmlNode->first_node("node");
		while(element) {
			processNode(element);
			element = element->next_sibling("node");
			_loadingObserver->operationFinished();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processTerrain(rapidxml::xml_node<> * xmlNode) {
		// Sacamos la información de los atributos del elemento.
		Ogre::Real worldSize = XmlNodeGetAttributeAsReal(xmlNode, "worldSize");
		int mapSize = XmlNodeGetAttributeAsInteger(xmlNode, "mapSize");
		bool colourmapEnabled = XmlNodeGetAttributeAsBool(xmlNode, "colourmapEnabled");
		int colourMapTextureSize = XmlNodeGetAttributeAsInteger(xmlNode, "colourMapTextureSize");
		int compositeMapDistance = XmlNodeGetAttributeAsInteger(xmlNode, "tuningCompositeMapDistance");
		int maxPixelError = XmlNodeGetAttributeAsInteger(xmlNode, "tuningMaxPixelError");

		// Si el gestor del terreno no está inicializado, lo inicializamos.
		TerrainManager * terrainManager = TerrainManager::GetInstance();
		if(!terrainManager->isInitialized()) terrainManager->initialize();

		// Configuramos las opciones por defecto para los terrenos.
		Ogre::TerrainGlobalOptions * tgo = terrainManager->getTerrainGlobalOptions();
		tgo->setMaxPixelError((Ogre::Real)maxPixelError);
		tgo->setCompositeMapDistance((Ogre::Real)compositeMapDistance);

		// Creamos y configuramos el gestor de conjuntos de terrenos, asumiendo que los ficheros
		// de terreno están en el mismo grupo de recursos que el fichero que estamos cargando.
		terrainManager->resetTerrainGroup(_sceneManager, mapSize, worldSize);
		terrainManager->configureTerrainGroup(_fileGroupName);
		_loadingObserver->operationFinished();

		// Con estas variables almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;
		rapidxml::xml_node<> * pageElement = 0;

		// Comprobamos si existe el nodo "terrainPages".
		element = xmlNode->first_node("terrainPages");
		if(element) {
			// Recorremos los nodos "terrainPage".
			pageElement = element->first_node("terrainPage");
			while(pageElement) {
				processTerrainPage(pageElement);
				pageElement = pageElement->next_sibling("terrainPage");
				_loadingObserver->operationFinished();
			}
		}

		// Cargamos el terreno y después liberamos los ficheros temporales.
		terrainManager->loadAllTerrains();
		terrainManager->freeTemporaryResources();
		_loadingObserver->operationFinished();
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processTerrainPage(rapidxml::xml_node<> * xmlNode) {
		// Definimos un fragmento de terreno, con la información del nodo actual.
		TerrainManager::GetInstance()->defineTerrain(
			XmlNodeGetAttributeAsInteger(xmlNode, "pageX"),
			XmlNodeGetAttributeAsInteger(xmlNode, "pageY"),
			XmlNodeGetAttribute(xmlNode, "name")
		);
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processSceneManager(rapidxml::xml_node<> * xmlNode) {
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processSkyBox(rapidxml::xml_node<> * xmlNode) {
		// Comprobamos que el skybox esté activado en la escena.
		bool active = XmlNodeGetAttributeAsBool(xmlNode, "active", false);
		if(!active) return;

		// Lo siguiente es comprobar que al menos tiene un material asignado.
		std::string material = XmlNodeGetAttribute(xmlNode, "material", "");
		if(material.size() > 0) {
			// Obtenemos el resto de atributos del skybox.
			Ogre::Real distance = XmlNodeGetAttributeAsReal(xmlNode, "distance", 5000);
			bool drawFirst = XmlNodeGetAttributeAsBool(xmlNode, "drawFirst", true);

			// Con esta variable almacenaremos referencias a subnodos del actual.
			rapidxml::xml_node<> * element = 0;

			// Comprobamos si existe el nodo "rotation".
			Quaternion rotation = Quaternion::IDENTITY;
			element = xmlNode->first_node("rotation");
			if(element) rotation = XmlNodeParseQuaternion(element);

			// Y por último configuramos en el gestor de escena el skybox.
			_sceneManager->setSkyBox(true, material, distance, drawFirst, rotation, _fileGroupName);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processSkyDome(rapidxml::xml_node<> * xmlNode) {
		// Comprobamos que el skydome esté activado en la escena.
		bool active = XmlNodeGetAttributeAsBool(xmlNode, "active", false);
		if(!active) return;

		// Lo siguiente es comprobar que al menos tiene un material asignado.
		std::string material = XmlNodeGetAttribute(xmlNode, "material", "");
		if(material.size() > 0) {
			// Obtenemos el resto de atributos del skydome.
			Ogre::Real curvature = XmlNodeGetAttributeAsReal(xmlNode, "curvature", 10);
			Ogre::Real tiling = XmlNodeGetAttributeAsReal(xmlNode, "tiling", 8);
			Ogre::Real distance = XmlNodeGetAttributeAsReal(xmlNode, "distance", 4000);
			bool drawFirst = XmlNodeGetAttributeAsBool(xmlNode, "drawFirst", true);

			// Con esta variable almacenaremos referencias a subnodos del actual.
			rapidxml::xml_node<> * element = 0;

			// Comprobamos si existe el nodo "rotation".
			Quaternion rotation = Quaternion::IDENTITY;
			element = xmlNode->first_node("rotation");
			if(element) rotation = XmlNodeParseQuaternion(element);

			// Y por último configuramos en el gestor de escena el skydome.
			_sceneManager->setSkyDome(true, material, curvature, tiling, distance, drawFirst, rotation,
				16, 16, -1, _fileGroupName);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processSkyPlane(rapidxml::xml_node<> * xmlNode) {
		// Comprobamos que el skyplane tiene al menos un material asignado.
		std::string material = XmlNodeGetAttribute(xmlNode, "material", "");
		if(material.size() > 0) {
			// Obtenemos el resto de atributos del skyplane.
			Ogre::Real planeX = XmlNodeGetAttributeAsReal(xmlNode, "planeX", 0);
			Ogre::Real planeY = XmlNodeGetAttributeAsReal(xmlNode, "planeY", -1);
			Ogre::Real planeZ = XmlNodeGetAttributeAsReal(xmlNode, "planeZ", 0);
			Ogre::Real planeD = XmlNodeGetAttributeAsReal(xmlNode, "planeD", 5000);
			Ogre::Real scale = XmlNodeGetAttributeAsReal(xmlNode, "scale", 1000);
			Ogre::Real tiling = XmlNodeGetAttributeAsReal(xmlNode, "tiling", 10);
			bool drawFirst = XmlNodeGetAttributeAsBool(xmlNode, "drawFirst", true);
			Ogre::Real bow = XmlNodeGetAttributeAsReal(xmlNode, "bow", 0);

			// Configuramos un plano.
			Ogre::Plane plane;
			plane.normal = Vector3(planeX, planeY, planeZ);
			plane.d = planeD;

			// Y por último configuramos en el gestor de escena el skyplane.
			_sceneManager->setSkyPlane(true, plane, material, scale, tiling, drawFirst, bow, 1, 1, _fileGroupName);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processFog(rapidxml::xml_node<> * xmlNode) {
		// Sacamos la información de los atributos del elemento.
		Ogre::Real linearStart = XmlNodeGetAttributeAsReal(xmlNode, "start", 0.0f);
		Ogre::Real linearEnd = XmlNodeGetAttributeAsReal(xmlNode, "end", 1.0f);
		Ogre::Real expDensity = XmlNodeGetAttributeAsReal(xmlNode, "density", 0.001f);

		Ogre::FogMode mode = Ogre::FOG_NONE;
		std::string modeValue = XmlNodeGetAttribute(xmlNode, "mode");
		if(modeValue == "none")
			mode = Ogre::FOG_NONE;
		else if(modeValue == "exp")
			mode = Ogre::FOG_EXP;
		else if(modeValue == "exp2")
			mode = Ogre::FOG_EXP2;
		else if(modeValue == "linear")
			mode = Ogre::FOG_LINEAR;

		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "colour".
		Ogre::ColourValue colour = Ogre::ColourValue::White;
		element = xmlNode->first_node("colour");
		if(element) colour = XmlNodeParseColour(element);

		// Y por último configuramos en el gestor de escena la niebla.
		_sceneManager->setFog(mode, colour, expDensity, linearStart, linearEnd);
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processClipping(rapidxml::xml_node<> * xmlNode) {
		// Sacamos la información de los atributos del elemento.
		Ogre::Real nearValue = XmlNodeGetAttributeAsReal(xmlNode, "near", 0.0f);
		Ogre::Real farValue = XmlNodeGetAttributeAsReal(xmlNode, "far", 1.0f);

		// Y por último configuramos la cámara de la escena.
		_scene->getCamera()->getCamera()->setNearClipDistance(nearValue);
		_scene->getCamera()->getCamera()->setFarClipDistance(farValue);

		// Comprobamos si la tarjeta soporta renderizar con el "plano lejano" en el infinito.
		if(BaseManager::GetInstance()->isInfiniteFarPlaneSupported()) {
			// Si lo soporta configuramos el "plano lejano" para que esté en el infinito.
			_scene->getCamera()->getCamera()->setFarClipDistance(0);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processViewport(rapidxml::xml_node<> * xmlNode) {
		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "colour".
		Ogre::ColourValue colour = Ogre::ColourValue::White;
		element = xmlNode->first_node("colour");
		if(element) colour = XmlNodeParseColour(element);

		// Y por último configuramos el viewport de la escena.
		_scene->setBackgroundColour(colour);
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processLookTarget(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processTrackTarget(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processCamera(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
		// Sacamos la información de los atributos del elemento.
		std::string name = XmlNodeGetAttribute(xmlNode, "name");
		Ogre::Real fov = XmlNodeGetAttributeAsReal(xmlNode, "fov", 1.0f);
		Ogre::Real aspectRatio = XmlNodeGetAttributeAsReal(xmlNode, "aspectRatio", 1.3333f);
		std::string projectionType = XmlNodeGetAttribute(xmlNode, "projectionType", "perspective");

		// Obtenemos la cámara de la escena para configurarla.
		Camera * cameraEntity = _scene->getCamera();
		Ogre::Camera * camera = cameraEntity->getCamera();

		if(projectionType == "orthographic")
			camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
		else
			camera->setProjectionType(Ogre::PT_PERSPECTIVE);

		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "clipping".
		element = xmlNode->first_node("clipping");
		if(element) processClipping(element);

		// Comprobamos si existe el nodo "position".
		element = xmlNode->first_node("position");
		if(element) cameraEntity->setPosition(XmlNodeParseVector3(element));

		// Comprobamos si existe el nodo "rotation".
		element = xmlNode->first_node("rotation");
		if(element) cameraEntity->setOrientation(XmlNodeParseQuaternion(element));
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processLight(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
		// Tomamos el nombre de la entidad.
		std::string name = XmlNodeGetAttribute(xmlNode, "name");

		// Empieza la definición de un descriptor.
		beginEntityInProgress(name, _attributeNames->lightType);

		// Cogemos la información almacenada en los atributos.
		std::string ligthType = XmlNodeGetAttribute(xmlNode, "type", XML_LIGHT_TYPE_POINT);
		_entityInProgress->setAttribute(_attributeNames->lightTypeOfLight, ligthType);
		setAttributeAsBool(_attributeNames->lightVisible, xmlNode, "visible", true);
		setAttributeAsBool(_attributeNames->lightCastShadows, xmlNode, "castShadows", true);

		// Una pequeña comprobación para evitar que la luz no tenga algún tipo.
		if(ligthType != XML_LIGHT_TYPE_POINT && ligthType != XML_LIGHT_TYPE_DIRECTIONAL &&
			ligthType != XML_LIGHT_TYPE_SPOT && ligthType != XML_LIGHT_TYPE_RADPOINT) {
			ligthType = XML_LIGHT_TYPE_POINT;
		}

		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "position".
		element = xmlNode->first_node("position");
		if(element) setAttributeAsVector3(_attributeNames->position, element);

		// Comprobamos si existe el nodo "normal" o el nodo "directionVector".
		element = xmlNode->first_node("normal");
		if(element) setAttributeAsVector3(_attributeNames->lightDirection, element);

		element = xmlNode->first_node("directionVector");
		if(element) setAttributeAsVector3(_attributeNames->lightDirection, element);

		// Comprobamos si existe el nodo "colourDiffuse".
		element = xmlNode->first_node("colourDiffuse");
		if(element) setAttributeAsColourValue(_attributeNames->lightColourDiffuse, element);

		// Comprobamos si existe el nodo "colourSpecular".
		element = xmlNode->first_node("colourSpecular");
		if(element) setAttributeAsColourValue(_attributeNames->lightColourSpecular, element);

		if(ligthType == XML_LIGHT_TYPE_DIRECTIONAL || ligthType == XML_LIGHT_TYPE_POINT) {
			// Comprobamos si existe el nodo "lightRange".
			element = xmlNode->first_node("lightRange");
			if(element) processLightRange(element);

			// Comprobamos si existe el nodo "lightAttenuation".
			element = xmlNode->first_node("lightAttenuation");
			if(element) processLightAttenuation(element);

			// Si el gestor del terreno no está inicializado, lo inicializamos.
			TerrainManager * terrainManager = TerrainManager::GetInstance();
			if(!terrainManager->isInitialized()) terrainManager->initialize();

			// Configuramos las opciones por defecto para los terrenos.
			Ogre::TerrainGlobalOptions * tgo = terrainManager->getTerrainGlobalOptions();
			if(_entityInProgress->hasAttribute(_attributeNames->lightDirection)) {
				tgo->setLightMapDirection(
					_entityInProgress->getAttributeAsVector3(_attributeNames->lightDirection)
				);
			}
			if(_entityInProgress->hasAttribute(_attributeNames->lightColourDiffuse)) {
				tgo->setCompositeMapDiffuse(
					_entityInProgress->getAttributeAsColourValue(_attributeNames->lightColourDiffuse)
				);
			}
		}

		// Comprobamos si existe el nodo "userData".
		element = xmlNode->first_node("userData");
		if(element) processUserData(element);

		// Termina la definición de un descriptor.
		endEntityInProgress();
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processEntity(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
		// Tomamos el nombre de la entidad.
		std::string name = XmlNodeGetAttribute(xmlNode, "name");

		// Empieza la definición de un descriptor.
		beginEntityInProgress(name, _attributeNames->lightType);

		// Cogemos la información almacenada en los atributos.
		std::string meshFile = XmlNodeGetAttribute(xmlNode, "meshFile");
		if(meshFile.size() > 0) {
			_entityInProgress->setAttribute(_attributeNames->graphicMeshFile, meshFile);
			ResourcesManager::GetInstance()->loadMeshFile(meshFile);
		}

		std::string materialFile = XmlNodeGetAttribute(xmlNode, "materialFile");
		if(materialFile.size() > 0) {
			_entityInProgress->setAttribute(_attributeNames->graphicMaterialFile, materialFile);
		}

		setAttributeAsBool(_attributeNames->graphicStatic, xmlNode, "static", false);
		setAttributeAsBool(_attributeNames->graphicCastShadows, xmlNode, "castShadows", true);

		// Cogemos la información del nodo en el que se crea la entidad.
		_entityInProgress->setAttributeAsVector3(_attributeNames->position, _lastNodePosition);
		_entityInProgress->setAttributeAsQuaternion(_attributeNames->orientation, _lastNodeOrientation);
		_entityInProgress->setAttributeAsVector3(_attributeNames->scale, _lastNodeScale);

		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "userData".
		element = xmlNode->first_node("userData");
		if(element) processUserData(element);

		// Termina la definición de un descriptor.
		endEntityInProgress();
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processParticleSystem(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
		if(_entityInProgress) {
			setAttribute(_attributeNames->particleSystemName, xmlNode, "name");
			setAttribute(_attributeNames->particleSystemFile, xmlNode, "file");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processBillboardSet(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processPlane(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processNode(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent) {
		// El nodo contenedor actual de entidades gráficas, por si en el cargador hubieramos creado
		// el grafo de escena mientras interpretamos el fichero xml con la descripción de la escena.
		GraphicNodeEntity * currentNode = 0;

		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Comprobamos si existe el nodo "position".
		element = xmlNode->first_node("position");
		_lastNodePosition = element ? XmlNodeParseVector3(element) : Vector3::ZERO;

		// Comprobamos si existe el nodo "rotation".
		element = xmlNode->first_node("rotation");
		_lastNodeOrientation = element ? XmlNodeParseQuaternion(element) : Quaternion::IDENTITY;

		// Comprobamos si existe el nodo "scale".
		element = xmlNode->first_node("scale");
		_lastNodeScale = element ? XmlNodeParseVector3(element) : Vector3::UNIT_SCALE;

		// Comprobamos si existe el nodo "lookTarget".
		element = xmlNode->first_node("lookTarget");
		if(element) processLookTarget(element, currentNode);

		// Comprobamos si existe el nodo "trackTarget".
		element = xmlNode->first_node("trackTarget");
		if(element) processTrackTarget(element, currentNode);

		// Recorremos los nodos "camera".
		element = xmlNode->first_node("camera");
		while(element) {
			processCamera(element, currentNode);
			element = element->next_sibling("camera");
		}

		// Recorremos los nodos "light".
		element = xmlNode->first_node("light");
		while(element) {
		    processLight(element, currentNode);
		    element = element->next_sibling("light");
		}

		// Recorremos los nodos "entity".
		element = xmlNode->first_node("entity");
		while(element) {
			processEntity(element, currentNode);
			element = element->next_sibling("entity");
		}

		// Recorremos los nodos "particleSystem".
		element = xmlNode->first_node("particleSystem");
		while(element) {
			processParticleSystem(element, currentNode);
			element = element->next_sibling("particleSystem");
		}

		// Recorremos los nodos "billboardSet".
		element = xmlNode->first_node("billboardSet");
		while(element) {
			processBillboardSet(element, currentNode);
			element = element->next_sibling("billboardSet");
		}

		// Recorremos los nodos "plane".
		element = xmlNode->first_node("plane");
		while(element) {
			processPlane(element, currentNode);
			element = element->next_sibling("plane");
		}

		// Recorremos los nodos "node".
		element = xmlNode->first_node("node");
		while(element) {
			processNode(element, currentNode);
			element = element->next_sibling("node");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processLightRange(rapidxml::xml_node<> * xmlNode, Ogre::Light * light) {
		setAttributeAsFloat(_attributeNames->lightSpotlightRangeInner, xmlNode, "inner");
		setAttributeAsFloat(_attributeNames->lightSpotlightRangeOuter, xmlNode, "outer");
		setAttributeAsFloat(_attributeNames->lightSpotlightRangeFalloff, xmlNode, "falloff", 1.0f);
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processLightAttenuation(rapidxml::xml_node<> * xmlNode, Ogre::Light * light) {
		setAttributeAsFloat(_attributeNames->lightAttenuationRange, xmlNode, "range");
		setAttributeAsFloat(_attributeNames->lightAttenuationConstant, xmlNode, "constant");
		setAttributeAsFloat(_attributeNames->lightAttenuationLinear, xmlNode, "linear");
		setAttributeAsFloat(_attributeNames->lightAttenuationQuadratic, xmlNode, "quadratic");
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::processUserData(rapidxml::xml_node<> * xmlNode) {
		// Con esta variable almacenaremos referencias a subnodos del actual.
		rapidxml::xml_node<> * element = 0;

		// Con estas variables almacenaremos la clave y el contenido de cada propiedad de usuario.
		std::string name, data;

		// Recorremos los nodos "property".
		element = xmlNode->first_node("property");
		while(element) {
			name = XmlNodeGetAttribute(element, "name");
			data = XmlNodeGetAttribute(element, "data");
			if(name == InfoTableWithName::NameAttributeKey) {
				_entityInProgress->setName(data);
			} else if(name == EntityInfoTable::TypeAttributeKey) {
				_entityInProgress->setType(data);
			} else {
				_entityInProgress->setAttribute(name, data);
			}
			element = element->next_sibling("property");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::beginEntityInProgress(const std::string & name) {
		// Creamos el descriptor de la entidad si no hay uno ya creado.
		if(!_entityInProgress) {
			_entityInProgress = new Core::EntityInfoTable(name);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::beginEntityInProgress(const std::string & name, const std::string & type) {
		// Creamos el descriptor de la entidad si no hay uno ya creado.
		if(!_entityInProgress) {
			_entityInProgress = new Core::EntityInfoTable(name);
			_entityInProgress->setType(type);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::endEntityInProgress() {
		// Añadimos el descriptor de la entidad a la lista final si hay uno ya creado.
		if(_entityInProgress) {
			_entities->push_back(_entityInProgress);
			_entityInProgress = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool XmlSceneLoader::checkOrCreateComponent(const std::string & componentName) {
		if(!_entityInProgress->hasComponent(componentName)) {
			_entityInProgress->addComponent(componentName);
			return _entityInProgress->hasComponent(componentName);
		} else {
			return true;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::setAttribute(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
	const std::string & nodeAttribute, const std::string & defaultValue) {
		_entityInProgress->setAttribute(entityAttribute, XmlNodeGetAttribute(xmlNode, nodeAttribute, defaultValue));
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::setAttributeAsFloat(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
	const std::string & nodeAttribute, float defaultValue) {
		_entityInProgress->setAttributeAsFloat(entityAttribute, XmlNodeGetAttributeAsFloat(xmlNode, nodeAttribute, defaultValue));
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::setAttributeAsInteger(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
	const std::string & nodeAttribute, int defaultValue) {
		_entityInProgress->setAttributeAsInteger(entityAttribute, XmlNodeGetAttributeAsInteger(xmlNode, nodeAttribute, defaultValue));
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::setAttributeAsBool(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
	const std::string & nodeAttribute, bool defaultValue) {
		_entityInProgress->setAttributeAsBool(entityAttribute, XmlNodeGetAttributeAsBool(xmlNode, nodeAttribute, defaultValue));
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::setAttributeAsVector3(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode) {
		_entityInProgress->setAttributeAsVector3(entityAttribute, XmlNodeParseVector3(xmlNode));
	}

	//--------------------------------------------------------------------------------------------------------

	void XmlSceneLoader::setAttributeAsColourValue(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode) {
		_entityInProgress->setAttributeAsColourValue(entityAttribute, XmlNodeParseColour(xmlNode));
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	XmlSceneLoader::XmlSceneLoader(EntityInfoTableList * entities, const EntityInfoTableNames * attributeNames)
	: _entities(entities), _attributeNames(attributeNames), _log(0), _sceneManager(0), _fatherNode(0),
	_entityInProgress(0), _loadingObserver(0) {}

	//--------------------------------------------------------------------------------------------------------

	XmlSceneLoader::~XmlSceneLoader() {}
}
