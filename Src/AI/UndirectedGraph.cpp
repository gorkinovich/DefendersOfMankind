/**
@file UndirectedGraph.cpp

Clase que permite crear grafos no dirigidos.

@see UndirectedGraph

@author Gonzalo Flórez
@date Diciembre 2010

*/
#include "UndirectedGraph.h"

#pragma warning(disable:4172)

/////////////////////////////////////////
/**
Constructor
*/
CUndirectedGraph::CUndirectedGraph(void) : _edgeCount(0)
{
}
/////////////////////////////////////////
/**
Destructor
*/
CUndirectedGraph::~CUndirectedGraph(void)
{
	std::map<int, std::list<int>*>::iterator it;
	for (it = _adjacency.begin(); it != _adjacency.end(); it++) {
		delete (*it).second;
	}
	std::vector<CNode*>::iterator it2;
	for (it2 = _nodes.begin(); it2 != _nodes.end(); it2++) {
		delete (*it2);
	}
}
/////////////////////////////////////////
/**
Añade un nodo al grafo. Es el propio grafo en su destructor quien
se encarga de eliminar los nodos. NO elimina su contenido, solamente
el CNode.

@param node puntero al nodo que se añade.
*/
void CUndirectedGraph::addNode(CNode* node)
{
	_nodes.push_back(node);
}
/////////////////////////////////////////
/**
Crea una arista entre dos nodos existentes y le asigna un coste.

@param node1 Identificador del primer nodo.
@param node2 Identificador del segundo nodo.
@param cost Coste asociado a la arista.
*/
void CUndirectedGraph::addEdge(int node1, int node2, float cost)
{
	assert(node1 < (int)_nodes.size() && node2 < (int)_nodes.size());
	setAdjacent(node1, node2);
	setAdjacent(node2, node1);
	_cost.setElement(node1, node2, cost);
	_edgeCount++;
}
/////////////////////////////////////////
/**
Crea una arista que va desde el nodo de origen (orig) al de destino (dest)
añadiendo el segundo a la lista del primero. Crea la lista en el caso de que
no exista.
<p>
@remarks Este método no crea la arista en sentido contrario (desde dest a orig). 
Hay que hacerlo manualmente.

@param orig Id del nodo de origen.
@param dest Id del nodo de destino.
*/
void CUndirectedGraph::setAdjacent(int orig, int dest) {
	std::list<int>* neighbours = _adjacency[orig];
	// Si es null es porque nuevo
	if (neighbours == NULL) {
		neighbours = new std::list<int>();
		_adjacency[orig] = neighbours;
	}
	neighbours->push_back(dest);
}
/////////////////////////////////////////
/**
Devuelve una lista con todos los nodos conectados al especificado.

@param idNode Identificador del nodo para el que se va a obtener la 
lista de vecinos.
@return Lista de vecinos.
*/
const std::list<int> &CUndirectedGraph::getNeighbours(int idNode) 
{
	assert(idNode < (int)_nodes.size());
	std::list<int>* neighbours = _adjacency[idNode];
	if (neighbours == NULL) {
		return (std::list<int>());
	} else {
		return (*neighbours);
	}
}
/////////////////////////////////////////
/**
Devuelve la etiqueta de un nodo.

@param id Identificador del nodo.
@return CNode con el contenido del nodo.
*/
CNode* CUndirectedGraph::getNode(int id)
{
	assert(id < (int)_nodes.size());
	return (_nodes[id]);
}
