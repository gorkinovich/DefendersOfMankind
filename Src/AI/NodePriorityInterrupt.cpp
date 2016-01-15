#include "NodePriorityInterrupt.h"

namespace AI
{

	// -----------------------------------------------------------
	
	BEHAVIOR_STATUS CNodePriorityInterrupt::execute(void* agent)
	{
		if (children.size() == 0)
			return BT_SUCCESS;

		if (currentPosition == -1)
			init(agent);

		// Nodo que vamos a comprobar a continuación
		int checkedNode = 0;
		BEHAVIOR_STATUS status;
		BehaviorTreeNode* currentlyRunningNode;
		while (checkedNode < children.size()) //keep trying children until one doesn't fail
		{
			currentlyRunningNode = children.at(checkedNode);
			status = currentlyRunningNode->execute(agent);
			if (status == BT_FAILURE) {
				// Si el nodo falla al ejecutarse lo reiniciamos y pasamos al siguiente
				currentlyRunningNode->init(agent);
				checkedNode++;
			} else {
				// Si el nodo actual se ejecuta tenemos que comprobar si se ha interrumpido 
				// la ejecución de otro nodo menos prioritario, para poder reinicializarlo.
				// El último nodo no ejecutado se almacena en currentPosition. 
				// Tendremos que comprobar si tiene menos prioridad, es decir, si su índice
				// es mayor que el que ocupa el que acabamos de ejecutar con éxito.
				if (checkedNode < currentPosition)
					children.at(currentPosition)->init(agent);
				// Si el nodo ha terminado con éxito, el selector también termina con éxito
				if (status == BT_SUCCESS) {
					// Además, dejamos inicializado el nodo que acaba de terminar para la próxima vuelta
					currentlyRunningNode->init(agent);
					currentPosition = 0;
					return BT_SUCCESS;
				} else {
					// Sólo queda que el status sea BT_RUNNING
					// En este caso actualizamos el nodo actual por si ha cambiado
					currentPosition = checkedNode;
					return BT_RUNNING;
				}
				//assert(!"BT in an unsupported state");
			}
		}
		// Si ha llegado al final de la lista de nodos y todos han fallado el selector
		// tendrá también que fallar
		currentPosition = 0;
		return BT_FAILURE;
	}

} // namespace AI
