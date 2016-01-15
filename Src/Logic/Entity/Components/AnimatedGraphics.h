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

/**
Contiene la declaraci�n del componente que controla la representaci�n
gr�fica de una entidad est�tica.
*/

#ifndef __Logic_AnimatedGraphics_H
#define __Logic_AnimatedGraphics_H

#include "Core/Graphics/AnimatedEntity.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic {
	/**
	Componente que se encarga de la representaci�n gr�fica animada de una 
	entidad. Especializa a la clase Graphics para que la entidad gr�fica
	creada sea animada.
	<p>
	Adem�s de los mensajes de cambio de posici�n y de cambio de orientaci�n
	que acepta Graphics, acepta mensajes para poner o para una animaci�n
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
		// M�todos de AnimatedEntityListener //
		///////////////////////////////////////
		/**
		M�todo que ser� invocado siempre que se termine una animaci�n.
		Las animaciones en c�clicas no invocar�n nunca este m�todo.
		@param animation Nombre de la animaci�n terminada.
		*/
		void animationFinished(const std::string & animation);

	protected:
		/**
		 * Comprueba si un mensaje es v�lido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser v�lido devolver� true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje reci�n sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

		/**
		M�todo virtual que construye la entidad gr�fica animada de la entidad. 
		Sobreescribe el m�todo de la clase Graphics.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Entidad gr�fica creada, NULL si hubo alg�n problema.
		*/
		virtual Core::GraphicEntity * createGraphicsEntity(const Core::EntityInfoTable * entityInfo);
		
		/**
		Entidad gr�fica animada.
		*/
		Core::AnimatedEntity * _animatedGraphicsEntity;

		/**
		Animaci�n por defecto de una entidad gr�fica animada.
		*/
		std::string _defaultAnimation;
	};
}

#endif
