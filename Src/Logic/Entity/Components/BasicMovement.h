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
@file BasicMovement.h

Contiene la declaraci�n del componente que controla el movimiento de una entidad.

@see Logic::BasicMovement
@see Core::Component
*/
#ifndef __Logic_BasicMovement_H
#define __Logic_BasicMovement_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"
#include "Logic/Entity/Types of movement/IMovement.h"



//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class Position;

	/**
	Este componente controla el movimiento de una entidad.
    @ingroup logicGroup
	*/
	class BasicMovement : public Core::Component
	{
	public:
		ComponentCreateMethod(BasicMovement);

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		BasicMovement() : Component("BasicMovement"), _moveID(""), _moveDesc(""), _actionCenter(0.0f, 0.0f, 0.0f),
				_positionComponent(0), Axis(0.0f, 0.0f), _movement(0) {}

		/**
		Destructor
		*/
		virtual ~BasicMovement();

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
		M�todo llamado en cada frame que actualiza el estado del componente.
		Se encarga de mover la entidad enemigo seg�n el tipo de movimiento establecido.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);


		// =========
		// Atributos
		// =========

		// Tipo de movimiento que tendr� la entidad
		std::string _moveID;

		// Descriptor para el tipo de movimiento
		std::string _moveDesc;

		// Valores para posicionar correctamente los elementos en funci�n del centro de la acci�n
		Vector3 _actionCenter;

		// Puntero al componente de posici�n (por eficiencia simplemente, para no obtenerlo en cada tick)
		Position* _positionComponent;

		// Estructura de tipo par que contiene la posici�n actual de la entidad. Cada atributo de la estructura
		// hace referencia a un eje en concreto del plano de movimiento, sea cual sea dicho eje en el mundo 3D.
		std::pair<float, float> Axis;

		// Puntero al tipo de movimiento de la entidad.
		IMovement* _movement;


	private:

		/**
		M�todo encargado de crear e inicializar el tipo de movimiento de la entidad.
		@param Nombre del tipo de movimiento a crear (reci�n leido del mapa).
		@param Nombre del descriptor a usar (de entre los que hay para elegir, de cada tipo de movimiento).
		@return Puntero al tipo de movimiento creado.
		*/
		IMovement* createAndInitialiseMovement();


	};
}

#endif
