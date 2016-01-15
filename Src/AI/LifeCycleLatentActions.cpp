/*
@file LyfeCycleLatentActions.cpp

Fichero que implementa las acciones latentes propias de la máquina de estados que controla el ciclo de vida
de algunas entidades (en concreto enemigos comunes y balas).

@author Grupo 3
@date Mayo 2011
*/

#include "LifeCycleLatentActions.h"
#include "Server.h"

#include "Core/BaseManager.h"
#include "Core/Data/EntityInfoTable.h"
#include "Core/Entities/Entity.h"
#include "Core/Graphics/GraphicEntity.h"
#include "Logic/Entity/Components/Graphics.h"
#include "Logic/Entity/Messages/MessageFactory.h"
#include "Logic/Entity/Messages/MessageTypes.h"
#include "Physics/Server.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "Logic/MissionManager.h"

#include "Core/Entities/World.h"
#include "Logic/Entity/Messages/ParticleSystemEndMessage.h"
#include "Logic/Entity/Messages/ShowHideEntityMessage.h"
#include "Logic/Entity/Messages/PlaySoundMessage.h"
#include "Logic/Entity/Components/Life.h"
#include "Logic/Entity/Components/PowerUpController.h"


namespace AI 
{

/**
============================================================================================================
CLALifeCycle_SLEEP: Esta acción "desactiva" la entidad hasta que se recibe un mensaje de tipo LIFE_CYCLE_ON.
============================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_SLEEP::OnStart()
	{	
		// Dormimos todos los componentes de la entidad excepto el físico y el ejecutor de la máquina de estados
		// TODO: leerlos de un descriptor
		Core::StringList exceptList;
		exceptList.push_back("PhysicEntity");
		exceptList.push_back("StateMachineExecutor");
		_entity->sleepAllComponentsExcept(exceptList);
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_SLEEP::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_SLEEP::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_SLEEP::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_SLEEP::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_ON);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_SLEEP::process(const Core::SmartMessage & message)
	{
		if (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_ON)
			finish(true);
	}


/**
========================================================================================================
CLALifeCycle_ON: esta acción hace completamente funcional la entidad, despertando todos sus componentes.
========================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_ON::OnStart()
	{	

		// Hacemos la entidad completamente funcional despertando a todos sus componentes
		_entity->awakeAllComponents();
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_ON::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_OFF || message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON::process(const Core::SmartMessage & message)
	{

		if (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_OFF) {
			finish(true);
		} else if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(false);
		}
	}


	
/**
===================================================================================================================
CLALifeCycle_OFF: esta acción duerme la mayoría de los componentes de la entidad, dejándola parcialmente funcional.
===================================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_OFF::OnStart()
	{	

		// Hacemos la entidad parcialmente funcional
		// TODO: leerlos de un descriptor
		Core::StringList exceptList;
		exceptList.push_back("Graphics");
		exceptList.push_back("ParticleSystem");
		exceptList.push_back("Death");
		exceptList.push_back("Sound");
		exceptList.push_back("StateMachineExecutor");
		_entity->sleepAllComponentsExcept(exceptList);

		// Directamente eliminamos su componente físico para evitar colisiones irreales
		_entity->removeComponent("PhysicEntity");

		// Mandamos ocultar la entidad, reproducimos el sonido de exposión, y mostramos un SP de explosión
		_entity->sendMessage(Logic::MessageFactory::CreateShowHideEntityMessage(false));
		_entity->sendMessage(Logic::MessageFactory::CreatePlaySoundMessage("Explosion1.wav"));
		_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("Explosion"));

		// Incrementamos en uno el número de enemigos comunes que ha destruido el jugador
		Logic::MissionManager::GetInstance()->increaseCommonEnemiesDestroyed();
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_OFF::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_OFF::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_OFF::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_OFF::accept(const Core::SmartMessage & message)
	{
		return (message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM_END);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_OFF::process(const Core::SmartMessage & message)
	{
		if (message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM_END) {			
			// Obtenemos el nombre del SP que ha finalizado. Si es "Explosion" pasamos al estado RELEASE
			if (message->getDataRefAs<Logic::ParticleSystemEndMessage>().getParticleSystemName() == "Explosion") 
				finish(true);
			
		}
	}



/**
======================================================================================================================
CLALifeCycle_BOSS_OFF: esta acción duerme la mayoría de los componentes de la entidad, dejándola parcialmente
funcional. Se muestra un sistema de partículas de "gran explosión" y al terminar este, pasa a un estado de liberación.
======================================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_BOSS_OFF::OnStart()
	{	

		// Hacemos la entidad parcialmente funcional
		// TODO: leerlos de un descriptor
		Core::StringList exceptList;
		exceptList.push_back("Graphics");
		exceptList.push_back("ParticleSystem");
		exceptList.push_back("Death");
		exceptList.push_back("Sound");
		exceptList.push_back("StateMachineExecutor");
		_entity->sleepAllComponentsExcept(exceptList);

		// Directamente eliminamos su componente físico para evitar colisiones irreales
		_entity->removeComponent("PhysicEntity");

		// Mandamos ocultar la entidad, reproducimos el sonido de exposión, y mostramos un SP de gran explosión
		_entity->sendMessage(Logic::MessageFactory::CreateShowHideEntityMessage(false));
		_entity->sendMessage(Logic::MessageFactory::CreatePlaySoundMessage("Explosion1.wav"));
		_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("BigExplosion"));
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_BOSS_OFF::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_BOSS_OFF::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_BOSS_OFF::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_BOSS_OFF::accept(const Core::SmartMessage & message)
	{
		return (message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM_END);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_BOSS_OFF::process(const Core::SmartMessage & message)
	{
		if (message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM_END) {			
			// Obtenemos el nombre del SP que ha finalizado. Si es "BigExplosion" pasamos al estado RELEASE
			if (message->getDataRefAs<Logic::ParticleSystemEndMessage>().getParticleSystemName() == "BigExplosion") 
				finish(true);
			
		}
	}


/**
==============================================================================================
CLALifeCycle_RELEASE: esta acción manda destruir la entidad, eviando un mensaje de tipo DEATH.
==============================================================================================
*/


