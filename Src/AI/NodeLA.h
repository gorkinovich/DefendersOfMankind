/**
 * @file NodeLA.h
 *
 * Nodo atómico que ejecuta una acción latente.
 *
 * @author "Gonzalo Flórez"
 * @date 11/04/2011
 */

#ifndef __AI_NodeLA_H
#define __AI_NodeLA_H

#include "BehaviorTreeBase.h"

namespace AI
{
	class CLatentAction;

	/**
	 * Implementación de un nodo atómico de un BT que ejecuta una acción latente.
	 * <p>
	 * Cada uno de los métodos del nodo llama al método correspondiente de la
	 * acción latente. También se encarga de traducir el estado.
	 * <p>
	 * Además, también delega la ejecución de los métodos accept y process en la
	 * acción latente.
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class CNodeLA : public BehaviorTreeNode
	{
	public:

		/**
		 * Constructor. Asigna la acción latente al nodo. La acción pasa a ser
		 * responsabilidad del nodo, quien se encarga de liberarla en su destructor.
		 *
		 * @param action Accion latente correspondiente al nodo
		 */
		CNodeLA(CLatentAction* action) : _action (action)
		{
			_name = "Latent action node";
		}

		/**
		 * Destructor. Libera también la acción latente asociada.
		 *
		 */
		~CNodeLA();

		/**
		 * Ejecuta la acción latente asociada al nodo y devuelve el estado correspondiente.
		 * <p>
		 * Si la acción latente devuelve SUCCESS o FAIL, esta función devuelve el valor
		 * correspondiente para el nodo. En otro caso, devuelve BT_RUNNING.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 * @return estado en que queda el nodo después de la ejecución
		 */
		virtual BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Si la acción latente no está lista para ser ejecutada (si el estado no
		 * es READY) la resetea.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 */
		virtual void init(void* agent);

		/**
		 * Invoca al método accept de la acción latente asociada para comprobar si
		 * ésta acepta el mensaje.
		 *
		 * @param message Mensaje
		 * @return true si la acción latente acepta el mensaje
		 */
		virtual bool accept(const Core::SmartMessage & message);

		/**
		 * Invoca al método process de la acción latente asociada para que procese
		 * el mensaje
		 *
		 * @param message Mensaje
		 */
		virtual void process(const Core::SmartMessage & message);

		/**
		 * Asigna el contexto de ejecución al nodo actual y también a la acción latente asociada.
		 *
		 * @param context Contexto de ejecución
		 */
		virtual void useContext(CBehaviorExecutionContext* context);


	private:
		/**
		 * Acción latente asociada al nodo.
		 */
		CLatentAction* _action;
	}; //class CNodeLA

} // namespace AI

#endif __AI_NodeLA_H
