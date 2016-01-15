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

#ifndef __CORE_SCENE_H__
#define __CORE_SCENE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <OgreColourValue.h>

#include "Core/Math.h"
#include "Core/Types/GraphicsTypes.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class Root;
	class Viewport;
	class SceneNode;
	class SceneManager;
	class StaticGeometry;
	class TerrainGroup;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Camera;
	class GenericGraphicEntity;
	class GraphicEntity;
	class AnimatedEntity;
	class ImmutableEntity;
	class GraphicNodeEntity;
	class GraphicsManager;

	/**
	 * Esta clase representa una escena gráfica que poder mostrar con el motor. Conceptualmente esta es la
	 * vista del mundo y del mismo modo tendrá que haber una representación lógica del mundo. Las escenas
	 * se pueden usar para mostrar la representación gráfica de los niveles del juego, entre otras cosas.
	 * @remarks La clase está diseñada para tener un solo viewport de la escena, para tener más de uno
	 *          y hacer representaciones más complejas en pantalla, hay que cambiar la implementación.
	 * @remarks Solo el gestor del motor gráfico puede crear y destruir escenas.
	 */
	class Scene {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nombre de la escena.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene el gestor Ogre de la escena.
		 */
		inline Ogre::SceneManager * getSceneManager() { return _sceneManager; }

		/**
		 * Obtiene el nodo raíz de la escena de Ogre.
		 */
		Ogre::SceneNode * getRootSceneNode();

		/**
		 * Obtiene el viewport de la escena.
		 */
		inline Ogre::Viewport * getViewport() { return _viewport; }

		/**
		 * Obtiene el color de fondo del viewport de la escena.
		 */
		Ogre::ColourValue getBackgroundColour() const;

		/**
		 * Modifica el color de fondo del viewport de la escena.
		 */
		void setBackgroundColour(const Ogre::ColourValue & value);

		/**
		 * Obtiene la cámara de la escena (asociada al viewport).
		 */
		inline Camera * getCamera() { return _camera; }

		/**
		 * Obtiene el controlador del terreno en la escena.
		 */
		inline Ogre::TerrainGroup * getTerrain() { return _terrain; }

		/**
		 * Modifica el controlador del terreno en la escena.
		 */
		inline void setTerrain(Ogre::TerrainGroup * value) { _terrain = value; }

		/**
		 * Obtiene el gestor de la geometría inmutable de la escena.
		 */
		inline Ogre::StaticGeometry * getImmutableGeometry() { return _immutableGeometry; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade una entidad gráfica a la escena.
		 * @param entity La entidad gráfica que se quiere añadir a la escena.
		 * @param father El nodo padre al que puede pertenecer la entidad.
		 * @return Devuelve true si la entidad es añadida y cargada correctamente.
		 * @remarks La escena no es responsable de destruir la entidad.
		*/
		bool addEntity(GenericGraphicEntity * entity, GraphicNodeEntity * father = 0);

		/**
		 * Elimina una entidad gráfica de la escena.
		 * @param entity La entidad gráfica que se quiere eliminar de la escena.
		 * @remarks Este método no destruye a la entidad, tan solo dejará de ser parte de la escena.
		 */
		void removeEntity(GenericGraphicEntity * entity);

		/**
		 * Muestra un skybox.
		 * @param enable Flag para activar o no el skybox.
		 * @param material El material del skybox.
		 * @param distance La distancia que hay entre la cámara y los planos del skybox.
		 * @param paintBefore Flag para indicar si pintar primero el skybox sin modificar el buffer de profundidad.
		 */
		void showSkyBox(bool enable, const std::string & material, float distance, bool paintBefore);

		/**
		 * Mueve el terreno de posición.
		 * @param offset El vector que indica cuanto se debe mover y en qué dirección.
		 */
		void moveTerrain(const Vector3 & offset);

		//----------------------------------------------------------------------------------------------------
		// Operadores
		//----------------------------------------------------------------------------------------------------

		GenericGraphicEntity * operator [](const std::string & index);

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre de la escena.
		 */
		std::string _name;

		/**
		 * El gestor Ogre de la aplicación.
		 */
		Ogre::Root * _root;

		/**
		 * El gestor Ogre de la escena.
		 */
		Ogre::SceneManager * _sceneManager;

		/**
		 * El viewport de la escena.
		 */
		Ogre::Viewport * _viewport;

		/**
		 * El color de fondo del viewport de la escena.
		 */
		Ogre::ColourValue _backgroundColour;

		/**
		 * La cámara de la escena (asociada al viewport).
		 */
		Camera * _camera;

		/**
		 * El controlador del terreno en la escena.
		 */
		Ogre::TerrainGroup * _terrain;

		/**
		 * La lista de entidades de la escena.
		 */
		GenericGraphicEntityTable _entities;

		/**
		 * La lista de entidades de la escena que requieren ser actualizadas.
		 */
		GenericGraphicEntityList _updateableEntities;

		/**
		 * El gestor de la geometría inmutable de la escena.
		 */
		Ogre::StaticGeometry * _immutableGeometry;

		/**
		 * La lista de entidades inmutables de la escena.
		 */
		ImmutableEntityList _immutableEntities;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Activa la escena y crea un viewport que ocupe toda la pantalla.
		 */
		void activate();

		/**
		 * Desactiva la escena y destruye su viewport para no seguir reenderizándolo.
		 */
		void deactivate();

		/**
		 * Actualiza el estado de la escena, actualizando a su vez a todas las entidades gráficas.
		 * @param lastInterval El tiempo total en segundos del último intervalo entre frame y frame.
		 */
		void update(float lastInterval);

		/**
		 * Añade las entidades inmutable a la geometría "estática" del nivel y la construye. Esta geometría
		 * inmutable una vez es construida, no se vuelve a construir.
		 * @remarks Una vez construida la geometría estática no se podrá modificar los valores de las entidades.
		 */
		void buildImmutableGeometry();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la escena.
		 */
		Scene(const std::string & name);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Scene();

		friend class Core::GraphicsManager;
	};
}

#endif
