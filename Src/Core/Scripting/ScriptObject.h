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

#ifndef __CORE_SCRIPTOBJECT_H__
#define __CORE_SCRIPTOBJECT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Core/Pointer.h"

//************************************************************************************************************
// Lua y luabind
//************************************************************************************************************

extern "C" {
	struct lua_State;
}

namespace luabind {
	class object;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ScriptingManager;

	/**
	 * Esta clase representa un objeto o variable dentro de una máquina virtual de scripts.
	 * @remarks Solo el gestor del motor de scripting puede crear y destruir objetos de esta clase.
	 */
	class ScriptObject {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el objeto interno con la variable de Lua.
		 */
		inline luabind::object & getLuaBindObject() const { return *_data; }

		/**
		 * Obtiene el valor como si fuera un tipo booleano.
		 */
		bool getAsBoolean() const;

		/**
		 * Modifica el valor como si fuera un tipo booleano.
		 */
		void setAsBoolean(bool value);

		/**
		 * Obtiene el valor como si fuera un tipo número.
		 */
		double getAsNumber() const;

		/**
		 * Modifica el valor como si fuera un tipo número.
		 */
		void setAsNumber(double value);

		/**
		 * Obtiene el valor como si fuera un tipo número.
		 */
		float getAsFloat() const;

		/**
		 * Modifica el valor como si fuera un tipo número.
		 */
		void setAsFloat(float value);

		/**
		 * Obtiene el valor como si fuera un tipo número.
		 */
		int getAsInteger() const;

		/**
		 * Modifica el valor como si fuera un tipo número.
		 */
		void setAsInteger(int value);

		/**
		 * Obtiene el valor como si fuera un tipo cadena.
		 */
		std::string getAsString() const;

		/**
		 * Modifica el valor como si fuera un tipo cadena.
		 */
		void setAsString(const std::string & value);

		/**
		 * Obtiene el valor como si fuera un tipo datos de usuario.
		 */
		void * getAsUserData() const;

		/**
		 * Modifica el valor como si fuera un tipo datos de usuario.
		 */
		void setAsUserData(void * value);

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si el objeto interno es de tipo nulo.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isNil() const;

		/**
		 * Comprueba si el objeto interno es de tipo booleano.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isBoolean() const;

		/**
		 * Comprueba si el objeto interno es de tipo número.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isNumber() const;

		/**
		 * Comprueba si el objeto interno es de tipo cadena.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isString() const;

		/**
		 * Comprueba si el objeto interno es de tipo tabla.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isTable() const;

		/**
		 * Comprueba si el objeto interno es de tipo función.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isFunction() const;

		/**
		 * Comprueba si el objeto interno es de tipo datos de usuario.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isUserData() const;

		/**
		 * Comprueba si el objeto interno es de tipo datos de usuario.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isLightUserData() const;

		/**
		 * Comprueba si el objeto interno es de tipo hilo.
		 * @return Devuelve true cuando el tipo es correcto.
		 */
		bool isThread() const;

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		ScriptObject(const ScriptObject & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~ScriptObject();

		//----------------------------------------------------------------------------------------------------
		// Operadores
		//----------------------------------------------------------------------------------------------------

		ScriptObject & operator =(const ScriptObject & obj);

		ScriptObject operator [](const std::string & index);

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El gestor del motor de scripting.
		 */
		static ScriptingManager * _scripting;

		/**
		 * El nombre identificador del objeto.
		 */
		std::string _name;

		/**
		 * El objeto padre que lo contiene.
		 */
		ScriptObject * _father;

		/**
		 * El objeto interno con la variable de Lua.
		 */
		SmartPointer<luabind::object> _data;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Modifica el valor interno del objeto.
		 */
		template<class TValue>
		inline void setValueAs(TValue value);

		//----------------------------------------------------------------------------------------------------
		// Constructores
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre identificador del objeto.
		 * @param father El objeto padre que lo contiene.
		 */
		ScriptObject(const std::string & name, ScriptObject * father = 0);

		friend class Core::ScriptingManager;
	};
}

#endif
