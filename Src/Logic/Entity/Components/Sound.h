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
@file Sound.h

Contiene la declaraci�n del componente que controla los sonidos que genera la entidad.

@see Logic::Sound
@see Core::Component
*/
#ifndef __Logic_Sound_H
#define __Logic_Sound_H

#include "Core/Entities/Component.h"
#include "Core/Sound/Sound.h"

#include <map>


//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {

	class Sound : public Core::Component
	{
	public:
		ComponentCreateMethod(Sound);

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		Sound() : Component("Sound"), _idSound(0) {}

		/**
		Destructor
		*/
		virtual ~Sound();

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
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		M�todo que se invoca al desactivar el componente.
		*/
		virtual void deactivate();


		// =========
		// Atributos
		// =========

		// Mapa con los sonidos de la entidad
		typedef std::map<std::string, Core::Sound*> TSoundsMap;
		typedef TSoundsMap::iterator TSoundsMapIterator;
		TSoundsMap _soundsMap;

		// Contador del n�mero de sonidos creados hasta el momento. Necesario para no repetir nombre del sonido al crearlo.
		unsigned int _idSound;

	};
}

#endif
