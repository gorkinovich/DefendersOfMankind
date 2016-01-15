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

#ifndef __CORE_XMLNODEUTIL_H__
#define __CORE_XMLNODEUTIL_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>
#include <rapidxml.hpp>
#include <OgreColourValue.h>

#include "Core/Math.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Convierte un atributo de un nodo XML en una cadena.
	 * @param xmlNode El nodo XML.
	 * @param name El nombre del atributo.
	 * @param defaultValue El valor por defecto en caso de fallo.
	 * @return El valor convertido o defaultValue en caso de fallo.
	 */
	std::string XmlNodeGetAttribute(rapidxml::xml_node<> * xmlNode, const std::string & name, const std::string & defaultValue = "");

	/**
	 * Convierte un atributo de un nodo XML en un número real.
	 * @param xmlNode El nodo XML.
	 * @param name El nombre del atributo.
	 * @param defaultValue El valor por defecto en caso de fallo.
	 * @return El valor convertido o defaultValue en caso de fallo.
	 */
	Ogre::Real XmlNodeGetAttributeAsReal(rapidxml::xml_node<> * xmlNode, const std::string & name, Ogre::Real defaultValue = 0.0f);

	/**
	 * Convierte un atributo de un nodo XML en un float.
	 * @param xmlNode El nodo XML.
	 * @param name El nombre del atributo.
	 * @param defaultValue El valor por defecto en caso de fallo.
	 * @return El valor convertido o defaultValue en caso de fallo.
	 */
	float XmlNodeGetAttributeAsFloat(rapidxml::xml_node<> * xmlNode, const std::string & name, float defaultValue = 0.0f);

	/**
	 * Convierte un atributo de un nodo XML en un entero.
	 * @param xmlNode El nodo XML.
	 * @param name El nombre del atributo.
	 * @param defaultValue El valor por defecto en caso de fallo.
	 * @return El valor convertido o defaultValue en caso de fallo.
	 */
	int XmlNodeGetAttributeAsInteger(rapidxml::xml_node<> * xmlNode, const std::string & name, int defaultValue = 0);

	/**
	 * Convierte un atributo de un nodo XML en un booleano.
	 * @param xmlNode El nodo XML.
	 * @param name El nombre del atributo.
	 * @param defaultValue El valor por defecto en caso de fallo.
	 * @return El valor convertido o defaultValue en caso de fallo.
	 */
	bool XmlNodeGetAttributeAsBool(rapidxml::xml_node<> * xmlNode, const std::string & name, bool defaultValue = false);



	/**
	 * Convierte un nodo XML en un Vector3.
	 * @param xmlNode El nodo XML.
	 * @return El Vector3 inicializado con los datos del nodo.
	 */
	Vector3 XmlNodeParseVector3(rapidxml::xml_node<> * xmlNode);

	/**
	 * Convierte un nodo XML en un Quaternion.
	 * @param xmlNode El nodo XML.
	 * @return El Quaternion inicializado con los datos del nodo.
	 */
	Quaternion XmlNodeParseQuaternion(rapidxml::xml_node<> * xmlNode);

	/**
	 * Convierte un nodo XML en un Ogre::ColourValue.
	 * @param xmlNode El nodo XML.
	 * @return El Ogre::ColourValue inicializado con los datos del nodo.
	 */
	Ogre::ColourValue XmlNodeParseColour(rapidxml::xml_node<> * xmlNode);
}

#endif
