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

#ifndef __CORE_GRAPHICSMANAGER_H__
#define __CORE_GRAPHICSMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Types/GraphicsTypes.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define DEFAULT_SCENE_NAME "DefaultScene"

//************************************************************************************************************
// Ogre
//************************************************************************************************************

namespace Ogre {
	class Root;
	class RenderWindow;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class Scene;
	class InputManager;
	class WindowEventListener;

	/**
	 * Esta clase representa al gestor del motor gráfico.
	 */
	class GraphicsManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el identificador de la ventana en Windows.
		 */
		unsigned int getWindowHandle();

		/**
		 * Obtiene la ventana de renderizado.
		 */
		inline Ogre::RenderWindow * getRenderWindow() { return _renderWindow; }

		/**
		 * Obtiene si la ventana está en modo pantalla completa.
		 */
		bool isFullScreen();

		/**
		 * Obtiene la escena actual.
		 */
		inline Scene * getCurrentScene() { return _currentScene; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static GraphicsManager * GetInstance() {
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

		/**
		 * Actualiza el estado del gestor.
		 * @param lastInterval El tiempo total en segundos del último intervalo entre frame y frame.
		 */
		void update(float lastInterval);

		/**
		 * Muestra la ventana.
		 */
		void showWindow();

		/**
		 * Esconde la ventana.
		 */
		void hideWindow();

		/**
		 * Maximiza la ventana.
		 */
		void maximizeWindow();

		/**
		 * Minimiza la ventana.
		 */
		void minimizeWindow();

		/**
		 * Restaura la ventana.
		 */
		void restoreWindow();

		/**
		 * Devuelve las dimensiones de la ventana.
		 * @param width Devuelve el ancho de la ventana en píxeles.
		 * @param height Devuelve el alto de la ventana en píxeles.
		 */
		void getWindowSize(unsigned int & width, unsigned int & height);

		/**
		 * Añade una escena en el gestor.
		 * @param name El nombre de la escena.
		 * @return Devuelve la escena creada y si falla algo da NULL.
		 * @remarks La eliminación del puntero a la escena creada es gestionada por la clase.
		 */
		Scene * createScene(const std::string & name);

		/**
		 * Busca una escena registrada en el gestor.
		 * @param name El nombre de la escena.
		 * @return Devuelve la escena si la encuentra y si no da NULL.
		 */
		Scene * findScene(const std::string & name);

		/**
		 * Elimina una escena registrada en el gestor.
		 * @param scene La escena.
		 */
		void removeScene(Scene * scene);

		/**
		 * Elimina una escena registrada en el gestor.
		 * @param name El nombre de la escena.
		 */
		void removeScene(const std::string & name);

		/**
		 * Cambia la escena actual.
		 * @param scene La escena.
		 */
		void changeCurrentScene(Scene * scene);

		/**
		 * Cambia la escena actual.
		 * @param name El nombre de la escena.
		 */
		void changeCurrentScene(const std::string & name);

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~GraphicsManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static GraphicsManager * _instance;

		/**
		 * El gestor Ogre de la aplicación.
		 */
		Ogre::Root * _root;

		/**
		 * La ventana de renderizado.
		 */
		Ogre::RenderWindow * _renderWindow;

		/**
		 * El capturador de los eventos de ventana. Su misión principal es controlar si
		 * se ha pulsado el botón que las ventanas tienen para cerrar el programa.
		 */
		WindowEventListener * _windowEventListener;

		/**
		 * La tabla de escenas registradas en el motor.
		 */
		ScenesTable _scenes;

		/**
		 * La escena actual (suponemos con esto que solo hay una escena activa a la vez).
		 */
		Scene * _currentScene;

		/**
		 * La escena por defecto para cuando no hay ninguna escena asignada.
		 */
		Scene * _defaultScene;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Carga la configuración del motor gráfico.
		 * @param force Flag con el que forzar la salida del cuadro de diálogo para configurar el motor.
		 * @return Devuelve true si se logra cargar la configuración del motor gráfico.
		 */
		bool loadEngineConfiguration(bool force = false);

		/**
		 * Inicializa el motor gráfico.
		 * @return Devuelve true si se logra inicializar el motor gráfico.
		 */
		bool initializeEngine();

		/**
		 * Actualiza las dimensiones de la ventana.
		 * @param width El ancho de la ventana en píxeles.
		 * @param height El alto de la ventana en píxeles.
		 */
		void updateWindowSize(unsigned int width, unsigned int height);

		/**
		 * Inicializa el sistema encargado de la gestión de las escenas.
		 * @return Devuelve true si se logra inicializar el sistema.
		 */
		bool initializeSceneSystem();

		/**
		 * Finaliza el sistema encargado de la gestión de las escenas.
		 */
		void releaseSceneSystem();

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		GraphicsManager() : _root(0), _renderWindow(0), _windowEventListener(0),
			_currentScene(0), _defaultScene(0) {}

		friend class Core::InputManager;
		friend class Core::WindowEventListener;
	};
}

#endif
