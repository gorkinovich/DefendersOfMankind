/**
 * @file NodeParallel.h
 *
 * Implementación del nodo Parallel de un BT
 *
 * @author "Gonzalo Flórez"
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
	 * Para decidir si falla o tiene éxito, el nodo tiene dos políticas de fallo y dos
	 * políticas de éxito posibles. Para el fallo, puede fallar cuando fallan todos sus
	 * hijos o cuando alguno de ellos falla. De la misma forma, puede tener éxito si lo
	 * tienen todos sus hijos o si lo tiene alguno de ellos.
	 *
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class CNodeParallel:public BehaviorTreeInternalNode
	{
	public:
		/**
		 * Ejecuta cada uno de los hijos del nodo. Aunque todos se ejecutan
		 * en el mismo tick, dentro del tick se ejecutan según el orden en que
		 * se añadieron.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 * @return estado en que queda el nodo después de la ejecución
		 */
		BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Inicializa el nodo parallel y todos sus hijos.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 */
		void init(void* agent);

		/**
		 * Constructor. Recibe como parámetros las políticas de fallo y de éxito.
		 * <p>
		 * La política de fallo indica en qué casos tiene que fallar este nodo
		 * (si fallan TODOS sus hijos o si falla ALGUNO de sus hijos). La política
		 * de éxito, en qué casos tiene éxito (si lo tienen TODOS sus hijos o si lo
		 * tiene ALGUNO sus hijos). En  el caso de que se solapen gana la política de fallo.
		 *
		 * @param failurePolicy Política de fallo: FAIL_ON_ALL (valor por defecto) indica que
		 * 						fallará si fallan todos sus hijos y FAIL_ON_ONE si falla alguno.
		 * @param successPolicy Política de éxito: SUCCEED_ON_ALL (valor por defecto) indica que
		 * 						tendrá éxito si lo tienen todos sus hijos y SUCCEED_ON_ONE si lo tiene alguno.
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
		Politicas de fallo y éxito
		*/
		FAILURE_POLICY failPolicy;
		SUCCESS_POLICY succeedPolicy;
	};
}


#endif AI_ParallelNode_H_
