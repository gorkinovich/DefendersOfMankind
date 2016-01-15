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

//TODO: Completar y comentar el fichero...

#ifndef __LOGIC_OPTIONSCONTROLLER_H__
#define __LOGIC_OPTIONSCONTROLLER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class GameManager;

	/**
	 * Esta clase representa el controlador de las opciones del juego.
	 * @remark Este tipo de clase solo puede ser creado y destruido por el GameManager.
	 */
	class OptionsController {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		//...

		/**
		 * Obtiene el volumen de la música.
		 */
		inline float getMusicVolume() const { return _musicVolume; }

		/**
		 * Obtiene el volumen de los sonidos ambientales.
		 */
		inline float getSoundsVolume() const { return _soundsVolume; }

		/**
		 * Obtiene el volumen de las voces.
		 */
		inline float getVoicesVolume() const { return _voicesVolume; }

		//...

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicializa el controlador.
		 * @return Devuelve true si se logra inicializar el controlador.
		 */
		bool initialize();

		/**
		 * Finaliza el controlador.
		 */
		void release();

		//...

		/**
		 * Cambia las opciones del sonido, actualizando las diversas partes del motor afectadas.
		 * @param music El volumen de la música.
		 * @param sounds El volumen de los sonidos ambientales.
		 * @param voices El volumen de las voces.
		 */
		void changeSoundOptions(float music, float sounds, float voices);

		//...

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * ...
		 */
		//...

		/**
		 * El volumen de la música.
		 */
		float _musicVolume;

		/**
		 * El volumen de los sonidos ambientales.
		 */
		float _soundsVolume;

		/**
		 * El volumen de las voces.
		 */
		float _voicesVolume;

		//...

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		OptionsController();

		/**
		 * Destructor del objeto.
		 */
		virtual ~OptionsController();

		friend class Logic::GameManager;
	};
}

#endif
