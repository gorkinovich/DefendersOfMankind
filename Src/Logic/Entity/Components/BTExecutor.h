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

/*
Componente encargado de ejecutar un �rbol de comportamiento (BT)
*/

#ifndef __Logic_BTExecutor_H
#define __Logic_BTExecutor_H

#include "Core/Entities/Component.h"

#include "AI/BehaviorTreeBase.h"

namespace AI
{
	class CLatentAction;
	class CBehaviorExecutionContext;
}

namespace Logic
{
	class BTExecutor : public Core::Component
	{

	public:
		ComponentCreateMethod(BTExecutor);

		/*
		Constructor
		*/
		BTExecutor();

		/*
		Destructor
		*/
		~BTExecutor();

	protected:

		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

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


	private:

		/*
		�rbol de comportamiento a ejecutar
		*/
		AI::BehaviorTreeNode* _bt;

		/*
		Contexto de ejecuci�n del BT
		*/
		AI::CBehaviorExecutionContext* _context;

	}; //class BTExecutor

} // namespace Logic

#endif __Logic_BTExecutor_H