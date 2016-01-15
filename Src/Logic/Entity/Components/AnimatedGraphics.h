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

/**
Contiene la declaración del componente que controla la representación
gráfica de una entidad estática.
*/

#ifndef __Logic_AnimatedGraphics_H
#define __Logic_AnimatedGraphics_H

#include "Core/Graphics/AnimatedEntity.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic {
	/**
	Componente que se encarga de la representación gráfica animada de una 
	entidad. Especializa a la clase Graphics para que la entidad gráfica
	creada sea animada.
	<p>
	Además de los mensajes de cambio de posición y de cambio de orientación
	que acepta Graphics, acepta mensajes para poner o para una animación
	(SET_ANIMATION y STOP_ANIMATION).
	*/
	class AnimatedGraphics : public Graphics, public Core::AnimatedEntityListener
	{
	public:
		ComponentCreateMethod(AnimatedGraphics);

		/**
		Constructor por defecto; inicializa los atributos a su valor por defecto.
		*/
		AnimatedGraphics() : Graphics("AnimatedGraphics"), _animatedGraphicsEntity(0), _defaultAnimation("") {}

		///////////////////////////////////////
		// Métodos de AnimatedEntityListener //
		///////////////////////////////////////
		/**
		Método que será invocado siempre que se termine una animación.
		Las animaciones en cíclicas no invocarán nunca este método.
		@param animation Nombre de la animación terminada.
		*/
		void animationFinished(const std::string & animation);

	protected:
		/**
		 * Comprueba si un mensaje es válido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser válido devolverá true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje recién sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

		/**
		Método virtual que construye la entidad gráfica animada de la entidad. 
		Sobreescribe el método de la clase Graphics.
		@param entityInfo Información de construcción del objeto leído del fichero de disco.
		@return Entidad gráfica creada, NULL si hubo algún problema.
		*/
		virtual Core::GraphicEntity * createGraphicsEntity(const Core::EntityInfoTable * entityInfo);
		
		/**
		Entidad gráfica animada.
		*/
		Core::AnimatedEntity * _animatedGraphicsEntity;

		/**
		Animación por defecto de una entidad gráfica animada.
		*/
		std::string _defaultAnimation;
	};
}

#endif
