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

#ifndef __CORE_LOCALIZATIONMANAGER_H__
#define __CORE_LOCALIZATIONMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa un gestor de cadenas para la localización del juego. De ese modo podemos
	 * indicar como valor una clave para pedírsela al gestor y recibir la cadena en el lenguaje actual.
	 */
	class LocalizationManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static LocalizationManager * GetInstance() {
			return _instance;
		}

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene una cadena en base a un nombre identificador.
		 * @param name El nombre identificador de la cadena.
		 * @return La cadena localizada si la encuentra, sino lanza una excepción.
		 */
		const std::string & get(const std::string & name) const;

		/**
		 * Carga una tabla de texto localizado.
		 * @param name El nombre de la tabla.
		 * @return Si la tabla se ha cargado o no.
		 */
		bool load(const std::string & tableName);

		/**
		 * Añade una cadena a la tabla de texto localizado.
		 * @param name El nombre identificador de la cadena.
		 * @param content La cadena con el texto localizado.
		 * @return Si la cadena ha sido añadida o no.
		 */
		bool add(const std::string & name, const std::string & content);

		/**
		 * Elimina una cadena de la tabla de texto localizado.
		 * @param name El nombre identificador de la cadena.
		 */
		void remove(const std::string & name);

		/**
		 * Elimina todas las cadenas almacenadas en la tabla de texto localizado.
		 */
		void clear();

		/**
		 * Comprueba si una cadena está en la tabla de texto localizado.
		 * @param name El nombre identificador de la cadena.
		 * @return Si la cadena está en la tabla de texto localizado o no.
		 */
		bool contains(const std::string & name) const;

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~LocalizationManager() { clear(); }

		//----------------------------------------------------------------------------------------------------
		// Operadores
		//----------------------------------------------------------------------------------------------------

		inline const std::string & operator [](const std::string & name) { return get(name); }

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de cadenas de texto.
		 */
		typedef std::map<std::string, std::string> StringsTable;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static LocalizationManager * _instance;

		/**
		 * La tabla con las cadenas de texto localizadas.
		 */
		StringsTable _table;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		LocalizationManager() {}
	};
}

#endif
