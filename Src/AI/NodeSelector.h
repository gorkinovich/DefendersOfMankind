/**
 * @file NodeSelector.h
 *
 * Implementaci�n de un nodo selector.
 *
 * @author "Gonzalo Fl�rez"
 * @date 11/04/2011
 */

#ifndef __AI_NodeSelector_H_
#define __AI_NodeSelector_H_


#include "BehaviorTreeBase.h"

namespace AI
{
	/**
	 * Implementaci�n de un nodo selector para un BT.
	 * <p>
	 * Este nodo ejecuta cada uno de sus hijos sucesivamente hasta que
	 * alguno de ellos tiene �xito. Si recorre toda la lista de hijos y
	 * todos fallan entonces este nodo tambi�n falla.
	 *
	 * @author "Gonzalo Fl�rez"
	 * @date 11/04/2011
	 */
	class CNodeSelector:public BehaviorTreeInternalNode
	{
	public:

		/**
		 * Ejecuta los siguientes hijos del nodo hasta que alguno de ellos
		 * tenga �xito o fallen todos. Si alguno queda en estado BT_RUNNING,
		 * el nodo detiene su ejecuci�n y en el siguiente tick contin�a ejecut�ndolo:<bR>
		 * � Si el hijo actual devuelve BT_SUCCESS, el nodo termina con �xito (BT_SUCCESS).<br>
		 * � Si el hijo actual devuelve BT_RUNNING, el nodo devuelve BT_RUNNING.
		 * En el siguiente tick se continuar� ejecutando el mismo hijo.<br>
		 * � Si el hijo actual devuelve BT_FAILURE, se ejecuta el siguiente hijo. Si no hay m�s hijos,
		 * el nodo termina con fallo.
		 * <p>
		 * El orden de ejecuci�n lo da el orden en que se a�aden los hijos al nodo.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 * @return estado en que queda el nodo despu�s de la ejecuci�n
		 */
		BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Constructor
		 */
		CNodeSelector::CNodeSelector();

		/**
		 * Inicializa el nodo y todos sus hijos.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 */
		void init(void* agent);


	protected:

		int currentPosition;

	};
}

#endif __AI_NodeSelector_H_
