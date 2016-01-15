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

#ifndef __LOGIC_RECTILINEARMOVEMENT_H__
#define __LOGIC_RECTILINEARMOVEMENT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "IMovement.h"
#include <utility>

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {

	/**
	 * Esta clase representa el tipo de movimiento rectil�neo.
	 */
	class RectilinearMovement: public IMovement
	{
	public:
		MovementCreateMethod(RectilinearMovement);

		/**
		Constructor por defecto.
		*/
		RectilinearMovement() : IMovement("RectilinearMovement"), _dir(0.0f, 0.0f) {}

		/*
		Funci�n que calcula el siguiente paso de la trayectoria en particular.
		@param posAxis Estructura de tipo par que contiene la posici�n actual de la entidad. Cada atributo hace referencia
		a un eje en concreto del plano de movimiento, sea cual sea dicho eje en el mundo 3D.
		@param actionCenter Posici�n actual del centro de la acci�n.
		@param actualView Tipo actual de la vista.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		void calculatePath(std::pair<float, float>& posAxis, const Vector3& actionCenter, CameraType actualView, unsigned int lastInterval);

	protected:

		/**
		M�todo "activate" para el movimiento.
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		 * M�todo para inicializar el movimiento en base a los datos de su descriptor.
		 * @param info La informaci�n inicial del movimiento.
		 * @return Devuelve true si se inicializa correctamente.
		 */
		virtual bool spawn(Core::InfoTable* info, Core::Entity* owner);

		/**
		 * Comprueba si un mensaje es v�lido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser v�lido devolver� true.
		 */
		virtual bool accept(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje reci�n sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void process(const Core::SmartMessage & message);

	private:

		/*
		Estructura de tipo par que representa la direcci�n (y velocidad) del movimiento.
		No utilizo un vector debido a que puede dar lugar a confusi�n al leer el c�digo ya que
		los atributos ".x" y ".y" de un Vector2 pueden no coincidir con los ejes de movimiento actuales
		ya que dependen del tipo de vista. No s� si me explico bien xDD
		*/
		std::pair<float, float> _dir;

	};
}	// namespace Logic

#endif	// __LOGIC_RECTILINEARMOVEMENT_H__
