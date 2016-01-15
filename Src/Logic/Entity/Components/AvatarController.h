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
@file AvatarController.h

Contiene la declaraci�n del componente que controla el movimiento 
de la entidad.

@see Logic::AvatarController
@see Core::Component

@author David Llans�
@date Agosto, 2010
*/
#ifndef __Logic_AvatarController_H
#define __Logic_AvatarController_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"
#include "Core/Input/Keys.h"
#include "Core/Input/GamePadState.h"

//declaraci�n de la clase
namespace Logic {
	/**
	Este componente es el encargado de mover a una entidad animada. Tiene
	diferentes m�todos que permiten avances o giros. El uso de este componente
	es un poco at�pico ya que se puede registrar en otro controlador externo
	(i.e. GUI::CPlayerController) que sea el que de las �rdenes que se deben
	llevar a cabo mediante llamadas a m�todos p�blicos del componente. Puede
	no obstante ampliarse este componente para aceptar mensajes tradicionales
	con las �rdenes, sin embargo de momento as� es suficiente.
	
    @ingroup logicGroup
	@author David Llans� Garc�a
	@date Agosto, 2010
	*/
	class AvatarController : public Core::Component
	{
	public:
		ComponentCreateMethod(AvatarController);

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		AvatarController() : Component("AvatarController"), _up(false), _down(false), 
			_left(false), _right(false), _fire(false), _damageUp(false), _speed(0.05f), _travelTime(0.0f),
			_limitX(75.0f), _limitY(45.0f), _limitZ(75.0f), _offset(0,0,0), _speedUp(false),
			_autoFire(false), _fireTime(0){}
		//AvatarController() : Component(), _walking(false), _walkingBack(false), 
		//	_strafingLeft(false), _strafingRight(false), _speed(0.05f) {}
		
		//void upPressed();
		//void downPressed();
		//void leftPressed();
		//void rightPressed();
		//void firePressed();

		//void upReleased();
		//void downReleased();
		//void leftReleased();
		//void rightReleased();
		//void fireReleased();

		///**
		//Provoca que la entidad avance.
		//*/
		//void walk();

		///**
		//Provoca que la entidad retroceda.
		//*/
		//void walkBack();

		///**
		//Provoca que la entidad cese el avance.
		//*/
		//void stopWalk();

		///**
		//Provoca que la entidad se desplace lateralmente a la izquierda.
		//*/
		//void strafeLeft();

		///**
		//Provoca que la entidad se desplace lateralmente a la derecha.
		//*/
		//void strafeRight();

		///**
		//Provoca que la entidad cese el desplazamiento lateral.
		//*/
		//void stopStrafe();

		///**
		//Acci�n especial para depuraci�n.
		//*/
		//void specialAction();

		/**
		Provoca que la entidad gire. N�meros Positivos para	giro a 
		derechas, negativos para giro izquierdas.

		@param amount Cantidad de giro. Positivos giro a derechas,
		negativos a izquierdas.
		*/
		void turn(float amount);

	protected:
		/**
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::Entity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se mover� el jugador.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se registra as� mismo en el controlador del GUI para que las ordenes 
		se reciban a partir de los eventos de teclado y rat�n.
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.<p>
		Si el componente pertenece a la entidad del jugador, el componente
		se deregistra as� mismo en el controlador del GUI para dejar de
		recibir las ordenes dadas a partir de los eventos de teclado y rat�n.
		*/
		virtual void deactivate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando est� andando o desplaz�ndose lateralmente).
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


		bool _up;
		bool _down;
		bool _right;
		bool _left;
		bool _fire;

		float _travelTime;

		/**
		Atributo para saber si la entidad est� avanzando.
		*/
		//bool _walking;

		/**
		Atributo para saber si la entidad est� retrocediendo.
		*/
		//bool _walkingBack;

		/**
		Atributo para saber si la entidad est� moviendose lateralmente
		a la izquierda.
		*/
		//bool _strafingLeft;

		/**
		Atributo para saber si la entidad est� moviendose lateralmente
		a la derecha.
		*/
		//bool _strafingRight;

		/**
		Atributo que indica la magnitud de velocidad de la entidad.
		*/
		float _speed;

		/**
		Atributo que indica la distancia respecto al centro de la escena.
		*/
		Vector3 _offset;

		/**
		Indica si tenemos activada la supervelocidad
		*/
		bool _speedUp;

		/**
		Indica si tenemos activado el autodisparo
		*/
		bool _autoFire;

		/**
		Indica si tenemos activada el da�o mayor
		*/
		bool _damageUp;

		/**
		Indica el tiempo entre disparo y disparo
		*/
		unsigned int _fireTime;

		/**
		Variables que controlan los l�mites del movimiento
		*/
		float _limitX;
		float _limitY;
		float _limitZ;

		

		/**
		 * Delegado para procesar el evento de una tecla pulsada.
		 */
		bool keyPressed(Core::KeyCode key);
		
		/**
		 * Delegado para procesar el evento de una tecla pulsada.
		 */
		bool keyReleased(Core::KeyCode key);
		
		/**
		 * Delegado para procesar el evento de un movimiento en el mando.
		 */
		bool gamePadAxis(const Core::GamePadState & state, unsigned short player);
		
		/**
		 * Delegado para procesar el evento de un bot�n pulsado en el mando.
		 */
		bool gamePadPressed(const Core::GamePadState & state, unsigned short player);
		
		/**
		 * Delegado para procesar el evento de un bot�n soltado en el mando.
		 */
		bool gamePadReleased(const Core::GamePadState & state, unsigned short player);
	};
}

#endif
