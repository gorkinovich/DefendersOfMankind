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

#ifndef __CORE_INFOTABLE_H__
#define __CORE_INFOTABLE_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <string>
#include <OgreColourValue.h>

#include "Core/Math.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una tabla con información asociada a una clave determinada. La clave es
	 * una cadena y la información se almacena también como una cadena, no obstante podemos recibirla
	 * transformada como un número entero o real, un booleano, un vector, etcétera.
	 */
	class InfoTable {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si la tabla tiene un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return Devuelve true en caso de existir el atributo.
		 */
		virtual bool hasAttribute(const std::string & name) const;

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		virtual const std::string & getAttribute(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		virtual void setAttribute(const std::string & name, const std::string & value);

		/**
		 * Borra un atributo determinado de la tabla.
		 * @param name El nombre del atributo.
		 */
		void removeAttribute(const std::string & name);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		bool getAttributeAsBool(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsBool(const std::string & name, bool value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		int getAttributeAsInteger(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsInteger(const std::string & name, int value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		unsigned int getAttributeAsDword(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsDword(const std::string & name, unsigned int value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		float getAttributeAsFloat(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsFloat(const std::string & name, float value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		double getAttributeAsDouble(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsDouble(const std::string & name, double value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Vector2 getAttributeAsVector2(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsVector2(const std::string & name, const Vector2 & value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Vector3 getAttributeAsVector3(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsVector3(const std::string & name, const Vector3 & value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Vector4 getAttributeAsVector4(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsVector4(const std::string & name, const Vector4 & value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Matrix3 getAttributeAsMatrix3(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsMatrix3(const std::string & name, const Matrix3 & value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Matrix4 getAttributeAsMatrix4(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsMatrix4(const std::string & name, const Matrix4 & value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Quaternion getAttributeAsQuaternion(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsQuaternion(const std::string & name, const Quaternion & value);

		/**
		 * Obtiene el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @return El valor del atributo, si no existe devuelve una excepción.
		 */
		Ogre::ColourValue getAttributeAsColourValue(const std::string & name) const;

		/**
		 * Modifica el valor de un atributo determinado.
		 * @param name El nombre del atributo.
		 * @param value El valor del atributo.
		 */
		void setAttributeAsColourValue(const std::string & name, const Ogre::ColourValue & value);

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		InfoTable();

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		InfoTable(const InfoTable & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~InfoTable();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de atributos.
		 */
		typedef std::map<std::string, std::string> AttributesTable;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La tabla de atributos.
		 */
		AttributesTable _attributes;
	};
}

#endif
