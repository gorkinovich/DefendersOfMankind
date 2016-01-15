/**
@file CStateMachine.h

En este fichero se define la clase CStateMachine,
que es la clase padre de las m�quinas de estado,
CStateMachineFactory, factor�a de m�quinas de estado
para las pr�cticas, y CSMWander, una m�quina de estado
de ejemplo.

@author Gonzalo Fl�rez
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
	Clase padre para las m�quinas de estado.
	<p>
	Es una clase parametrizada. El par�metro es la clase de 
	los elementos en los nodos. En general, este par�metro ser�
	una acci�n ejecutable (CLatentAction).
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
		Constructor que recibe la entidad que ejecuta la m�quina de estado
		*/
		CStateMachine(Core::Entity* entity) : _entity(entity), _currentNodeId(-1), _initialNodeId(-1) { _edges = new EdgeList(); };
		/**
		Destructor
		*/
		~CStateMachine();
		/**
		Este m�todo a�ade un nodo a la m�quina de estado y devuelve un identificador
		del nodo. Este identificador se usa para referirse a los nodos al a�adir
		aristas y establecer el nodo inicial.
		<p>
		Los nodos ser�n destruidos cuando se destruya la m�quina de estado.

		@param content Contenido del nodo.
		@return Identificador para el nodo.
		*/
		int addNode(TNode *content);
		/**
		A�ade una arista a la m�quina de estado.
		<p>
		El m�todo recibe los identificadores del nodo de origen y destino y una condici�n
		que indica cu�ndo se activa la transici�n de la arista.
		<p>
		Las condiciones ser�n destruidas cuando se destruya la m�quina de estado.

		@param idOrig Identificador del nodo de origen.
		@param idDest Identificador del nodo de destino.
		@param cond Condici�n asociada a la arista.
		*/
		void addEdge(int idOrig, int idDest, ICondition<TNode> *cond);
		/**
		Este m�todo comprueba las condiciones de las aristas que salen del 
		nodo actual y cambia de nodo si alguna de ellas es cierta. El m�todo
		devuelve true si alguna transici�n es cierta (aunque no se cambie el
		nodo actual) y false en otro caso.
		<p>
		Las aristas se comprueban en el orden en que se han a�adido y 
		la comprobaci�n se detiene en el momento en que una de ellas se hace 
		cierta.
		*/
		bool update();
		/**
		Devuelve el contenido del nodo actual.
		*/
		TNode* getCurrentNode();
		/**
		Establece cu�l es la entidad que ejecuta la m�quina de estado.
		*/
		void setEntity(Core::Entity *entity) { _entity = entity; };
		/**
		Establece el nodo inicial.

		@param idNode Identificador del nodo inicial.
		*/
		void setInitialNode(int idNode) { _initialNodeId = idNode; };
		/**
		Reinicia la ejecuci�n de la m�quina de estado.
		*/
		void resetExecution(){ _currentNodeId = -1; };

	protected:
		/**
		Tipo que guarda la informaci�n de las aristas salientes de un nodo.
		Para cada arista tenemos un vector de pares con la condici�n y el 
		nodo de destino.
		*/
		typedef std::vector<std::pair<ICondition<TNode>*, int>> PairVector;
		/** 
		Tipo que guarda la informaci�n de todas las aristas. Est� indexado 
		por el identificador del nodo de origen.
		*/
		typedef std::map<int, PairVector*> EdgeList;
		/**
		Entidad que ejecuta la m�quina de estado.
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
	Esta clase implementa una m�quina de estado para un comportamiento
	Wander. Es un comportamiento simple que consta de dos estados. En primer
	lugar, la entidad que lo ejecuta la acci�n latente CLARouteTo, que 
	busca una ruta hasta un punto aleatorio del mapa. Cuando ha finalizado,
	ejecuta CLAWait, que espera durante un periodo fijo de tiempo (3 segundos).
	Despu�s de esperar vuelve al comienzo.
	*/
	class CSMWander : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMWander(Core::Entity* entity) : CStateMachine(entity) {

			// TODO PR�CTICA IA
			// Aqu� tiene que venir el c�digo para crear la m�quina de estado:
			// En primer lugar se a�aden los nodos. A continuaci�n, utilizando 
			// los ids que obtenemos al a�adir los nodos se a�aden las aristas.
			// Por �ltimo hay que decir cu�l es el nodo inicial.

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
	Esta clase implementa una m�quina de estados para controlar el ciclo de 
	vida de algunas entidades.
	*/
	class CSMLifeCycle_ENEMY : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_ENEMY(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la m�quina de estados
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
	Esta clase implementa una m�quina de estados para controlar el ciclo de 
	vida de los jefes finales.
	*/
	class CSMLifeCycle_BOSS : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_BOSS(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la m�quina de estados
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
	Esta clase implementa una m�quina de estados para controlar el ciclo de 
	vida de las balas.
	*/
	class CSMLifeCycle_BULLET : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_BULLET(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la m�quina de estados
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
	Esta clase implementa una m�quina de estados para controlar el ciclo de 
	vida de las balas del jefe final del nivel 1.
	*/
	class CSMLifeCycle_BULLET_BOSS_1 : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_BULLET_BOSS_1(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la m�quina de estados
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
	Esta clase implementa una m�quina de estados para controlar el ciclo de 
	vida de las balas del jugador.
	*/
	class CSMLifeCycle_PLAYER_BULLET : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_PLAYER_BULLET(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la m�quina de estados
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
	Esta clase implementa una m�quina de estados para controlar el ciclo de 
	vida de la nave del jugador.
	*/
	class CSMLifeCycle_PLAYER : public CStateMachine<CLatentAction>
	{
	public:
		/**
		Constructor. A�ade los nodos y las aristas, establece el nodo de inicio
		y deja la m�quina de estado lista para ser ejecutada.
		*/
		CSMLifeCycle_PLAYER(Core::Entity* entity) : CStateMachine(entity) {

			// Creamos la m�quina de estados
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
	Factor�a que devuelve m�quinas de estado predefinidas.
	*/
	class CStateMachineFactory 
	{
	public:
		static CStateMachine<CLatentAction>* getStateMachine(std::string smName, Core::Entity * entity)
		{
			// M�quina de estados de la pr�ctica de IA
			if (smName == "wander") {
				return new CSMWander(entity);
			}
			// M�quina de estados que controla el ciclo de vida de los enemigos comunes
			else if (smName == "LifeCycle_ENEMY") {
				return new CSMLifeCycle_ENEMY(entity);
			}
			// M�quina de estados que controla el ciclo de vida de las balas
			else if (smName == "LifeCycle_BULLET") {
				return new CSMLifeCycle_BULLET(entity);
			}
			// M�quina de estados que controla el ciclo de vida de las balas del jugador
			else if (smName == "LifeCycle_PLAYER_BULLET") {
				return new CSMLifeCycle_PLAYER_BULLET(entity);
			}
			// M�quina de estados que controla el ciclo de vida de la nave del jugador
			else if (smName == "LifeCycle_PLAYER") {
				return new CSMLifeCycle_PLAYER(entity);
			}
			// M�quina de estados que controla el ciclo de vida de los jefes finales
			else if (smName == "LifeCycle_BOSS") {
				return new CSMLifeCycle_BOSS(entity);
			}
			// M�quina de estados que controla el ciclo de vida de las balas del jefe
			// final del nivel 1
			else if (smName == "LifeCycle_BULLET_BOSS_1") {
				return new CSMLifeCycle_BULLET_BOSS_1(entity);
			}
			else return 0;
		}
	};



//////////////////////////////
//	Implementaci�n de CStateMachine
//////////////////////////////
	template <class TNode>
	CStateMachine<TNode>::~CStateMachine() 
	{
		// Borramos las aristas
		for (EdgeList::iterator it = _edges->begin(); it != _edges->end(); it++)
		{
			PairVector* v = it->second;
			for (PairVector::iterator it2 = v->begin(); it2 != v->end(); it2++) {
				// Borra la condici�n
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
		// A�adimos el par (condici�n, nodo de destino)
		vector->push_back(std::pair<ICondition<TNode>*, int>(cond, idDest));
	} // addEdge
//////////////////////////////
	template <class TNode>
	bool CStateMachine<TNode>::update()
	{
		// Si es el primer update devolvemos que s� hay un cambio de nodo)
		if (_currentNodeId == -1) {
			_currentNodeId = _initialNodeId;
			return true;
		}
		// Buscamos la lista de aristas que salen del nodo actual
		EdgeList::iterator it = _edges->find(_currentNodeId);
		if (it != _edges->end()) {
			// Sacamos el nodo actual por si hay que comprobar la condici�n
			TNode* node = _nodes[_currentNodeId];
			PairVector* vector = (*it).second;
			// Para cada elemento del vector (arista que sale del nodo actual)
			for (PairVector::iterator edgeIt = vector->begin(); edgeIt != vector->end(); edgeIt++){
				// Si la condici�n es verdadera
				if (edgeIt->first->check(node, _entity)) {
					// S�lo hacemos la primera transici�n que encontramos
					int newNode = edgeIt->second;
					_currentNodeId = newNode;
					// Si la transici�n se hace cierta siempre consideramos que el comportamiento cambia
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
