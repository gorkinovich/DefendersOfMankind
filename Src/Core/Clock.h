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

#ifndef __CORE_CLOCK_H__
#define __CORE_CLOCK_H__

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class Timer;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa el reloj interno de la aplicación.
	 */
	class Clock {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el tiempo total desde que se inició el gestor del tiempo tras iniciar la aplicación.
		 */
		inline unsigned long getTotalTime() const { return _totalTime; }

		/**
		 * Obtiene el tiempo total del último intervalo de tiempo entre anterior frame y el actual.
		 */
		inline unsigned int getLastInterval() const { return _lastInterval; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la información interna del reloj.
		 */
		void update();

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Clock();

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 */
		Clock(const Clock & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~Clock();

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El tiempo total desde que se inició el gestor del tiempo tras iniciar la aplicación.
		 */
		unsigned long _totalTime;

		/**
		 * El tiempo total del último intervalo de tiempo entre anterior frame y el actual.
		 */
		unsigned int _lastInterval;

		/**
		 * Controlador que tiene Ogre para obtener el tiempo.
		 */
		Ogre::Timer * _timer;
	};
}

#endif
