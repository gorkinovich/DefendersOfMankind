/**
@file CStateMachine.h

En este fichero se define la clase CStateMachine,
que es la clase padre de las máquinas de estado,
CStateMachineFactory, factoría de máquinas de estado
para las prácticas, y CSMWander, una máquina de estado
de ejemplo.

@author Gonzalo Flórez
@date Diciembre 2010

*/

#pragma once

#ifndef __AI_StateMachine_H
#define __AI_StateMachine_H


#include "Condition.h"

#include "LatentAction.h"
#include "SimpleLatentActions.h"
#include "LifeCycleLatentActions.h"

namespace AI 
{

	/**
	Clase padre para las máquinas de estado.
	<p>
	Es una clase parametrizada. El parámetro es la clase de 
	los elementos en los nodos. En general, este parámetro será
	una acción ejecutable (CLatentAction).
	*/
	template <class TNode>
	class CStateMachine
	{
	public: 
		/**
		Constructor
		*/
		CStateMachine() : _entity(0), _currentNodeId(-1), _initialNodeId(-1) { _edges = new EdgeList(); };
		/**
		Constructor que recibe la entidad que ejecuta la máquina de estado
		*/
		CStateMachine(Core::Entity* entity) : _entity(entity), _currentNodeId(-1), _initialNodeId(-1) { _edges = new EdgeList(); };
		/**
		Destructor
		*/
		~CStateMachine();
		/**
		Este método añade un nodo a la máquina de estado y devuelve un identificador
		del nodo. Este identificador se usa para referirse a los nodos al añadir
		aristas y establecer el nodo inicial.
		<p>
		Los nodos serán destruidos cuando se destruya la máquina de estado.

		@param content Contenido del nodo.
		@return Identificador para el nodo.
		*/
		int addNode(TNode *content);
		/**
		Añade una arista a la máquina de estado.
		<p>
		El método recibe los identificadores del nodo de origen y destino y una condición
		que indica cuándo se activa la transición de la arista.
		<p>
		Las condiciones serán destruidas cuando se destruya la máquina de estado.

		@param idOrig Identificador del nodo de origen.
		@param idDest Identificador del nodo de destino.
		@param cond Condición asociada a la arista.
		*/
		void addEdge(int idOrig, int idDest, ICondition<TNode> *cond);
		/**
		Este método comprueba las condiciones de las aristas que salen del 
		nodo actual y cambia de nodo si alguna de ellas es cierta. El método
		devuelve true si alguna transición es cierta (aunque no se cambie el
		nodo actual) y false en otro caso.
		<p>
		Las aristas se comprueban en el orden en que se han añadido y 
		la comprobación se detiene en el momento en que una de ellas se hace 
		cierta.
		*/
		bool update();
		/**
		Devuelve el contenido del nodo actual.
		*/
		TNode* getCurrentNode();
		/**
		Establece cuál es la entidad que ejecuta la máquina de estado.
		*/
		void setEntity(Core::Entity *entity) { _entity = entity; };
		/**
		Establece el nodo inicial.

		@param idNode Identificador del nodo inicial.
		*/
		void setInitialNode(int idNode) { _initialNodeId = idNode; };
		/**
		Reinicia la ejecución de la máquina de estado.
		*/
		void resetExecution(){ _currentNodeId = -1; };

	protected:
		/**
		Tipo que guarda la información de las aristas salientes de un nodo.
		Para cada arista tenemos un vector de pares con la condición y el 
		nodo de destino.
		*/
		typedef std::vector<std::pair<ICondition<TNode>*, int>> PairVector;
		/** 
		Tipo que guarda la información de todas las aristas. Está indexado 
		por el identificador del nodo de origen.
		*/
		typedef std::map<int, PairVector*> EdgeList;
		/**
		Entidad que ejecuta la máquina de estado.
		*/
		Core::Entity *_entity;
		/**
		Valores del nodo actual e inicial
		*/
		int _currentNodeId, _initialNodeId;
		/**
		Lista de nodos
		*/
		std::map<int, TNode*> _nodes;
		/**
		Lista de aristas
		*/
		EdgeList * _edges;

	}; // class CStateMachine

