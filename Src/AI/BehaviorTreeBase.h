
#ifndef __AI_BehaviorTreeBase_H
#define __AI_BehaviorTreeBase_H

#include <vector>
#include <map>

#include "Core/Entities/Message.h"

namespace AI
{

	class CBehaviorExecutionContext;

	/// Enumerates the states every node can be in after execution during a particular time step
	/**
	- BT_SUCCESS indicates the node has completed running during this time step.
	- BT_FAILURE indicates the node has determined it will not be able to complete its task.
	- BT_RUNNING indicates that the node has successfully moved forward during this time step, but the task is not yet complete.
	*/
	enum BEHAVIOR_STATUS {BT_SUCCESS,BT_FAILURE,BT_RUNNING};
	
	class BehaviorTreeNode;
	
	/// A standard vector of Behavior Tree nodes. Provided for convenience.
	typedef std::vector<BehaviorTreeNode*> BehaviorTreeList;
	
	/// A standard iterator of a BehaviorTreeList. Provided for convenience.
	typedef BehaviorTreeList::iterator BehaviorTreeListIter;

	/// Enumerates the options for when a parallel node is considered to have failed.
	/**
	- FAIL_ON_ONE indicates that the node will return failure as soon as one of its children fails.
	- FAIL_ON_ALL indicates that all of the node's children must fail before it returns failure.

	If FAIL_ON_ONE and SUCEED_ON_ONE are both active and are both trigerred in the same time step, failure will take precedence.
	*/
	enum FAILURE_POLICY {FAIL_ON_ONE,FAIL_ON_ALL};
	
	/// Enumerates the options for when a parallel node is considered to have succeeded.
	/**
	- SUCCEED_ON_ONE indicates that the node will return success as soon as one of its children succeeds.
	- SUCCEED_ON_ALL indicates that all of the node's children must succeed before it returns success.
	*/
	enum SUCCESS_POLICY {SUCCEED_ON_ONE,SUCCEED_ON_ALL};


	///Abstract base clase for Behavior Tree Nodes
	/**
	 *
	 * Clase abstracta base de los árboles de comportamiento.
	 * <p>
	 * Esta clase representa a un nodo genérico y define los métodos para
	 * inicializarlo (init) y ejecutar la acción asociada al nodo (execute),
	 * además de otros métodos auxiliares.
	 * <p>
	 * Todos los tipos de nodos de los árboles (incluidos los nodos
	 * intermedios) heredan directa o indirectamente de esta clase.
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class BehaviorTreeNode
	{
	public:
		/**
		 * Destructor virtual
		 *
		 */
		virtual ~BehaviorTreeNode() {};

		/**
		 * Ejecuta la acción asociada al nodo. Es un método abstracto que deberán implementar
		 * todas las clases que deriven de esta.
		 * <p>
		 * El valor devuelto por este método será:<br>
		 * · BT_SUCCESS: si la acción del nodo ha terminado con éxito.<br>
		 * · BT_FAILURE: si la acción del nodo ha fallado.<br>
		 * · BT_RUNNING: si la acción necesita más ticks para poder terminar.<br>
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 * @return estado en que queda el nodo después de la ejecución
		 */
		virtual BEHAVIOR_STATUS execute(void* agent) = 0;

		/// This method will be invoked before the node is executed for the first time.
		/**
		 * Inicialización del nodo. Este método abstracto inicializa los datos necesarios
		 * para la ejecución del nodo.
		 * <p>
		 * Este método será invocado cada vez que se necesite reiniciar un nodo:<br>
		 * · Antes de la primera ejecución.<bR>
		 * · Cuando el padre necesite que el nodo se reinicie.<br>
		 * <p>
		 * Por ejemplo, si tenemos un nodo de tipo secuencia, cuando se ejecuta por primera
		 * vez, el nodo se inicializa, inicializando a su vez a todos sus hijos. Si el nodo
		 * termina y vuelve a ejecutarse de nuevo, tendrá que inicializar también a sus hijos
		 * de nuevo.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 */

		virtual void init(void* agent) = 0;
		/**
		 * Modifica el nombre de un nodo. El nombre sólo se utiliza para facilitar la
		 * depuración.
		 *
		 * @param name Nombre del nodo
		 * @return El nodo con el nombre modificado
		 */
		BehaviorTreeNode* setName(const std::string name) { _name = name; return this; };

		/**
		 * Devuelve el nombre de un nodo. El nombre sólo se utiliza para facilitar la
		 * depuración.
		 *
		 * @return Nombre del nodo
		 */
		std::string getName() { return _name; }

		/**
		 * Devuelve cierto si el nodo acepta el mensaje que recibe como parámetro
		 *
		 * @param message Mensaje
		 * @return true si se acepta este mensaje
		 */
		virtual bool accept(const Core::SmartMessage & message) { return false; };

		/**
		 * Procesa un mensaje. En general, el procesamiento lo realizará otra clase
		 * asociada al nodo (por ejemplo, una acción latente).
		 *
		 * @param message Mensaje
		 */
		virtual void process(const Core::SmartMessage & message) { };

