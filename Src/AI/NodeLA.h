/**
 * @file NodeLA.h
 *
 * Nodo at�mico que ejecuta una acci�n latente.
 *
 * @author "Gonzalo Fl�rez"
 * @date 11/04/2011
 */

#ifndef __AI_NodeLA_H
#define __AI_NodeLA_H

#include "BehaviorTreeBase.h"

namespace AI
{
	class CLatentAction;

	/**
	 * Implementaci�n de un nodo at�mico de un BT que ejecuta una acci�n latente.
	 * <p>
	 * Cada uno de los m�todos del nodo llama al m�todo correspondiente de la
	 * acci�n latente. Tambi�n se encarga de traducir el estado.
	 * <p>
	 * Adem�s, tambi�n delega la ejecuci�n de los m�todos accept y process en la
	 * acci�n latente.
	 *
	 * @author "Gonzalo Fl�rez"
	 * @date 11/04/2011
	 */
	class CNodeLA : public BehaviorTreeNode
	{
	public:

		/**
		 * Constructor. Asigna la acci�n latente al nodo. La acci�n pasa a ser
		 * responsabilidad del nodo, quien se encarga de liberarla en su destructor.
		 *
		 * @param action Accion latente correspondiente al nodo
		 */
		CNodeLA(CLatentAction* action) : _action (action)
		{
			_name = "Latent action node";
		}

		/**
		 * Destructor. Libera tambi�n la acci�n latente asociada.
		 *
		 */
		~CNodeLA();

		/**
		 * Ejecuta la acci�n latente asociada al nodo y devuelve el estado correspondiente.
		 * <p>
		 * Si la acci�n latente devuelve SUCCESS o FAIL, esta funci�n devuelve el valor
		 * correspondiente para el nodo. En otro caso, devuelve BT_RUNNING.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 * @return estado en que queda el nodo despu�s de la ejecuci�n
		 */
		virtual BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Si la acci�n latente no est� lista para ser ejecutada (si el estado no
		 * es READY) la resetea.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 */
		virtual void init(void* agent);

		/**
		 * Invoca al m�todo accept de la acci�n latente asociada para comprobar si
		 * �sta acepta el mensaje.
		 *
		 * @param message Mensaje
		 * @return true si la acci�n latente acepta el mensaje
		 */
		virtual bool accept(const Core::SmartMessage & message);

		/**
		 * Invoca al m�todo process de la acci�n latente asociada para que procese
		 * el mensaje
		 *
		 * @param message Mensaje
		 */
		virtual void process(const Core::SmartMessage & message);

		/**
		 * Asigna el contexto de ejecuci�n al nodo actual y tambi�n a la acci�n latente asociada.
		 *
		 * @param context Contexto de ejecuci�n
		 */
		virtual void useContext(CBehaviorExecutionContext* context);


	private:
		/**
		 * Acci�n latente asociada al nodo.
		 */
		CLatentAction* _action;
	}; //class CNodeLA

} // namespace AI

#endif __AI_NodeLA_H
