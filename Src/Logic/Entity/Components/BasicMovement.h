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
@file BasicMovement.h

Contiene la declaración del componente que controla el movimiento de una entidad.

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
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		Se encarga de mover la entidad enemigo según el tipo de movimiento establecido.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);


		// =========
		// Atributos
		// =========

		// Tipo de movimiento que tendrá la entidad
		std::string _moveID;

		// Descriptor para el tipo de movimiento
		std::string _moveDesc;

		// Valores para posicionar correctamente los elementos en función del centro de la acción
		Vector3 _actionCenter;

		// Puntero al componente de posición (por eficiencia simplemente, para no obtenerlo en cada tick)
		Position* _positionComponent;

		// Estructura de tipo par que contiene la posición actual de la entidad. Cada atributo de la estructura
		// hace referencia a un eje en concreto del plano de movimiento, sea cual sea dicho eje en el mundo 3D.
		std::pair<float, float> Axis;

		// Puntero al tipo de movimiento de la entidad.
		IMovement* _movement;


	private:

		/**
		Método encargado de crear e inicializar el tipo de movimiento de la entidad.
		@param Nombre del tipo de movimiento a crear (recién leido del mapa).
		@param Nombre del descriptor a usar (de entre los que hay para elegir, de cada tipo de movimiento).
		@return Puntero al tipo de movimiento creado.
		*/
		IMovement* createAndInitialiseMovement();


	};
}

#endif
