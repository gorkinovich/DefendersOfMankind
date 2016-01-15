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

#include <assert.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include "Core/SafeDelete.h"
#include "Core/BaseManager.h"
#include "Core/GenericApplication.h"
#include "Core/Resources/ResourcesManager.h"
#include "Core/Input/Mouse.h"
#include "Core/Graphics/Scene.h"
#include "Core/Graphics/GraphicsManager.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

/**
 * Si se define la siguiente directiva, en modo ventana se seguirá renderizando aunque
 * la ventana no esté en primer plano y siempre que esté visible de algún modo.
 */
#define RENDER_IN_BACKGROUND

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// WindowEventListener
	//********************************************************************************************************

	/**
	 * Esta clase representa al encargado de recibir los eventos de la ventana.
	 */
	class WindowEventListener : public Ogre::WindowEventListener {
	public:
		/**
		 * Capturador del evento que se produce al intentar cerrar la ventana
		 * (al pulsar la 'x' de la ventana o pulsar Alt-F4).
		 * @param renderWindow La ventana sobre la que se produce el evento.
		 * @return Siempre falso para controlar nosotros el cierre de la aplicación.
		 */
		virtual bool windowClosing(Ogre::RenderWindow * renderWindow) {
			GenericApplication::GetInstance()->exitRequest();
			return false;
		}

		/**
		 * Capturador del evento que se produce al redimensionar la ventana.
		 * @param renderWindow La ventana sobre la que se produce el evento.
		 */
		virtual void windowResized(Ogre::RenderWindow * renderWindow) {
		}

		/**
		 * Capturador del evento que se produce al ganar o perder el foco de la ventana.
		 * @param renderWindow La ventana sobre la que se produce el evento.
		 */
		virtual void windowFocusChange(Ogre::RenderWindow * renderWindow) {
		}
	};

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	GraphicsManager * GraphicsManager::_instance = new GraphicsManager();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	unsigned int GraphicsManager::getWindowHandle() {
		assert(_renderWindow && "GraphicsManager::getWindowHandle -> The render window has not been created...");
		if(_renderWindow) {
			unsigned int handle;
			_renderWindow->getCustomAttribute("WINDOW", &handle);
			return handle;
		}
		return 0;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicsManager::isFullScreen() {
		return _renderWindow ? _renderWindow->isFullScreen() : false;
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GraphicsManager::initialize() {
		// Obtenemos el gestor Ogre de la aplicación.
		_root = BaseManager::GetInstance()->getOgreRoot();

		// Tratamos de cargar la configuración del motor.
		if(!loadEngineConfiguration()) return false;

		// De tener una configuración inicializamos el motor gráfico.
		if(!initializeEngine()) {
			// Puede darse la situación de haber cargado una configuración previa que no corresponde con
			// el hardware actual, con lo que tratamos de cargar la configuración del motor nuevamente.
			if(!loadEngineConfiguration(true)) return false;

			// Nuevamente tratamos de inicializar el motor gráfico y si no se puede se desiste.
			if(!initializeEngine()) return false;
		}

		// Tratamos de inicializar el sistema encargado de la gestión de las escenas.
		if(!initializeSceneSystem()) return false;

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::release() {
		// Finalizamos el sistema encargado de la gestión de las escenas.
		releaseSceneSystem();
		// Eliminamos las vistas creadas por el motor de Ogre.
		if(_renderWindow) {
			_renderWindow->removeAllViewports();
			_root->detachRenderTarget(_renderWindow);
		}
		// Borramos los objetos de Ogre.
		SafeDelete(_renderWindow);
		SafeDelete(_windowEventListener);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::update(float lastInterval) {
		if(_currentScene != _defaultScene) {
			_currentScene->update(lastInterval);
		}
		if(_root) {
			// Actualizamos todas las ventanas de reenderizado.
			Ogre::WindowEventUtilities::messagePump();
			// Reenderizamos un frame.
			_root->renderOneFrame(lastInterval);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::showWindow() {
		ShowWindow((HWND)getWindowHandle(), SW_SHOW);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::hideWindow() {
		ShowWindow((HWND)getWindowHandle(), SW_HIDE);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::maximizeWindow() {
		ShowWindow((HWND)getWindowHandle(), SW_MAXIMIZE);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::minimizeWindow() {
		ShowWindow((HWND)getWindowHandle(), SW_MINIMIZE);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::restoreWindow() {
		ShowWindow((HWND)getWindowHandle(), SW_RESTORE);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::getWindowSize(unsigned int & width, unsigned int & height) {
		assert(_renderWindow && "GraphicsManager::getWindowSize -> The render window has not been created...");
		if(_renderWindow) {
			width = _renderWindow->getWidth();
			height = _renderWindow->getHeight();
		} else {
			width = height = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	Scene * GraphicsManager::createScene(const std::string & name) {
		// Nos aseguramos de que no exista ya una escena con este nombre.
		assert(!findScene(name) && "GraphicsManager::createScene -> Can't create two scene with the same name...");
		// Entonces creamos la escena, para luego añadirla y devolver el puntero.
		Scene * scene = new Scene(name);
		_scenes[name] = scene;
		return scene;
	}

	//--------------------------------------------------------------------------------------------------------

	Scene * GraphicsManager::findScene(const std::string & name) {
		ScenesTable::iterator victim = _scenes.find(name);
		return victim != _scenes.end() ? victim->second : 0;
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::removeScene(Scene * scene) {
		if(scene) {
			if(_currentScene == scene) {
				_currentScene = 0;
			}
			_scenes.erase(scene->getName());
			delete scene;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::removeScene(const std::string & name) {
		Scene * victim = findScene(name);
		removeScene(victim);
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::changeCurrentScene(Scene * scene) {
		// En caso de que hubiese una escena activa la desactivamos.
		if(_currentScene) {
			_currentScene->deactivate();
		}
		if(scene) {
			// Nos aseguramos de que la escena pertenezca al servidor, aunque nadie más puede crear escenas.
			assert(findScene(scene->getName()) && "GraphicsManager::changeCurrentScene -> The scene doesn't exists...");
			_currentScene = scene;
		} else {
			// Si se añade NULL ponemos la escena por defecto.
			_currentScene = _defaultScene;
		}
		_currentScene->activate();
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::changeCurrentScene(const std::string & name) {
		// En caso de que hubiese una escena activa la desactivamos.
		if(_currentScene) {
			_currentScene->deactivate();
		}
		// Nos aseguramos de que exista una escena con este nombre.
		_currentScene = findScene(name);
		assert(_currentScene && "GraphicsManager::changeCurrentScene -> The scene doesn't exists...");
		_currentScene->activate();
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicsManager::loadEngineConfiguration(bool force) {
		// Se comprueba si existe ya una configuración guardada en ogre.cfg y de existir se carga.
		if(force || !_root->restoreConfig()) {
			// Si no existe el archivo de configuración, se lanza el cuadro de diálogo de configuración.
			if(!_root->showConfigDialog()) {
				// De no poder obtener una configuración, se avisa al juego para que finalice.
				return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicsManager::initializeEngine() {
		try {
			// Inicializamos el sistema de renderizado, creando una ventana por defecto. Con el
			// primer parametro a false tendríamos que crear la ventana manualmente con el método
			// Root::createRenderWindow, pasándole toda la información de la configuración elegida.
			_renderWindow = _root->initialise(true, BaseManager::GetInstance()->getTitle());

#if defined RENDER_IN_BACKGROUND
			// Le indicamos a Ogre que la ventana siga renderizando en caso de perder el foco.
			_renderWindow->setDeactivateOnFocusChange(false);
#endif

			// Actualizamos la resolución de la ventana de renderizado.
			_renderWindow->setFullscreen(_renderWindow->isFullScreen(), _renderWindow->getWidth(),
				_renderWindow->getHeight());
			
			// Añadimos a Ogre el listener que gestiona los evento que genera la ventana creada.
			_windowEventListener = new WindowEventListener();
			Ogre::WindowEventUtilities::addWindowEventListener(_renderWindow, _windowEventListener);
		} catch(...) {
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::updateWindowSize(unsigned int width, unsigned int height) {
		// Actualizamos la resolución de la ventana de renderizado.
		_renderWindow->setFullscreen(_renderWindow->isFullScreen(), width, height);
		// Comprobamos si hay un ratón conectado al sistema.
		Mouse * mouse = Mouse::GetInstance();
		if(mouse->isConnected()) {
			// Y actualizamos los límites del ratón en su estado interno.
			mouse->setWindowSize(width, height);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool GraphicsManager::initializeSceneSystem() {
		// Creamos la escena dummy para cuando no hay ninguna activa.
		_defaultScene = createScene(DEFAULT_SCENE_NAME);
		// Por defecto la escena activa es la dummy.
		changeCurrentScene(_defaultScene);
		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GraphicsManager::releaseSceneSystem() {
		if(_currentScene) {
			_currentScene->deactivate();
			_currentScene = 0;
		}
		while(!_scenes.empty()) {
			removeScene(_scenes.begin()->second);
		}
	}
}
