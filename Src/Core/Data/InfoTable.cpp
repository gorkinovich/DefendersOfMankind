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

#include <assert.h>
#include <sstream>
#include <exception>
#include <OgreStringConverter.h>

#include "Core/Data/InfoTable.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool InfoTable::hasAttribute(const std::string & name) const {
		return _attributes.count(name) > 0;
	}

	//--------------------------------------------------------------------------------------------------------

	const std::string & InfoTable::getAttribute(const std::string & name) const {
		AttributesTable::const_iterator victim = _attributes.find(name);
		if(victim != _attributes.end()) {
			return victim->second;
		} else {
			throw std::exception("InfoTable::getAttribute => The attribute doesn't exists...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttribute(const std::string & name, const std::string & value) {
		_attributes[name] = value;
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::removeAttribute(const std::string & name) {
		_attributes.erase(name);
	}

	//--------------------------------------------------------------------------------------------------------

	bool InfoTable::getAttributeAsBool(const std::string & name) const {
		return Ogre::StringConverter::parseBool(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsBool(const std::string & name, bool value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	int InfoTable::getAttributeAsInteger(const std::string & name) const {
		return Ogre::StringConverter::parseInt(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsInteger(const std::string & name, int value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	unsigned int InfoTable::getAttributeAsDword(const std::string & name) const {
		return Ogre::StringConverter::parseUnsignedInt(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsDword(const std::string & name, unsigned int value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	float InfoTable::getAttributeAsFloat(const std::string & name) const {
		return Ogre::StringConverter::parseReal(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsFloat(const std::string & name, float value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	double InfoTable::getAttributeAsDouble(const std::string & name) const {
		std::stringstream stream(getAttribute(name));
		double result = 0.0;
		stream >> result;
		return result;
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsDouble(const std::string & name, double value) {
		std::stringstream stream;
		stream.precision(6);
		stream.width(0);
		stream.fill(32);
		stream << value;
		setAttribute(name, stream.str());
	}

	//--------------------------------------------------------------------------------------------------------

	Vector2 InfoTable::getAttributeAsVector2(const std::string & name) const {
		return Ogre::StringConverter::parseVector2(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsVector2(const std::string & name, const Vector2 & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	Vector3 InfoTable::getAttributeAsVector3(const std::string & name) const {
		return Ogre::StringConverter::parseVector3(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsVector3(const std::string & name, const Vector3 & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	Vector4 InfoTable::getAttributeAsVector4(const std::string & name) const {
		return Ogre::StringConverter::parseVector4(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsVector4(const std::string & name, const Vector4 & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	Matrix3 InfoTable::getAttributeAsMatrix3(const std::string & name) const {
		return Ogre::StringConverter::parseMatrix3(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsMatrix3(const std::string & name, const Matrix3 & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	Matrix4 InfoTable::getAttributeAsMatrix4(const std::string & name) const {
		return Ogre::StringConverter::parseMatrix4(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsMatrix4(const std::string & name, const Matrix4 & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	Quaternion InfoTable::getAttributeAsQuaternion(const std::string & name) const {
		return Ogre::StringConverter::parseQuaternion(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsQuaternion(const std::string & name, const Quaternion & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//--------------------------------------------------------------------------------------------------------

	Ogre::ColourValue InfoTable::getAttributeAsColourValue(const std::string & name) const {
		return Ogre::StringConverter::parseColourValue(getAttribute(name));
	}

	//--------------------------------------------------------------------------------------------------------

	void InfoTable::setAttributeAsColourValue(const std::string & name, const Ogre::ColourValue & value) {
		setAttribute(name, Ogre::StringConverter::toString(value));
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	InfoTable::InfoTable() {}

	//--------------------------------------------------------------------------------------------------------

	InfoTable::InfoTable(const InfoTable & obj) {
		_attributes = obj._attributes;
	}

	//--------------------------------------------------------------------------------------------------------

	InfoTable::~InfoTable() {
		_attributes.clear();
	}
}
