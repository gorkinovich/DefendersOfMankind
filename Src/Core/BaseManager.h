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

#ifndef __CORE_BASEMANAGER_H__
#define __CORE_BASEMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class Log;
	class Root;
	class Timer;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class SequenceManager;
	class ResourcesManager;
	class GraphicsManager;
	class GUIManager;
	class InputManager;
	class SoundManager;
	class ScriptingManager;

	/**
	 * Esta clase representa al gestor base del motor.
	 */
	class BaseManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el gestor del log de la aplicación.
		 */
		inline Ogre::Log * getOgreLog() { return _log; }

		/**
		 * Obtiene el gestor Ogre de la aplicación.
		 */
		inline Ogre::Root * getOgreRoot() { return _root; }

		/**
		 * Obtiene el controlador que tiene Ogre para obtener el tiempo.
		 */
		Ogre::Timer * getTimer();

		/**
		 * Obtiene el título del juego.
		 */
		inline const char * getTitle() { return _title.c_str(); }

		/**
		 * Obtiene el gestor de secuencias del motor.
		 */
		inline SequenceManager * getSequence() { return _sequence; }

		/**
		 * Obtiene el gestor de recursos del motor.
		 */
		inline ResourcesManager * getResources() { return _resources; }

		/**
		 * Obtiene el gestor del motor gráfico.
		 */
		inline GraphicsManager * getGraphics() { return _graphics; }

		/**
		 * Obtiene el gestor de la GUI.
		 */
		inline GUIManager * getGUI() { return _gui; }

		/**
		 * Obtiene el gestor del motor de entrada.
		 */
		inline InputManager * getInput() { return _input; }

		/**
		 * Obtiene el gestor del motor de sonido.
		 */
		inline SoundManager * getSound() { return _sound; }

		/**
		 * Obtiene el gestor del motor de scripting.
		 */
		inline ScriptingManager * getScripting() { return _scripting; }

		/**
		 * Obtiene si la aplicación soporta el plano lejano infinito.
		 */
		bool isInfiniteFarPlaneSupported() const;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static BaseManager * GetInstance() {
			return _instance;
		}

		/**
		 * Inicializa el gestor.
		 * @param title El título del juego.
		 * @param logPath La ruta del log del motor.
		 * @return Devuelve true si se logra inicializar el manager.
		 */
		bool initialize(const char * title, const char * logPath = 0);

		/**
		 * Finaliza el gestor.
		 */
		void release();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~BaseManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static BaseManager * _instance;

		/**
		 * El gestor del log de la aplicación.
		 */
		Ogre::Log * _log;

		/**
		 * El gestor Ogre de la aplicación.
		 */
		Ogre::Root * _root;

		/**
		 * El título del juego.
		 */
		std::string _title;

		/**
		 * El gestor de secuencias del motor.
		 */
		SequenceManager * _sequence;

		/**
		 * El gestor de recursos del motor.
		 */
		ResourcesManager * _resources;

		/**
		 * El gestor del motor gráfico.
		 */
		GraphicsManager * _graphics;

		/**
		 * El gestor de la GUI.
		 */
		GUIManager * _gui;

		/**
		 * El gestor del motor de entrada.
		 */
		InputManager * _input;

		/**
		 * El gestor del motor de sonido.
		 */
		SoundManager * _sound;

		/**
		 * El gestor del motor de scripting.
		 */
		ScriptingManager * _scripting;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		BaseManager() : _log(0), _root(0), _sequence(0), _resources(0), _graphics(0), _gui(0),
		_input(0), _sound(0), _scripting(0) {}
	};
}

#endif
