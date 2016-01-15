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
#include <OgreRoot.h>

#include "Core/BaseManager.h"
#include "Core/SafeDelete.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/GUI/GUIManager.h"
#include "Core/Input/InputManager.h"
#include "Core/Resources/ResourcesManager.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Sequences/SequenceManager.h"
#include "Core/Sound/SoundManager.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#ifdef _DEBUG
	#define PLUGINS_CFG "plugins_d.cfg"
#else
	#define PLUGINS_CFG "plugins.cfg"
#endif

#define ENGINE_LOG "engine.log"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	BaseManager * BaseManager::_instance = new BaseManager();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	Ogre::Timer * BaseManager::getTimer() {
		assert(_root && "BaseManager::getTimer -> The Ogre root has not been created...");
		return _root ? _root->getTimer() : 0;
	}

	//--------------------------------------------------------------------------------------------------------

	bool BaseManager::isInfiniteFarPlaneSupported() const {
		Ogre::RenderSystem * renderSystem = _root->getRenderSystem();
		return renderSystem->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE);
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool BaseManager::initialize(const char * title, const char * logPath) {
		// Guardamos el título del juego.
		_title = title;

		// Obtenemos las instancias de los gestores del motor.
		_sequence = SequenceManager::GetInstance();
		_resources = ResourcesManager::GetInstance();
		_graphics = GraphicsManager::GetInstance();
		_gui = GUIManager::GetInstance();
		_input = InputManager::GetInstance();
		_sound = SoundManager::GetInstance();
		_scripting = ScriptingManager::GetInstance();
		//TODO: Completar la obtención de los gestores...
		//...

		// Inicializamos el gestor del log de la aplicación.
		Ogre::LogManager * killedByDeath = new Ogre::LogManager();
		_log = Ogre::LogManager::getSingleton().createLog(logPath ? logPath : ENGINE_LOG, true, true, false);

		// Inicializamos el gestor que Ogre tiene para la aplicación.
		_root = new Ogre::Root(PLUGINS_CFG);

		// Inicializamos el gestor de secuencias.
		_sequence->initialize();

		// Inicializamos el gestor de recursos.
		_resources->initialize();

		// Inicializamos el gestor del motor de scripting.
		if(!_scripting->initialize()) return false;

		// Inicializamos el gestor del motor gráfico.
		if(!_graphics->initialize()) return false;

		// Inicializamos los grupos registrados en el gestor de recursos.
		_resources->initialiseAllGroups();

		// Inicializamos el gestor del motor de entrada.
		if(!_input->initialize()) return false;

		// Inicializamos el gestor del motor de sonido.
		if(!_sound->initialize()) return false;

		// Inicializamos el gestor del motor de GUI.
		if(!_gui->initialize()) return false;

		//TODO: Completar el método...
		//...

		return true;
	}

	//--------------------------------------------------------------------------------------------------------

	void BaseManager::release() {
		//TODO: Completar el método...
		//...
		_gui->release();
		_sound->release();
		_input->release();
		_graphics->release();
		_scripting->release();
		_resources->release();
		_sequence->release();
		SafeDelete(_root);

		// Destruimos el gestor del log de la aplicación.
		Ogre::LogManager::getSingleton().destroyLog(_log);
		_log = 0;

		// Borramos los punteros a los gestores del motor.
		_sequence = 0;
		_resources = 0;
		_graphics = 0;
		_gui = 0;
		_input = 0;
		_sound = 0;
		_scripting = 0;
		//TODO: Completar el método...
		//...
	}
}
