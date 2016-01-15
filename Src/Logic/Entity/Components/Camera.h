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
@file Camera.h

Contiene la declaración del componente que controla la cámara gráfica de una escena.

@see Logic::Camera
@see Core::Component

@author David Llansó
@date Septiembre, 2010
*/
#ifndef __Logic_Camera_H
#define __Logic_Camera_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"
#include "Logic/Entity/Components/CameraType.h"

namespace Core {
	class Entity;
	class Camera;
}

namespace Logic {
	/**
	Componente que se encarga de mover la cámara gráfica de una escena, para que 
	ésta se pueda reenderizar, siguiendo al jugador.<p>
	La cámara se situará a una distancia detrás del jugador y a una altura del 
	suelo y enfocará a un punto imaginario por delante del jugador que estará 
	también a cierta altura del suelo. Todas estas características son configurables 
	desde la declaración del mapa definiendo los nombres de atributo "distance",
	"height", "targetDistance" y "targetHeight".<p>
	El componente irá recalculando en cada ciclo las posiciones de la cámara y del
	punto de mira en función de la posición y orientación del jugador.
    @ingroup logicGroup
	@author David Llansó García
	@date Septiembre, 2010
	*/
	class Camera : public Core::Component
	{
	public:
		ComponentCreateMethod(Camera);

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		Camera();

		virtual Vector3 getCenter();
		
		virtual void setCenter(/*Vector3*/);

		virtual CameraType getType();

		virtual void setType(CameraType);

		virtual float getDistance();

		virtual void setCamera();

		virtual void moveCamera(CameraType);

		virtual void interpolateCenter(Vector3, float);

		~Camera();

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
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::Entity). Se accede a los atributos 
		necesarios como la cámara gráfica y se leen atributos del mapa.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.<p>
		Se coge el jugador del mapa, la entidad que se quiere "seguir".
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.<p>
		Se pone el objetivo a seguir a NULL.
		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.<p>
		Se encarga de mover la cámara siguiendo al jugador.
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Cámara gráfica.
		*/
		Core::Camera * _graphicsCamera;

		/**
		Entidad que se usa como objetivo
		*/
		Core::Entity * _target;

		/**
		Distancia de la cámara respecto a la entidad objetivo. Es distancia
		sobre el plano XZ, la altura tiene su propio atributo.
		*/
		float _distance;
		
		/**
		altura de la cámara respecto del suelo o plano XZ.
		*/
		float _height;

		/**
		Distancia del punto al que mirará la cámara respecto a la entidad 
		objetivo. Es distancia sobre el plano XZ, la altura tiene su propio 
		atributo.
		*/
		float _targetDistance;
		
		/**
		altura del punto al que mirará la cámara respecto del suelo o plano XZ.
		*/
		float _targetHeight;

		/**
		Centro de rotación de la cámara
		*/
		Vector3 _center;

		/**
		tipo de cámara durante el juego
		*/

		CameraType _type;

		/**
		Indica si se está haciendo una traslación de cámara
		*/
		bool _moving;

		/**
		Indica si se está interpolando el centro (movimiento en bifurcaciones)
		*/
		bool _interpolating;
		
		/**
		Indica el destino en caso de estar moviéndose
		*/
		Vector3 _origin;

		/**
		Indica el destino en caso de estar moviéndose
		*/
		Vector3 _destination;

		/**
		Indica el centro que tenía la cámara al empezar a moverse en un cambio de tipo
		*/
		Vector3 _origCenter;

		/**
		Indica el centro que tenía la cámara al empezar a moverse en un cambio de tipo
		*/
		Vector3 _oldCenter;

		/**
		Indica el centro que tenía la cámara al empezar a moverse en un cambio de tipo
		*/
		Vector3 _destCenter;

		/**
		Indica la rotación origen en caso de estar moviéndose
		*/
		Quaternion _origRotation;

		/**
		Indica la rotación destino en caso de estar moviéndose
		*/
		Quaternion _destRotation;
	
		/**
		La variación a cada paso de la posición de la cámara
		*/
		Vector3 _direction;

		/**
		El tiempo actual del travelling
		*/
		unsigned int _travelTime;

		/**
		El tiempo actual de la interpolacion
		*/
		unsigned int _interpTime;

		/**
		El tiempo total que debe durar la interpolacion
		*/
		float _interpTotalTime;

		/**
		Posición actual de la cámara
		*/
		Vector3 _actPosition;
		
		/**
		Rotación actual de la cámara
		*/
		Quaternion _actRoll;
	};
}

#endif
