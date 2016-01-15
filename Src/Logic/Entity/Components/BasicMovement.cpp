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
Contiene la implementación del componente que controla el movimiento de una entidad.
*/

#include <assert.h>

#include "Logic/Entity/Components/BasicMovement.h"

#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Messages/MessageTypes.h"

#include "Core/Scripting/ScriptingManager.h"
#include "Core/Scripting/InfoTableUtils.h"

namespace Logic
{

	BasicMovement::~BasicMovement()
	{
		// Liberamos el tipo de movimiento de la entidad.
		if(_movement)
		{
			delete _movement;
			_movement = 0;
		}
	}

	//---------------------------------------------------------

	bool BasicMovement::spawn(const Core::EntityInfoTable *entityInfo) 
	{
		assert(_owner && "The component does not have an entity...");

		// Leemos los atributos de inicialización del componente
//		if(entityInfo->hasAttribute("movementID"))
//			_moveID = entityInfo->getAttribute("movementID");

		if(entityInfo->hasAttribute("movementDescriptor")) {
			_moveDesc = entityInfo->getAttribute("movementDescriptor");
		}

		// Creamos e inicializamos el tipo de movimiento de la entidad
		_movement = createAndInitialiseMovement();
		assert(_movement && "Error al crear el tipo de movimiento. O bien se ha escrito mal en el mapa, o ha habido un error al inicializarlo.");
						
		return true;
	}
	
	//---------------------------------------------------------

	bool BasicMovement::activate()
	{
		// Obtenemos el centro sobre el que realizar los movimientos
		_actionCenter = Logic::MissionManager::GetInstance()->getCenter();

		// Obtenemos el puntero al componente de posición
		_positionComponent = _owner->getComponentAs<Position>("Position");

		// Llamamos al "activate" del movimiento
		_movement->activate();

		return true;
	}

	//---------------------------------------------------------

	void BasicMovement::update(unsigned int lastInterval)
	{
		Component::update(lastInterval);

		// Obtenemos la posición actual de la entidad
		Vector3 pos = _positionComponent->getPosition();
		
		// Obtenemos el centro sobre el que realizar los movimientos
		_actionCenter = Logic::MissionManager::GetInstance()->getCenter();

		// Preparamos todo adecuadamente dependiendo del tipo de vista actual
		CameraType cameraType = Logic::MissionManager::GetInstance()->getCameraType();
		if(cameraType==SIDE || cameraType==SIDE_ROTATE) Axis.first = pos.y;
		else Axis.first = -pos.x;
		Axis.second = pos.z;


		// Calculamos un nuevo paso del movimiento
		_movement->calculatePath(Axis, _actionCenter, cameraType, lastInterval);


		// Ajustamos los ejes adecuadamente según la vista de la cámara
		if(cameraType==SIDE || cameraType==SIDE_ROTATE)
		{
			pos.y = Axis.first;
			pos.x = _actionCenter.x;
		}
		else
		{
			pos.x = -Axis.first;
			pos.y = _actionCenter.y;
		}
		pos.z = Axis.second;

		//  Por último actualizamos la posición de la entidad
		_positionComponent->setPosition(pos);

		//printf("X: %f; Y: %f; Z: %f\n", pos.x, pos.y, pos.z);
	}

	//---------------------------------------------------------

	bool BasicMovement::acceptMessage(const Core::SmartMessage & message)
	{
		// Llamamos al "accept" del movimiento en concreto
		return _movement->accept(message);
	}
	
	//---------------------------------------------------------

	void BasicMovement::processMessage(const Core::SmartMessage & message)
	{
		// Llamamos al "process" del movimiento en concreto
		_movement->process(message);
	}

	//---------------------------------------------------------

	IMovement* BasicMovement::createAndInitialiseMovement()
	{
		Core::InfoTable* info = 0;
		IMovement* movement = 0;

		// Construimos el nombre completo del descriptor
		std::string descriptor = _moveDesc;
		descriptor.append(".lua");

		// Cargamos el descriptordel movimiento
		if (Core::ScriptingManager::GetInstance()->loadAndRunFile(descriptor)) {
			info = Core::LuaGetInfoTable(_moveDesc);	// Obtenemos la tabla de datos del descriptor

			// Creamos e inicializamos el movimiento
			movement = MissionManager::GetInstance()->getMovementsFactory().create(info->getAttribute("movementID"));
			if(!movement->spawn(info, _owner))
				movement = 0;	// Si se ha inicializado mal, devolvemos error
		}

		// Liberamos la tabla de información
		if(info) {
			delete info;
			info = 0;
		}

		return movement;
	}


}
