/**
@file CCondition.h

En este fichero se define la interfaz para las condiciones
de las aristas de las m�quinas de estado, as� como cuatro 
condiciones de ejemplo: CConditionTrue (una condici�n que 
siempre se eval�a como verdadera), CConditionFinished (es 
verdadera si la acci�n asociada al nodo ha terminado), 
CConditionSuccess (es  verdadera si la acci�n asociada al 
nodo ha terminado con �xito) y CConditionFail (es verdadera 
si la acci�n asociada al nodo ha terminado con fallo).

@author Gonzalo Fl�rez
@date Diciembre 2010

*/

#pragma once

#ifndef __AI_Condition_H
#define __AI_Condition_H

#include "LatentAction.h"

namespace AI 
{
	/**
	Interfaz que deber�n implementar las condiciones de 
	las m�quinas de estado.
	*/
	template <class TNode>
	class ICondition
	{
	public:
		/**
		En este m�todo se comprobar� la condici�n. Recibe el 
		nodo al que pertenece la condici�n (de esta manera 
		podemos comprobar si el nodo ha terminado y en qu� 
		condiciones) y la entidad que ejecuta el comportamiento 
		(que puede ser NULL).

		@param currentNode Nodo al que pertenece la condici�n.
		@param entity Entidad que ejecuta el comportamiento
		@return true o false seg�n si se cumple la condici�n o no.
		*/
		virtual bool check(TNode* currentNode, Core::Entity* entity) = 0;
	}; // class CCondition

	/**
	Esta clase define una condici�n que siempre se eval�a a true.
	*/
	template <class TNode>
	class CConditionTrue : public ICondition<TNode>
	{
	public:
		bool check(TNode* currentNode, Core::Entity* entity) { return true; }
	};
	
	/**
	Esta clase define una condici�n que se eval�a a true si la 
	acci�n a la que pertenece ha terminado.
	*/
	class CConditionFinished : public ICondition<CLatentAction>
	{
	public:
		bool check(CLatentAction* currentNode, Core::Entity* entity) 
		{ 
			// TODO PR�CTICA IA
			// Comprobar si el estado del nodo que se est� ejecutando es terminado

			CLatentAction::LAStatus status = currentNode->getStatus();
			return status == CLatentAction::SUCCESS || status == CLatentAction::FAIL;
		}
	};

	/**
	Esta clase define una condici�n que se eval�a a true si la 
	acci�n a la que pertenece ha terminado con �xito.
	*/
	class CConditionSuccess : public ICondition<CLatentAction>
	{
	public:
		bool check(CLatentAction* currentNode, Core::Entity* entity) 
		{ 
			// TODO PR�CTICA IA
			// Comprobar si el estado del nodo que se est� ejecutando es �xito

			CLatentAction::LAStatus status = currentNode->getStatus();
			return status == CLatentAction::SUCCESS;
		}
	};

	/**
	Esta clase define una condici�n que se eval�a a true si la 
	acci�n a la que pertenece ha terminado con fallo.
	*/
	class CConditionFail : public ICondition<CLatentAction>
	{
	public:
		bool check(CLatentAction* currentNode, Core::Entity* entity) 
		{ 
			
			// TODO PR�CTICA IA
			// Comprobar si el estado del nodo que se est� ejecutando es fallo
			
			CLatentAction::LAStatus status = currentNode->getStatus();
			return status == CLatentAction::FAIL;
		}
	};


} // namespace AI 

#endif // __AI_Condition_H
