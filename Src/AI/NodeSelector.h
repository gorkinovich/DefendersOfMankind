/**
 * @file NodeSelector.h
 *
 * Implementación de un nodo selector.
 *
 * @author "Gonzalo Flórez"
 * @date 11/04/2011
 */

#ifndef __AI_NodeSelector_H_
#define __AI_NodeSelector_H_


#include "BehaviorTreeBase.h"

namespace AI
{
	/**
	 * Implementación de un nodo selector para un BT.
	 * <p>
	 * Este nodo ejecuta cada uno de sus hijos sucesivamente hasta que
	 * alguno de ellos tiene éxito. Si recorre toda la lista de hijos y
	 * todos fallan entonces este nodo también falla.
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class CNodeSelector:public BehaviorTreeInternalNode
	{
	public:

		/**
		 * Ejecuta los siguientes hijos del nodo hasta que alguno de ellos
		 * tenga éxito o fallen todos. Si alguno queda en estado BT_RUNNING,
		 * el nodo detiene su ejecución y en el siguiente tick continúa ejecutándolo:<bR>
		 * · Si el hijo actual devuelve BT_SUCCESS, el nodo termina con éxito (BT_SUCCESS).<br>
		 * · Si el hijo actual devuelve BT_RUNNING, el nodo devuelve BT_RUNNING.
		 * En el siguiente tick se continuará ejecutando el mismo hijo.<br>
		 * · Si el hijo actual devuelve BT_FAILURE, se ejecuta el siguiente hijo. Si no hay más hijos,
		 * el nodo termina con fallo.
		 * <p>
		 * El orden de ejecución lo da el orden en que se añaden los hijos al nodo.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 * @return estado en que queda el nodo después de la ejecución
		 */
		BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Constructor
		 */
		CNodeSelector::CNodeSelector();

		/**
		 * Inicializa el nodo y todos sus hijos.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 */
		void init(void* agent);


	protected:

		int currentPosition;

	};
}

#endif __AI_NodeSelector_H_
