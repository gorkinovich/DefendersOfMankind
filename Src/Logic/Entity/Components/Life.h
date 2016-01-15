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
@file Life.h

Contiene la declaraci�n del componente que controla la vida de una entidad.

@see Logic::Life
@see Core::Component

@author David Llans�
@date Octubre, 2010
*/
#ifndef __Logic_Life_H
#define __Logic_Life_H

#include "Core/Entities/Component.h"

namespace Logic 
{
	/**
	Este componente controla la vida de una entidad. Procesa mensajes de tipo 
	DAMAGED (indican que la entidad ha sido herida) y resta el da�o a la vida de la
	entidad. <p>
	La vida de la entidad se especifica en el mapa con el atributo "life".

	@todo  Si la vida pasa a ser 0 que la entidad muera (poner animaci�n de muerte?)
	y si es el jugador habr� que terminar el juego. Si la vida sigue siendo mayor 
	que 0 tr�s un golpe �poner la animaci�n de herido?.
	
    @ingroup logicGroup
	@author David Llans� Garc�a
	@date Octubre, 2010
	*/
	class Life : public Core::Component {
	public:
		ComponentCreateMethod(Life);

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		Life() : Component("Life"), _life(100.f), _maxLife(100.0f), _playerLifeCounter(3), _dead(false), 
			_isPlayer(false), _isBullet(false), _isPlayerBullet(false), _isBoss(false),  _invincibility(false), _autoHeal(false), _actualHealTime(0), 
			_healInterval(100) {}

		/*
		M�todo que devuelve el n�mero de vidas restantes del jugador
		*/
		inline int getPlayerLives() { return _playerLifeCounter; }

		/*
		M�todos para obtener/modificar la cantidad de vida restante de la entidad
		*/
		inline float getLife() { return _life; }
		inline void setLife(float life) { _life = life; }

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
		M�todo llamado en cada frame que actualiza el estado de los power ups.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Vida de la entidad
		*/
		float _life;

		/**
		M�xima vida de la entidad
		*/
		float _maxLife;

		/**
		N�mero de vidas restantes del jugador
		*/
		int _playerLifeCounter;

		/**
		Indica si ya fue puesto en cola para ser eliminado
		*/
		bool _dead;

		/**
		Indica si el padre del componente es la nave del jugador
		*/
		bool _isPlayer;

		/**
		Indica si la entidad propietaria del componente es una bala
		*/
		bool _isBullet;
		bool _isPlayerBullet;

		/**
		Indica si la entidad propietaria del componente es una bala
		*/
		bool _isBoss;

		/**
		Indica si estamos en modo invincibilidad
		*/
		bool _invincibility;

		/**
		Indica si estamos en recuperaci�n de vida autom�tica
		*/
		bool _autoHeal;

		/**
		Tiempo actual entre recuperaci�n y recuperaci�n de unidad de vida
		*/
		unsigned int _actualHealTime;

		/**
		Intervalo entre recuperaci�n y recuperaci�n de unidad de vida
		*/
		unsigned int _healInterval;

	};
}

#endif
