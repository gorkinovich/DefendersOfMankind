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
@file SwitchTrigger.h

Contiene la declaración del componente que envia un mensaje SWITCH a una
entidad cuando su entidad es tocada o dejada de ser tocada.

@see Logic::SwitchTrigger
@see Core::Component

@author David Llansó
@date Octubre, 2010
*/
#ifndef __Logic_SwitchTrigger_H
#define __Logic_SwitchTrigger_H

#include "Core/Entities/Component.h"

namespace Core {
	class Entity;
}

namespace Logic {
	/**
	Este componente procesa mensajes de tipo TOUCHED o UNTOUCHED (indican que la 
	entidad ha sido tocada o dejada de ser tocada) para enviar un mensaje SWITCH a 
	una entidad objetivo.
	<p>
	La entidad objetivo se especifica en el mapa con el atributo "target". Este 
	atributo <em>debe</em> ser especificado.
	
    @ingroup logicGroup
	@author David Llansó García
	@date Octubre, 2010
	*/
	class SwitchTrigger : public Core::Component
	{
	public:
		ComponentCreateMethod(SwitchTrigger);

		/**
		Constructor por defecto.
		*/
		SwitchTrigger() : Component("SwitchTrigger"), _targetName(""), _target(0) {}

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
		Nombre de la entidad a la que se desea enviar un SWITCH cuando se 
		recibe un mensaje TOUCHED o UNTOUCHED.
		*/
		std::string _targetName;

		/**
		Entidad a la que se desea enviar un SWITCH cuando se recibe un mensaje 
		TOUCHED o UNTOUCHED.
		*/
		Core::Entity *_target;
	};
}

#endif
