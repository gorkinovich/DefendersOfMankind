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

#ifndef __CORE_BLUEPRINTSUTILS_H__
#define __CORE_BLUEPRINTSUTILS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class EntityInfoTable;
	class ComplexEntityInfoTable;

	/**
	 * Convierte una variable global de la máquina virtual de Lua en una EntityInfoTable.
	 * @param name El nombre de la variable global.
	 * @return Devuelve si todo ha ido correctamente la nueva EntityInfoTable con la información
	 *         obtenida, en caso de fallo devuelve NULL.
	 * @remark Esta función devuelve un nuevo puntero a un objeto, por lo que el usuario tendrá que
	 *         encargarse de eliminarlo cuando deje de necesitarlo.
	 */
	EntityInfoTable * BlueprintsGetEntityInfoTable(const std::string & name);

	/**
	 * Convierte una variable global de la máquina virtual de Lua en una ComplexEntityInfoTable.
	 * @param name El nombre de la variable global.
	 * @return Devuelve si todo ha ido correctamente la nueva ComplexEntityInfoTable con la información
	 *         obtenida, en caso de fallo devuelve NULL.
	 * @remark Esta función devuelve un nuevo puntero a un objeto, por lo que el usuario tendrá que
	 *         encargarse de eliminarlo cuando deje de necesitarlo.
	 */
	ComplexEntityInfoTable * BlueprintsGetComplexEntityInfoTable(const std::string & name);
}

#endif