	CLatentAction::LAStatus CLALifeCycle_RELEASE::OnStart()
	{	

		// Enviamos un mesaje de tipo DEATH a la entidad
		_entity->sendMessage(Logic::MessageFactory::CreateDeathMessage(0));

		finish(true);
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_RELEASE::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_RELEASE::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_RELEASE::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_RELEASE::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_RELEASE::process(const Core::SmartMessage & message)
	{
	}



/**
========================================================================================
CLALifeCycle_BOSS_RELEASE: 	esta acción manda destruir la entidad, eviando un mensaje de
tipo DEATH. Ademas da la orden de fin de misión (al haber acabado con el jefe final).
========================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_BOSS_RELEASE::OnStart()
	{	

		// Enviamos un mesaje de tipo DEATH a la entidad
		_entity->sendMessage(Logic::MessageFactory::CreateDeathMessage(0));

		// Ordenamos la finalización del nivel
		Logic::MissionManager::GetInstance()->setEndOfLevel(true);

		finish(true);
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_BOSS_RELEASE::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_BOSS_RELEASE::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_BOSS_RELEASE::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_BOSS_RELEASE::accept(const Core::SmartMessage & message)
	{
		return false;
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_BOSS_RELEASE::process(const Core::SmartMessage & message)
	{
	}


/**
========================================================================================================================
CLALifeCycle_CHECK_BULLET: Este estado es el inicial en el ciclo de vida de las balas. Se encarga de comprobar si
la bala está dentro de una AABB que simula la caja de la muerte, en cuyo caso pasará a un estado de total funcionalidad.
En caso contrario pasa a un estado de liberación.
========================================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_CHECK_BULLET::OnStart()
	{

		// Desactivamos todos los componentes excepto los siguientes
		// TODO: leerlos de un descriptor
		Core::StringList exceptList;
		//exceptList.push_back("Graphics"); BasicMovement Position

		exceptList.push_back("Death");
		exceptList.push_back("PhysicEntity");
		exceptList.push_back("StateMachineExecutor");
		_entity->sleepAllComponentsExcept(exceptList);

		// Obtenemos los datos necesarios
		Vector3 center = Logic::MissionManager::GetInstance()->getCenter();	// Centro de la acción
		Vector3 dim; dim.x = dim.y = dim.z = 250;							// Dimensiones del AABB por defecto (TODO: leerlo de datos externos)

		// Obtenemos las dimensiones de la caja de la muerte para que la AABB la simule perfectamente
		Core::Entity* deathBox = _entity->getWorld()->getEntityByName("DeathBox");
		if (deathBox != 0)
		{
			const Core::EntityInfoTable* entityInfo = deathBox->getInfo();
			if (entityInfo->hasAttribute("physic_dimensions"))
			{
				dim = entityInfo->getAttributeAsVector3("physic_dimensions");	// Guardamos las dimensiones
				dim += 50;														// La hacemos 50 unidades más grande para curarnos en salud
			}
		}		

		// Comprobamos si hay colisión entre el AABB y la entidad física
		bool colision = Physics::CServer::getSingletonPtr()->checkHardColision(
							_entity->getComponentAs<Logic::PhysicEntity>("PhysicEntity")->getPhysicEntity(),
							center,
							dim);

		// Si esta dentro (hay colision), pasar al estado ON. Si esta fuera, pasar al estado RELEASE
		if (colision) _entity->sendMessage(Logic::MessageFactory::CreateLifeCycleONMessage());
		else _entity->sendMessage(Logic::MessageFactory::CreateLifeCycleRELEASEMessage());

		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_CHECK_BULLET::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_CHECK_BULLET::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_CHECK_BULLET::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_CHECK_BULLET::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_ON || message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_CHECK_BULLET::process(const Core::SmartMessage & message)
	{
		if (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_ON) {
			finish(true);
		} else if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(false);
		}
	}


/**
==============================================================================================
CLALifeCycle_ON_ENEMY_BULLET: esta acción hace completamente funcional la entidad, despertando
todos sus componentes.
==============================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_ON_ENEMY_BULLET::OnStart()
	{	

		// Hacemos la entidad completamente funcional despertando a todos sus componentes
		_entity->awakeAllComponents();

		_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("RedBullet"));
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON_ENEMY_BULLET::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON_ENEMY_BULLET::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON_ENEMY_BULLET::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_ON_ENEMY_BULLET::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON_ENEMY_BULLET::process(const Core::SmartMessage & message)
	{
		if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(false);
		}
	}


/**
==============================================================================================
CLALifeCycle_ON_BOSS1_BULLET: esta acción hace completamente funcional la entidad, despertando
todos sus componentes. Muestra el SP propio de las balas del jefe final del nivel 1.
==============================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_ON_BOSS1_BULLET::OnStart()
	{	

		// Hacemos la entidad completamente funcional despertando a todos sus componentes
		_entity->awakeAllComponents();

		_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("BulletBoss1"));
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON_BOSS1_BULLET::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON_BOSS1_BULLET::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON_BOSS1_BULLET::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_ON_BOSS1_BULLET::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON_BOSS1_BULLET::process(const Core::SmartMessage & message)
	{
		if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(false);
		}
	}


/**
=====================================================================================================
CLALifeCycle_ON_PLAYER_BULLET: esta acción hace completamente funcional la entidad, despertando todos
sus componentes. Además contabiliza la bala en el contador total.
=====================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_ON_PLAYER_BULLET::OnStart()
	{	

		// Hacemos la entidad completamente funcional despertando a todos sus componentes
		_entity->awakeAllComponents();

		// Contabilizamos el disparo en el contador total de balas disparadas.
		Logic::MissionManager::GetInstance()->increaseTotalBulletCounter();
		if(_entity->getType() == "Bullet2") {
			_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("GreenBullet"));
		} else {
			_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("PowerBullet"));
		}
		_entity->sendMessage(Logic::MessageFactory::CreatePlaySoundMessage("Bullet.wav"));
		
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON_PLAYER_BULLET::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON_PLAYER_BULLET::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.
		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_ON_PLAYER_BULLET::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_ON_PLAYER_BULLET::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_OFF || message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}

	// -----------------------------------------------------------

	void CLALifeCycle_ON_PLAYER_BULLET::process(const Core::SmartMessage & message)
	{

		if (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_OFF) {
			finish(true);
		} else if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(false);
		}
	}

/**
=============================================================================================================
CLALifeCycle_OFF_BULLET: Este estado se encarga de dar la orden de contabilizar el que la bala haya impactado
contra un enemigo.
=============================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_OFF_BULLET::OnStart()
	{
		// Contabilizamos el impacto de la bala sobre un enemigo
		Logic::MissionManager::GetInstance()->increaseImpactBulletCounter();

		// Enviamos un mensaje para transitar a un estado de liberación
		_entity->sendMessage(Logic::MessageFactory::CreateLifeCycleRELEASEMessage());

		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_OFF_BULLET::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_OFF_BULLET::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_OFF_BULLET::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_OFF_BULLET::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_OFF_BULLET::process(const Core::SmartMessage & message)
	{
		if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(true);
		}
	}

/**
===========================================================================================================
CLALifeCycle_POSITIONING_PLAYER: Éste estado es el inicial en el ciclo de vida del jugador. Se encarga de
posicionar la nave correctamente en el plano de acción, tras lo cual, el jugador podrá empezar a manejarla.
===========================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_POSITIONING_PLAYER::OnStart()
	{
		//printf("PLAYER::POSITIONING\n");

		// TODO: dormir los componentes necesarios ("AvatarController" entre otros...)

		// TODO (David R.): llamar a la función de posicionamiento
		// IMPORTANTE (David R.): cuando acabe de posicionarse la nave ha de enviarse un msj de tipo "PLAYER_POSITIONED"
		
		//_entity->sendMessage(Logic::MessageFactory::CreateShowHideEntityMessage(true));
		_entity->sendMessage(Logic::MessageFactory::CreateSwitchMessage(0));
		_entity->sendMessage(Logic::MessageFactory::CreatePlayerPositionedMessage());

		// Ordenamos mostrar el SP del propuksor de la nave
		if (!_initializedRocket)
		{
			_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("Rocket"));
			_initializedRocket = true;
		}

		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_POSITIONING_PLAYER::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_POSITIONING_PLAYER::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_POSITIONING_PLAYER::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_POSITIONING_PLAYER::accept(const Core::SmartMessage & message)
	{

		return message->getType() == MESSAGE_TYPE_PLAYER_POSITIONED;
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_POSITIONING_PLAYER::process(const Core::SmartMessage & message)
	{
		// Al recibir un mensaje de PLAYER_POSITIONED, transitamos al estado PLAYING_PLAYER
		if (message->getType() == MESSAGE_TYPE_PLAYER_POSITIONED)
			finish(true);
	}


/**
=================================================================================================
CLALifeCycle_PLAYING_PLAYER: cuando la nave del jugador se ha posicionado correctamente se pasa a
éste estado, en el cual se hace completamente funcional dicha entidad.
=================================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_PLAYING_PLAYER::OnStart()
	{
		//printf("PLAYER::PLAYING\n");

		// Hacemos la entidad completamente funcional despertando a todos sus componentes
		_entity->awakeAllComponents();

		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_PLAYING_PLAYER::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_PLAYING_PLAYER::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_PLAYING_PLAYER::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_PLAYING_PLAYER::accept(const Core::SmartMessage & message)
	{

		return message->getType() == MESSAGE_TYPE_PLAYER_DEAD;
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_PLAYING_PLAYER::process(const Core::SmartMessage & message)
	{

		// Al recibir unmensaje de PLAYER_DEAD, transitamos al estado DEAD_PLAYER
		if (message->getType() == MESSAGE_TYPE_PLAYER_DEAD)
			finish(true);
	}


/**
========================================================================================
CLALifeCycle_DEAD_PLAYER: cuando se llega a éste estado es porque han matado al jugador.
========================================================================================
*/

	CLatentAction::LAStatus CLALifeCycle_DEAD_PLAYER::OnStart()
	{
		//printf("PLAYER::DEAD\n");

		// Si el numero de vidas restantes es mayor que cero...
		int nLives = _entity->getComponentAs<Logic::Life>("Life")->getPlayerLives();
		if (nLives>=0)
		{
			// Cambiamos el material de la entidad, reproducimos el sonido de exposión, y mostramos un SP de explosión
			// Tras finalizar el SP se vuelve al estado de POSITIONING
			_entity->sendMessage(Logic::MessageFactory::CreateSwitchMessage(1));
			_entity->sendMessage(Logic::MessageFactory::CreatePlaySoundMessage("Explosion1.wav"));
			_entity->sendMessage(Logic::MessageFactory::CreateParticleSystemMessage("Explosion"));

			// Durante este tiempo la entidad no recibe daño
			_entity->sleepComponent("Life");

		}
		else	// Si no...
		{
			// Enviamos un mensaje para transitar al estado de liberación de la entidad
			_entity->sendMessage(Logic::MessageFactory::CreateLifeCycleRELEASEMessage());
		}
			
		return SUSPENDED;
	}

	// -----------------------------------------------------------

	void CLALifeCycle_DEAD_PLAYER::OnStop()
	{
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_DEAD_PLAYER::OnRun() {
		// Si el flujo de ejecución llega a entrar en este método
		// significa que hay algo que no va bien. Se supone que 
		// la acción, nada más iniciarse se queda suspendida (por 
		// lo que no se llega a llamar a este método) y cuando 
		// recibe los mensajes pasa directamente a terminar con
		// éxito o con fallo.

		return RUNNING;
	}

	// -----------------------------------------------------------

	CLatentAction::LAStatus CLALifeCycle_DEAD_PLAYER::OnAbort() 
	{
		return FAIL;
	}

	// -----------------------------------------------------------

	bool CLALifeCycle_DEAD_PLAYER::accept(const Core::SmartMessage & message)
	{

		return (message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM_END || message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE);
	}
	
	// -----------------------------------------------------------

	void CLALifeCycle_DEAD_PLAYER::process(const Core::SmartMessage & message)
	{

		if (message->getType() == MESSAGE_TYPE_PARTICLE_SYSTEM_END) {			
			// Obtenemos el nombre del SP que ha finalizado. Si es "Explosion" pasamos al estado RELEASE
			if (message->getDataRefAs<Logic::ParticleSystemEndMessage>().getParticleSystemName() == "Explosion") 
				finish(true);

		} else if(message->getType() == MESSAGE_TYPE_LIFE_CYCLE_RELEASE) {
			finish(false);
		}
	}

} //namespace AI 