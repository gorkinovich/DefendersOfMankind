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

#ifndef __LOGIC_RESEARCHINFO_H__
#define __LOGIC_RESEARCHINFO_H__

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
	 * Esta clase representa los datos relativos al área de investigación del juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class ResearchInfo {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Esta estructura representa los datos relativos a una investigación.
		 */
		typedef struct {
			/** El nombre de la investigación. */
			std::string name;
			/** La descripción de la investigación. */
			std::string description;
			/** El coste de la investigación. */
			unsigned int cost;
			/** El flag que indica si ha sido comprada o no. */
			bool buyed;
		} AreaResearchInfo;

		/**
		 * Este tipo representa un vector de investigaciones.
		 */
		typedef std::vector<AreaResearchInfo> AreaResearchInfoVector;

		/**
		 * Esta estructura representa un área de investigación.
		 */
		typedef struct {
			/** El nombre del área de investigación. */
			std::string name;
			/** La rama izquierda del área de investigación. */
			AreaResearchInfoVector left;
			/** La rama central del área de investigación. */
			AreaResearchInfoVector middle;
			/** La rama derecha del área de investigación. */
			AreaResearchInfoVector right;
		} AreaInfo;

		/**
		 * Este tipo representa una tabla con las áreas de investigación.
		 */
		typedef std::map<std::string, AreaInfo> AreaInfoTable;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el inicio de la secuencia de áreas de investigación.
		 */
		inline AreaInfoTable::iterator getAreasBegin() { return _areas.begin(); }

		/**
		 * Obtiene el inicio de la secuencia de áreas de investigación.
		 */
		inline AreaInfoTable::iterator getAreasEnd() { return _areas.end(); }

		/**
		 * Obtiene el número de áreas de investigación.
		 */
		inline unsigned int getAreasCount() const { return _areas.size(); }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si existe el área indicada por el usuario.
		 * @param name El nombre del área de investigación.
		 * @return Devuelve true cuando encuentra el área.
		 */
		bool containsArea(const std::string & name);

		/**
		 * Busca un área indicada por el usuario.
		 * @param name El nombre del área de investigación.
		 * @return Devuelve la referencia al área o una excepción si no la encuentra.
		 */
		AreaInfo & findArea(const std::string & name);

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Las áreas de investigación.
		 */
		AreaInfoTable _areas;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

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
		ResearchInfo();

		/**
		 * Destructor del objeto.
		 */
		virtual ~ResearchInfo();

		friend class Logic::GameManager;
	};
}

#endif
