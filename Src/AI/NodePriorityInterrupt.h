/**
 * @file NodePriorityInterrupt.h
 *
 * Implementaci�n de un nodo selector con prioridad
 *
 * @author "Gonzalo Fl�rez"
 * @date 11/04/2011
 */

#ifndef AI_NodePriorityInterrupt_H_
#define AI_NodePriorityInterrupt_H_

#include "NodeSelector.h"

namespace AI
{

	/**
	 * Implementaci�n de un nodo selector con prioridad para un BT.
	 * <p>
	 * Este nodo ejecuta sus hijos sucesivamente hasta que uno de ellos tiene �xito,
	 * pero se diferencia del selector en que en cada tick vuelve a intentar ejecutar
	 * todos los nodos desde el principio. Si alguno de los nodos que hab�a fallado antes
	 * se puede ejecutar ahora pasa a ejecutarse, y el que se estaba ejecutando, al tener
	 * menor prioridad, se cancela.
	 *
	 * @author "Gonzalo Fl�rez"
	 * @date 11/04/2011
	 */
	class CNodePriorityInterrupt : public CNodeSelector
	{

	public:

		/**
		 * Constructor
		 */
		CNodePriorityInterrupt() : CNodeSelector() { currentPosition = -1; _name = "Priority interrupt";};

		/**
		 * El comportamiento de este nodo es muy parecido al del nodo selector (CNodeSelector).<br>
		 * Intenta ejecutar todos los nodos desde el m�s prioritario. Si alguno de los nodos
		 * no falla, cancela todos los nodos siguientes, si alguno de ellos se estaba ejecutando.
		 * <p>
		 * � Si el hijo actual devuelve BT_SUCCESS, el nodo termina con �xito (BT_SUCCESS).<br>
		 * � Si el hijo actual devuelve BT_RUNNING, el nodo devuelve BT_RUNNING.
		 * En el siguiente tick se continuar� ejecutando el mismo hijo.<br>
		 * En estos dos casos, si se estaba ejecutando alg�n nodo de menor prioridad se cancela su
		 * ejecuci�n.
		 * � Si el hijo actual devuelve BT_FAILURE, se ejecuta el siguiente hijo. Si no hay m�s hijos,
		 * el nodo termina con fallo.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 * @return estado en que queda el nodo despu�s de la ejecuci�n
		 */
		BEHAVIOR_STATUS execute(void* agent);

	};

} // namespace AI

#endif AI_NodePriorityInterrupt_H_
