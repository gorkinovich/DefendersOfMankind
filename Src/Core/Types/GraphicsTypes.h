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

#ifndef __CORE_GRAPHICSTYPES_H__
#define __CORE_GRAPHICSTYPES_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <list>
#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;
	class ImmutableEntity;
	class GenericGraphicEntity;


	/**
	 * Este tipo representa una lista de entidades gráficas inmutables.
	 */
	typedef std::list<ImmutableEntity *> ImmutableEntityList;

	/**
	 * Este tipo representa una lista de entidades gráficas.
	 */
	typedef std::list<GenericGraphicEntity *> GenericGraphicEntityList;

	/**
	 * Este tipo representa una tabla de escenas.
	 */
	typedef std::map<std::string, Scene *> ScenesTable;

	/**
	 * Este tipo representa una tabla de entidades gráficas.
	 */
	typedef std::map<std::string, GenericGraphicEntity *> GenericGraphicEntityTable;


	/**
	 * Este tipo representa un iterador de una lista de entidades gráficas inmutables.
	 */
	typedef ImmutableEntityList::iterator ImmutableEntityListIterator;

	/**
	 * Este tipo representa un iterador de una lista de entidades gráficas.
	 */
	typedef GenericGraphicEntityList::iterator GenericGraphicEntityListIterator;

	/**
	 * Este tipo representa un iterador de una tabla de escenas.
	 */
	typedef ScenesTable::iterator ScenesTableIterator;

	/**
	 * Este tipo representa un iterador de una tabla de entidades gráficas.
	 */
	typedef GenericGraphicEntityTable::iterator GenericGraphicEntityTableIterator;
}

#endif
