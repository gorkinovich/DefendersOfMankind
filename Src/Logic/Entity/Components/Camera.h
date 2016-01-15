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
@file Camera.h

Contiene la declaraci�n del componente que controla la c�mara gr�fica de una escena.

@see Logic::Camera
@see Core::Component

@author David Llans�
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
	Componente que se encarga de mover la c�mara gr�fica de una escena, para que 
	�sta se pueda reenderizar, siguiendo al jugador.<p>
	La c�mara se situar� a una distancia detr�s del jugador y a una altura del 
	suelo y enfocar� a un punto imaginario por delante del jugador que estar� 
	tambi�n a cierta altura del suelo. Todas estas caracter�sticas son configurables 
	desde la declaraci�n del mapa definiendo los nombres de atributo "distance",
	"height", "targetDistance" y "targetHeight".<p>
	El componente ir� recalculando en cada ciclo las posiciones de la c�mara y del
	punto de mira en funci�n de la posici�n y orientaci�n del jugador.
    @ingroup logicGroup
	@author David Llans� Garc�a
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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::Entity). Se accede a los atributos 
		necesarios como la c�mara gr�fica y se leen atributos del mapa.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.<p>
		Se coge el jugador del mapa, la entidad que se quiere "seguir".
		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		M�todo que desactiva el componente; invocado cuando se
		desactiva el mapa donde est� la entidad a la que pertenece el
		componente. Se invocar� siempre, independientemente de si estamos
		activados o no.<p>
		Se pone el objetivo a seguir a NULL.
		*/
		virtual void deactivate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.<p>
		Se encarga de mover la c�mara siguiendo al jugador.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

		/**
		C�mara gr�fica.
		*/
		Core::Camera * _graphicsCamera;

		/**
		Entidad que se usa como objetivo
		*/
		Core::Entity * _target;

		/**
		Distancia de la c�mara respecto a la entidad objetivo. Es distancia
		sobre el plano XZ, la altura tiene su propio atributo.
		*/
		float _distance;
		
		/**
		altura de la c�mara respecto del suelo o plano XZ.
		*/
		float _height;

		/**
		Distancia del punto al que mirar� la c�mara respecto a la entidad 
		objetivo. Es distancia sobre el plano XZ, la altura tiene su propio 
		atributo.
		*/
		float _targetDistance;
		
		/**
		altura del punto al que mirar� la c�mara respecto del suelo o plano XZ.
		*/
		float _targetHeight;

		/**
		Centro de rotaci�n de la c�mara
		*/
		Vector3 _center;

		/**
		tipo de c�mara durante el juego
		*/

		CameraType _type;

		/**
		Indica si se est� haciendo una traslaci�n de c�mara
		*/
		bool _moving;

		/**
		Indica si se est� interpolando el centro (movimiento en bifurcaciones)
		*/
		bool _interpolating;
		
		/**
		Indica el destino en caso de estar movi�ndose
		*/
		Vector3 _origin;

		/**
		Indica el destino en caso de estar movi�ndose
		*/
		Vector3 _destination;

		/**
		Indica el centro que ten�a la c�mara al empezar a moverse en un cambio de tipo
		*/
		Vector3 _origCenter;

		/**
		Indica el centro que ten�a la c�mara al empezar a moverse en un cambio de tipo
		*/
		Vector3 _oldCenter;

		/**
		Indica el centro que ten�a la c�mara al empezar a moverse en un cambio de tipo
		*/
		Vector3 _destCenter;

		/**
		Indica la rotaci�n origen en caso de estar movi�ndose
		*/
		Quaternion _origRotation;

		/**
		Indica la rotaci�n destino en caso de estar movi�ndose
		*/
		Quaternion _destRotation;
	
		/**
		La variaci�n a cada paso de la posici�n de la c�mara
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
		Posici�n actual de la c�mara
		*/
		Vector3 _actPosition;
		
		/**
		Rotaci�n actual de la c�mara
		*/
		Quaternion _actRoll;
	};
}

#endif