	/**
	Esta clase implementa una máquina de estado para un comportamiento
	Wander. Es un comportamiento simple que consta de dos estados. En primer
	lugar, la entidad que lo ejecuta la acción latente CLARouteTo, que 
	busca una ruta hasta un punto aleatorio del mapa. Cuando ha finalizado,
	ejecuta CLAWait, que espera durante un periodo fijo de tiempo (3 segundos).
	Después de esperar vuelve al comienzo.
	*/
	class CSMWander : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMWander(Core::Entity* entity) : CStateMachine(entity) {

			// TODO PRÁCTICA IA
			// Aquí tiene que venir el código para crear la máquina de estado:
			// En primer lugar se añaden los nodos. A continuación, utilizando 
			// los ids que obtenemos al añadir los nodos se añaden las aristas.
			// Por último hay que decir cuál es el nodo inicial.

			int routeTo = this->addNode(new CLARouteTo(entity));
			int wait = this->addNode(new CLAWait(3000));
			this->addEdge(routeTo, wait, new CConditionSuccess());
			this->addEdge(routeTo, routeTo, new CConditionFail());
			this->addEdge(wait, routeTo, new CConditionFinished());
			this->setInitialNode(routeTo);
			this->resetExecution();
		}
	};


	/**
	Esta clase implementa una máquina de estados para controlar el ciclo de 
	vida de algunas entidades.
	*/
	class CSMLifeCycle_ENEMY : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_ENEMY(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la máquina de estados
			int LifeCycle_SLEEP  = this->addNode(new CLALifeCycle_SLEEP(entity));
			int LifeCycle_ON  = this->addNode(new CLALifeCycle_ON(entity));
			int LifeCycle_OFF = this->addNode(new CLALifeCycle_OFF(entity));
			int LifeCycle_RELEASE = this->addNode(new CLALifeCycle_RELEASE(entity));

			this->addEdge(LifeCycle_SLEEP, LifeCycle_ON, new CConditionSuccess());
			this->addEdge(LifeCycle_ON, LifeCycle_OFF, new CConditionSuccess());
			this->addEdge(LifeCycle_ON, LifeCycle_RELEASE, new CConditionFail());
			this->addEdge(LifeCycle_OFF, LifeCycle_RELEASE, new CConditionSuccess());

			this->setInitialNode(LifeCycle_SLEEP);
			this->resetExecution();

		}
	};

	/**
	Esta clase implementa una máquina de estados para controlar el ciclo de 
	vida de los jefes finales.
	*/
	class CSMLifeCycle_BOSS : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_BOSS(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la máquina de estados
			int LifeCycle_SLEEP  = this->addNode(new CLALifeCycle_SLEEP(entity));
			int LifeCycle_ON  = this->addNode(new CLALifeCycle_ON(entity));
			int LifeCycle_BOSS_OFF = this->addNode(new CLALifeCycle_BOSS_OFF(entity));
			int LifeCycle_BOSS_RELEASE = this->addNode(new CLALifeCycle_BOSS_RELEASE(entity));

			this->addEdge(LifeCycle_SLEEP, LifeCycle_ON, new CConditionSuccess());
			this->addEdge(LifeCycle_ON, LifeCycle_BOSS_OFF, new CConditionSuccess());
			this->addEdge(LifeCycle_ON, LifeCycle_BOSS_RELEASE, new CConditionFail());
			this->addEdge(LifeCycle_BOSS_OFF, LifeCycle_BOSS_RELEASE, new CConditionSuccess());

			this->setInitialNode(LifeCycle_SLEEP);
			this->resetExecution();

		}
	};

	/**
	Esta clase implementa una máquina de estados para controlar el ciclo de 
	vida de las balas.
	*/
	class CSMLifeCycle_BULLET : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_BULLET(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la máquina de estados
			int LifeCycle_CHECK_BULLET  = this->addNode(new CLALifeCycle_CHECK_BULLET(entity));
			int LifeCycle_ON  = this->addNode(new CLALifeCycle_ON_ENEMY_BULLET(entity));
			int LifeCycle_RELEASE = this->addNode(new CLALifeCycle_RELEASE(entity));

			this->addEdge(LifeCycle_CHECK_BULLET, LifeCycle_ON, new CConditionSuccess());
			this->addEdge(LifeCycle_CHECK_BULLET, LifeCycle_RELEASE, new CConditionFail());
			this->addEdge(LifeCycle_ON, LifeCycle_RELEASE, new CConditionFail());

			this->setInitialNode(LifeCycle_CHECK_BULLET);
			this->resetExecution();

		}
	};

