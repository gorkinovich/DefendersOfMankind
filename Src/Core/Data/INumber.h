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

#ifndef __CORE_INUMBER_H__
#define __CORE_INUMBER_H__

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta interfaz representa un número de forma genérica.
	 */
	class INumber {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el número como un entero con signo de 8 bits.
		 */
		virtual char getAsInt8() const = 0;

		/**
		 * Obtiene el número como un entero sin signo de 8 bits.
		 */
		virtual unsigned char getAsByte() const = 0;

		/**
		 * Obtiene el número como un entero con signo de 16 bits.
		 */
		virtual short int getAsInt16() const = 0;

		/**
		 * Obtiene el número como un entero sin signo de 16 bits.
		 */
		virtual unsigned short int getAsWord() const = 0;

		/**
		 * Obtiene el número como un entero con signo de 32 bits.
		 */
		virtual long int getAsInt32() const = 0;

		/**
		 * Obtiene el número como un entero sin signo de 32 bits.
		 */
		virtual unsigned long int getAsDword() const = 0;

		/**
		 * Obtiene el número como un entero con signo de 64 bits.
		 */
		virtual long long getAsInt64() const = 0;

		/**
		 * Obtiene el número como un entero sin signo de 64 bits.
		 */
		virtual unsigned long long getAsQword() const = 0;

		/**
		 * Obtiene el número como un real simple.
		 */
		virtual float getAsFloat() const = 0;

		/**
		 * Obtiene el número como un real doble.
		 */
		virtual double getAsDouble() const = 0;

		/**
		 * Obtiene el número como un real doble largo.
		 */
		virtual long double getAsLongDouble() const = 0;


		/**
		 * Modifica el número como un entero con signo de 8 bits.
		 */
		virtual void setAsInt8(char value) = 0;

		/**
		 * Modifica el número como un entero sin signo de 8 bits.
		 */
		virtual void setAsByte(unsigned char value) = 0;

		/**
		 * Modifica el número como un entero con signo de 16 bits.
		 */
		virtual void setAsInt16(short int value) = 0;

		/**
		 * Modifica el número como un entero sin signo de 16 bits.
		 */
		virtual void setAsWord(unsigned short int value) = 0;

		/**
		 * Modifica el número como un entero con signo de 32 bits.
		 */
		virtual void setAsInt32(long int value) = 0;

		/**
		 * Modifica el número como un entero sin signo de 32 bits.
		 */
		virtual void setAsDword(unsigned long int value) = 0;

		/**
		 * Modifica el número como un entero con signo de 64 bits.
		 */
		virtual void setAsInt64(long long value) = 0;

		/**
		 * Modifica el número como un entero sin signo de 64 bits.
		 */
		virtual void setAsQword(unsigned long long value) = 0;

		/**
		 * Modifica el número como un real simple.
		 */
		virtual void setAsFloat(float value) = 0;

		/**
		 * Modifica el número como un real doble.
		 */
		virtual void setAsDouble(double value) = 0;

		/**
		 * Modifica el número como un real doble largo.
		 */
		virtual void setAsLongDouble(long double value) = 0;

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~INumber() {}

	protected:
		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		INumber() {}
	};
}

#endif
