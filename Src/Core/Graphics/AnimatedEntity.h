//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
	 * Esta clase representa un listener para poder saber cuando termina una animaci�n.
	*/
	class AnimatedEntityListener {
	public:
		/**
		 * M�todo que ser� invocado siempre que una animaci�n, no c�clica, se termine.
		 * @param animation El nombre de la animaci�n terminada.
		 */
		virtual void animationFinished(const std::string & animation) {}
	};

	/**
	 * Esta clase representa una entidad gr�fica animada dentro de una escena.
	 */
	class AnimatedEntity : public GraphicEntity {
	public:
		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Inicia una animaci�n de la entidad.
		 * @param name El nombre de la animaci�n.
		 * @param loop El flag de reproducci�n c�clica.
		 * @return De vuelve true si se logra iniciar la animaci�n.
		 */
		bool setAnimation(const std::string & name, bool loop);

		/**
		 * Para una animaci�n de la entidad.
		 * @param name El nombre de la animaci�n.
		 * @return De vuelve true si se logra parar la animaci�n.
		 */
		bool stopAnimation(const std::string & name);

		/**
		 * Para todas las animaciones de la entidad.
		 */
		void stopAllAnimations();

		/**
		 * Registra el "oyente" de la entidad gr�fica animada.
		 */
		inline void setObserver(AnimatedEntityListener * observer) {
			_observer = observer;
		}

		/**
		 * Elimina el "oyente" de la entidad gr�fica animada.
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
		 * El "oyente" de la entidad gr�fica animada.
		 */
		AnimatedEntityListener * _observer;

		/**
		 * La animaci�n que tiene la entidad activada.
		 */
		Ogre::AnimationState * _currentAnimation;

		//----------------------------------------------------------------------------------------------------
		// M�todos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza el estado interno de la entidad.
		 * @param lastInterval El tiempo total en segundos del �ltimo intervalo entre frame y frame.
		 */
		virtual void update(float lastInterval);

		friend class Core::Scene;
	};
}

#endif
