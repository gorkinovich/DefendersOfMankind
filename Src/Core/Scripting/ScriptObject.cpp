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

#include <exception>

#include "Core/Scripting/ScriptingInclude.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Scripting/ScriptObject.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	ScriptingManager * ScriptObject::_scripting = 0;

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	bool ScriptObject::getAsBoolean() const {
		if(isBoolean()) {
			return luabind::object_cast<bool>(*_data);
		} else {
			throw std::exception("ScriptObject::getAsBoolean => Invalid type...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptObject::setAsBoolean(bool value) {
		setValueAs(value);
	}

	//--------------------------------------------------------------------------------------------------------

	double ScriptObject::getAsNumber() const {
		if(isNumber()) {
			return luabind::object_cast<double>(*_data);
		} else {
			throw std::exception("ScriptObject::getAsNumber => Invalid type...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptObject::setAsNumber(double value) {
		setValueAs(value);
	}

	//--------------------------------------------------------------------------------------------------------

	float ScriptObject::getAsFloat() const {
		if(isNumber()) {
			return luabind::object_cast<float>(*_data);
		} else {
			throw std::exception("ScriptObject::getAsFloat => Invalid type...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptObject::setAsFloat(float value) {
		setValueAs(value);
	}

	//--------------------------------------------------------------------------------------------------------

	int ScriptObject::getAsInteger() const {
		if(isNumber()) {
			return luabind::object_cast<int>(*_data);
		} else {
			throw std::exception("ScriptObject::getAsInteger => Invalid type...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptObject::setAsInteger(int value) {
		setValueAs(value);
	}

	//--------------------------------------------------------------------------------------------------------

	std::string ScriptObject::getAsString() const {
		if(isString()) {
			const char * aux = luabind::object_cast<const char *>(*_data);
			return std::string(aux);
		} else {
			throw std::exception("ScriptObject::getAsString => Invalid type...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptObject::setAsString(const std::string & value) {
		setValueAs(value.c_str());
	}

	//--------------------------------------------------------------------------------------------------------

	void * ScriptObject::getAsUserData() const {
		if(isUserData()) {
			return luabind::object_cast<void *>(*_data);
		} else {
			throw std::exception("ScriptObject::getAsUserData => Invalid type...");
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void ScriptObject::setAsUserData(void * value) {
		setValueAs(value);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool ScriptObject::isNil() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TNIL);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isBoolean() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TBOOLEAN);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isNumber() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TNUMBER);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isString() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TSTRING);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isTable() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TTABLE);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isFunction() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TFUNCTION);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isUserData() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TUSERDATA);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isLightUserData() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TLIGHTUSERDATA);
	}

	//--------------------------------------------------------------------------------------------------------

	bool ScriptObject::isThread() const {
		luabind::object & obj = *_data;
		return obj.is_valid() && (luabind::type(obj) == LUA_TTHREAD);
	}

	//--------------------------------------------------------------------------------------------------------

	template<class TValue>
	void ScriptObject::setValueAs(TValue value) {
		try {
			if(_father) {
				// Si el objeto tiene un padre, buscamos y comprobamos la validez de su información
				// interna antes de asignar el valor final.
				if(luabind::object * fatherData = _father->_data.get()) {
					(*fatherData)[_name.c_str()] = value;
				}
			} else {
				// Si no tiene padre, la información interna estará en el espacio global.
				luabind::globals(_scripting->getLuaState())[_name.c_str()] = value;
			}
		} catch(...) {
		}
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	ScriptObject::ScriptObject(const std::string & name, ScriptObject * father) {
		_name = name;
		_father = father;
		// Tras asignar el resto de propiedades, vamos a obtener la información interna del objeto.
		luabind::object * victim = 0;
		try {
			if(_father) {
				// Si el objeto tiene un padre, buscamos y comprobamos la validez de su información
				// interna antes de tomar el elemento que buscamos.
				if(luabind::object * fatherData = _father->_data.get()) {
					victim = new luabind::object((*fatherData)[_name.c_str()]);
				}
			} else {
				// Si no tiene padre, la información interna estará en el espacio global.
				victim = new luabind::object(luabind::globals(_scripting->getLuaState())[_name.c_str()]);
			}
		} catch(...) {
			victim = 0;
		}
		_data = SmartPointer<luabind::object>(victim);
	}

	//--------------------------------------------------------------------------------------------------------

	ScriptObject::ScriptObject(const ScriptObject & obj) {
		_name = obj._name;
		_father = obj._father;
		_data = obj._data;
	}

	//--------------------------------------------------------------------------------------------------------

	ScriptObject::~ScriptObject() {}

	//********************************************************************************************************
	// Operadores
	//********************************************************************************************************

	ScriptObject & ScriptObject::operator =(const ScriptObject & obj) {
		ScriptObject::ScriptObject(obj);
		return *this;
	}

	//--------------------------------------------------------------------------------------------------------

	ScriptObject ScriptObject::operator [](const std::string & index) {
		if(_data.get()) {
			return ScriptObject(index, this);
		} else {
			throw std::exception("ScriptObject::operator => Invalid inner data...");
		}
	}
}
