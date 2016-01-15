/**
 * @file NodeSequential.h
 *
 * Implementaci�n de un nodo secuencial
 *
 * @author "Gonzalo Fl�rez"
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
 * Implementaci�n de un nodo secuencial para un BT.
 * <p>
 * En los nodos secuenciales se ejecutan sus hijos por orden. El orden en que
 * se ejecutar�n viene dado por el orden en que se a�adieron a la secuencia.
 * <p>
 * Un nodo secuencia falla si ALGUNO de sus hijos falla. Un nodo secuencia tiene
 * �xito si TODOS sus hijos tienen �xito.
 *
 *
 * @author "Gonzalo Fl�rez"
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
			 * La ejecuci�n terminar� si alguno de los hijos falla (entonces el nodo
			 * secuencia falla) o si devuelve BT_RUNNING (el nodo secuencia tambi�n
			 * devuelve BT_RUNNING). Si el hijo actual devuelve BT_SUCCESS, pasa a
			 * ejecutarse el siguiente. Si es el �ltimo, entonces el nodo secuencia
			 * termina con �xito.
			 *
			 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
			 * @return estado en que queda el nodo despu�s de la ejecuci�n
			 */
			BEHAVIOR_STATUS execute(void* agent);

			/**
			 * Inicializa el nodo y todos sus hijos.
			 *
			 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
			 */
			void init(void* agent);

		protected:
			/**
			 * N�mero de hijo que se est� ejecutando actualmente. -1 indica que no se est� ejecutando ninguno.
			 */
			int currentPosition;
	};
}

#endif AI_SequentialNode_H_
