//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodríguez, Gorka Suárez, Roberto Jiménez
// 
// This program is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//************************************************************************************************************
// Defenders of Mankind: Juego shoot'em up de naves en 3D.
// Copyright  (c) 2011  Grupo 03
// Grupo 03: David Entrena, David Rodríguez, Gorka Suárez, Roberto Jiménez
//************************************************************************************************************

//TODO: Completar y comentar el fichero...

#include <assert.h>

#include "Logic/MissionManager.h"

#include "Core/SafeDelete.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Entities/Entity.h"
#include "Core/Entities/World.h"
#include "Core/GUI/GUIManager.h"
#include "Core/Input/Keyboard.h"
#include "Core/Sound/Sound.h"
#include "Core/Sound/SoundManager.h"
#include "Logic/HUDController.h"
#include "Logic/MissionManager.h"
#include "Logic/Entity/Components/GeneralData.h"



//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	MissionManager * MissionManager::_instance = new MissionManager();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	//...

	//--------------------------------------------------------------------------------------------------------

	std::string MissionManager::getStatisticsLabels() const
	{
		//return std::string("Enemies destroyed\nSuccessful shots / Total shots\nAccuracy percent\n");

		std::stringstream ss;
		ss << "Enemies destroyed:" << "\n \n \n";
		ss << "Successful shots / Total shots:" << "\n \n \n";
		ss << "Accuracy:" << "\n";

		return std::string(ss.str());

		
	}

	//--------------------------------------------------------------------------------------------------------


	std::string MissionManager::getStatisticsValues() const
	{
		std::stringstream ss;
		ss << MissionManager::GetInstance()->getCommonEnemiesDestroyed()	<< "\n";
		ss << "x50 = " << MissionManager::GetInstance()->getCommonEnemiesTotalBonus() << "\n \n";
		ss << MissionManager::GetInstance()->getImpactBulletCounter()		<< " of ";
		ss << MissionManager::GetInstance()->getTotalBulletCounter()		<< "\n";
		ss << "x25 = " << MissionManager::GetInstance()->getImpactBulletTotalBonus() << "\n \n";
		ss << MissionManager::GetInstance()->getAccuracyPercentage()		<< " % \n";
		ss << "x100 = " << MissionManager::GetInstance()->getAccuracyTotalBonus() << " \n";

		return std::string(ss.str());
	}

	//--------------------------------------------------------------------------------------------------------

	std::string MissionManager::getFinalPointsLabel() const
	{
		return std::string("Total Points:");
	}

	//--------------------------------------------------------------------------------------------------------

	std::string MissionManager::getFinalPointsValue() const
	{
		std::stringstream ss;
		ss << MissionManager::GetInstance()->getTotalBonus();
		return std::string(ss.str());
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MissionManager::initialize() {
		//TODO: Completar el método...

		// Inicializamos la interfaz con el usuario.
		_HUDController = new HUDController();

		// Inicializamos el gestor de entidades.
		if(!Core::EntitiesManager::GetInstance()->initialize()) return false;

		// Registra los tipos de componentes que forman parte del juego.
		if(!registerComponentTypes()) return false;

		// Registra todos los tipos de movimientos predefinidos que existen.
		if(!registerMovementTypes()) return false;

		// Ponemos la velocidad inicial
		_speed = 0.1f;

		// Ponemos los valores iniciales de bifurcación
		_bifurcation = false;
		_bifurcationDirection = Vector3::ZERO;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::release() {
		//TODO: Completar el método...
		unloadLevel();
		Core::EntitiesManager::GetInstance()->release();
		SafeDelete(_HUDController);
	}
	
	//--------------------------------------------------------------------------------------------------------

	void MissionManager::prepareUpdate(unsigned int lastInterval) {
		//TODO: Completar el método...
		assert(_world && "MissionManager::prepareUpdate -> The world can't be null...");
		_world->prepareUpdate(lastInterval);
	}
	
	//--------------------------------------------------------------------------------------------------------

	void MissionManager::update(unsigned int lastInterval) {
		//TODO: Completar el método...
		assert(_world && "MissionManager::update -> The world can't be null...");
		_world->update(lastInterval);
		// Eliminamos las entidades que se han marcado para ser eliminadas.
		Core::EntitiesManager::GetInstance()->deleteDeferredEntities();
	}
	
	//--------------------------------------------------------------------------------------------------------

	bool MissionManager::activateMap() {
		//TODO: Completar el método...
		assert(_world && "MissionManager::activateMap -> The world can't be null...");
		return _world->activate();
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::deactivateMap() {
		//TODO: Completar el método...
		assert(_world && "MissionManager::deactivateMap -> The world can't be null...");
		_world->deactivate();
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::unloadLevel() {
		Core::EntitiesManager::GetInstance()->unloadCurrentWorld();
		endLevel();
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::startLevel() {
		_world = Core::EntitiesManager::GetInstance()->getCurrentWorld();
		//Inicializamos las variables de las bonificaciones
		_endOfLevel = false;
		initBonusVars();
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::endLevel() {
		_world = 0;
		_player = 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::RegisterUnLoadMissionSound(const std::string& soundName)
	{
		// Comprobamos si ya ha sido registrado o no
		TSoundList::const_iterator it = _soundsToUnload.begin();
		TSoundList::const_iterator end = _soundsToUnload.end();
		TSoundList::const_iterator aux = std::find(it, end, soundName);

		// Si no ha sido registrado previamente... lo registramos en la lista
		if(aux==end) _soundsToUnload.push_back(soundName);

	}

	//--------------------------------------------------------------------------------------------------------

	bool MissionManager::UnLoadMissionSounds()
	{
		bool ret = true;

		// Recorremos la lista y descargamos cada sonido
		TSoundList::iterator it = _soundsToUnload.begin();
		TSoundList::iterator end = _soundsToUnload.end();
		for(it; it!=end; ++it)
		{
			ret = ret && Core::SoundManager::GetInstance()->unloadSound((*it));
		}
		
		// Limpiamos la tabla
		_soundsToUnload.clear();

		return ret;
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::tryAgainLevel() {
		//TODO: Completar el método...
	}

	//--------------------------------------------------------------------------------------------------------

	//...

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::initBonusVars() {

		_commonEnemiesDestroyed = 0;
		_commonEnemyBonus = 50;

		_totalBulletCounter = 0;
		_impactBulletCounter = 0;
		_bulletImpactBonus = 25;


		/*//Cargamos los máximos para las puntuaciones (LUA)
		maxPoints = 0;
		maxTimeBonus = 0.0f;
		minTimeBonus = 0.0f;
		maxDamage = 0.0f;
		gunnedInArrowMax = 0;

		//Cargamos los elementos totales de cada tipo (entity list)
		const char * targetType = "Enemy";
		if(_world->existsEntitiesByType(targetType)) {
			std::list<int> tempSquadList;
			Core::EntityListIterator itEntByType = _world->getEntitiesByTypeBegin(targetType);
			Core::EntityListIterator endEntByType = _world->getEntitiesByTypeEnd(targetType);
			for(totalEnemies = 0; itEntByType != endEntByType; ++itEntByType, ++totalEnemies) {
				Core::Entity * tempEntity = (*itEntByType);
				std::list<int>::const_iterator it;
				int auxIDSquadron = tempEntity->getComponentAs<GeneralData>("GeneralData")->getIDSquadron();
				for(it = tempSquadList.begin(); it != tempSquadList.end() && *it != auxIDSquadron; ++it);

				if(it != tempSquadList.end() && tempSquadList.size() != 0)
					tempSquadList.push_back(auxIDSquadron);
			}
			totalSquads = tempSquadList.size();
			printf("%d\n", totalSquads);
			//for(totalHumans = 0; _world->getEntityByType("human") != 0; totalHumans++);
			//for(totalPowerUps = 0; _world->getEntityByType("powerUp") != 0; totalPowerUps++);
		}

		//Iniciamos las variables que llevan el estado de las puntuaciones
		enemies = 0;
		enemyCombo = 0;
		enemyMaxCombo = 0;
		squadrons = 0;
		powerUps = 0;
		time = 0.0f;
		damageRecieved = 0.0f;
		humansRescued = 0; */
	}

	float MissionManager::getAccuracyPercentage()
	{
		if (_totalBulletCounter==0) return 0.0f;
		else
			return (float) (((int)(_impactBulletCounter*10000.0f)/_totalBulletCounter))/100.0f;
	
	}

	unsigned int MissionManager::getActualBonus()
	{
		unsigned int total = 0;

		total += getCommonEnemiesTotalBonus() +
				 getImpactBulletTotalBonus();

		return total;
	}

	unsigned int MissionManager::getTotalBonus()
	{
		unsigned int total = 0;

		total += getCommonEnemiesTotalBonus() +
				 getImpactBulletTotalBonus() +
				 getAccuracyTotalBonus();

		return total;
	}

	//--------------------------------------------------------------------------------------------------------

	void MissionManager::takeBifurcation(Vector3 dest, float time){
		_bifurcation = true;
		Vector3 * center = &Logic::MissionManager::GetInstance()->getCenter();
		_bifurcationDirection = dest - *center;
		_bifurcationDestination = dest;
		_bifurcationTime = time * 1000.0f;
		_bifurcationActualTime = 0;
	}

	Vector3 MissionManager::bifurcationStep(unsigned int lastInterval){
		if((_center.z - (_bifurcationDirection.z * (_speed * (float)lastInterval / 500.0f))) > _bifurcationDestination.z) {
			return _bifurcationDirection * _speed * (float)lastInterval / 500.0f;
		} else {
			_bifurcation = false;
			_bifurcationDirection = Vector3::ZERO;
			_bifurcationActualTime = 0;
			_center = _bifurcationDestination;
		}

		//Old way of life
/*		if (_bifurcationActualTime < _bifurcationTime){
			_bifurcationActualTime += lastInterval;
			float prop = (Ogre::Real)(lastInterval) * 0.001f;
			return _bifurcationDirection * prop;
		}else{
			_bifurcation=false;
			_bifurcationDirection = Vector3::ZERO;
			_bifurcationActualTime = 0;
			_center = _bifurcationDestination;
		}
*/
		return Vector3::ZERO;
	}

	//...
}
