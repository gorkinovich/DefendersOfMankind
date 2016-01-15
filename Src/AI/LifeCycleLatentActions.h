/**
@file LyfeCycleLatentActions.h

Fichero que implementa las acciones latentes propias de la máquina de estados que controla el ciclo de vida
de algunas entidades.

@author Grupo 3
@date Mayo 2011

*/

#pragma once

#ifndef __AI_LifeCycleLatentActions_H
#define __AI_LifeCycleLatentActions_H

#include "LatentAction.h"

namespace AI 
{

/**
==============================================================================================
CLALifeCycle_SLEEP:

	- Esta acción "desactiva" la entidad hasta que se recibe un mensaje de tipo LIFE_CYCLE_ON.
==============================================================================================
*/
	class CLALifeCycle_SLEEP : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_SLEEP(Core::Entity* entity) : CLatentAction(), _entity(entity) {};
		/**
		Destructor
		*/
		~CLALifeCycle_SLEEP() {};

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
=============================================================================================
CLALifeCycle_ON:

	- Esta acción hace completamente funcional la entidad, despertando todos sus componentes.
=============================================================================================
*/
	class CLALifeCycle_ON : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_ON(Core::Entity* entity) : CLatentAction(), _entity(entity) {};
		/**
		Destructor
		*/
		~CLALifeCycle_ON() {};

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
============================================================================================================
CLALifeCycle_OFF:

	- Esta acción duerme la mayoría de los componentes de la entidad, dejándola parcialmente funcional.
	- Se muestra un sistema de partículas de "explosión" y al terminar este, pasa a un estado de liberación.
============================================================================================================
*/
	class CLALifeCycle_OFF : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_OFF(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_OFF() {};

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
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=================================================================================================================
CLALifeCycle_BOSS_OFF:

	- Esta acción duerme la mayoría de los componentes de la entidad, dejándola parcialmente funcional.
	- Se muestra un sistema de partículas de "gran explosión" y al terminar este, pasa a un estado de liberación.
=================================================================================================================
*/
	class CLALifeCycle_BOSS_OFF : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_BOSS_OFF(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_BOSS_OFF() {};

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
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
==============================================================================
CLALifeCycle_RELEASE:

	- Esta acción manda destruir la entidad, eviando un mensaje de tipo DEATH.
==============================================================================
*/
	class CLALifeCycle_RELEASE : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_RELEASE(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_RELEASE() {};

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

		@return Estado de la acción tras la ejecución del método;
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
===============================================================================
CLALifeCycle_BOSS_RELEASE:

	- Esta acción manda destruir la entidad, eviando un mensaje de tipo DEATH.
	- Ademas da la orden de fin de misión (al haber acabado con el jefe final).
===============================================================================
*/
	class CLALifeCycle_BOSS_RELEASE : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_BOSS_RELEASE(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_BOSS_RELEASE() {};

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

		@return Estado de la acción tras la ejecución del método;
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=============================================================================================
CLALifeCycle_CHECK_BULLET:

	- Este estado es el inicial en el ciclo de vida de las balas. Se encarga de comprobar si
	  la bala está dentro de la caja de la muerte, en cuyo caso pasará a un estado de total
	  funcionalidad. En caso contrario pasa a un estado de liberación.
=============================================================================================
*/
	class CLALifeCycle_CHECK_BULLET : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_CHECK_BULLET(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_CHECK_BULLET() {};

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

		@return Estado de la acción tras la ejecución del método;
		permite indicar si la acción ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=============================================================================================
CLALifeCycle_ON_PLAYER_BULLET:

	- Esta acción hace completamente funcional la entidad, despertando todos sus componentes.
	- Además contabiliza la bala en el contador total.
=============================================================================================
*/
	class CLALifeCycle_ON_PLAYER_BULLET : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_ON_PLAYER_BULLET(Core::Entity* entity) : CLatentAction(), _entity(entity) {};
		/**
		Destructor
		*/
		~CLALifeCycle_ON_PLAYER_BULLET() {};

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
=============================================================================================
CLALifeCycle_ON_ENEMY_BULLET:

	- Esta acción hace completamente funcional la entidad, despertando todos sus componentes.
=============================================================================================
*/
	class CLALifeCycle_ON_ENEMY_BULLET : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_ON_ENEMY_BULLET(Core::Entity* entity) : CLatentAction(), _entity(entity) {};
		/**
		Destructor
		*/
		~CLALifeCycle_ON_ENEMY_BULLET() {};

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
=============================================================================================
CLALifeCycle_ON_BOSS1_BULLET:

	- Esta acción hace completamente funcional la entidad, despertando todos sus componentes.
	- Muestra el SP propio de las balas del jefe final del nivel 1.
=============================================================================================
*/
	class CLALifeCycle_ON_BOSS1_BULLET : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_ON_BOSS1_BULLET(Core::Entity* entity) : CLatentAction(), _entity(entity) {};
		/**
		Destructor
		*/
		~CLALifeCycle_ON_BOSS1_BULLET() {};

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
=================================================================================================
CLALifeCycle_OFF_BULLET:

	- Este estado se encarga de dar la orden de contabilizar el que la bala haya impactado contra
	un enemigo.
=================================================================================================
*/
	class CLALifeCycle_OFF_BULLET : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_OFF_BULLET(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_OFF_BULLET() {};

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

		@return Estado de la acción tras la ejecución del método;
		permite indicar si la acción ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=================================================================================================
CLALifeCycle_POSITIONING_PLAYER:

	- Este estado es el inicial en el ciclo de vida del jugador. Se encarga de posicionar la
	nave correctamente en el plano de acción, tras lo cual, el jugador podrá empezar a manejarla.
=================================================================================================
*/
	class CLALifeCycle_POSITIONING_PLAYER : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_POSITIONING_PLAYER(Core::Entity* entity) : CLatentAction(), _entity(entity), _initializedRocket(false) {};

		/**
		Destructor
		*/
		~CLALifeCycle_POSITIONING_PLAYER() {};

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

		@return Estado de la acción tras la ejecución del método;
		permite indicar si la acción ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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

		bool _initializedRocket;

	};



/**
==================================================================================================
CLALifeCycle_PLAYING_PLAYER:

	- Cuando la nave del jugador se ha posicionado correctamente se pasa a éste estado, en el cual
	se hace completamente funcional dicha entidad.
==================================================================================================
*/
	class CLALifeCycle_PLAYING_PLAYER : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_PLAYING_PLAYER(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_PLAYING_PLAYER() {};

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

		@return Estado de la acción tras la ejecución del método;
		permite indicar si la acción ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
====================================================================
LALifeCycle_DEAD_PLAYER:

	- Cuando se llega a éste estado es porque han matado al jugador.
====================================================================
*/
	class CLALifeCycle_DEAD_PLAYER : public CLatentAction
	{
	public:
		/**
		Constructor.
		
		@param entity
		*/
		CLALifeCycle_DEAD_PLAYER(Core::Entity* entity) : CLatentAction(), _entity(entity) {};

		/**
		Destructor
		*/
		~CLALifeCycle_DEAD_PLAYER() {};

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

		@return Estado de la acción tras la ejecución del método;
		permite indicar si la acción ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		Método invocado cuando la acción ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier razón).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecución
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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

} //namespace AI 

#endif // __AI_LifeCycleLatentActions_H