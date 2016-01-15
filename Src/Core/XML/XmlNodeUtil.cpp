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

#include <OgreStringConverter.h>

#include "Core/XML/XmlNodeUtil.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Funciones
	//********************************************************************************************************

	std::string XmlNodeGetAttribute(rapidxml::xml_node<> * xmlNode, const std::string & name, const std::string & defaultValue) {
		rapidxml::xml_attribute<char> * aux = xmlNode->first_attribute(name.c_str());
		return aux ? std::string(aux->value()) : defaultValue;
	}

	//--------------------------------------------------------------------------------------------------------

	Ogre::Real XmlNodeGetAttributeAsReal(rapidxml::xml_node<> * xmlNode, const std::string & name, Ogre::Real defaultValue) {
		rapidxml::xml_attribute<char> * aux = xmlNode->first_attribute(name.c_str());
		return aux ? Ogre::StringConverter::parseReal(aux->value()) : defaultValue;
	}

	//--------------------------------------------------------------------------------------------------------

	float XmlNodeGetAttributeAsFloat(rapidxml::xml_node<> * xmlNode, const std::string & name, float defaultValue) {
		rapidxml::xml_attribute<char> * aux = xmlNode->first_attribute(name.c_str());
		return aux ? (float)Ogre::StringConverter::parseReal(aux->value()) : defaultValue;
	}

	//--------------------------------------------------------------------------------------------------------

	int XmlNodeGetAttributeAsInteger(rapidxml::xml_node<> * xmlNode, const std::string & name, int defaultValue) {
		rapidxml::xml_attribute<char> * aux = xmlNode->first_attribute(name.c_str());
		return aux ? Ogre::StringConverter::parseInt(aux->value()) : defaultValue;
	}

	//--------------------------------------------------------------------------------------------------------

	bool XmlNodeGetAttributeAsBool(rapidxml::xml_node<> * xmlNode, const std::string & name, bool defaultValue) {
		static const std::string trueValue = std::string("true");
		rapidxml::xml_attribute<char> * aux = xmlNode->first_attribute(name.c_str());
		return aux ? std::string(aux->value()) == trueValue : defaultValue;
	}

	//--------------------------------------------------------------------------------------------------------

	Vector3 XmlNodeParseVector3(rapidxml::xml_node<> * xmlNode) {
		return Ogre::Vector3(
			Ogre::StringConverter::parseReal(xmlNode->first_attribute("x")->value()),
			Ogre::StringConverter::parseReal(xmlNode->first_attribute("y")->value()),
			Ogre::StringConverter::parseReal(xmlNode->first_attribute("z")->value())
		);
	}

	//--------------------------------------------------------------------------------------------------------

	Quaternion XmlNodeParseQuaternion(rapidxml::xml_node<> * xmlNode) {
		Ogre::Quaternion orientation;

		rapidxml::xml_attribute<char> * aux1 = xmlNode->first_attribute("qx");
		rapidxml::xml_attribute<char> * aux2 = xmlNode->first_attribute("qy");
		rapidxml::xml_attribute<char> * aux3 = xmlNode->first_attribute("qz");
		rapidxml::xml_attribute<char> * aux4 = xmlNode->first_attribute("qw");

		if(aux1 && aux2 && aux3 && aux4) {
			orientation.x = Ogre::StringConverter::parseReal(aux1->value());
			orientation.y = Ogre::StringConverter::parseReal(aux2->value());
			orientation.z = Ogre::StringConverter::parseReal(aux3->value());
			orientation.w = Ogre::StringConverter::parseReal(aux4->value());
			return orientation;
		}

		aux1 = xmlNode->first_attribute("x");
		aux2 = xmlNode->first_attribute("y");
		aux3 = xmlNode->first_attribute("z");
		aux4 = xmlNode->first_attribute("w");

		if(aux1 && aux2 && aux3 && aux4) {
			orientation.x = Ogre::StringConverter::parseReal(aux1->value());
			orientation.y = Ogre::StringConverter::parseReal(aux2->value());
			orientation.z = Ogre::StringConverter::parseReal(aux3->value());
			orientation.w = Ogre::StringConverter::parseReal(aux4->value());
			return orientation;
		}

		aux1 = xmlNode->first_attribute("axisX");
		aux2 = xmlNode->first_attribute("axisY");
		aux3 = xmlNode->first_attribute("axisZ");
		aux4 = xmlNode->first_attribute("angle");

		if(aux1 && aux2 && aux3 && aux4) {
			Ogre::Vector3 axis;
			axis.x = Ogre::StringConverter::parseReal(aux1->value());
			axis.y = Ogre::StringConverter::parseReal(aux2->value());
			axis.z = Ogre::StringConverter::parseReal(aux3->value());
			Ogre::Real angle = Ogre::StringConverter::parseReal(aux4->value());
			orientation.FromAngleAxis(Ogre::Angle(angle), axis);
			return orientation;
		}

		aux1 = xmlNode->first_attribute("angleX");
		aux2 = xmlNode->first_attribute("angleY");
		aux3 = xmlNode->first_attribute("angleZ");

		if(aux1 && aux2 && aux3) {
			Ogre::Vector3 axis;
			axis.x = Ogre::StringConverter::parseReal(aux1->value());
			axis.y = Ogre::StringConverter::parseReal(aux2->value());
			axis.z = Ogre::StringConverter::parseReal(aux3->value());
			orientation.FromAxes(&axis);
			return orientation;
		}

		assert("XmlNodeParseQuaternion -> Orientation data not found...");
		return orientation;
	}

	//--------------------------------------------------------------------------------------------------------

	Ogre::ColourValue XmlNodeParseColour(rapidxml::xml_node<> * xmlNode) {
		return Ogre::ColourValue(
			Ogre::StringConverter::parseReal(xmlNode->first_attribute("r")->value()),
			Ogre::StringConverter::parseReal(xmlNode->first_attribute("g")->value()),
			Ogre::StringConverter::parseReal(xmlNode->first_attribute("b")->value()),
			xmlNode->first_attribute("a") != 0 ?
				Ogre::StringConverter::parseReal(xmlNode->first_attribute("a")->value()) : 1.0f
		);
	}
}
