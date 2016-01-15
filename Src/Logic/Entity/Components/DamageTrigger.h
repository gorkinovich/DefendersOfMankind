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
@file DamageTrigger.h

Contiene la declaraci�n de un componente que envia un mensaje DAMAGED cuando su 
entidad es tocada. El mensaje se env�a a la entidad que se ha tocado.

@see Logic::DamageTrigger
@see Core::Component

@author David Llans�
@date Octubre, 2010
*/
#ifndef __Logic_DamageTrigger_H
#define __Logic_DamageTrigger_H

#include <string>

#include "Core/Entities/Component.h"

// Los componentes pertenecen al namespace Logic
namespace Logic {
	/**
	Este componente procesa mensajes de tipo TOUCHED (indican que la entidad ha 
	sido tocada) para enviar un mensaje DAMAGED a la entidad que toc�.<p>
	El da�o que recibe la entidad se especifica en el mapa con el atributo "damage".
	
    @ingroup logicGroup
	@author David Llans� Garc�a
	@date Octubre, 2010
	*/
	class DamageTrigger: public Core::Component
	{
	public:
		ComponentCreateMethod(DamageTrigger);

		/**
		Constructor por defecto.
		*/
		DamageTrigger() : Component("DamageTrigger"), _damage(20.f) {}

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
		Da�o que se produce cada vez que se toca.
		*/
		float _damage;

		/**
		 * El tipo del objetivo del da�o.
		 */
		std::string _damageTarget;
	};
}

#endif
