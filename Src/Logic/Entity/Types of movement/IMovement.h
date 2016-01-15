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

#ifndef __LOGIC_IMOVEMENT_H__
#define __LOGIC_IMOVEMENT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************
#include "Core/Math.h"
#include "Core/Entities/Entity.h"
#include "Logic/MissionManager.h"	// Para el tipo de vista actual
#include "Core/Data/InfoTable.h"

#include <string>
#include <utility>

//************************************************************************************************************
// Macros
//************************************************************************************************************

#define MovementCreateMethod(ClassType) static IMovement* create() { return new ClassType(); }

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {

	/**
	 * Esta clase representa la interfaz que deberán implementar todos los tipos de movimiento.
	 */
	class IMovement
	{
		public:

			/*
			Constructor.
			*/
			IMovement(const std::string& name) : _name(name) {};

			/*
			Destructor.
			*/
			virtual ~IMovement() {};

			/**
			 * Obtiene el nombre del movimiento.
			 */
			inline const std::string& getName() const { return _name; }

			/*
			Función que calcula el siguiente paso de la trayectoria en particular.
			@param posAxis Estructura de tipo par que contiene la posición actual de la entidad. Cada atributo hace referencia
			a un eje en concreto del plano de movimiento, sea cual sea dicho eje en el mundo 3D.
			@param actionCenter Posición actual del centro de la acción.
			@param actualView Tipo actual de la vista.
			@param lastInterval Milisegundos transcurridos desde el último tick.
			*/
			virtual void calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval) = 0;

			/**
			Método "activate" para el movimiento.
			@return true si todo ha ido correctamente.
			*/
			virtual bool activate() = 0;

			/**
			 * Método para inicializar el movimiento en base a los datos de su descriptor.
			 * @param info La información inicial del movimiento.
			 * @param owner Puntero a la entidad propietaria del movimiento
			 * @return Devuelve true si se inicializa correctamente.
			*/
			virtual bool spawn(Core::InfoTable* info, Core::Entity* owner) = 0;

			/**
			 * Comprueba si un mensaje es válido para ser procesado o no.
			 * @param message El mensaje enviado al puerto.
			 * @return De ser válido devolverá true.
			 */
			virtual bool accept(const Core::SmartMessage & message) = 0;

			/**
			 * Procesa un mensaje recién sacado de la lista.
			 * @param message El mensaje sacado de la lista.
			 */
			virtual void process(const Core::SmartMessage & message) = 0;



		protected:

			/*
			Nombre del movimiento.
			*/
			std::string _name;


	};
}	// namespace Logic

#endif	// __LOGIC_IMOVEMENT_H__
