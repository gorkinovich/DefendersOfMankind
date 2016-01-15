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

#ifndef __CORE_NUMBER_H__
#define __CORE_NUMBER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Data/Variable.h"
#include "Core/Data/INumber.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa una variable de tipo número.
	 */
	template<class T>
	class Number : public Variable<T>, public INumber {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el número como un entero con signo de 8 bits.
		 */
		virtual char getAsInt8() const { return (char)_data; }

		/**
		 * Obtiene el número como un entero sin signo de 8 bits.
		 */
		virtual unsigned char getAsByte() const { return (unsigned char)_data; }

		/**
		 * Obtiene el número como un entero con signo de 16 bits.
		 */
		virtual short int getAsInt16() const { return (short int)_data; }

		/**
		 * Obtiene el número como un entero sin signo de 16 bits.
		 */
		virtual unsigned short int getAsWord() const { return (unsigned short int)_data; }

		/**
		 * Obtiene el número como un entero con signo de 32 bits.
		 */
		virtual long int getAsInt32() const { return (long int)_data; }

		/**
		 * Obtiene el número como un entero sin signo de 32 bits.
		 */
		virtual unsigned long int getAsDword() const { return (unsigned long int)_data; }

		/**
		 * Obtiene el número como un entero con signo de 64 bits.
		 */
		virtual long long getAsInt64() const { return (long long)_data; }

		/**
		 * Obtiene el número como un entero sin signo de 64 bits.
		 */
		virtual unsigned long long getAsQword() const { return (unsigned long long)_data; }

		/**
		 * Obtiene el número como un real simple.
		 */
		virtual float getAsFloat() const { return (float)_data; }

		/**
		 * Obtiene el número como un real doble.
		 */
		virtual double getAsDouble() const { return (double)_data; }

		/**
		 * Obtiene el número como un real doble largo.
		 */
		virtual long double getAsLongDouble() const { return (long double)_data; }


		/**
		 * Modifica el número como un entero con signo de 8 bits.
		 */
		virtual void setAsInt8(char value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero sin signo de 8 bits.
		 */
		virtual void setAsByte(unsigned char value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero con signo de 16 bits.
		 */
		virtual void setAsInt16(short int value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero sin signo de 16 bits.
		 */
		virtual void setAsWord(unsigned short int value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero con signo de 32 bits.
		 */
		virtual void setAsInt32(long int value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero sin signo de 32 bits.
		 */
		virtual void setAsDword(unsigned long int value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero con signo de 64 bits.
		 */
		virtual void setAsInt64(long long value) { _data = (T)value; }

		/**
		 * Modifica el número como un entero sin signo de 64 bits.
		 */
		virtual void setAsQword(unsigned long long value) { _data = (T)value; }

		/**
		 * Modifica el número como un real simple.
		 */
		virtual void setAsFloat(float value) { _data = (T)value; }

		/**
		 * Modifica el número como un real doble.
		 */
		virtual void setAsDouble(double value) { _data = (T)value; }

		/**
		 * Modifica el número como un real doble largo.
		 */
		virtual void setAsLongDouble(long double value) { _data = (T)value; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Number() : Variable() {}

		/**
		 * Construye un nuevo objeto.
		 */
		Number(T data) : Variable(data) {}

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Number(const Number & obj) : Variable(obj) {}

		/**
		 * Destructor del objeto.
		 */
		virtual ~Number() {}
	};
}

#endif
