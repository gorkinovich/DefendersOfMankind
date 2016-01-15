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

#ifndef __CORE_LUABINDUTILS_H__
#define __CORE_LUABINDUTILS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#pragma warning(disable:4251)
#include <luabind/luabind.hpp>

#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Obtención de datos
	//********************************************************************************************************

	/**
	 * Obtiene una variable global de la máquina virtual de Lua.
	 * @param name El nombre de la variable global.
	 * @param retValue El valor recibido con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaGetGlobal(const char * name, luabind::object & retValue);

	//********************************************************************************************************
	// Comprobación de tipos
	//********************************************************************************************************

	/**
	 * Comprueba si un objeto de Lua es una tabla o no.
	 * @param victim El objeto a comprobar.
	 * @return Devuelve true si el objeto es una tabla.
	 */
	bool LuaIsTable(const luabind::object & victim);

	//********************************************************************************************************
	// Conversión de datos
	//********************************************************************************************************

	/**
	 * Convierte un objeto de Lua en un valor booleano.
	 * @param victim El objeto a convertir.
	 * @param retValue El valor recibido de la conversión con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaConvertToBool(luabind::object & victim, bool & retValue);

	/**
	 * Convierte un objeto de Lua en un valor numérico.
	 * @param victim El objeto a convertir.
	 * @param retValue El valor recibido de la conversión con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaConvertToNumber(luabind::object & victim, double & retValue);

	/**
	 * Convierte un objeto de Lua en un valor de coma flotante.
	 * @param victim El objeto a convertir.
	 * @param retValue El valor recibido de la conversión con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaConvertToFloat(luabind::object & victim, float & retValue);

	/**
	 * Convierte un objeto de Lua en un valor entero.
	 * @param victim El objeto a convertir.
	 * @param retValue El valor recibido de la conversión con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaConvertToInteger(luabind::object & victim, int & retValue);

	/**
	 * Convierte un objeto de Lua en una cadena.
	 * @param victim El objeto a convertir.
	 * @param retValue El valor recibido de la conversión con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaConvertToString(luabind::object & victim, std::string & retValue);

	/**
	 * Convierte un objeto de Lua en un puntero genérico.
	 * @param victim El objeto a convertir.
	 * @param retValue El valor recibido de la conversión con éxito.
	 * @return Devuelve true si la operación se realiza correctamente.
	 */
	bool LuaConvertToUserData(luabind::object & victim, void * & retValue);
}

#endif
