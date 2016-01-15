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

#ifndef __CORE_ANIMATEDENTITY_H__
#define __CORE_ANIMATEDENTITY_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Graphics/GraphicEntity.h"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class AnimationState;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;

	/**
	 * Esta clase representa un listener para poder saber cuando termina una animación.
	*/
	class AnimatedEntityListener {
	public:
		/**
		 * Método que será invocado siempre que una animación, no cíclica, se termine.
		 * @param animation El nombre de la animación terminada.
		 */
		virtual void animationFinished(const std::string & animation) {}
	};

	/**
	 * Esta clase representa una entidad gráfica animada dentro de una escena.
	 */
	class AnimatedEntity : public GraphicEntity {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicia una animación de la entidad.
		 * @param name El nombre de la animación.
		 * @param loop El flag de reproducción cíclica.
		 * @return De vuelve true si se logra iniciar la animación.
		 */
		bool setAnimation(const std::string & name, bool loop);

		/**
		 * Para una animación de la entidad.
		 * @param name El nombre de la animación.
		 * @return De vuelve true si se logra parar la animación.
		 */
		bool stopAnimation(const std::string & name);

		/**
		 * Para todas las animaciones de la entidad.
		 */
		void stopAllAnimations();

		/**
		 * Registra el "oyente" de la entidad gráfica animada.
		 */
		inline void setObserver(AnimatedEntityListener * observer) {
			_observer = observer;
		}

		/**
		 * Elimina el "oyente" de la entidad gráfica animada.
		 */
		inline void removeObserver(AnimatedEntityListener * observer) {
			if(_observer == observer) _observer = 0;
		}

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 * @param name El nombre de la entidad.
		 * @param mesh El nombre del modelo que debe cargarse.
		 */
		AnimatedEntity(const std::string & name, const std::string & mesh);

		/**
		 * Constructor copia del objeto.
		 * @param obj El objeto a copiar.
		 * @remark El constructor copia crea una copia nueva, los punteros del objeto origen se conservan,
		 *         con lo que existe el peligro de borrar el original sin que la copia se entere.
		 */
		AnimatedEntity(const AnimatedEntity & obj);

		/**
		 * Destructor del objeto.
		 */
		virtual ~AnimatedEntity();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * El "oyente" de la entidad gráfica animada.
		 */
		AnimatedEntityListener * _observer;

		/**
		 * La animación que tiene la entidad activada.
		 */
		Ogre::AnimationState * _currentAnimation;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza el estado interno de la entidad.
		 * @param lastInterval El tiempo total en segundos del último intervalo entre frame y frame.
		 */
		virtual void update(float lastInterval);

		friend class Core::Scene;
	};
}

#endif
