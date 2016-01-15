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
#include <OgreRenderWindow.h>

#include <CEGUISystem.h>
#include <CEGUIScheme.h>
#include <CEGUIFont.h>
#include <CEGUIWindow.h>
#include <CEGUIImageset.h>
#include <CEGUIMouseCursor.h>
#include <CEGUIFontManager.h>
#include <CEGUISchemeManager.h>
#include <CEGUIWindowManager.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIDefaultResourceProvider.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <falagard/CEGUIFalWidgetLookManager.h>
#include <OISKeyboard.h>

#include "Core/SafeDelete.h"
#include "Core/Input/InputListenersManager.h"
#include "Core/Input/Keyboard.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/GUI/GUIManager.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Keyboard char listener
	//********************************************************************************************************

	class KeyboardCharListener : public OIS::KeyListener {
	public:
		/**
		 * El delegado que captura el evento de tecla pulsada.
		 */
		bool keyPressed(const OIS::KeyEvent & e) {
			_system->injectChar(e.text);
			return true;
		}

		/**
		 * El delegado que captura el evento de tecla liberada.
		 */
		bool keyReleased(const OIS::KeyEvent & e) {
			return true;
		}

		/**
		 * Construye un nuevo objeto.
		 */
		KeyboardCharListener(CEGUI::System * system) : _system(system) {}

		/**
		 * Destructor del objeto.
		 */
		virtual ~KeyboardCharListener() {}

	private:
		/**
		 * El gestor CEGUI de la interfaz gráfica.
		 */
		CEGUI::System * _system;
	};

	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	GUIManager * GUIManager::_instance = new GUIManager();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	CEGUI::Scheme & GUIManager::getScheme(const std::string & schemeName) {
		return CEGUI::SchemeManager::getSingleton().get(schemeName);
	}

	//--------------------------------------------------------------------------------------------------------

	CEGUI::Font & GUIManager::getFont(const std::string & fontName) {
		return CEGUI::FontManager::getSingleton().get(fontName);
	}

	//--------------------------------------------------------------------------------------------------------

	CEGUI::Imageset & GUIManager::getImageset(const std::string & imagesetName) {
		return CEGUI::ImagesetManager::getSingleton().get(imagesetName);
	}

	//--------------------------------------------------------------------------------------------------------

	CEGUI::Window * GUIManager::getWindow(const std::string & windowName) {
		return CEGUI::WindowManager::getSingleton().getWindow(windowName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::containsWindow(const std::string & windowName) {
		return CEGUI::WindowManager::getSingleton().isWindowPresent(windowName);
	}

	//--------------------------------------------------------------------------------------------------------

	CEGUI::Window * GUIManager::getRootWindow() {
		return _system->getGUISheet();
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::setRootWindow(CEGUI::Window * value) {
		_system->setGUISheet(value);
	}

	//--------------------------------------------------------------------------------------------------------

	CEGUI::Font * GUIManager::getDefaultFont() {
		return _system->getDefaultFont();
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::setDefaultFont(const std::string & fontName) {
		_system->setDefaultFont(fontName);
	}

	//--------------------------------------------------------------------------------------------------------

	const CEGUI::Image * GUIManager::getDefaultMouseCursor() {
		return _system->getDefaultMouseCursor();
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::setDefaultMouseCursor(const std::string & imageSet, const std::string & imageName) {
		_system->setDefaultMouseCursor(imageSet, imageName);
	}

	//--------------------------------------------------------------------------------------------------------

	float GUIManager::getMouseMoveScaling() {
		return _system->getMouseMoveScaling();
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::setMouseMoveScaling(float value) {
		_system->setMouseMoveScaling(value);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool GUIManager::initialize() {
		// Primero creamos e inicializamos el sistema gestor CEGUI para controlar la GUI.
		Ogre::RenderWindow * renderWindow = Core::GraphicsManager::GetInstance()->getRenderWindow();
		CEGUI::OgreRenderer & renderer = CEGUI::OgreRenderer::create(*renderWindow);
		CEGUI::System::create(renderer);

		_system = CEGUI::System::getSingletonPtr();
		if(!_system) return false;

		// Segundo, inicializamos el gestor de rutas para los recursos de la interfaz gráfica.
		CEGUI::DefaultResourceProvider * rp = static_cast<CEGUI::DefaultResourceProvider *>(_system->getResourceProvider());

		rp->setResourceGroupDirectory("fonts", "media/gui/fonts");
		rp->setResourceGroupDirectory("imagesets", "media/gui/imagesets");
		rp->setResourceGroupDirectory("layouts", "media/gui/layouts");
		rp->setResourceGroupDirectory("looknfeels", "media/gui/looknfeel");
		rp->setResourceGroupDirectory("schemes", "media/gui/schemes");

		// Tercero, definiremos los grupos de recursos que van a ser usados.
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Imageset::setDefaultResourceGroup("imagesets");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");

		// Y por último, añadimos los listeners para procesar los eventos.
		InputListenersManager * ilm = InputListenersManager::GetInstance();
		ilm->addKeyPressedDelegate(this, CreateKeyboardDelegate(&GUIManager::keyPressed, this));
		ilm->addKeyReleasedDelegate(this, CreateKeyboardDelegate(&GUIManager::keyReleased, this));
		ilm->addMouseAxisDelegate(this, CreateMouseDelegate(&GUIManager::mouseAxis, this));
		ilm->addMousePressedDelegate(this, CreateMouseDelegate(&GUIManager::mousePressed, this));
		ilm->addMouseReleasedDelegate(this, CreateMouseDelegate(&GUIManager::mouseReleased, this));
		ilm->addGamePadAxisDelegate(this, CreateGamePadDelegate(&GUIManager::gamePadAxis, this));
		ilm->addGamePadPressedDelegate(this, CreateGamePadDelegate(&GUIManager::gamePadPressed, this));
		ilm->addGamePadReleasedDelegate(this, CreateGamePadDelegate(&GUIManager::gamePadReleased, this));

		// Ponemos un listener para poder capturar la entrada de texto de forma fácil.
		Keyboard::GetInstance()->getOISKeyboard()->setEventCallback(new KeyboardCharListener(_system));

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::release() {
		// Borramos los listeners para procesar los eventos.
		InputListenersManager * ilm = InputListenersManager::GetInstance();
		ilm->removeKeyPressedDelegate(this);
		ilm->removeKeyReleasedDelegate(this);
		ilm->removeMouseAxisDelegate(this);
		ilm->removeMousePressedDelegate(this);
		ilm->removeMouseReleasedDelegate(this);
		ilm->removeGamePadAxisDelegate(this);
		ilm->removeGamePadPressedDelegate(this);
		ilm->removeGamePadReleasedDelegate(this);

		// Borramos el listener que captura la entrada de texto.
		OIS::KeyListener * victim = Keyboard::GetInstance()->getOISKeyboard()->getEventCallback();
		SafeDelete(victim);

		// Destruimos el gestor CEGUI de la interfaz gráfica.
		if(_system) {
			CEGUI::System::destroy();
			_system = 0;
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::update() {
		_system->renderGUI();
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::showMouseCursor() {
		CEGUI::MouseCursor::getSingleton().show();
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::hideMouseCursor() {
		CEGUI::MouseCursor::getSingleton().hide();
	}

	//--------------------------------------------------------------------------------------------------------

	CEGUI::Window * GUIManager::createWindow(const std::string & objectType, const std::string & windowName) {
		return CEGUI::WindowManager::getSingleton().createWindow(objectType, windowName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::loadWindow(const std::string & fileName) {
		CEGUI::WindowManager::getSingleton().loadWindowLayout(fileName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::unloadWindow(const std::string & windowName) {
		CEGUI::WindowManager::getSingleton().destroyWindow(windowName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::isLoadedWindow(const std::string & windowName) {
		return CEGUI::WindowManager::getSingleton().isWindowPresent(windowName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::loadScheme(const std::string & fileName) {
		CEGUI::SchemeManager::getSingleton().create(fileName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::unloadScheme(const std::string & schemeName) {
		CEGUI::SchemeManager::getSingleton().destroy(schemeName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::isLoadedScheme(const std::string & schemeName) {
		return CEGUI::SchemeManager::getSingleton().isDefined(schemeName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::loadFont(const std::string & fileName) {
		CEGUI::FontManager::getSingleton().create(fileName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::unloadFont(const std::string & fontName) {
		CEGUI::FontManager::getSingleton().destroy(fontName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::isLoadedFont(const std::string & fontName) {
		return CEGUI::FontManager::getSingleton().isDefined(fontName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::loadImageset(const std::string & fileName) {
		CEGUI::ImagesetManager::getSingleton().create(fileName);
	}

	//--------------------------------------------------------------------------------------------------------

	void GUIManager::unloadImageset(const std::string & imagesetName) {
		CEGUI::ImagesetManager::getSingleton().destroy(imagesetName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::isLoadedImageset(const std::string & imagesetName) {
		return CEGUI::ImagesetManager::getSingleton().isDefined(imagesetName);
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::keyPressed(KeyCode key) {
		_system->injectKeyDown(key);
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::keyReleased(KeyCode key) {
		_system->injectKeyUp(key);
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::mouseAxis(const MouseState & state) {
		_system->injectMouseMove((float)state.x, (float)state.y);
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::mousePressed(const MouseState & state) {
		if(state.left) _system->injectMouseButtonDown(CEGUI::LeftButton);
		if(state.right) _system->injectMouseButtonDown(CEGUI::RightButton);
		if(state.middle) _system->injectMouseButtonDown(CEGUI::MiddleButton);
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::mouseReleased(const MouseState & state) {
		if(!state.left) _system->injectMouseButtonUp(CEGUI::LeftButton);
		if(!state.right) _system->injectMouseButtonUp(CEGUI::RightButton);
		if(!state.middle) _system->injectMouseButtonUp(CEGUI::MiddleButton);
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::gamePadAxis(const GamePadState & state, unsigned short player) {
		//TODO: Completar el método...
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::gamePadPressed(const GamePadState & state, unsigned short player) {
		//TODO: Completar el método...
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool GUIManager::gamePadReleased(const GamePadState & state, unsigned short player) {
		//TODO: Completar el método...
		return false;
	}
}
