/**
 * @file NodeSequential.h
 *
 * Implementación de un nodo secuencial
 *
 * @author "Gonzalo Flórez"
 * @date 11/04/2011
 */

#ifndef AI_SequentialNode_H_
#define AI_SequentialNode_H_

#include "BehaviorTreeBase.h"

namespace AI
{
///Executes behaviors in order
/** Executes its children in the order they were added.
If the currently executing child returns BT_FAILURE, BT_ERROR, or BT_RUNNING, this returns the same status.
If the currently executing child returns BT_SUCCESS, this begins executing the next child, if it exists. It continues in this fashion until one of the children returns BT_FAILURE, BT_ERROR, or BT_RUNNING. If all children have successfully executed, it will return BT_SUCCESS.
*/

/**
 * Implementación de un nodo secuencial para un BT.
 * <p>
 * En los nodos secuenciales se ejecutan sus hijos por orden. El orden en que
 * se ejecutarán viene dado por el orden en que se añadieron a la secuencia.
 * <p>
 * Un nodo secuencia falla si ALGUNO de sus hijos falla. Un nodo secuencia tiene
 * éxito si TODOS sus hijos tienen éxito.
 *
 *
 * @author "Gonzalo Flórez"
 * @date 11/04/2011
 */
	class CNodeSequential :public BehaviorTreeInternalNode
	{
		public:

			/**
			 * Constructor
			 */
			CNodeSequential::CNodeSequential();

			/**
			 * Ejecuta los siguientes nodos de la secuencia.
			 * <p>
			 * La ejecución terminará si alguno de los hijos falla (entonces el nodo
			 * secuencia falla) o si devuelve BT_RUNNING (el nodo secuencia también
			 * devuelve BT_RUNNING). Si el hijo actual devuelve BT_SUCCESS, pasa a
			 * ejecutarse el siguiente. Si es el último, entonces el nodo secuencia
			 * termina con éxito.
			 *
			 * @param agent dato que podemos pasar al árbol para su ejecución
			 * @return estado en que queda el nodo después de la ejecución
			 */
			BEHAVIOR_STATUS execute(void* agent);

			/**
			 * Inicializa el nodo y todos sus hijos.
			 *
			 * @param agent dato que podemos pasar al árbol para su ejecución
			 */
			void init(void* agent);

		protected:
			/**
			 * Número de hijo que se está ejecutando actualmente. -1 indica que no se está ejecutando ninguno.
			 */
			int currentPosition;
	};
}

#endif AI_SequentialNode_H_
