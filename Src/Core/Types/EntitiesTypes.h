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

#ifndef __CORE_ENTITIESTYPES_H__
#define __CORE_ENTITIESTYPES

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <list>
#include <string>

#include "Core/IdType.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Entity;
	class Component;


	/**
	 * Este tipo representa una lista de entidades.
	 */
	typedef std::list<Entity *> EntityList;

	/**
	 * Este tipo representa una lista de componentes.
	 */
	typedef std::list<Component *> ComponentList;

	/**
	 * Este tipo representa una tabla de entidades en base a su identificador �nico.
	 */
	typedef std::map<Core::IdType, Entity *> EntityIdTable;

	/**
	 * Este tipo representa una tabla de componentes.
	 */
	typedef std::map<std::string, Component *> ComponentTable;


	/**
	 * Este tipo representa un iterador de una lista de entidades.
	 */
	typedef EntityList::iterator EntityListIterator;

	/**
	 * Este tipo representa un iterador de una lista de componentes.
	 */
	typedef ComponentList::iterator ComponentListIterator;

	/**
	 * Este tipo representa un iterador de una tabla de entidades en base a su identificador �nico.
	 */
	typedef EntityIdTable::iterator EntityIdTableIterator;

	/**
	 * Este tipo representa un iterador de una tabla de componentes.
	 */
	typedef ComponentTable::iterator ComponentTableIterator;
}

#endif
