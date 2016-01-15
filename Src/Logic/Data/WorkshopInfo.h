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

#ifndef __LOGIC_WORKSHOPINFO_H__
#define __LOGIC_WORKSHOPINFO_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <vector>
#include <string>

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class GameManager;

	/**
	 * Esta clase representa los datos relativos a la tienda del juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class WorkshopInfo {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Esta estructura representa los datos relativos a una parte de la nave.
		 */
		typedef struct {
			/** El nombre del componente. */
			std::string name;
			/** La descripción del componente. */
			std::string description;
			/** El coste del componente. */
			unsigned int cost;
			/** El flag que indica si ha sido comprado o no. */
			bool buyed;
			/** El flag que indica si está seleccionado o no. */
			bool selected;
		} ComponentInfo;

		/**
		 * Este tipo representa un vector de componentes que pueden seleccionarse para la parte de una nave.
		 */
		typedef std::vector<ComponentInfo> ComponentInfoVector;

		/**
		 * Esta estructura representa los datos relativos a una parte de la nave.
		 */
		typedef struct {
			/** El nombre de la parte de la nave. */
			std::string name;
			/** Los componentes que pueden seleccionarse para dicha parte. */
			ComponentInfoVector components;
		} PartInfo;

		/**
		 * Este tipo representa una tabla con los datos relativos a las partes de la nave.
		 */
		typedef std::map<std::string, PartInfo> PartInfoTable;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si existe la parte indicada por el usuario.
		 * @param name El nombre de la parte de la nave.
		 * @return Devuelve true cuando encuentra la parte.
		 */
		bool containsPart(const std::string & name);

		/**
		 * Busca una parte indicada por el usuario.
		 * @param name El nombre de la parte de la nave.
		 * @return Devuelve la referencia a la parte o una excepción si no la encuentra.
		 */
		PartInfo & findPart(const std::string & name);

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Los datos relativos a las partes de la nave.
		 */
		PartInfoTable _parts;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Añade una parte indicada por el usuario.
		 * @param name El nombre de la parte de la nave.
		 * @param components Los componentes que pueden seleccionarse para dicha parte.
		 */
		void addPart(const std::string & name, const ComponentInfoVector & components);

		/**
		 * Carga la información en la clase.
		 */
		void loadParts();

		/**
		 * Borra la información en la clase.
		 */
		void unloadParts();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		WorkshopInfo();

		/**
		 * Destructor del objeto.
		 */
		virtual ~WorkshopInfo();

		friend class Logic::GameManager;
	};
}

#endif
