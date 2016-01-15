/**
 * @file DoMBehaviorTrees.h
 *
 * Distintas clases que implementan comportamientos de ejemplo para los BTs de DoM.
 * <p>
 * Las clases incluidas son:<br>
 * · CBT_Test: cuando la entidad pierde vida, ésta genera un disparo.<br>
 * · CBT_AvoidPlayer: Situa al enemigo a distinta altura que el jugador para que no le den sus disparos.
 *
 *
 */


#ifndef AI_DoMBehaviorTrees_H_
#define AI_DoMBehaviorTrees_H_

#include "BehaviorTreeBase.h"
#include "NodeParallel.h"
#include "NodeSequential.h"
#include "NodePriorityInterrupt.h"
#include "NodeRepeat.h"

#include "Core/Entities/Entity.h"

namespace AI
{
	/*
	Árbol de comportamiento de prueba:
		- Cuando la entidad recibe un impacto de bala...
		- Se genera un disparo por parte de la entidad.
	*/
	class CBT_Test : public CNodeSequential
	{
		public:

			CBT_Test(Core::Entity* entity);
			~CBT_Test() {};

		private:
			Core::Entity* _entity;

	}; //class CBT_Test



	/*
	Árbol de comportamiento que esquiva al jugador:
		- Cuando la entidad detecta que el jugador está a su misma altura...
		- Entonces cambia de posición para esquivar sus disparos.
	*/
	class CBT_AvoidPlayer : public CNodeSequential
	{
		public:

			CBT_AvoidPlayer(Core::Entity* entity);
			~CBT_AvoidPlayer() {};

		private:
			Core::Entity* _entity;

	}; //class CBT_AvoidPlayer


	/*
	Árbol de comportamiento del jefe final del nivel 2.
	*/
	class CBT_Boss_Level2 : public CNodeSequential
	{
		public:

			CBT_Boss_Level2(Core::Entity* entity);
			~CBT_Boss_Level2() {};

		private:
			Core::Entity* _entity;

	}; //class CBT_AvoidPlayer



	/**
	Factoría que devuelve árboles de comportamiento predefinidos.
	*/
	class CBehaviourTreeFactory 
	{
	public:
		static BehaviorTreeNode* getBehaviourTree(std::string smName, Core::Entity * entity)
		{
			// Árbol de comportamiento de prueba
			if (smName == "BT_Test") {
				return new CBT_Test(entity);
			}
			// Árbol de comportamiento que se situa a distinta altura del jugador
			else if (smName == "BT_AvoidPlayer") {
				return new CBT_AvoidPlayer(entity);
			}
			// Árbol de comportamiento que se situa a distinta altura del jugador
			else if (smName == "BT_Boss_Level2") {
				return new CBT_Boss_Level2(entity);
			}
			else return 0;
		}
	};



} //namespace AI

#endif AI_DoMBehaviorTrees_H_
