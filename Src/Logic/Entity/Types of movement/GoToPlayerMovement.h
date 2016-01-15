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

#ifndef __LOGIC_GOTOPLAYERMOVEMENT_H__
#define __LOGIC_GOTOPLAYERMOVEMENT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "IMovement.h"

#include "Logic/Entity/Components/Position.h"
#include <utility>

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {

	/**
	 * Esta clase representa un tipo de movimiento que constantemente se dirige hacia la posición actual del jugador.
	 */
	class GoToPlayerMovement: public IMovement
	{
	public:
		MovementCreateMethod(GoToPlayerMovement);

		/**
		Constructor por defecto.
		*/
		GoToPlayerMovement() : IMovement("GoToPlayerMovement"), _owner(0), _playerTarget(0), _playerPositionComponent(0), _vel(0.0f) {}

		/*
		Función que calcula el siguiente paso de la trayectoria en particular.
		@param posAxis Estructura de tipo par que contiene la posición actual de la entidad. Cada atributo hace referencia
		a un eje en concreto del plano de movimiento, sea cual sea dicho eje en el mundo 3D.
		@param actionCenter Posición actual del centro de la acción.
		@param actualView Tipo actual de la vista.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		void calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval);

	protected:

		/**
		Método "activate" para el movimiento.
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		 * Método para inicializar el movimiento en base a los datos de su descriptor.
		 * @param info La información inicial del movimiento.
		 * @return Devuelve true si se inicializa correctamente.
		 */
		virtual bool spawn(Core::InfoTable* info, Core::Entity* owner);

		/**
		 * Comprueba si un mensaje es válido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser válido devolverá true.
		 */
		virtual bool accept(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje recién sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void process(const Core::SmartMessage & message);

	private:

		/*
		Entidad propietaria del movimiento (en este movimiento si se usa)
		*/
		Core::Entity* _owner;

		/*
		Indica a cual de los dos jugadores se debe perseguir
		*/
		unsigned int _playerTarget;

		/*
		Puntero al componente de posición de la entidad jugador a seguir
		*/
		Logic::Position* _playerPositionComponent;

		/*
		Velocidad a la que se realiza el movimiento
		*/
		float _vel;

		/*
		Velocidad a la que se mueve verticalmente
		*/
		float _velVert;

	};
}	// namespace Logic

#endif	// __LOGIC_GOTOPLAYERMOVEMENT_H__
