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
@file PowerUpController.h

Controlador del estado de los power ups activados en el jugador.

@see Logic::PowerUpController
@see Core::Component

@author Grupo 3
@date Abril, 2011
*/
#ifndef __Logic_PowerUpController_H
#define __Logic_PowerUpController_H

#include "Core/Entities/Component.h"

namespace Core {
	class Entity;
}

namespace Logic {

	/**
	Este componente procesa mensajes que activan el power up determinado
	
    @ingroup logicGroup
	@author Grupo 3
	@date Junio, 2011
	*/
	class PowerUpController : public Core::Component
	{
	public:
		ComponentCreateMethod(PowerUpController);

		/**
		Constructor por defecto.
		*/
		PowerUpController() : Component("PowerUpController"), _autoFireTime(0),
			_invincibilityTime(0), _superSpeedTime(0), _autoHealTime(0),
			_damageUpTime(0), _autoFire(false), _invincibility(false), 
			_superSpeed(false), _autoHeal(false),_damageUp(false){}

		/**
		 * Devuelve si está activado el flag damageUp.
		 */
		bool getDamageUp() {return _damageUp;}

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
		Método llamado en cada frame que actualiza el estado de los power ups.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

	private:

		/**
		Tiempo que durarán los power ups
		*/
		unsigned int _powerUpTotalTime;

		/**
		Tiempo transcurrido del power up autodisparo
		*/
		unsigned int _autoFireTime;

		/**
		Tiempo transcurrido del power up invencibilidad
		*/
		unsigned int _invincibilityTime;
		
		/**
		Tiempo transcurrido del power up supervelocidad
		*/
		unsigned int _superSpeedTime;
		
		/**
		Tiempo transcurrido del power up recperación progresiva de vida
		*/
		unsigned int _autoHealTime;
		
		/**
		Tiempo transcurrido del power up aumento de daño
		*/
		unsigned int _damageUpTime;

		/**
		Power up autodisparo activado
		*/
		bool _autoFire;

		/**
		Power up invencibilidad activado
		*/
		bool _invincibility;

		/**
		Power up autodisparo activado
		*/
		bool _superSpeed;

		/**
		Power up autodisparo activado
		*/
		bool _autoHeal;

		/**
		Power up autodisparo activado
		*/
		bool _damageUp;

	};
}

#endif