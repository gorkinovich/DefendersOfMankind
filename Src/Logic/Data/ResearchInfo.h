//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
	 * Esta clase representa los datos relativos al �rea de investigaci�n del juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class ResearchInfo {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Esta estructura representa los datos relativos a una investigaci�n.
		 */
		typedef struct {
			/** El nombre de la investigaci�n. */
			std::string name;
			/** La descripci�n de la investigaci�n. */
			std::string description;
			/** El coste de la investigaci�n. */
			unsigned int cost;
			/** El flag que indica si ha sido comprada o no. */
			bool buyed;
		} AreaResearchInfo;

		/**
		 * Este tipo representa un vector de investigaciones.
		 */
		typedef std::vector<AreaResearchInfo> AreaResearchInfoVector;

		/**
		 * Esta estructura representa un �rea de investigaci�n.
		 */
		typedef struct {
			/** El nombre del �rea de investigaci�n. */
			std::string name;
			/** La rama izquierda del �rea de investigaci�n. */
			AreaResearchInfoVector left;
			/** La rama central del �rea de investigaci�n. */
			AreaResearchInfoVector middle;
			/** La rama derecha del �rea de investigaci�n. */
			AreaResearchInfoVector right;
		} AreaInfo;

		/**
		 * Este tipo representa una tabla con las �reas de investigaci�n.
		 */
		typedef std::map<std::string, AreaInfo> AreaInfoTable;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el inicio de la secuencia de �reas de investigaci�n.
		 */
		inline AreaInfoTable::iterator getAreasBegin() { return _areas.begin(); }

		/**
		 * Obtiene el inicio de la secuencia de �reas de investigaci�n.
		 */
		inline AreaInfoTable::iterator getAreasEnd() { return _areas.end(); }

		/**
		 * Obtiene el n�mero de �reas de investigaci�n.
		 */
		inline unsigned int getAreasCount() const { return _areas.size(); }

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si existe el �rea indicada por el usuario.
		 * @param name El nombre del �rea de investigaci�n.
		 * @return Devuelve true cuando encuentra el �rea.
		 */
		bool containsArea(const std::string & name);

		/**
		 * Busca un �rea indicada por el usuario.
		 * @param name El nombre del �rea de investigaci�n.
		 * @return Devuelve la referencia al �rea o una excepci�n si no la encuentra.
		 */
		AreaInfo & findArea(const std::string & name);

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Las �reas de investigaci�n.
		 */
		AreaInfoTable _areas;

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Carga la informaci�n en la clase.
		 */
		void loadParts();

		/**
		 * Borra la informaci�n en la clase.
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
