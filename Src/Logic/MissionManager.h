//************************************************************************************************************
// Defenders of Mankind: A 3D space shoot'em up game.
// Copyright (C) 2011  David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
// Grupo 03: David Entrena, David Rodr�guez, Gorka Su�rez, Roberto Jim�nez
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
	 * Este tipo representa una factor�a de movimientos.
	 */
	typedef Core::SimpleFactory<IMovement> MovementsFactory;

	/**
	 * Esta clase representa al gestor de la misi�n del juego.
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
		 * Obtiene el mapa l�gico del juego.
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
		 * Obtiene la entidad de la c�mara.
		 */
		inline Core::Entity * getCamera() { return _camera; }

		/**
		 * Modifica la entidad de la c�mara.
		 */
		inline void setCamera(Core::Entity * value) { _camera = value; }

		/**
		 * Obtiene la entidad de la c�mara.
		 */
		inline Camera * getGameCamera() { return _gameCamera; }

		/**
		 * Modifica la entidad de la c�mara.
		 */
		inline void setGameCamera(Camera * value) { _gameCamera = value; }

		/**
		 * Obtiene el tipo de c�mara actual.
		 */
		inline CameraType getCameraType() { return _cameraType; }

		/**
		 * Modifica el tipo de c�mara actual.
		 * @remark Este valor es informativo, el aut�ntico est� en la entidad c�mara
		 *         que se encargar� de actualizarlo.
		 */
		inline void setCameraType(CameraType value) { _cameraType = value; }

		/**
		 * Obtiene el centro de la acci�n.
		 */
		inline Vector3 getCenter() const { return _center; }

		/**
		 * Modifica el centro de la acci�n.
		 */
		inline void setCenter(const Vector3 & value) { _center = value; }

		/**
		 * Obtiene la distancia de la acci�n.
		 */
		inline float getDistance() const { return _distance; }

		/**
		 * Modifica la velocidad de la acci�n.
		 */
		inline void setSpeed(const float & value) { _speed = value; }

		/**
		 * Obtiene la velocidad de la acci�n.
		 */
		inline float getSpeed() const { return _speed; }

		/**
		 * Modifica la distancia de la acci�n.
		 */
		inline void setDistance(const float & value) { _distance = value; }

		/**
		 * Obtiene si estamos en una bifurcaci�n.
		 */
		inline float getBifurcation() const { return _bifurcation; }

		/**
		 * Obtiene la direcci�n de bifurcaci�n.
		 */
		inline Vector3 getBifurcationDirection() const { return _bifurcationDirection; }

		/**
		 * Devuelve la instancia de la clase GUI que se encarga de manejar el HUD.
		 * @return Instancia de la clase GUI que controla el HUD.
		 */
		inline HUDController * getHUDController() { return _HUDController; }

		/**
		 * Devuelve si se termin� el nivel.
		 * @return TRUE = EndOfLevel, FALSE = CONTINUE
		 */
		inline bool getEndOfLevel() { return _endOfLevel; }

		/**
		 * Devuelve si se termin� el nivel.
		 * @return TRUE = EndOfLevel, FALSE = CONTINUE
		 */
		inline void setEndOfLevel(bool eol) { _endOfLevel = eol; }

		/**
		 * Obtiene la factor�a de movimientos.
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

		// M�todos de obtenci�n de bonificaci�n y porcentajes
		unsigned int getCommonEnemiesTotalBonus() { return (_commonEnemiesDestroyed * _commonEnemyBonus); }
		unsigned int getImpactBulletTotalBonus() { return (_impactBulletCounter * _bulletImpactBonus); }
		unsigned int getActualBonus();
		unsigned int getTotalBonus();
		float getAccuracyPercentage();
		unsigned int getAccuracyTotalBonus() { return (unsigned int) (getAccuracyPercentage()*100); }

		//----------------------------------------------------------------------------------------------------
		// M�todos
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
		 * @param lastInterval El tiempo total del �ltimo intervalo entre frame y frame.
		 */
		void update(unsigned int lastInterval);

		/**
		 * Funci�n que activa el mapa actual.
		 * @return Devuelve true si la inicializaci�n fue correcta.
		 */
		bool activateMap();

		/**
		 * Funci�n que desactiva el mapa actual.
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
		* M�todo para registrar los sonidos que se han de descargar tras finalizar la misi�n.
		* @param soundName Nombre del sonido a registrar.
		*/
		void RegisterUnLoadMissionSound(const std::string& soundName);

		/*
		* M�todo para descargar los sonidos que han sido cargados durante la misi�n.
		*/
		bool UnLoadMissionSounds();

		//...
		void tryAgainLevel();
		//...
		
		/*
		 * M�todo que activa la bifurcaci�n.
		 */
		void takeBifurcation(Vector3 dir, float time);

		/*
		 * M�todo que devuelve el vector de movimiento del paso de la bifurcaci�n
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
		 * Mapa donde se encuentran todas las entidades l�gicas.
		 */
		Core::World * _world;

		/**
		 * Entidad del jugador.
		 */
		Core::Entity * _player;

		/**
		 * Entidad de la c�mara.
		 */
		Core::Entity * _camera;

		/**
		 * Componente c�mara de juego.
		 */
		Camera * _gameCamera;

		/**
		 * Tipo de c�mara en uso.
		 */
		CameraType _cameraType;

		/**
		 * Centro de la acci�n.
		 */
		Vector3 _center;

		/**
		 * Distancia a la acci�n.
		 */
		float _distance;

		/**
		 * Velocidad la acci�n.
		 */
		float _speed;
		
		/**
		 * Destino de movimiento de la escena (en caso de bifurcaci�n)
		 */
		Vector3 _bifurcationDestination;

		/**
		 * Direcci�n de movimiento de la escena (en caso de bifurcaci�n)
		 */
		Vector3 _bifurcationDirection;

		/**
		 * Indica si estamos en una bifurcaci�n
		 */
		bool _bifurcation;

		/*
		 * Tiempo total de bifurcaci�n
		 */
		float _bifurcationTime;

		/*
		 * Tiempo de la bifurcaci�n actual
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
		* Factor�a de movimientos (para que la use el componente de movimiento).
		*/
		MovementsFactory _movementsFactory;

		/**
		* Lista con los nombres de los sonidos que se han de descargar tras finalizar la misi�n.
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


		/*//Estas variables definen los m�ximos y m�nimos a tener en cuenta en las puntuaciones.
		int maxPoints;	//Puntos m�ximos que se pueden otorgar en el nivel.	
		float maxTimeBonus, minTimeBonus;	//Tiempos m�ximo y m�nimo para puntuar por tardar en matar a un enemigo.
		float maxDamage; //M�ximo da�o que se puede sufrir para puntuar.
		int gunnedInArrowMax; //M�ximo n�mero de enemigosabatidos sin sufrir da�os.

		//Estas variables se generan con la carga del .scene
		int totalEnemies;
		int totalSquads;
		int totalHumans;
		int totalPowerUps;

		//Vaiables para controlar qu� va consiguiendo el jugador en el nivel
		int enemies;
		int enemyCombo;
		int enemyMaxCombo;
		int squadrons;
		int powerUps;
		float time;
		float damageRecieved;
		int humansRescued;	*/

		//----------------------------------------------------------------------------------------------------
		// M�todos
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
