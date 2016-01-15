/*
@file BehaviourTreesLatentActions.cpp

Fichero que implementa las acciones latentes propias de los árboles de comportamiento.

@author Grupo 3
@date Junio 2011
*/
#include <assert.h>

#include "BehaviourTreesLatentActions.h"
#include "BehaviorExecutionContext.h"
#include "Server.h"

#include "Core/BaseManager.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"

#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Logic/Entity/Messages/CreateChildMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantMessage.h"
#include "Logic/Entity/Messages/GoToVirtualQuadrantAbortMessage.h"


#include "Logic/Entity/Components/Life.h"
#include "Logic/Entity/Components/Position.h"

#include "Logic/MissionManager.h"
#include <stdlib.h>


namespace AI 
{

/**
==========================================================================================
CLA_BT_CHECK_LIFE: Esta acción comprueba si la vida de la entidad está por debajo del 100%.
==========================================================================================
*/

	CLatentAction::LAStatus CLA_BT_CHECK_LIFE::OnStart()
	{	

		float life = _entity->getComponentAs<Logic::Life>("Life")->getLife();
		if (life<40.0f)	return SUCCESS;
		
		return FAIL;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHECK_LIFE::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHECK_LIFE::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHECK_LIFE::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_CHECK_LIFE::accept(const Core::SmartMessage & message)
	{

		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHECK_LIFE::process(const Core::SmartMessage & message)
	{
	}



/**
====================================================================
CLA_BT_SHOOT: Esta acción ordena a la entidad que genere un disparo.
====================================================================
*/

	CLatentAction::LAStatus CLA_BT_SHOOT::OnStart()
	{	
		//printf("SHOOT\n");
		_entity->sendMessage(Logic::MessageFactory::CreateCreateChildMessage(0,"") );
		_entity->getComponentAs<Logic::Life>("Life")->setLife(40.0f);

		return SUCCESS;
	}

	// -----------------------------------------------------------

	void CLA_BT_SHOOT::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_SHOOT::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_SHOOT::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_SHOOT::accept(const Core::SmartMessage & message)
	{

		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_SHOOT::process(const Core::SmartMessage & message)
	{
	}



/**
=======================================================================================================
CLA_BT_CHECK_HEIGHT: esta acción comprueba si el jugador se encuentra a la misma altura que la entidad.
=======================================================================================================
*/

	CLatentAction::LAStatus CLA_BT_CHECK_HEIGHT::OnStart()
	{	
		// Obtenemos la entidad "Jugador"
		Core::Entity* player = _entity->getWorld()->getEntityByName("Jugador1");
		assert(player && "CLA_BT_AVOID_PLAYER::constructor --> Puntero a la entidad jugador no válido.");
		// Obtenemos un puntero a su componente de posición
		Logic::Position* _playerPositionComponent = player->getComponentAs<Logic::Position>("Position");
		assert(_playerPositionComponent && "CLA_BT_AVOID_PLAYER::constructor --> Puntero al componente POSITION de la entidad jugador no válido.");

		// Obtenemos la posición actual del jugador
		Vector3 playerPos = _playerPositionComponent->getPosition();

		// Obtenemos el cuadrante en el que se encuentra el jugador
		Logic::CameraType actualView = Logic::MissionManager::GetInstance()->getCameraType();
		TQuadrant* q = _virtualBoard.getQuadrantFromPosition(playerPos, actualView);
		int playerQ1 = q->first; int playerQ2 = q->second;

		// Obtenemos el cuadrante en el que se encuentra la entidad
		Vector3 entityPos = _entity->getComponentAs<Logic::Position>("Position")->getPosition();
		q = _virtualBoard.getQuadrantFromPosition(entityPos, actualView);

		// Comprobamos si estan a la misma "altura"
		if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
		{
			if (q->second == playerQ2)
			{
				return SUCCESS;
			}
		}
		else
		{
			if (q->first == playerQ1)
			{
				return SUCCESS;
			}
		}

		return FAIL;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHECK_HEIGHT::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHECK_HEIGHT::OnRun()
	{

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHECK_HEIGHT::OnAbort() 
	{	
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_CHECK_HEIGHT::accept(const Core::SmartMessage & message)
	{
		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHECK_HEIGHT::process(const Core::SmartMessage & message)
	{
	}




/**
================================================================================================
CLA_BT_CHANGE_TARGET_QUADRANT: esta acción calcula un nuevo cuadrante objetivo y lo guarda en el
contexto de ejecución.
================================================================================================
*/

	CLatentAction::LAStatus CLA_BT_CHANGE_TARGET_QUADRANT::OnStart()
	{	
		// Obtenemos la vista actual
		Logic::CameraType actualView = Logic::MissionManager::GetInstance()->getCameraType();

		// Obtenemos el cuadrante en el que se encuentra la entidad
		Vector3 entityPos = _entity->getComponentAs<Logic::Position>("Position")->getPosition();
		TQuadrant* q = _virtualBoard.getQuadrantFromPosition(entityPos, actualView);

		int targetQ1 = 0;
		int targetQ2 = 0;
	

		// Cambiamos el cuadrante objetivo teniendo en cuenta el tipo de vista actual
		if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
		{
			targetQ1 = q->first;
			targetQ2 = rand() % 7 - 3;
		}
		else
		{
			targetQ1 = rand() % 7 - 3;
			targetQ2 = q->second;
		}

		// Guardamos el nuevo objetivo en el contexto
		_context->setIntAttribute("targetQ1", targetQ1);
		_context->setIntAttribute("targetQ2", targetQ2);
		
		return SUCCESS;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHANGE_TARGET_QUADRANT::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHANGE_TARGET_QUADRANT::OnRun()
	{

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHANGE_TARGET_QUADRANT::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_CHANGE_TARGET_QUADRANT::accept(const Core::SmartMessage & message)
	{
		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHANGE_TARGET_QUADRANT::process(const Core::SmartMessage & message)
	{
	}


/**
=======================================================================================================
CLA_BT_MOVE_TO_QUADRANT: esta acción envía un mensaje para que la entidad se mueva hacia otro cuadrante.
=======================================================================================================
*/

	CLatentAction::LAStatus CLA_BT_MOVE_TO_QUADRANT::OnStart()
	{	
		// Comprobamos que existe la información adecuada en el contexto
		if ( !_context->hasAttribute("targetQ1") || !_context->hasAttribute("targetQ2") )
		{
			assert("Error en BT: cuadrante objetivo no encontrado");
			_entity->sendMessage(Logic::MessageFactory::CreateGoToVirtualQuadrantAbortMessage());
			return FAIL;
		}

		// Leemos el cuadrante objetivo del contexto
		int targetQ1 = _context->getIntAttribute("targetQ1");
		int targetQ2 = _context->getIntAttribute("targetQ2");

		// Enviamos un mensaje con el nuevo cuadrante objetivo
		_entity->sendMessage(Logic::MessageFactory::CreateGoToVirtualQuadrantMessage(targetQ1, targetQ2) );

		return SUSPENDED;
		
	}

	// -----------------------------------------------------------

	void CLA_BT_MOVE_TO_QUADRANT::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_MOVE_TO_QUADRANT::OnRun()
	{

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_MOVE_TO_QUADRANT::OnAbort() 
	{
		// Enviamos un mensaje para abortar el movimiento
		_entity->sendMessage(Logic::MessageFactory::CreateGoToVirtualQuadrantAbortMessage());

		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_MOVE_TO_QUADRANT::accept(const Core::SmartMessage & message)
	{
		return (message->getType() == MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_END);
	}

	// -----------------------------------------------------------

	void CLA_BT_MOVE_TO_QUADRANT::process(const Core::SmartMessage & message)
	{
		if (message->getType() == MESSAGE_TYPE_TARGET_VIRTUAL_QUADRANT_END)
		{
			finish(true);
		}
	}



/**
======================================
CLA_BT_IDLE: Esta acción no hace nada.
======================================
*/

	CLatentAction::LAStatus CLA_BT_IDLE::OnStart()
	{	
		//printf("BT: Idle node\n");
		//_entity->sendMessage(Logic::MessageFactory::CreateGoToVirtualQuadrantAbortMessage());


		return RUNNING;
	}

	// -----------------------------------------------------------

	void CLA_BT_IDLE::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_IDLE::OnRun()
	{
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_IDLE::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_IDLE::accept(const Core::SmartMessage & message)
	{
		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_IDLE::process(const Core::SmartMessage & message)
	{
	}



/**
===================================================================================================
CLA_BT_INIT_QUADRANT: esta acción guarda el el contexto de ejecución el cuadrante objetivo inicial.
===================================================================================================
*/

	CLatentAction::LAStatus CLA_BT_INIT_QUADRANT::OnStart()
	{		

		// Comprobamos que en el contexto hay un cuadrante objetivo inicial
		if ( _context->hasAttribute("targetQ1") && _context->hasAttribute("targetQ2") )
		{
			return SUCCESS;
		}

		return FAIL;		
	}

	// -----------------------------------------------------------

	void CLA_BT_INIT_QUADRANT::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_INIT_QUADRANT::OnRun()
	{

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_INIT_QUADRANT::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_INIT_QUADRANT::accept(const Core::SmartMessage & message)
	{
		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_INIT_QUADRANT::process(const Core::SmartMessage & message)
	{
	}


/**
=======================================================================================================
CLA_BT_CHECK_HEIGHT_BOSS2: esta acción comprueba si el jugador se encuentra a la misma altura que la entidad.
=======================================================================================================
*/

	CLatentAction::LAStatus CLA_BT_CHECK_HEIGHT_BOSS2::OnStart()
	{	
		// Obtenemos la entidad "Jugador"
		Core::Entity* player = _entity->getWorld()->getEntityByName("Jugador1");
		assert(player && "CLA_BT_BOSS_LEVEL2::onStart --> Puntero a la entidad jugador no válido.");
		// Obtenemos un puntero a su componente de posición
		Logic::Position* _playerPositionComponent = player->getComponentAs<Logic::Position>("Position");
		assert(_playerPositionComponent && "CLA_BT_BOSS_LEVEL2::onStart --> Puntero al componente POSITION de la entidad jugador no válido.");

		// Obtenemos la posición actual del jugador
		Vector3 playerPos = _playerPositionComponent->getPosition();

		// Obtenemos el cuadrante en el que se encuentra el jugador
		Logic::CameraType actualView = Logic::MissionManager::GetInstance()->getCameraType();
		TQuadrant* q = _virtualBoard.getQuadrantFromPosition(playerPos, actualView);
		int playerQ1 = q->first; int playerQ2 = q->second;

		// Obtenemos el cuadrante en el que se encuentra la entidad
		Vector3 entityPos = _entity->getComponentAs<Logic::Position>("Position")->getPosition();
		q = _virtualBoard.getQuadrantFromPosition(entityPos, actualView);

		// Comprobamos si estan a la misma "altura"
		if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
		{
			assert(false && "BT (BossLevel2): no definido para las vistas de perfil.");
		}
		else
		{
			if (q->first == playerQ1)	// Si esta a la misma altura que el jugador
			{
				if(q->second != -2) _context->setStringAttribute("State", "GoFront");
				else _context->setStringAttribute("State", "GoBack");
			}
			else
			{
				if (_left)
				{
					if (q->first>-5)_context->setStringAttribute("State", "Left");
					else _left = false;
				}
				if (!_left)
				{
					if (q->first<5) _context->setStringAttribute("State", "Right");
					else _left = true;
				}
			}
		}


		return SUCCESS;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHECK_HEIGHT_BOSS2::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHECK_HEIGHT_BOSS2::OnRun()
	{

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHECK_HEIGHT_BOSS2::OnAbort() 
	{	
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_CHECK_HEIGHT_BOSS2::accept(const Core::SmartMessage & message)
	{
		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHECK_HEIGHT_BOSS2::process(const Core::SmartMessage & message)
	{
	}

/**
================================================================================================
CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2: esta acción calcula un nuevo cuadrante objetivo y lo guarda en el
contexto de ejecución.
================================================================================================
*/

	CLatentAction::LAStatus CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2::OnStart()
	{	
		// Obtenemos la vista actual
		Logic::CameraType actualView = Logic::MissionManager::GetInstance()->getCameraType();

		// Obtenemos el cuadrante en el que se encuentra la entidad
		Vector3 entityPos = _entity->getComponentAs<Logic::Position>("Position")->getPosition();
		TQuadrant* q = _virtualBoard.getQuadrantFromPosition(entityPos, actualView);

		int targetQ1 = 0;
		int targetQ2 = 0;

		if (!_context->hasAttribute("State"))
		{
			assert(false && "BT (BossLevel2): la variable STATE no existe en el contexto.");
		}

		std::string state = _context->getStringAttribute("State");
		if (state == "GoFront")
		{
			// Cambiamos el cuadrante objetivo teniendo en cuenta el tipo de vista actual
			if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
			{
				assert(false && "BT (BossLevel2): no definido para las vistas de perfil.");
			}
			else
			{
				targetQ1 = q->first;
				targetQ2 = -3;
			}
		}
		else if(state == "GoBack")
		{
			// Cambiamos el cuadrante objetivo teniendo en cuenta el tipo de vista actual
			if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
			{
				assert(false && "BT (BossLevel2): no definido para las vistas de perfil.");
			}
			else
			{
				targetQ1 = q->first;
				targetQ2 = 3;
			}
		}
		else if(state == "Left")
		{
			// Cambiamos el cuadrante objetivo teniendo en cuenta el tipo de vista actual
			if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
			{
				assert(false && "BT (BossLevel2): no definido para las vistas de perfil.");
			}
			else
			{
				targetQ1 = q->first-1;
				targetQ2 = 3;
			}
		}
		else if(state == "Right")
		{
			// Cambiamos el cuadrante objetivo teniendo en cuenta el tipo de vista actual
			if (actualView==Logic::SIDE || actualView==Logic::SIDE_ROTATE)
			{
				assert(false && "BT (BossLevel2): no definido para las vistas de perfil.");
			}
			else
			{
				targetQ1 = q->first+1;
				targetQ2 = 3;
			}
		}


		// Guardamos el nuevo objetivo en el contexto
		_context->setIntAttribute("targetQ1", targetQ1);
		_context->setIntAttribute("targetQ2", targetQ2);
		
		return SUCCESS;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2::OnRun()
	{

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2::accept(const Core::SmartMessage & message)
	{
		return false;
	}

	// -----------------------------------------------------------

	void CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2::process(const Core::SmartMessage & message)
	{
	}


} //namespace AI 