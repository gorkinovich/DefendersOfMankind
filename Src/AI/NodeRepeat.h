/**
 * @file NodeRepeat.h
 *
 * Implementaci�n de un nodo (decorador) repetidor
 *
 * @author "Gonzalo Fl�rez"
 * @date 11/04/2011
 */

#ifndef AI_BTRepeatNode_H_
#define AI_BTRepeatNode_H_

#include "BehaviorTreeBase.h"


namespace AI
{

	/**
	 * Implementaci�n de un nodo repetidor para un BT.
	 * <p>
	 * El repetidor es un decorador (nodo intermedio que s�lo puede tener 1 hijo).
	 * Al ejecutarse, ejecuta a su hijo repetidamente. El n�mero de repeticiones
	 * puede especificarse mediante un par�metro o hacer que se repita indefinidamente.
	 * <p>
	 * Si en alguna de las repeticiones el hijo falla, el repetidor fallar�. Tendr� �xito
	 * si en todas ellas su hijo termina con �xito.
	 * <p>
	 * En cada tick s�lo se invoca una vez al execute del hijo (si este devuelve BT_SUCCESS
	 * no se volver� a invocar hasta el pr�ximo tick).
	 *
	 * @author "Gonzalo Fl�rez"
	 * @date 11/04/2011
	 */
	class CNodeRepeat: public BehaviorTreeInternalNode
	{
	public:

		/**
		 * Constructor. Recibe un par�metro que indica el n�mero de repeticiones de su hijo.
		 *
		 * @param repeats N�mero de repeticiones. Si este par�metro es -1 el nodo seguir� repiti�ndose hasta que falle.
		 */
		CNodeRepeat::CNodeRepeat(int repeats);

		/**
		 * A�ade un hijo al nodo. Al ser un decorador s�lo puede tener 1 hijo. Si se a�ade
		 * un segundo hijo, saltar� un assert.
		 *
		 * @param BehaviorTreeNode* Nodo hijo
		 * @return Referencia al nodo repetidor
		 */
		BehaviorTreeInternalNode* addChild(BehaviorTreeNode* newChild);

		/**
		 * Ejecuta la siguiente repetici�n del hijo.
		 * <p>
		 * Cada vez que el hijo tiene �xito, antes de la siguiente ejecuci�n, este se inicializa de nuevo.
		 *
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 * @return estado en que queda el nodo despu�s de la ejecuci�n
		 */
		BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Inicializa el nodo y su hijo.
		 * @param agent dato que podemos pasar al �rbol para su ejecuci�n
		 */
		void init(void* agent);

	protected:

		/**
		 * Repeticiones actuales
		 */
		int count;

		/**
		 * Repeticiones totales
		 */
		int target;

		/**
		 * Inicializa los hijos del nodo
		 */
		void initChildren(void* agent);

	};
}

#endif AI_BTRepeatNode_H_
