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

#ifndef __CORE_GENERICGRAPHICENTITY_H__
#define __CORE_GENERICGRAPHICENTITY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Core/Math.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class SceneNode;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;
	class GraphicNodeEntity;

	/**
	 * Esta clase abstracta representa una entidad gráfica genérica dentro de una escena.
	 */
	class GenericGraphicEntity {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * Sufijo que llevan los nombres de los nodos de escena creados para Ogre.
		 */
		static const std::string NodeSuffixus;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el nodo de escena de la entidad.
		 */
		inline Ogre::SceneNode * getSceneNode() { return _entityNode; }

		/**
		 * Obtiene el nodo padre al que puede pertenecer la entidad.
		 */
		inline GraphicNodeEntity * getFather() { return _father; }

		/**
		 * Obtiene el nombre de la entidad.
		 */
		inline const std::string & getName() const { return _name; }

		/**
		 * Obtiene el nombre completo de la entidad.
		 */
		inline const std::string & getFullName() const { return _fullName; }

		/**
		 * Modifica la transformación de la entidad.
		 */
		void setTransform(const Matrix4 & value);

		/**
		 * Obtiene la posición de la entidad.
		 */
		const Vector3 & getPosition() const;

		/**
		 * Modifica la posición de la entidad.
		 */
		void setPosition(const Vector3 & value);

		/**
		 * Obtiene la orientación de la entidad.
		 */
		const Quaternion & getOrientation() const;

		/**
		 * Modifica la orientación de la entidad.
		 */
		void setOrientation(const Quaternion & value);

		/**
		 * Modifica la orientación de la entidad.
		 */
		void setOrientation(const Matrix3 & value);

		/**
		 * Obtiene la escala de la entidad.
		 */
		const Vector3 & getScale() const;

		/**
		 * Modifica la escala de la entidad.
		 */
		void setScale(const Vector3 & value);

		/**
		 * Modifica la escala de la entidad.
		 */
		void setScale(float value);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 */
		GenericGraphicEntity(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 * @remark El constructor copia crea una copia nueva, los punteros del objeto origen se conservan,
		 *         con lo que existe el peligro de borrar el original sin que la copia se entere.
		 */
		GenericGraphicEntity(const GenericGraphicEntity & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~GenericGraphicEntity();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El nombre de la entidad.
		 */
		std::string _name;

		/**
		 * El nombre de la entidad.
		 */
		std::string _fullName;

		/**
		 * El nodo de escena de la entidad.
		 */
		Ogre::SceneNode * _entityNode;

		/**
		 * La escena a la que pertenece la entidad.
		 */
		Scene * _scene;

		/**
		 * El nodo padre al que puede pertenecer la entidad.
		 */
		GraphicNodeEntity * _father;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade la entidad a una escena. Si la entidad no está cargada se fuerza su carga.
		 * @param scene La escena a la que se quiere añadir la entidad.
		 * @param father El nodo padre al que puede pertenecer la entidad.
		 * @return Devuelve true si se logra cargar y añadir la entidad a la escena.
		 */
		virtual bool attachToScene(Scene * scene, GraphicNodeEntity * father = 0);

		/**
		 * Quita la entidad de la escena en la que se encuentra cargada.
		 * @return Devuelve true si se logra descargar y quitar la entidad de la escena. Si la no estaba
		 *         cargada se devuelve false como respuesta.
		 */
		virtual bool deattachFromScene();

		/**
		 * Actualiza el estado interno de la entidad.
		 * @param lastInterval El tiempo total en segundos del último intervalo entre frame y frame.
		 */
		virtual void update(float lastInterval);

		friend class Core::GraphicNodeEntity;
		friend class Core::Scene;
	};
}

#endif
