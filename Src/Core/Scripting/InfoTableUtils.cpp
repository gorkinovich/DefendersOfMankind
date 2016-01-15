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

#include "Core/Scripting/LuabindUtils.h"
#include "Core/Data/InfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	InfoTable * LuaGetInfoTable(const std::string & name) {
		// Primero intentamos obtener el objeto almacenado en la máquina virtual de Lua.
		luabind::object victim;
		if(LuaGetGlobal(name.c_str(), victim) && LuaIsTable(victim)) {
			// En caso de existir y ser una tabla, pasamos a crear una tabla para almacenar la información.
			InfoTable * aux = new InfoTable();

			// A continuación vamos a iterar sobre todos los elementos de la tabla.
			luabind::iterator i(victim), end;
			luabind::object objKey, objVal;
			std::string currentKey, currentValue;
			for(; i != end; ++i) {
				// Tomamos la clave del elemento actual y comprobamos si es una cadena.
				objKey = i.key();
				if(LuaConvertToString(objKey, currentKey)) {
					objVal = *i;
					if(LuaConvertToString(objVal, currentValue)) {
						// Si el valor es una cadena se trata de un atributo normal.
						aux->setAttribute(currentKey, currentValue);
					}
				}
			}

			// Finalmente devolvemos el nuevo descriptor.
			return aux;
		} else {
			return 0;
		}
	}
}
