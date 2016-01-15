
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
	 * Clase abstracta base de los �rboles de comportamiento.
	 * <p>
	 * Esta clase representa a un nodo gen�rico y define los m�todos para
	 * inicializarlo (init) y ejecutar la acci�n asociada al nodo (execute),
	 * adem�s de otros m�todos auxiliares.
	 * <p>
	 * Todos los tipos de nodos de los �rboles (incluidos los nodos
	 * intermedios) heredan directa o indirectamente de esta clase.
	 *
	 * @author "Gonzalo Fl�rez"
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
		 * Ejecuta la acci�n asociada al nodo. Es un m�todo abstracto que deber�n implementar
		 * todas las clases que deriven de esta.
		 * <p>
		 * El valor devuelto por este m�todo ser�:<br>
		 * � BT_SUCCESS: si la acci�n del nodo ha terminado con �xito.<br>
		 * � BT_FAILURE: si la acci�n del nodo ha fallado.<br>
		 * � BT_RUNNING: si la acci�n necesita m�s ticks para poder terminar.<br>
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 * @return estado en que queda el nodo despu�s de la ejecuci�n
		 */
		virtual BEHAVIOR_STATUS execute(void* agent) = 0;

		/// This method will be invoked before the node is executed for the first time.
		/**
		 * Inicializaci�n del nodo. Este m�todo abstracto inicializa los datos necesarios
		 * para la ejecuci�n del nodo.
		 * <p>
		 * Este m�todo ser� invocado cada vez que se necesite reiniciar un nodo:<br>
		 * � Antes de la primera ejecuci�n.<bR>
		 * � Cuando el padre necesite que el nodo se reinicie.<br>
		 * <p>
		 * Por ejemplo, si tenemos un nodo de tipo secuencia, cuando se ejecuta por primera
		 * vez, el nodo se inicializa, inicializando a su vez a todos sus hijos. Si el nodo
		 * termina y vuelve a ejecutarse de nuevo, tendr� que inicializar tambi�n a sus hijos
		 * de nuevo.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 */

		virtual void init(void* agent) = 0;
		/**
		 * Modifica el nombre de un nodo. El nombre s�lo se utiliza para facilitar la
		 * depuraci�n.
		 *
		 * @param name Nombre del nodo
		 * @return El nodo con el nombre modificado
		 */
		BehaviorTreeNode* setName(const std::string name) { _name = name; return this; };

		/**
		 * Devuelve el nombre de un nodo. El nombre s�lo se utiliza para facilitar la
		 * depuraci�n.
		 *
		 * @return Nombre del nodo
		 */
		std::string getName() { return _name; }

		/**
		 * Devuelve cierto si el nodo acepta el mensaje que recibe como par�metro
		 *
		 * @param message Mensaje
		 * @return true si se acepta este mensaje
		 */
		virtual bool accept(const Core::SmartMessage & message) { return false; };

		/**
		 * Procesa un mensaje. En general, el procesamiento lo realizar� otra clase
		 * asociada al nodo (por ejemplo, una acci�n latente).
		 *
		 * @param message Mensaje
		 */
		virtual void process(const Core::SmartMessage & message) { };

		/**
		 * Asigna un contexto de ejecuci�n al nodo. El contexto de ejecuci�n permite
		 * almacenar y recuperar valores y tambi�n comunicarselos a otros nodos.
		 *
		 * @param context Contexto de ejecuci�n del nodo
		 */
		virtual void useContext(CBehaviorExecutionContext* context) { _context = context; };

	protected:
		/**
		 * Nombre del nodo
		 */
		std::string _name;
		/**
		 * Contexto de ejecuci�n
		 */
		CBehaviorExecutionContext * _context;
	};



	/// Abstract base class for Behavior Tree nodes with children
	/**
	 * Clase abstracta que representa un nodo intermedio de un �rbol de comportamiento.
	 * <p>
	 * Hereda de BehaviorTreeNode.
	 * <p>
	 * A�ade a su clase padre una lista en la que almacena los nodos hijos y un m�todo
	 * para a�ad�rselos.
	 * <p>
	 * De esta clase heredar�n todos los nodos intermedios y los decoradores.
	 *
	 *
	 * @author "Gonzalo Fl�rez"
	 * @date 11/04/2011
	 */
	class BehaviorTreeInternalNode :public BehaviorTreeNode
	{

	public:

		/// Add a child to this node. Takes ownership of the child.
		/**
		 * A�ade un nuevo hijo a este nodo. El comportamiento por defecto es a�adirlo
		 * a la lista de hijos, aunque puede ser modificado si es necesario (por ejemplo,
		 * en el caso de un decorador habr� que comprobar que s�lo se a�ade un hijo).
		 * <p>
		 * El nodo se hace responsable de eliminar todos sus hijos cuando se destruya.
		 *
		 * @param newChild Nodo que se a�adir� como hijo de este nodo intermedio
		 * @return Puntero al nodo al que se ha a�adido el hijo
		 */
		virtual BehaviorTreeInternalNode* addChild(BehaviorTreeNode* newChild);

		/**
		 * Devuelve cierto si alguno de sus hijos acepta el mensaje que recibe como par�metro.
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
		 * Asigna un contexto de ejecuci�n al nodo. El contexto se asigna tambi�n
		 * recursivamente a todos sus hijos.
		 * <p>
		 * El contexto de ejecuci�n permite
		 * almacenar y recuperar valores y tambi�n comunicarselos a otros nodos.
		 *
		 * @param context Contexto de ejecuci�n del nodo
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
	 * Nodo at�mico que siempre devuelve el estado BT_RUNNING cuando se ejecuta
	 *
	 * @author "Gonzalo Fl�rez"
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
	 * Nodo at�mico que siempre devuelve el estado BT_SUCCESS cuando se ejecuta
	 *
	 * @author "Gonzalo Fl�rez"
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
	 * Nodo at�mico que siempre devuelve el estado BT_FAILURE cuando se ejecuta
	 *
	 * @author "Gonzalo Fl�rez"
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
	 * Nodo at�mico que se ejecuta un n�mero determinado de veces devolviendo
	 * BT_RUNNING y despu�s devuelve BT_SUCCESS
	 *
	 * @author "Gonzalo Fl�rez"
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
	 * Nodo at�mico que se ejecuta un n�mero determinado de veces devolviendo
	 * BT_RUNNING y despu�s devuelve BT_FAILURE
	 *
	 * @author "Gonzalo Fl�rez"
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
