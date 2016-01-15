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

#ifndef __CORE_XMLSCENELOADER_H__
#define __CORE_XMLSCENELOADER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <rapidxml.hpp>

#include "Core/Math.h"
#include "Core/Types/DataTypes.h"
#include "Core/Types/EntitiesTypes.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
    class SceneManager;
    class SceneNode;
    class Entity;
	class Log;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntityInfoTableNames;
	class GraphicNodeEntity;
	class EntityInfoTable;
	class LoadingObserver;
	class Scene;

	/**
	 * Esta clase representa al cargador de una escena almacenada en un fichero.
	 */
	class XmlSceneLoader {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Carga e interpreta el contenido de un fichero que describe una escena.
		 * @param fileName El nombre del fichero con la escena.
		 * @param scene La escena gráfica.
		 * @param fatherNode El nodo padre donde va a ir la escena.
		 * @param nodePraefixus El prefijo para los nombres de las entidades gráficas.
		 * @return Devuelve true si se consigue cargar la información con éxito.
		 */
		bool parse(const std::string & fileName, Scene * scene,
			GraphicNodeEntity * fatherNode = 0, const std::string & nodePraefixus = "");

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param entities La lista de descriptores de entidades.
		 * @param attributeNames Los nombres de los atributos en la tabla descriptora de entidades.
		 */
		XmlSceneLoader(EntityInfoTableList * entities, const EntityInfoTableNames * attributeNames);

		/**
		 * Destructor del objeto.
		 */
		virtual ~XmlSceneLoader();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La lista de descriptores de entidades.
		 */
		EntityInfoTableList * _entities;

		/**
		 * Los nombres de los atributos en la tabla descriptora de entidades.
		 */
		const EntityInfoTableNames * _attributeNames;

		/**
		 * El gestor del log de la aplicación.
		 */
		Ogre::Log * _log;

		/**
		 * El gestor de la escena.
		 */
		Ogre::SceneManager * _sceneManager;

		/**
		 * La escena gráfica.
		 */
		Scene * _scene;

		/**
		 * El nodo padre donde va a ir la escena.
		 */
		GraphicNodeEntity * _fatherNode;

		/**
		 * El prefijo para los nombres de las entidades gráficas.
		 */
		std::string _nodePraefixus;

		/**
		 * El nombre del grupo de recursos del fichero que se está cargando.
		 */
		std::string _fileGroupName;

		/**
		 * El descriptor de entidad en proceso de ser creado.
		 */
		Core::EntityInfoTable * _entityInProgress;

		/**
		 * La posición del último nodo procesado.
		 */
		Vector3 _lastNodePosition;

		/**
		 * La orientación del último nodo procesado.
		 */
		Quaternion _lastNodeOrientation;

		/**
		 * La escala del último nodo procesado.
		 */
		Vector3 _lastNodeScale;

		/**
		 * El gestor para observar un proceso de carga.
		 */
		LoadingObserver * _loadingObserver;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Procesa el nodo "scene" dentro del documento xml. Como curiosidad este nodo es la raíz del xml.
		 * @param rootNode El nodo raíz del documento.
		 */
		void processScene(rapidxml::xml_node<> * rootNode);

		/**
		 * Configura el gestor para observar un proceso de carga.
		 * @param xmlNode El nodo actual.
		 */
		void configureLoadingObserver(rapidxml::xml_node<> * rootNode);


		/**
		 * Procesa un nodo "environment" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processEnvironment(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "nodes" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processNodes(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "terrain" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processTerrain(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "terrainPage" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processTerrainPage(rapidxml::xml_node<> * xmlNode);


		/**
		 * Procesa un nodo "sceneManager" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processSceneManager(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "skyBox" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processSkyBox(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "skyDome" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processSkyDome(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "skyPlane" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processSkyPlane(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "fog" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processFog(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "clipping" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processClipping(rapidxml::xml_node<> * xmlNode);

		/**
		 * Procesa un nodo "viewport" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processViewport(rapidxml::xml_node<> * xmlNode);


		/**
		 * Procesa un nodo "lookTarget" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processLookTarget(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent);

		/**
		 * Procesa un nodo "trackTarget" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processTrackTarget(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent);

		/**
		 * Procesa un nodo "camera" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processCamera(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "light" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processLight(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "entity" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processEntity(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "particleSystem" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processParticleSystem(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "billboardSet" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processBillboardSet(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "plane" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processPlane(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "node" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processNode(rapidxml::xml_node<> * xmlNode, GraphicNodeEntity * parent = 0);

		/**
		 * Procesa un nodo "lightRange" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processLightRange(rapidxml::xml_node<> * xmlNode, Ogre::Light * light = 0);

		/**
		 * Procesa un nodo "lightAttenuation" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
		void processLightAttenuation(rapidxml::xml_node<> * xmlNode, Ogre::Light * light = 0);

		/**
		 * Procesa un nodo "userData" dentro del documento xml.
		 * @param xmlNode El nodo actual.
		 */
        void processUserData(rapidxml::xml_node<> * xmlNode);


		/**
		 * Empieza la definición de un descriptor.
		 * @param name El nombre de la entidad.
		 */
		inline void beginEntityInProgress(const std::string & name);

		/**
		 * Empieza la definición de un descriptor.
		 * @param name El nombre de la entidad.
		 * @param type El tipo de la entidad.
		 */
		inline void beginEntityInProgress(const std::string & name, const std::string & type);

		/**
		 * Termina la definición de un descriptor.
		 */
		inline void endEntityInProgress();

		/**
		 * Comprueba si existe un componente en el descriptor y sino lo añade.
		 * @param componentName El nombre del componente.
		 */
		inline bool checkOrCreateComponent(const std::string & componentName);

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param entityAttribute El nombre del atributo de la entidad.
		 * @param xmlNode El nodo actual.
		 * @param nodeAttribute El nombre del atributo del nodo.
		 * @param defaultValue El valor por defecto.
		 */
		inline void setAttribute(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
			const std::string & nodeAttribute, const std::string & defaultValue = "");

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param entityAttribute El nombre del atributo de la entidad.
		 * @param xmlNode El nodo actual.
		 * @param nodeAttribute El nombre del atributo del nodo.
		 * @param defaultValue El valor por defecto.
		 */
		inline void setAttributeAsFloat(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
			const std::string & nodeAttribute, float defaultValue = 0.0f);

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param entityAttribute El nombre del atributo de la entidad.
		 * @param xmlNode El nodo actual.
		 * @param nodeAttribute El nombre del atributo del nodo.
		 * @param defaultValue El valor por defecto.
		 */
		inline void setAttributeAsInteger(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
			const std::string & nodeAttribute, int defaultValue = 0);

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param entityAttribute El nombre del atributo de la entidad.
		 * @param xmlNode El nodo actual.
		 * @param nodeAttribute El nombre del atributo del nodo.
		 * @param defaultValue El valor por defecto.
		 */
		inline void setAttributeAsBool(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode,
			const std::string & nodeAttribute, bool defaultValue = false);

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param entityAttribute El nombre del atributo de la entidad.
		 * @param xmlNode El nodo actual.
		 */
		inline void setAttributeAsVector3(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode);

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param entityAttribute El nombre del atributo de la entidad.
		 * @param xmlNode El nodo actual.
		 */
		inline void setAttributeAsColourValue(const std::string & entityAttribute, rapidxml::xml_node<> * xmlNode);
	};
}

#endif