/**
	Esta clase implementa una máquina de estados para controlar el ciclo de 
	vida de las balas del jefe final del nivel 1.
	*/
	class CSMLifeCycle_BULLET_BOSS_1 : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_BULLET_BOSS_1(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la máquina de estados
			int LifeCycle_CHECK_BULLET  = this->addNode(new CLALifeCycle_CHECK_BULLET(entity));
			int LifeCycle_ON  = this->addNode(new CLALifeCycle_ON_BOSS1_BULLET(entity));
			int LifeCycle_RELEASE = this->addNode(new CLALifeCycle_RELEASE(entity));

			this->addEdge(LifeCycle_CHECK_BULLET, LifeCycle_ON, new CConditionSuccess());
			this->addEdge(LifeCycle_CHECK_BULLET, LifeCycle_RELEASE, new CConditionFail());
			this->addEdge(LifeCycle_ON, LifeCycle_RELEASE, new CConditionFail());

			this->setInitialNode(LifeCycle_CHECK_BULLET);
			this->resetExecution();

		}
	};


	/**
	Esta clase implementa una máquina de estados para controlar el ciclo de 
	vida de las balas del jugador.
	*/
	class CSMLifeCycle_PLAYER_BULLET : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_PLAYER_BULLET(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la máquina de estados
			int LifeCycle_CHECK_BULLET  = this->addNode(new CLALifeCycle_CHECK_BULLET(entity));
			int LifeCycle_ON_BULLET  = this->addNode(new CLALifeCycle_ON_PLAYER_BULLET(entity));
			int LifeCycle_OFF_BULLET  = this->addNode(new CLALifeCycle_OFF_BULLET(entity));
			int LifeCycle_RELEASE = this->addNode(new CLALifeCycle_RELEASE(entity));

			this->addEdge(LifeCycle_CHECK_BULLET, LifeCycle_ON_BULLET, new CConditionSuccess());
			this->addEdge(LifeCycle_CHECK_BULLET, LifeCycle_RELEASE, new CConditionFail());
			this->addEdge(LifeCycle_ON_BULLET, LifeCycle_OFF_BULLET, new CConditionSuccess());
			this->addEdge(LifeCycle_ON_BULLET, LifeCycle_RELEASE, new CConditionFail());
			this->addEdge(LifeCycle_OFF_BULLET, LifeCycle_RELEASE, new CConditionSuccess());

			this->setInitialNode(LifeCycle_CHECK_BULLET);
			this->resetExecution();

		}
	};

/**
	Esta clase implementa una máquina de estados para controlar el ciclo de 
	vida de la nave del jugador.
	*/
	class CSMLifeCycle_PLAYER : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. Añade los nodos y las aristas, establece el nodo de inicio
		y deja la máquina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_PLAYER(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la máquina de estados
			int LifeCycle_POSITIONING  = this->addNode(new CLALifeCycle_POSITIONING_PLAYER(entity));
			int LifeCycle_PLAYING  = this->addNode(new CLALifeCycle_PLAYING_PLAYER(entity));
			int LifeCycle_DEAD = this->addNode(new CLALifeCycle_DEAD_PLAYER(entity));
			int LifeCycle_RELEASE = this->addNode(new CLALifeCycle_RELEASE(entity));

			this->addEdge(LifeCycle_POSITIONING, LifeCycle_PLAYING, new CConditionSuccess());
			this->addEdge(LifeCycle_PLAYING, LifeCycle_DEAD, new CConditionSuccess());
			this->addEdge(LifeCycle_DEAD, LifeCycle_POSITIONING, new CConditionSuccess());
			this->addEdge(LifeCycle_DEAD, LifeCycle_RELEASE, new CConditionFail());

			this->setInitialNode(LifeCycle_POSITIONING);
			this->resetExecution();

		}
	};


	/**
	Factoría que devuelve máquinas de estado predefinidas.
	*/
	class CStateMachineFactory 
	{
	public:
		static CStateMachine<CLatentAction>* getStateMachine(std::string smName, Core::Entity * entity)
		{
			// Máquina de estados de la práctica de IA
			if (smName == "wander") {
				return new CSMWander(entity);
			}
			// Máquina de estados que controla el ciclo de vida de los enemigos comunes
			else if (smName == "LifeCycle_ENEMY") {
				return new CSMLifeCycle_ENEMY(entity);
			}
			// Máquina de estados que controla el ciclo de vida de las balas
			else if (smName == "LifeCycle_BULLET") {
				return new CSMLifeCycle_BULLET(entity);
			}
			// Máquina de estados que controla el ciclo de vida de las balas del jugador
			else if (smName == "LifeCycle_PLAYER_BULLET") {
				return new CSMLifeCycle_PLAYER_BULLET(entity);
			}
			// Máquina de estados que controla el ciclo de vida de la nave del jugador
			else if (smName == "LifeCycle_PLAYER") {
				return new CSMLifeCycle_PLAYER(entity);
			}
			// Máquina de estados que controla el ciclo de vida de los jefes finales
			else if (smName == "LifeCycle_BOSS") {
				return new CSMLifeCycle_BOSS(entity);
			}
			// Máquina de estados que controla el ciclo de vida de las balas del jefe
			// final del nivel 1
			else if (smName == "LifeCycle_BULLET_BOSS_1") {
				return new CSMLifeCycle_BULLET_BOSS_1(entity);
			}
			else return 0;
		}
	};



