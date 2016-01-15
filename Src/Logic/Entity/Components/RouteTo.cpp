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

#include <assert.h>

#include "Logic/Entity/Components/RouteTo.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
//#include "AI/Server.h"
//#include "AI/Movement.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"

namespace Logic 
{
	bool RouteTo::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");
		if(entityInfo->hasAttribute("arriveTolerance"))
			_arriveTolerance = entityInfo->getAttributeAsFloat("arriveTolerance");
		if(entityInfo->hasAttribute("seekTolerance"))
			_seekTolerance = entityInfo->getAttributeAsFloat("seekTolerance");
		return true;
	}

	//---------------------------------------------------------

	void RouteTo::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		// PRÁCTICA IA
		// En este método se gestiona el seguimiento de la ruta.
		// Realmente no se ocupa de mover la entidad, sino de controlar cuándo se ha 
		// llegado a un waypoint y notificar a SteeringMovement (que es quien mueve) 
		// del siguiente punto al que moverse y el tipo de movimiento a hacer.
		// El componente almacena su estado en las variables:
		// _target: destino final
		// _currentRoute: ruta actual (vector de posiciones)
		// _currentNode: posición de destino actual (posición en el vector)
		// Lo primero que hay que hacer es recalcular la ruta si es necesario.
		// A continuación hay que comprobar si la entidad ha llegado al siguiente 
		// punto de ruta. Si es así, pasamos al siguiente y hacemos las comprobaciones
		// necesarias para saber si tenemos que parar o no.
		/*
		if (_recalculateRoute) {
			if (_currentRoute != 0) delete _currentRoute;
			_currentRoute = AI::CServer::getSingletonPtr()->getAStarRoute(_owner->getPosition(), _target);
			_recalculateRoute = false;

			// Si no se puede calcular la ruta enviamos un mensaje de fallo
			if (_currentRoute == 0) {
				_arrived = true;
				GenericMessage message(MESSAGE_TYPE_FAILED_ROUTE);
				_owner->sendMessage(message, this);
			} else {
				_currentNode = 0;
				_arrived = false;
				// Si hay ruta hacemos que vaya al primer punto
				//sendMoveMessage((*_currentRoute)[0], AI::IMovement::MOVEMENT_KINEMATIC_SEEK);
				sendMoveMessage((*_currentRoute)[0], AI::IMovement::MOVEMENT_DYNAMIC_SEEK);
				_distanceTolerance = _seekTolerance;
			}
		}
		*/
		/*
		if (!_arrived) {
			// Si no hemos llegado al destino
			Vector3 currentTarget = (*_currentRoute)[_currentNode];
			// Si hemos llegado al siguiente punto
			if (_owner->getPosition().positionEquals(currentTarget, _distanceTolerance)) {
				// Pasamos al siguiente nodo
				_currentNode++;
				if (_currentNode >= _currentRoute->size()) {
					// Era el último nodo ==> parar
					_arrived = true;
					sendMoveMessage(_target, AI::IMovement::MOVEMENT_NONE);
					// Enviar un mensaje para notificar que hemos llegado la destino
					GenericMessage message(MESSAGE_TYPE_FINISHED_ROUTE);
					_owner->sendMessage(message, this);
				} else if (_currentNode == _currentRoute->size() - 1) {
					// Es el penúltimo nodo. Nos acercamos con Arrive
					//sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_KINEMATIC_ARRIVE);
					sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_DYNAMIC_ARRIVE);
					_distanceTolerance = _arriveTolerance;
				} else {
					// Nos movemos al siguiente
					//sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_KINEMATIC_SEEK);
					sendMoveMessage((*_currentRoute)[_currentNode], AI::IMovement::MOVEMENT_DYNAMIC_SEEK);
					_distanceTolerance = _seekTolerance;
				}
			}
		}
		*/
	}

	//---------------------------------------------------------

	void RouteTo::sendMoveMessage(Vector3 target, int movementType)
	{
		Vector3 msgTarget = target;
		msgTarget.y = 0.0f;
		_owner->sendMessage(MessageFactory::CreateMoveToMessage(movementType, msgTarget), this);
	}

	//---------------------------------------------------------

	bool RouteTo::acceptMessage(const Core::SmartMessage & message)
	{
		return message->getType() == MESSAGE_TYPE_ROUTE_TO;
	}

	//---------------------------------------------------------

	void RouteTo::processMessage(const Core::SmartMessage & message)
	{
		/*
		switch(message._type)
		{
		case MESSAGE_TYPE_ROUTE_TO:
			// Comprobamos el _bool para saber si tenemos que calcular la ruta o detenernos
			if (message._bool) {
				// Anotamos el vector de desplazamiento para usarlo posteriormente en 
				// el método tick. De esa forma, si recibimos varios mensajes AVATAR_MOVE
				// en el mismo ciclo sólo tendremos en cuenta el último.
				_target = message._vector3;
				_recalculateRoute = true;
			} else {
				// Dejamos de avanzar por la ruta
				_recalculateRoute = false;
				_arrived = true;
				// Eliminamos la ruta
				if (_currentRoute != 0) {
					delete _currentRoute;
					_currentRoute = 0;
				}
				// Y enviamos un mensaje para parar
				sendMoveMessage(_target, AI::IMovement::MOVEMENT_NONE);
			}
			break;
		}
		*/
	}
}
