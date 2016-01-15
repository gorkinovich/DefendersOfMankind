/**
@file BehaviourTreesLatentActions.h

Fichero que implementa las acciones latentes propias de los �rboles de comportamiento.

@author Grupo 3
@date Junio 2011

*/

#pragma once

#ifndef __AI_BehaviourTreesLatentActions_H
#define __AI_BehaviourTreesLatentActions_H

#include "LatentAction.h"

#include "VirtualBoard.h"

namespace AI 
{

/**
==============================================================================================
CLA_BT_CHECK_LIFE:

	- Esta acci�n comprueba si la vida de la entidad est� por debajo del 100%.
==============================================================================================
*/
	class CLA_BT_CHECK_LIFE : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_CHECK_LIFE(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLA_BT_CHECK_LIFE() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
			Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

	};



/*==========================================================
CLA_BT_SHOOT:

	- Esta acci�n ordena a la entidad que genere un disparo.
============================================================
*/
	class CLA_BT_SHOOT : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_SHOOT(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLA_BT_SHOOT() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
			Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

	};



/**
========================================================================================
CLA_BT_CHECK_HEIGHT:

	- Esta acci�n comprueba si el jugador se encuentra a la misma altura que la entidad.
========================================================================================
*/
	class CLA_BT_CHECK_HEIGHT : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_CHECK_HEIGHT(Core::Entity* entity) : CLatentAction(), _entity(entity) {}

		/**
		Destructor
		*/
		~CLA_BT_CHECK_HEIGHT() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

		/*
		Tablero virtual.
		*/
		VirtualBoard _virtualBoard;

	};

/**
==============================================================================================
CLA_BT_CHANGE_TARGET_QUADRANT:

	- Esta acci�n calcula un nuevo cuadrante objetivo y lo guarda en el contexto de ejecuci�n.
==============================================================================================
*/
	class CLA_BT_CHANGE_TARGET_QUADRANT : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_CHANGE_TARGET_QUADRANT(Core::Entity* entity) : CLatentAction(), _entity(entity) {}

		/**
		Destructor
		*/
		~CLA_BT_CHANGE_TARGET_QUADRANT() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

		/*
		Tablero virtual.
		*/
		VirtualBoard _virtualBoard;

	};


/**
=====================================================================================
CLA_BT_MOVE_TO_QUADRANT:

	- Esta acci�n env�a un mensaje para que la entidad se mueva hacia otro cuadrante.
=====================================================================================
*/
	class CLA_BT_MOVE_TO_QUADRANT : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_MOVE_TO_QUADRANT(Core::Entity* entity) : CLatentAction(), _entity(entity) {}

		/**
		Destructor
		*/
		~CLA_BT_MOVE_TO_QUADRANT() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

	};


/**
=====================================================================================
CLA_BT_IDLE:

	- Esta acci�n no hace nada.
=====================================================================================
*/
	class CLA_BT_IDLE : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_IDLE(Core::Entity* entity) : CLatentAction(), _entity(entity) {}

		/**
		Destructor
		*/
		~CLA_BT_IDLE() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

	};


/**
===================================================================================
CLA_BT_INIT_QUADRANT:

	- Esta acci�n guarda el el contexto de ejecuci�n el cuadrante objetivo inicial.
===================================================================================
*/
	class CLA_BT_INIT_QUADRANT : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_INIT_QUADRANT(Core::Entity* entity) : CLatentAction(), _entity(entity) {}

		/**
		Destructor
		*/
		~CLA_BT_INIT_QUADRANT() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

	};


/**
========================================================================================
CLA_BT_CHECK_HEIGHT_BOSS2:

	- Esta acci�n comprueba si el jugador se encuentra a la misma altura que la entidad.
========================================================================================
*/
	class CLA_BT_CHECK_HEIGHT_BOSS2 : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_CHECK_HEIGHT_BOSS2(Core::Entity* entity) : CLatentAction(), _entity(entity),  _left(true) {}

		/**
		Destructor
		*/
		~CLA_BT_CHECK_HEIGHT_BOSS2() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

		/*
		Tablero virtual.
		*/
		VirtualBoard _virtualBoard;

		bool _left;



	};


	/**
==============================================================================================
CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2:

	- Esta acci�n calcula un nuevo cuadrante objetivo y lo guarda en el contexto de ejecuci�n.
==============================================================================================
*/
	class CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2 : public CLatentAction
	{
	public:

		/**
		Constructor.
		
		@param entity
		*/
		CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2(Core::Entity* entity) : CLatentAction(), _entity(entity) {}

		/**
		Destructor
		*/
		~CLA_BT_CHANGE_TARGET_QUADRANT_BOSS2() {};

		/**
		M�todo invocado al principio de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al principio (y no durante toda la vida de la acci�n).

		@return Estado de la funci�n; si se indica que la
		acci�n a terminado (LatentAction::Completed), se invocar�
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		M�todo invocado al final de la ejecuci�n de la acci�n,
		para que se realicen las tareas que son �nicamente necesarias
		al final (y no durante toda la vida de la acci�n).

		En la mayor�a de los casos este m�todo no hace nada.
		*/
		virtual void OnStop();


		/**
		M�todo invocado c�clicamente para que se contin�e con la
		ejecuci�n de la acci�n.

		@return Estado de la acci�n tras la ejecuci�n del m�todo.
		*/
		virtual LAStatus OnRun() ;


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acci�n le interesa el tipo de mensaje
		enviado como par�metro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acci�n est� en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El m�todo es invocado durante la
		ejecuci�n de la acci�n cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acci�n.
		*/
		Core::Entity* _entity;

		/*
		Tablero virtual.
		*/
		VirtualBoard _virtualBoard;

	};

} //namespace AI 

#endif // __AI_BehaviourTreesLatentActions_H