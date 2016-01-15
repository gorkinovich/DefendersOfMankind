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

#ifndef __CORE_GRAPHICNODEENTITY_H__
#define __CORE_GRAPHICNODEENTITY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Types/GraphicsTypes.h"
#include "Core/Graphics/GenericGraphicEntity.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;

	/**
	 * Esta clase representa un nodo dentro del grafo de la escena para contener otras entidades.
	 */
	class GraphicNodeEntity : public GenericGraphicEntity {
	public:
		//----------------------------------------------------------------------------------------------------
		// Constantes
		//----------------------------------------------------------------------------------------------------

		/**
		 * El separador que llevan los nombres de los nodos de escena creados para Ogre.
		 */
		static const std::string NodeSeparator;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el número de nodos hijos.
		 */
		inline unsigned int getNumberOfChildren() const { return _children.size(); }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 */
		GraphicNodeEntity(const std::string & name);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 * @remark El constructor copia crea una copia nueva, los punteros del objeto origen se conservan,
		 *         con lo que existe el peligro de borrar el original sin que la copia se entere.
		 */
		GraphicNodeEntity(const GraphicNodeEntity & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~GraphicNodeEntity();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La lista de nodos hijos.
		 */
		GenericGraphicEntityList _children;

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

		friend class Core::GenericGraphicEntity;
		friend class Core::Scene;
	};
}

#endif
