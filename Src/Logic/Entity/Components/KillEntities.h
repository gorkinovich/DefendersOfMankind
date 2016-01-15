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
@file KillEntities.h

Componente encargado de enviar un mensaje de tipo LIFE_CYCLE_ON a toda entidad que entra en el volumen de colisión
de la entidad propietaria del componente.
A su vez envía un mensaje de tipo LIFE_CYCLE_RELEASE a toda entidad que sale de dicho volumen de colisión.

@see Logic::KillEntities
@see Core::Component

@author Grupo 3
@date Abril, 2011
*/
#ifndef __Logic_KillEntities_H
#define __Logic_KillEntities_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Core {
	class Entity;
}

namespace Logic {
	class Position;

	/**
	Este componente procesa mensajes de tipo TOUCHED o UNTOUCHED (indican que la 
	entidad ha sido tocada o dejada de ser tocada).
	Envía mensajes de tipo DEATH.
	
    @ingroup logicGroup
	@author Grupo 3
	@date Abril, 2011
	*/
	class KillEntities : public Core::Component
	{
	public:
		ComponentCreateMethod(KillEntities);

		/**
		Constructor por defecto.
		*/
		KillEntities() : Component("KillEntities"), _lastVictim(0), _lastVictim2(0), _dim(0.0f), _positionComponent(0) {}

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
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Método que se invoca para activar el componente.
		*/
		virtual bool activate();
		
		/**
		Método que se invoca al desactivar el componente.
		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		Se encarga de decrementar el tiempo de vida de la entidad y liberarla en su momento.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

	private:

		/*
		Dimensiones de la caja de la muerte.
		*/
		Vector3 _dim;

		/*
		HACK: necesario hasta que encuentre el fallo, que me tiene ya hasta los coj****
		*/
		Core::Entity* _lastVictim;
		Core::Entity* _lastVictim2;

		/*
		Por eficiencia simplemente, para no obtenerlo en cada tick.
		*/
		Position * _positionComponent;

	};
}

#endif