		/**
		 * Asigna un contexto de ejecución al nodo. El contexto de ejecución permite
		 * almacenar y recuperar valores y también comunicarselos a otros nodos.
		 *
		 * @param context Contexto de ejecución del nodo
		 */
		virtual void useContext(CBehaviorExecutionContext* context) { _context = context; };

	protected:
		/**
		 * Nombre del nodo
		 */
		std::string _name;
		/**
		 * Contexto de ejecución
		 */
		CBehaviorExecutionContext * _context;
	};



	/// Abstract base class for Behavior Tree nodes with children
	/**
	 * Clase abstracta que representa un nodo intermedio de un árbol de comportamiento.
	 * <p>
	 * Hereda de BehaviorTreeNode.
	 * <p>
	 * Añade a su clase padre una lista en la que almacena los nodos hijos y un método
	 * para añadírselos.
	 * <p>
	 * De esta clase heredarán todos los nodos intermedios y los decoradores.
	 *
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class BehaviorTreeInternalNode :public BehaviorTreeNode
	{

	public:

		/// Add a child to this node. Takes ownership of the child.
		/**
		 * Añade un nuevo hijo a este nodo. El comportamiento por defecto es añadirlo
		 * a la lista de hijos, aunque puede ser modificado si es necesario (por ejemplo,
		 * en el caso de un decorador habrá que comprobar que sólo se añade un hijo).
		 * <p>
		 * El nodo se hace responsable de eliminar todos sus hijos cuando se destruya.
		 *
		 * @param newChild Nodo que se añadirá como hijo de este nodo intermedio
		 * @return Puntero al nodo al que se ha añadido el hijo
		 */
		virtual BehaviorTreeInternalNode* addChild(BehaviorTreeNode* newChild);

		/**
		 * Devuelve cierto si alguno de sus hijos acepta el mensaje que recibe como parámetro.
		 *
		 * @param message Mensaje
		 * @return true si se acepta este mensaje
		 */
		virtual bool accept(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje. Se delega el procesamiento en los hijos del nodo.
		 *
		 * @param message Mensaje
		 */
		virtual void process(const Core::SmartMessage & message);

		/**
		 * Asigna un contexto de ejecución al nodo. El contexto se asigna también
		 * recursivamente a todos sus hijos.
		 * <p>
		 * El contexto de ejecución permite
		 * almacenar y recuperar valores y también comunicarselos a otros nodos.
		 *
		 * @param context Contexto de ejecución del nodo
		 */
		virtual void useContext(CBehaviorExecutionContext* context);


	protected:
		/**
		 * Lista con los hijos de este nodo
		 */
		BehaviorTreeList children;

		/**
		 * Destructor
		 */
		~BehaviorTreeInternalNode();

	};

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	// EJEMPLOS DE NODOS SIMPLES

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	/**
	 * Nodo atómico que siempre devuelve el estado BT_RUNNING cuando se ejecuta
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class AlwaysRunning :public BehaviorTreeNode
	{
		BEHAVIOR_STATUS execute(void* agent)
		{
			return BT_RUNNING;
		}
		void init(void* agent){};
	};

	/**
	 * Nodo atómico que siempre devuelve el estado BT_SUCCESS cuando se ejecuta
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class AlwaysSuccess :public BehaviorTreeNode
	{
		BEHAVIOR_STATUS execute(void* agent)
		{
			return BT_SUCCESS;
		}
		void init(void* agent){};
	};

	/**
	 * Nodo atómico que siempre devuelve el estado BT_FAILURE cuando se ejecuta
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class AlwaysFailure :public BehaviorTreeNode
	{
		BEHAVIOR_STATUS execute(void* agent)
		{
			return BT_FAILURE;
		}
		void init(void* agent){};
	};

	/**
	 * Nodo atómico que se ejecuta un número determinado de veces devolviendo
	 * BT_RUNNING y después devuelve BT_SUCCESS
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class SuccessAfter :public BehaviorTreeNode
	{
	public:
		int n;
		int total;
		BEHAVIOR_STATUS execute(void* agent)
		{
			if (n == 0)
			{
				return BT_SUCCESS;
			}
			else
			{
				n--;
				return BT_RUNNING;
			}
		}
		void init(void* agent)
		{
			n = total;
		};
		SuccessAfter::SuccessAfter(int t)
		{
			total = t;
			n = total;
		}
	};

	/**
	 * Nodo atómico que se ejecuta un número determinado de veces devolviendo
	 * BT_RUNNING y después devuelve BT_FAILURE
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class FailureAfter :public BehaviorTreeNode
	{
	public:
		int n;
		int total;
		BEHAVIOR_STATUS execute(void* agent)
		{
			if (n == 0)
			{
				return BT_FAILURE;
			}
			else
			{
				n--;
				return BT_RUNNING;
			}
		}
		void init(void* agent)
		{
			n = total;
		};
		FailureAfter::FailureAfter(int t)
		{
			total = t;
			n = total;
		}
	};
}

#endif __AI_BehaviorTreeBase_H
