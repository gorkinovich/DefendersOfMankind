#include <OgreTimer.h>

#include "SimpleLatentActions.h"
#include "WaypointGraph.h"
#include "Server.h"

#include "Core/BaseManager.h"
#include "Core/Entities/Entity.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
//#include "Logic/Entity/Messages/RouteToMessage.h"

#include "BehaviorExecutionContext.h"

namespace AI 
{
	/**
	M�todo invocado al principio de la ejecuci�n de la acci�n,
	para que se realicen las tareas que son �nicamente necesarias
	al principio (y no durante toda la vida de la acci�n).
	<p>
	En este caso, se debe enviar un mensaje al componente 
	RouteTo y cambiar al estado SUSPENDED.

	@return Estado de la funci�n; si se indica que la
	acci�n a terminado (LatentAction::Completed), se invocar�
	al OnStop().
	*/
	CLatentAction::LAStatus CLARouteTo::OnStart()
	{	
		// TODO PR�CTICA IA
		// Al comenzar la ejecuci�n, la acci�n env�a un mensaje al 
		// componente que calcula las rutas. Mientras este componente
		// se ejecuta, la acci�n se queda suspendida, esperando recibir
		// el mensaje de que ha llegado a destino o no se ha podido 
		// calcular la ruta.

		// Enviar un mensaje a la entidad que se ocupa de calcular rutas
		AI::CWaypointGraph *wg = AI::CServer::getSingletonPtr()->getNavigationGraph();
		int waypoints = wg->getWaypointCount();
		int targetId = rand() % waypoints;
		Vector3 target = wg->getWaypoint(targetId);
		std::cout << "Navigating to: " << target << std::endl;
		sendMoveMessage(true, target);
		return SUSPENDED;
	}

	/**
	M�todo invocado al final de la ejecuci�n de la acci�n,
	para que se realicen las tareas que son �nicamente necesarias
	al final (y no durante toda la vida de la acci�n).

	En la mayor�a de los casos este m�todo no hace nada.
	*/
	void CLARouteTo::OnStop()
	{
	}

	/**
	M�todo invocado c�clicamente para que se contin�e con la
	ejecuci�n de la acci�n.
	<p>
	En este caso no hace nada.

	@return Estado de la acci�n tras la ejecuci�n del m�todo;
	permite indicar si la acci�n ha terminado o se ha suspendido.
	*/
	CLatentAction::LAStatus CLARouteTo::OnRun() {
		// TODO PR�CTICA IA
		// Si el flujo de ejecuci�n llega a entrar en este m�todo
		// significa que hay algo que no va bien. Se supone que 
		// la acci�n, nada m�s iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este m�todo) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// �xito o con fallo.
		return RUNNING;
	}

	/**
	Env�a un mensaje de tipo ROUTE_TO.
	*/
	void CLARouteTo::sendMoveMessage(bool walk, Vector3 target)
	{
		/*
		// Env�a un mensaje para calcular una ruta.
		Logic::RouteToMessage message2;
		// El bool indica si el receptor debe calcular la ruta 
		// o debe dejar de recorrer la ruta actual y parar
		message2.setWalk(walk);
		// Destino de la ruta. Si el par�metro anterior es false
		// este valor no se utiliza
		message2.setTarget(target);
		//*/
		_entity->sendMessage(Logic::MessageFactory::CreateRouteToMessage(walk, target), NULL);
	}

	/**
	M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
	al que pertenece se ha abortado por cualquier raz�n).

	La tarea puede en este momento realizar las acciones que
	considere oportunas para "salir de forma ordenada".

	@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
	de OnStop().
	*/
	CLatentAction::LAStatus CLARouteTo::OnAbort() 
	{
		// TODO PR�CTICA IA
		// Cuando se interrumpe una acci�n de seguimiento de una ruta
		// hay que enviar un mensaje al componente de seguimiento de rutas
		// para que se detenga si hay una ruta a medioseguir.

		// Enviamos un mensaje al componente de enrutamiento para que pare.
		sendMoveMessage();
		return FAIL;
	}

	/**
	Devuelve true si a la acci�n le interesa el tipo de mensaje
	enviado como par�metro.
	<p>
	Esta acci�n acepta mensajes del tipo FAILED_ROUTE y FINISHED_ROUTE

	@param msg Mensaje que ha recibido la entidad.
	@return true Si la acci�n est� en principio interesada
	por ese mensaje.
	*/
	bool CLARouteTo::accept(const Core::SmartMessage & message)
	{
		// TODO PR�CTICA IA
		// Esta acci�n acepta mensajes del tipo FAILED_ROUTE y FINISHED_ROUTE
		return (message->getType() == MESSAGE_TYPE_FAILED_ROUTE || message->getType() == MESSAGE_TYPE_FINISHED_ROUTE);
	}
	/**
	Procesa el mensaje recibido. El m�todo es invocado durante la
	ejecuci�n de la acci�n cuando se recibe el mensaje.
	<p>
	Si recibe FINISHED_ROUTE la acci�n finaliza con �xito. Si recibe
	FAILED_ROUTE finaliza con fallo.

	@param msg Mensaje recibido.
	*/
	void CLARouteTo::process(const Core::SmartMessage & message)
	{
		// TODO PR�CTICA IA
		// Si se recibe un mensaje de fallo de la ruta hay que terminar con fallo.
		// Si es de finalizaci�n de la ruta hay que terminar con �xito.
		// Para terminar una acci�n latente usamos el m�todo finish (ver LatentAction.h)
		if (message->getType() == MESSAGE_TYPE_FAILED_ROUTE) {
			finish(false);
		} else if (message->getType() == MESSAGE_TYPE_FINISHED_ROUTE) {
			finish(true);
		}
	}

//////////////////////////////
//	Implementaci�n de CLAWait
//////////////////////////////

