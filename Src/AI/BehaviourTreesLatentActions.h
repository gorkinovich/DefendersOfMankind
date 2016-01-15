/**
@file BehaviourTreesLatentActions.h

Fichero que implementa las acciones latentes propias de los árboles de comportamiento.

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

	- Esta acción comprueba si la vida de la entidad está por debajo del 100%.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
			Entidad que ejecuta la acción.
		*/
		Core::Entity* _entity;

	};



/*==========================================================
CLA_BT_SHOOT:

	- Esta acción ordena a la entidad que genere un disparo.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
			Entidad que ejecuta la acción.
		*/
		Core::Entity* _entity;

	};



/**
========================================================================================
CLA_BT_CHECK_HEIGHT:

	- Esta acción comprueba si el jugador se encuentra a la misma altura que la entidad.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
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

	- Esta acción calcula un nuevo cuadrante objetivo y lo guarda en el contexto de ejecución.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
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

	- Esta acción envía un mensaje para que la entidad se mueva hacia otro cuadrante.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
		*/
		Core::Entity* _entity;

	};


/**
=====================================================================================
CLA_BT_IDLE:

	- Esta acción no hace nada.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
		*/
		Core::Entity* _entity;

	};


/**
===================================================================================
CLA_BT_INIT_QUADRANT:

	- Esta acción guarda el el contexto de ejecución el cuadrante objetivo inicial.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
		*/
		Core::Entity* _entity;

	};


/**
========================================================================================
CLA_BT_CHECK_HEIGHT_BOSS2:

	- Esta acción comprueba si el jugador se encuentra a la misma altura que la entidad.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
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

	- Esta acción calcula un nuevo cuadrante objetivo y lo guarda en el contexto de ejecución.
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
		Método invocado al principio de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al principio (y no durante toda la vida de la acción).

		@return Estado de la función; si se indica que la
		acción a terminado (LatentAction::Completed), se invocará
		al OnStop().
		*/
		virtual LAStatus OnStart();


		/**
		Método invocado al final de la ejecución de la acción,
		para que se realicen las tareas que son únicamente necesarias
		al final (y no durante toda la vida de la acción).

		En la mayoría de los casos este método no hace nada.
		*/
		virtual void OnStop();


		/**
		Método invocado cíclicamente para que se continúe con la
		ejecución de la acción.

		@return Estado de la acción tras la ejecución del método.
		*/
		virtual LAStatus OnRun() ;


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort() ;


		/**
		Devuelve true si a la acción le interesa el tipo de mensaje
		enviado como parámetro.

		@param msg Mensaje que ha recibido la entidad.
		@return true Si la acción está en principio interesada
		por ese mensaje.
		*/
		virtual bool accept(const Core::SmartMessage & message);


		/**
		Procesa el mensaje recibido. El método es invocado durante la
		ejecución de la acción cuando se recibe el mensaje.

		@param msg Mensaje recibido.
		*/
		virtual void process(const Core::SmartMessage & message);

	protected:

		/**
		Entidad que ejecuta la acción.
		*/
		Core::Entity* _entity;

		/*
		Tablero virtual.
		*/
		VirtualBoard _virtualBoard;

	};

} //namespace AI 

#endif // __AI_BehaviourTreesLatentActions_H