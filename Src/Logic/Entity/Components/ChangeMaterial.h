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
@file ChangeMaterial.h

Contiene la declaraci�n del componente que controla el cambio del material de la entidad en tiempo real.
Para ello acepta y procesa mensajes de tipo SWITCH.

@see Logic::ChangeMaterial
@see Core::Component

@author Grupo 3
@date Abril, 2011
*/
#ifndef __Logic_ChangeMaterial_H
#define __Logic_ChangeMaterial_H

#include "Core/Entities/Component.h"

namespace Logic {
	/**
	Este componente controla los cambios del material de la entidad durante el juego.
    @ingroup logicGroup
	@author Grupo 3
	@date Abril, 2011
	*/
	class ChangeMaterial : public Core::Component
	{
	public:
		ComponentCreateMethod(ChangeMaterial);

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		ChangeMaterial() : Component("ChangeMaterial"), _entityInfo(0) {}

		/**
		Destructor. Borra la informaci�n de las tablas con la informaci�n de los materiales.
		*/
		~ChangeMaterial();

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
		M�todo que se invoca para activar el componente.
		*/
		virtual bool activate();

		/**
		M�todo que se invoca al desactivar el componente.
		*/
		virtual void deactivate();

		/*
		Tablas hash con informaci�n acerca de los materiales:
			- Clave: �ndice de cada subentidad
			- Valor: nombre del material asociado a la subentidad
		*/
		typedef std::map<unsigned int, std::string> TMaterialTable;
		typedef TMaterialTable::iterator TMaterialTableIterator;
		TMaterialTable _origMaterials;		// Guarda los materiales originales
		TMaterialTable _modifiedMaterials;	// Guarda los materiales nuevos
		const Core::EntityInfoTable * _entityInfo;
	};
}

#endif
