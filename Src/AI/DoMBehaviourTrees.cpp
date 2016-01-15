/**
 * @file DoMBehaviorTrees.cpp
 *
 * Distintas clases que implementan comportamientos de ejemplo para los BTs de DoM.
 * <p>
 * Las clases incluidas son:<br>
 * · CBT_Test: cuando la entidad pierde vida, ésta genera un disparo.<br>
 * · CBT_AvoidPlayer: Situa al enemigo a distinta altura que el jugador para que no le den sus disparos.
 *
 *
 */

#include "DoMBehaviourTrees.h"


#include "SimpleLatentActions.h"
#include "BehaviourTreesLatentActions.h"
#include "NodeLA.h"

#include "LifeCycleLatentActions.h"



namespace AI
{

	// ----------------------------------------------------------------------
	// -------------------- BT: TEST ----------------------------------------
	// ----------------------------------------------------------------------

	CBT_Test::CBT_Test(Core::Entity* entity) : CNodeSequential()
	{
		// Guardamos un puntero a la entidad propietaria del BT
		_entity = entity;

		// Construimos el BT ("this" es un nodo secuencia)
		this->addChild( (new AI::CNodeLA( new AI::CLA_BT_CHECK_LIFE(entity) ) ));
		this->addChild( (new AI::CNodeLA( new AI::CLA_BT_SHOOT(entity) ) ));
	}



	// ----------------------------------------------------------------------
	// -------------------- BT: AVOID PLAYER --------------------------------
	// ----------------------------------------------------------------------

	CBT_AvoidPlayer::CBT_AvoidPlayer(Core::Entity* entity) : CNodeSequential()
	{
		// Guardamos un puntero a la entidad propietaria del BT
		_entity = entity;

		// Construimos el BT ("this" es un nodo secuencia)
		BehaviorTreeNode* check_height = new AI::CNodeLA (new AI::CLA_BT_CHECK_HEIGHT(entity));
		BehaviorTreeNode* change_target_quadrant = new AI::CNodeLA (new AI::CLA_BT_CHANGE_TARGET_QUADRANT(entity));
		BehaviorTreeNode* move_to_quadrant = new AI::CNodeLA (new AI::CLA_BT_MOVE_TO_QUADRANT(entity));
		BehaviorTreeNode* idle = new AI::CNodeLA (new AI::CLA_BT_IDLE(entity));

		BehaviorTreeInternalNode* sequential = new AI::CNodeSequential();
		BehaviorTreeInternalNode* priority_interrupt = new AI::CNodePriorityInterrupt();

		sequential->addChild(check_height);
		sequential->addChild(change_target_quadrant);
		sequential->addChild(move_to_quadrant);

		priority_interrupt->addChild(sequential);
		priority_interrupt->addChild(idle);

		BehaviorTreeInternalNode* repeat = new AI::CNodeRepeat(-1);
		repeat->addChild(priority_interrupt);

		BehaviorTreeNode* init_quadrant = new AI::CNodeLA (new AI::CLA_BT_INIT_QUADRANT(entity));
		BehaviorTreeNode* move_to_quadrant2 = new AI::CNodeLA (new AI::CLA_BT_MOVE_TO_QUADRANT(entity));

		this->addChild(init_quadrant);
		this->addChild(move_to_quadrant2);
		this->addChild(repeat);
	}


	// ----------------------------------------------------------------------
	// -------------------- BT: BOSS LEVEL 2 --------------------------------
	// ----------------------------------------------------------------------

	CBT_Boss_Level2::CBT_Boss_Level2(Core::Entity* entity) : CNodeSequential()
	{
		// Guardamos un puntero a la entidad propietaria del BT
		_entity = entity;

		// Construimos el BT ("this" es un nodo secuencia)
		BehaviorTreeNode* check_height = new AI::CNodeLA (new AI::CLA_BT_CHECK_HEIGHT_BOSS2(entity));
		BehaviorTreeNode* change_target_quadrant = new AI::CNodeLA (new AI::CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2(entity));
		BehaviorTreeNode* move_to_quadrant = new AI::CNodeLA (new AI::CLA_BT_MOVE_TO_QUADRANT(entity));
		BehaviorTreeNode* idle = new AI::CNodeLA (new AI::CLA_BT_IDLE(entity));

		BehaviorTreeInternalNode* sequential = new AI::CNodeSequential();
		BehaviorTreeInternalNode* priority_interrupt = new AI::CNodePriorityInterrupt();

		sequential->addChild(check_height);
		sequential->addChild(change_target_quadrant);
		sequential->addChild(move_to_quadrant);

		priority_interrupt->addChild(sequential);
		priority_interrupt->addChild(idle);

		BehaviorTreeInternalNode* repeat = new AI::CNodeRepeat(-1);
		repeat->addChild(priority_interrupt);

		BehaviorTreeNode* init_quadrant = new AI::CNodeLA (new AI::CLA_BT_INIT_QUADRANT(entity));
		BehaviorTreeNode* move_to_quadrant2 = new AI::CNodeLA (new AI::CLA_BT_MOVE_TO_QUADRANT(entity));

		this->addChild(init_quadrant);
		this->addChild(move_to_quadrant2);
		this->addChild(repeat);
	}


} // namespace AI
