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

#ifndef __LOGIC_SPACEMAPINFO_H__
#define __LOGIC_SPACEMAPINFO_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>
#include <string>

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class GameManager;

	/**
	 * Esta clase representa los datos relativos al mapa espacial del juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class SpaceMapInfo {
	public:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Esta estructura representa los datos relativos a una misión.
		 */
		typedef struct {
			/** El nombre de la misión. */
			std::string name;
			/** La descripción de la misión. */
			std::string description;
			/** El fichero con el que se carga la misión. */
			std::string file;
			/** La lista de qué misión como mínimo hace falta para poder hacer esta. */
			std::vector<std::string> requires;
			/** El nombre del botón con el que acceder a la misión. */
			std::string buttonName;
			/** El flag para indicar si la misión ha sido ya realizada. */
			bool isDone;
		} MissionInfo;

		/**
		 * Este tipo representa una vector con los datos relativos a las misiones.
		 */
		typedef std::vector<MissionInfo> MissionInfoVector;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el inicio de la secuencia de misiones.
		 */
		inline MissionInfoVector::iterator getMissionsBegin() { return _missions.begin(); }

		/**
		 * Obtiene el inicio de la secuencia de misiones.
		 */
		inline MissionInfoVector::iterator getMissionsEnd() { return _missions.end(); }

		/**
		 * Obtiene el número de misiones.
		 */
		inline unsigned int getMissionsCount() const { return _missions.size(); }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si existe la misión indicada por el usuario.
		 * @param name El nombre de la misión.
		 * @return Devuelve true cuando encuentra la misión.
		 */
		bool containsMission(const std::string & name);

		/**
		 * Busca una misión indicada por el usuario.
		 * @param name El nombre de la misión.
		 * @return Devuelve la referencia a la misión o una excepción si no la encuentra.
		 */
		MissionInfo & findMission(const std::string & name);

		/**
		 * Busca una misión indicada por el usuario para devolver su índice.
		 * @param name El nombre de la misión.
		 * @return Devuelve la posición de la misión o un -1 si no la encuentra.
		 */
		int findIndex(const std::string & name);

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Los datos relativos a las misiones.
		 */
		MissionInfoVector _missions;

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
		SpaceMapInfo();

		/**
		 * Destructor del objeto.
		 */
		virtual ~SpaceMapInfo();

		friend class Logic::GameManager;
	};
}

#endif
