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
@file RouteTo.h

Contiene la declaraci�n de la clase CSteringMovement. Se encarga de
mover un avatar utilizando movimientos cin�ticos o din�micos.

@author Gonzalo Fl�rez
@date Diciembre, 2010
*/
#pragma once

#ifndef __Logic_RouteTo_H
#define __Logic_RouteTo_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	/**
	Componente que se encarga de gestionar el c�lculo y el seguimiento
	de rutas. El componente acepta mensajes de tipo ROUTE_TO con un par�metro
	_vector que indica la posici�n de destino.
	<p>
	Cuando se recibe un mensaje de este tipo, se calcula una nueva ruta
	hasta el destino indicado y se comienza su seguimiento. Para cada 
	segmento de la ruta, el componente env�a un mensaje de tipo MOVE_TO, con el 
	destino de ese segmento y el tipo de movimiento necesario como par�metros 
	(estos mensajes pueden ser aceptados por el componente SteeringMovement).
	<p>
	Cuando se llega al �ltimo punto de la ruta la entidad se detiene y env�a 
	un mensaje del tipo FINISHED_ROUTE.
	<p>
	Si es imposible obtener una ruta hasta el destino se env�a un mensaje FAILED_ROUTE.
	*/
	class RouteTo : public Core::Component
	{
	public:
		ComponentCreateMethod(RouteTo);

		/**
		Constructor
		*/
		RouteTo(void) : Component ("RouteTo"), _recalculateRoute(false), _currentRoute(0),
			_arrived(true), _seekTolerance(7.0), _arriveTolerance(0.5){};

		/**
		Destructor
		*/
		~RouteTo(void) { if (_currentRoute != 0) delete _currentRoute; };

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
		la entidad le�da del mapa (Maps::Entity). Toma del mapa el atributo
		speed que indica a la velocidad m�xima a la que se mover� la entidad.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.<p>
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es necesario.
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);

	private:
		/**
		Destino de la ruta.
		*/
		Vector3 _target;

		/**
		Indica si hay que volver a calcular la ruta
		*/
		bool _recalculateRoute;

		/**
		Indica si se ha llegado al destino.
		*/
		bool _arrived;

		/**
		Almacena el punto de la ruta al que se est� intentando llegar.
		*/
		int _currentNode;

		/**
		Almacena la ruta actual
		*/
		std::vector<Vector3> *_currentRoute;

		/**
		Guarda las distancias a las que se considera que se ha llegado a un 
		punto de ruta al usar un movimiento de tipo seek o arrive
		*/
		float _seekTolerance, _arriveTolerance;

		/**
		Guarda la tolerancia para el movimiento actual.
		*/
		float _distanceTolerance;

		/** 
		Env�a un mensaje MOVE_TO.
		@param target Destino.
		@movementType Tipo de movimiento.
		*/
		void sendMoveMessage(Vector3 target, int movementType);
	};
}

#endif