	/**
	M�todo invocado al principio de la ejecuci�n de la acci�n,
	para que se realicen las tareas que son �nicamente necesarias
	al principio (y no durante toda la vida de la acci�n).
	<p>
	Al comenzar se obtiene el tiempo actual y se calcula el 
	tiempo en el que terminar� la acci�n mediante el atributo _time

	@return Estado de la funci�n; si se indica que la
	acci�n a terminado (LatentAction::Completed), se invocar�
	al OnStop().
	*/
	CLatentAction::LAStatus CLAWait::OnStart()
	{
		// TODO PR�CTICA IA
		// Al iniciar el wait, calculamos el instante de tiempo en 
		// el que se tiene que finalizar la acci�n. 
		// Para obtener el instante actual podemos usar 
		// Core::BaseManager::GetInstance()->getTimer()
		// para sacar el timer de la aplicaci�n y usar su m�todo 
		// getMilliseconds.

		Ogre::Timer* t = Core::BaseManager::GetInstance()->getTimer();
		_endingTime = t->getMilliseconds() + _time;
		return RUNNING; 
	}

	/**
	M�todo invocado al final de la ejecuci�n de la acci�n,
	para que se realicen las tareas que son �nicamente necesarias
	al final (y no durante toda la vida de la acci�n).

	En la mayor�a de los casos este m�todo no hace nada.
	*/
	void CLAWait::OnStop()
	{
	}

	/**
	M�todo invocado c�clicamente para que se contin�e con la
	ejecuci�n de la acci�n.
	<p>
	En cada paso de ejecuci�n se obtiene el tiempo actual 
	y se comprueba si se debe acabar la acci�n.

	@return Estado de la acci�n tras la ejecuci�n del m�todo;
	permite indicar si la acci�n ha terminado o se ha suspendido.
	*/
	CLatentAction::LAStatus CLAWait::OnRun() 
	{
		// TODO PR�CTICA IA
		// En cada paso de ejecuci�n tendremos que comprobar si hemos
		// superado el tiempo de espera. Seg�n lo hayamos superado o no,
		// la acci�n tendr� que pasar a un estado de terminado con �xito o
		// quedarse en el mismo estado en ejecuci�n.

		Ogre::Timer* t = Core::BaseManager::GetInstance()->getTimer();
		unsigned long currentTime = t->getMilliseconds();
		return (currentTime > _endingTime) ? SUCCESS : RUNNING;
	}

	/**
	M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
	al que pertenece se ha abortado por cualquier raz�n).

	La tarea puede en este momento realizar las acciones que
	considere oportunas para "salir de forma ordenada".

	@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
	de OnStop().
	*/
	CLatentAction::LAStatus CLAWait::OnAbort() 
	{
		// Cuando se aborta se queda en estado terminado con fallo
		return FAIL;
	}
	/**
	Devuelve true si a la acci�n le interesa el tipo de mensaje
	enviado como par�metro.
	<p>
	Esta acci�n no acepta mensajes de ning�n tipo.

	@param msg Mensaje que ha recibido la entidad.
	@return true Si la acci�n est� en principio interesada
	por ese mensaje.
	*/
	bool CLAWait::accept(const Core::SmartMessage & message)
	{
		// TODO PR�CTICA IA
		// La acci�n no acepta mensajes
		return false;
	}
	/**
	Procesa el mensaje recibido. El m�todo es invocado durante la
	ejecuci�n de la acci�n cuando se recibe el mensaje.

	@param msg Mensaje recibido.
	*/
	void CLAWait::process(const Core::SmartMessage & message)
	{
		// TODO PR�CTICA IA
		// La acci�n no procesa mensajes
	}


//////////////////////////////
//////////////////////////////
//	
//	Implementaci�n de CLAExistsData
//	
//////////////////////////////
//////////////////////////////

	CLatentAction::LAStatus CLAExistsData::OnStart()
	{
		if (_context->hasAttribute(_destVariable))
			return SUCCESS;
		return FAIL;
	}




//////////////////////////////
//////////////////////////////
//	
//	Implementaci�n de CLAInvalidateData
//	
//////////////////////////////
//////////////////////////////

	CLatentAction::LAStatus CLAInvalidateData::OnStart()
	{
		bool erased = _context->removeAttribute(_destVariable);
		return (erased ? SUCCESS : FAIL );
	}


} //namespace AI 