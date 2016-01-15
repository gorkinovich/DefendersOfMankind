/**
 * @file NodeParallel.h
 *
 * Implementaci�n del nodo Parallel de un BT
 *
 * @author "Gonzalo Fl�rez"
 * @date 11/04/2011
 */

#ifndef AI_ParallelNode_H_
#define AI_ParallelNode_H_

#include "BehaviorTreeBase.h"


namespace AI
{
	/**
	 * Esta clase implementa un nodo de tipo parallel. Es un nodo compuesto que ejecuta
	 * todos sus hijos "en paralelo" (en el mismo tick).
	 * <p>
	 * Para decidir si falla o tiene �xito, el nodo tiene dos pol�ticas de fallo y dos
	 * pol�ticas de �xito posibles. Para el fallo, puede fallar cuando fallan todos sus
	 * hijos o cuando alguno de ellos falla. De la misma forma, puede tener �xito si lo
	 * tienen todos sus hijos o si lo tiene alguno de ellos.
	 *
	 *
	 * @author "Gonzalo Fl�rez"
	 * @date 11/04/2011
	 */
	class CNodeParallel:public BehaviorTreeInternalNode
	{
	public:
		/**
		 * Ejecuta cada uno de los hijos del nodo. Aunque todos se ejecutan
		 * en el mismo tick, dentro del tick se ejecutan seg�n el orden en que
		 * se a�adieron.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 * @return estado en que queda el nodo despu�s de la ejecuci�n
		 */
		BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Inicializa el nodo parallel y todos sus hijos.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 */
		void init(void* agent);

		/**
		 * Constructor. Recibe como par�metros las pol�ticas de fallo y de �xito.
		 * <p>
		 * La pol�tica de fallo indica en qu� casos tiene que fallar este nodo
		 * (si fallan TODOS sus hijos o si falla ALGUNO de sus hijos). La pol�tica
		 * de �xito, en qu� casos tiene �xito (si lo tienen TODOS sus hijos o si lo
		 * tiene ALGUNO sus hijos). En  el caso de que se solapen gana la pol�tica de fallo.
		 *
		 * @param failurePolicy Pol�tica de fallo: FAIL_ON_ALL (valor por defecto) indica que
		 * 						fallar� si fallan todos sus hijos y FAIL_ON_ONE si falla alguno.
		 * @param successPolicy Pol�tica de �xito: SUCCEED_ON_ALL (valor por defecto) indica que
		 * 						tendr� �xito si lo tienen todos sus hijos y SUCCEED_ON_ONE si lo tiene alguno.
		 */
		CNodeParallel( FAILURE_POLICY failurePolicy = FAIL_ON_ALL, SUCCESS_POLICY successPolicy = SUCCEED_ON_ALL);

		/**
		 * Destructor. Libera todos sus hijos.
		 */
		virtual ~CNodeParallel(void);

	private:

		/*
		Mapa con los punteros de los nodos hijos y su estado
		*/
		typedef std::map<BehaviorTreeNode*, BEHAVIOR_STATUS> ChildrenStatusMap;
		ChildrenStatusMap* childrenStatus;

		/*
		Politicas de fallo y �xito
		*/
		FAILURE_POLICY failPolicy;
		SUCCESS_POLICY succeedPolicy;
	};
}


#endif AI_ParallelNode_H_
