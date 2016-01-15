/**
 * @file NodeRepeat.h
 *
 * Implementación de un nodo (decorador) repetidor
 *
 * @author "Gonzalo Flórez"
 * @date 11/04/2011
 */

#ifndef AI_BTRepeatNode_H_
#define AI_BTRepeatNode_H_

#include "BehaviorTreeBase.h"


namespace AI
{

	/**
	 * Implementación de un nodo repetidor para un BT.
	 * <p>
	 * El repetidor es un decorador (nodo intermedio que sólo puede tener 1 hijo).
	 * Al ejecutarse, ejecuta a su hijo repetidamente. El número de repeticiones
	 * puede especificarse mediante un parámetro o hacer que se repita indefinidamente.
	 * <p>
	 * Si en alguna de las repeticiones el hijo falla, el repetidor fallará. Tendrá éxito
	 * si en todas ellas su hijo termina con éxito.
	 * <p>
	 * En cada tick sólo se invoca una vez al execute del hijo (si este devuelve BT_SUCCESS
	 * no se volverá a invocar hasta el próximo tick).
	 *
	 * @author "Gonzalo Flórez"
	 * @date 11/04/2011
	 */
	class CNodeRepeat: public BehaviorTreeInternalNode
	{
	public:

		/**
		 * Constructor. Recibe un parámetro que indica el número de repeticiones de su hijo.
		 *
		 * @param repeats Número de repeticiones. Si este parámetro es -1 el nodo seguirá repitiéndose hasta que falle.
		 */
		CNodeRepeat::CNodeRepeat(int repeats);

		/**
		 * Añade un hijo al nodo. Al ser un decorador sólo puede tener 1 hijo. Si se añade
		 * un segundo hijo, saltará un assert.
		 *
		 * @param BehaviorTreeNode* Nodo hijo
		 * @return Referencia al nodo repetidor
		 */
		BehaviorTreeInternalNode* addChild(BehaviorTreeNode* newChild);

		/**
		 * Ejecuta la siguiente repetición del hijo.
		 * <p>
		 * Cada vez que el hijo tiene éxito, antes de la siguiente ejecución, este se inicializa de nuevo.
		 *
		 * @param agent dato que podemos pasar al árbol para su ejecución
		 * @return estado en que queda el nodo después de la ejecución
		 */
		BEHAVIOR_STATUS execute(void* agent);

		/**
		 * Inicializa el nodo y su hijo.
		 * @param agent dato que podemos pasar al árbol para su ejecución
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
