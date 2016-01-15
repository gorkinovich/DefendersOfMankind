/**
@file LyfeCycleLatentActions.h

Fichero que implementa las acciones latentes propias de la m�quina de estados que controla el ciclo de vida
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

	- Esta acci�n "desactiva" la entidad hasta que se recibe un mensaje de tipo LIFE_CYCLE_ON.
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
=============================================================================================
CLALifeCycle_ON:

	- Esta acci�n hace completamente funcional la entidad, despertando todos sus componentes.
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
============================================================================================================
CLALifeCycle_OFF:

	- Esta acci�n duerme la mayor�a de los componentes de la entidad, dej�ndola parcialmente funcional.
	- Se muestra un sistema de part�culas de "explosi�n" y al terminar este, pasa a un estado de liberaci�n.
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
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=================================================================================================================
CLALifeCycle_BOSS_OFF:

	- Esta acci�n duerme la mayor�a de los componentes de la entidad, dej�ndola parcialmente funcional.
	- Se muestra un sistema de part�culas de "gran explosi�n" y al terminar este, pasa a un estado de liberaci�n.
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
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
==============================================================================
CLALifeCycle_RELEASE:

	- Esta acci�n manda destruir la entidad, eviando un mensaje de tipo DEATH.
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
===============================================================================
CLALifeCycle_BOSS_RELEASE:

	- Esta acci�n manda destruir la entidad, eviando un mensaje de tipo DEATH.
	- Ademas da la orden de fin de misi�n (al haber acabado con el jefe final).
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=============================================================================================
CLALifeCycle_CHECK_BULLET:

	- Este estado es el inicial en el ciclo de vida de las balas. Se encarga de comprobar si
	  la bala est� dentro de la caja de la muerte, en cuyo caso pasar� a un estado de total
	  funcionalidad. En caso contrario pasa a un estado de liberaci�n.
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		permite indicar si la acci�n ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=============================================================================================
CLALifeCycle_ON_PLAYER_BULLET:

	- Esta acci�n hace completamente funcional la entidad, despertando todos sus componentes.
	- Adem�s contabiliza la bala en el contador total.
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
=============================================================================================
CLALifeCycle_ON_ENEMY_BULLET:

	- Esta acci�n hace completamente funcional la entidad, despertando todos sus componentes.
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
=============================================================================================
CLALifeCycle_ON_BOSS1_BULLET:

	- Esta acci�n hace completamente funcional la entidad, despertando todos sus componentes.
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		permite indicar si la acci�n ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
=================================================================================================
CLALifeCycle_POSITIONING_PLAYER:

	- Este estado es el inicial en el ciclo de vida del jugador. Se encarga de posicionar la
	nave correctamente en el plano de acci�n, tras lo cual, el jugador podr� empezar a manejarla.
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		permite indicar si la acci�n ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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

		bool _initializedRocket;

	};



/**
==================================================================================================
CLALifeCycle_PLAYING_PLAYER:

	- Cuando la nave del jugador se ha posicionado correctamente se pasa a �ste estado, en el cual
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		permite indicar si la acci�n ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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
====================================================================
LALifeCycle_DEAD_PLAYER:

	- Cuando se llega a �ste estado es porque han matado al jugador.
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

		@return Estado de la acci�n tras la ejecuci�n del m�todo;
		permite indicar si la acci�n ha terminado o se ha suspendido.
		*/
		virtual LAStatus OnRun();


		/**
		M�todo invocado cuando la acci�n ha sido cancelada (el comportamiento
		al que pertenece se ha abortado por cualquier raz�n).

		La tarea puede en este momento realizar las acciones que
		considere oportunas para "salir de forma ordenada".

		@note <b>Importante:</b> el Abort <em>no</em> provoca la ejecuci�n
		de OnStop().
		*/
		virtual LAStatus OnAbort();


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

} //namespace AI 

#endif // __AI_LifeCycleLatentActions_H