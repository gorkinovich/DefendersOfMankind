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

#ifndef __LOGIC_MISSIONMANAGER_H__
#define __LOGIC_MISSIONMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Logic/Entity/Components/Camera.h"

#include "Core/Data/SimpleFactory.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Sound;
	class World;
	class Entity;
}

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	class HUDController;
	class IMovement;

	/**
	 * Este tipo representa una factoría de movimientos.
	 */
	typedef Core::SimpleFactory<IMovement> MovementsFactory;

	/**
	 * Esta clase representa al gestor de la misión del juego.
	 */
	class MissionManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Obtiene el ...
		 */
		//inline xxx get() const { return xxx; }
		
		/**
		 * Modifica el ...
		 */
		//inline void set(xxx value) { xxx = value; }
		
		/**
		 * Obtiene el mapa lógico del juego.
		 */
		inline Core::World * getWorld() { return _world; }

		/**
		 * Obtiene la entidad del jugador.
		 */
		inline Core::Entity * getPlayer() { return _player; }

		/**
		 * Modifica la entidad del jugador.
		 */
		inline void setPlayer(Core::Entity * value) { _player = value; }

		/**
		 * Obtiene la entidad de la cámara.
		 */
		inline Core::Entity * getCamera() { return _camera; }

		/**
		 * Modifica la entidad de la cámara.
		 */
		inline void setCamera(Core::Entity * value) { _camera = value; }

		/**
		 * Obtiene la entidad de la cámara.
		 */
		inline Camera * getGameCamera() { return _gameCamera; }

		/**
		 * Modifica la entidad de la cámara.
		 */
		inline void setGameCamera(Camera * value) { _gameCamera = value; }

		/**
		 * Obtiene el tipo de cámara actual.
		 */
		inline CameraType getCameraType() { return _cameraType; }

		/**
		 * Modifica el tipo de cámara actual.
		 * @remark Este valor es informativo, el auténtico está en la entidad cámara
		 *         que se encargará de actualizarlo.
		 */
		inline void setCameraType(CameraType value) { _cameraType = value; }

		/**
		 * Obtiene el centro de la acción.
		 */
		inline Vector3 getCenter() const { return _center; }

		/**
		 * Modifica el centro de la acción.
		 */
		inline void setCenter(const Vector3 & value) { _center = value; }

		/**
		 * Obtiene la distancia de la acción.
		 */
		inline float getDistance() const { return _distance; }

		/**
		 * Modifica la velocidad de la acción.
		 */
		inline void setSpeed(const float & value) { _speed = value; }

		/**
		 * Obtiene la velocidad de la acción.
		 */
		inline float getSpeed() const { return _speed; }

		/**
		 * Modifica la distancia de la acción.
		 */
		inline void setDistance(const float & value) { _distance = value; }

		/**
		 * Obtiene si estamos en una bifurcación.
		 */
		inline float getBifurcation() const { return _bifurcation; }

		/**
		 * Obtiene la dirección de bifurcación.
		 */
		inline Vector3 getBifurcationDirection() const { return _bifurcationDirection; }

		/**
		 * Devuelve la instancia de la clase GUI que se encarga de manejar el HUD.
		 * @return Instancia de la clase GUI que controla el HUD.
		 */
		inline HUDController * getHUDController() { return _HUDController; }

		/**
		 * Devuelve si se terminó el nivel.
		 * @return TRUE = EndOfLevel, FALSE = CONTINUE
		 */
		inline bool getEndOfLevel() { return _endOfLevel; }

		/**
		 * Devuelve si se terminó el nivel.
		 * @return TRUE = EndOfLevel, FALSE = CONTINUE
		 */
		inline void setEndOfLevel(bool eol) { _endOfLevel = eol; }

		/**
		 * Obtiene la factoría de movimientos.
		 */
		inline MovementsFactory & getMovementsFactory() { return _movementsFactory; }

		std::string getStatisticsLabels() const;
		std::string getStatisticsValues() const;
		std::string getFinalPointsLabel() const;
		std::string getFinalPointsValue() const;
		
		// -------

		// Enemigos comunes
		inline void increaseCommonEnemiesDestroyed(unsigned int c = 1) { _commonEnemiesDestroyed += c; }
		inline unsigned int getCommonEnemiesDestroyed() { return _commonEnemiesDestroyed; }

		// Balas totales e impactadas
		inline void increaseTotalBulletCounter(unsigned int c = 1) { _totalBulletCounter += c; }
		inline unsigned int getTotalBulletCounter() { return _totalBulletCounter; }

		inline void increaseImpactBulletCounter(unsigned int c = 1) { _impactBulletCounter += c; }
		inline unsigned int getImpactBulletCounter() { return _impactBulletCounter; }

		// Métodos de obtención de bonificación y porcentajes
		unsigned int getCommonEnemiesTotalBonus() { return (_commonEnemiesDestroyed * _commonEnemyBonus); }
		unsigned int getImpactBulletTotalBonus() { return (_impactBulletCounter * _bulletImpactBonus); }
		unsigned int getActualBonus();
		unsigned int getTotalBonus();
		float getAccuracyPercentage();
		unsigned int getAccuracyTotalBonus() { return (unsigned int) (getAccuracyPercentage()*100); }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static MissionManager * GetInstance() {
			return _instance;
		}
		
		/**
		 * Inicializa el gestor.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize();

		/**
		 * Finaliza el gestor.
		 */
		void release();

		void prepareUpdate(unsigned int lastInterval);

		/**
		 * Actualiza el estado del gestor.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		void update(unsigned int lastInterval);

		/**
		 * Función que activa el mapa actual.
		 * @return Devuelve true si la inicialización fue correcta.
		 */
		bool activateMap();

		/**
		 * Función que desactiva el mapa actual.
		 */
		void deactivateMap();

		/**
		 * Si hay un nivel cargado lo descarga y lo destruye.
		 */
		void unloadLevel();

		//...
		void startLevel();
		void endLevel();
		//...

		/*
		* Método para registrar los sonidos que se han de descargar tras finalizar la misión.
		* @param soundName Nombre del sonido a registrar.
		*/
		void RegisterUnLoadMissionSound(const std::string& soundName);

		/*
		* Método para descargar los sonidos que han sido cargados durante la misión.
		*/
		bool UnLoadMissionSounds();

		//...
		void tryAgainLevel();
		//...
		
		/*
		 * Método que activa la bifurcación.
		 */
		void takeBifurcation(Vector3 dir, float time);

		/*
		 * Método que devuelve el vector de movimiento del paso de la bifurcación
		 */
		Vector3 bifurcationStep(unsigned int lastInterval);

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Destructor del objeto.
		 */
		virtual ~MissionManager() {}
		
	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * La instancia del objeto.
		 */
		static MissionManager * _instance;

		/**
		 * Mapa donde se encuentran todas las entidades lógicas.
		 */
		Core::World * _world;

		/**
		 * Entidad del jugador.
		 */
		Core::Entity * _player;

		/**
		 * Entidad de la cámara.
		 */
		Core::Entity * _camera;

		/**
		 * Componente cámara de juego.
		 */
		Camera * _gameCamera;

		/**
		 * Tipo de cámara en uso.
		 */
		CameraType _cameraType;

		/**
		 * Centro de la acción.
		 */
		Vector3 _center;

		/**
		 * Distancia a la acción.
		 */
		float _distance;

		/**
		 * Velocidad la acción.
		 */
		float _speed;
		
		/**
		 * Destino de movimiento de la escena (en caso de bifurcación)
		 */
		Vector3 _bifurcationDestination;

		/**
		 * Dirección de movimiento de la escena (en caso de bifurcación)
		 */
		Vector3 _bifurcationDirection;

		/**
		 * Indica si estamos en una bifurcación
		 */
		bool _bifurcation;

		/*
		 * Tiempo total de bifurcación
		 */
		float _bifurcationTime;

		/*
		 * Tiempo de la bifurcación actual
		 */
		unsigned int _bifurcationActualTime;

		/**
		 * Clase GUI que se encarga de controlar el HUD.
		 */
		HUDController * _HUDController;

		/**
		 * Clase GUI que se encarga de controlar el HUD.
		 */
		bool _endOfLevel;

		/**
		* Factoría de movimientos (para que la use el componente de movimiento).
		*/
		MovementsFactory _movementsFactory;

		/**
		* Lista con los nombres de los sonidos que se han de descargar tras finalizar la misión.
		*/
		typedef std::list<std::string> TSoundList;
		TSoundList _soundsToUnload;

		/**
		 * Variables para el control de las puntuaciones de la partida.
		 */
		unsigned int _commonEnemiesDestroyed;
		unsigned int _commonEnemyBonus;
		
		unsigned int _totalBulletCounter;
		unsigned int _impactBulletCounter;
		unsigned int _bulletImpactBonus;


		/*//Estas variables definen los máximos y mínimos a tener en cuenta en las puntuaciones.
		int maxPoints;	//Puntos máximos que se pueden otorgar en el nivel.	
		float maxTimeBonus, minTimeBonus;	//Tiempos máximo y mínimo para puntuar por tardar en matar a un enemigo.
		float maxDamage; //Máximo daño que se puede sufrir para puntuar.
		int gunnedInArrowMax; //Máximo número de enemigosabatidos sin sufrir daños.

		//Estas variables se generan con la carga del .scene
		int totalEnemies;
		int totalSquads;
		int totalHumans;
		int totalPowerUps;

		//Vaiables para controlar qué va consiguiendo el jugador en el nivel
		int enemies;
		int enemyCombo;
		int enemyMaxCombo;
		int squadrons;
		int powerUps;
		float time;
		float damageRecieved;
		int humansRescued;	*/

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		//...
		//...

		/**
		 * Inicializa las variables de las bonificaciones.
		 */
		void initBonusVars();

		/**
		 * Registra los tipos de componentes que forman parte del juego.
		 * @return Devuelve true si se logra registrar todo correctamente.
		 */
		bool registerComponentTypes();

		/**
		 * Registra los tipos de movimientos predefinidos que forman parte del juego.
		 * @return Devuelve true si se logra registrar todo correctamente.
		 */
		bool registerMovementTypes();

		//...
		//...

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------
		
		/**
		 * Construye un nuevo objeto.
		 */
		MissionManager() : _world(0), _player(0), _camera(0), _gameCamera(0), _cameraType(SIDE), _HUDController(0) {}
	};
}

#endif