//////////////////////////////
//	Implementación de CStateMachine
//////////////////////////////
	template <class TNode>
	CStateMachine<TNode>::~CStateMachine() 
	{
		// Borramos las aristas
		for (EdgeList::iterator it = _edges->begin(); it != _edges->end(); it++)
		{
			PairVector* v = it->second;
			for (PairVector::iterator it2 = v->begin(); it2 != v->end(); it2++) {
				// Borra la condición
				delete it2->first;
			}
			// Borra el vector
			delete v;
		}
		delete _edges;

		// Borramos los nodos
		for (std::map<int, TNode*>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
		{
			delete it->second;
		}
	}
//////////////////////////////
	template <class TNode>
	int CStateMachine<TNode>::addNode(TNode* content)
	{
		int id = _nodes.size();
		_nodes[id] = content;
		return id;
	} // addNode
//////////////////////////////
	template <class TNode>
	void CStateMachine<TNode>::addEdge(int idOrig, int idDest, ICondition<TNode> *cond)
	{
		// Buscamos la lista de aristas salientes para el nodo de origen.
		EdgeList::iterator it = _edges->find(idOrig);
		PairVector* vector = 0;
		// Si no hay ninguna arista saliente para ese nodo creamos una nueva lista
		if (it == _edges->end()) {
			vector = new PairVector();
			(*_edges)[idOrig] = vector;
		} else {
			vector = (*it).second;
		}
		// Añadimos el par (condición, nodo de destino)
		vector->push_back(std::pair<ICondition<TNode>*, int>(cond, idDest));
	} // addEdge
//////////////////////////////
	template <class TNode>
	bool CStateMachine<TNode>::update()
	{
		// Si es el primer update devolvemos que sí hay un cambio de nodo)
		if (_currentNodeId == -1) {
			_currentNodeId = _initialNodeId;
			return true;
		}
		// Buscamos la lista de aristas que salen del nodo actual
		EdgeList::iterator it = _edges->find(_currentNodeId);
		if (it != _edges->end()) {
			// Sacamos el nodo actual por si hay que comprobar la condición
			TNode* node = _nodes[_currentNodeId];
			PairVector* vector = (*it).second;
			// Para cada elemento del vector (arista que sale del nodo actual)
			for (PairVector::iterator edgeIt = vector->begin(); edgeIt != vector->end(); edgeIt++){
				// Si la condición es verdadera
				if (edgeIt->first->check(node, _entity)) {
					// Sólo hacemos la primera transición que encontramos
					int newNode = edgeIt->second;
					_currentNodeId = newNode;
					// Si la transición se hace cierta siempre consideramos que el comportamiento cambia
					// Esto implica que si se activa una arista circular (empieza y termina en el mismo nodo)
					// el comportamiento asociado se va a reiniciar
					return true;
				}
			}
		}
		return false;
	} // update
//////////////////////////////
	template <class TNode>
	TNode* CStateMachine<TNode>::getCurrentNode()
	{
		return _nodes[_currentNodeId];
	} // getCurrentNode
//////////////////////////////



} // namespace AI 

#endif // __AI_StateMachine_H
