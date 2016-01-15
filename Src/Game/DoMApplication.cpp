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

#include "Game/DoMApplication.h"

#include "Core/Graphics/GraphicsManager.h"
#include "Core/GUI/GUIManager.h"
#include "External/Splash.h"

//************************************************************************************************************
// Constantes
//************************************************************************************************************

#define SPLASH_TEXTURE "media/Splash/splash.bmp"

//************************************************************************************************************
// Game
//************************************************************************************************************

namespace Game {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool DoMApplication::initialize() {
		// Mostramos una splash screen.
		CSplash splash(TEXT(SPLASH_TEXTURE), RGB(255, 0, 255));
		splash.ShowSplash();

		// Inicializamos la base del motor de juego.
		if (!GenericApplication::initialize(TITLE)) {
			return false;
		}

		// Minimizamos la ventana principal, dejando solo la splash screen.
		Core::GraphicsManager::GetInstance()->minimizeWindow();

		// Obtenemos el gestor de la interfaz gráfica de usuario.
		Core::GUIManager * guiManager = Core::GUIManager::GetInstance();

		// Cargamos las distintas plantillas o esquemas de fichero que usaremos en
		// nuestro GUI (automáticamente cargan los archivos looknfeel e imageset).
		guiManager->loadScheme("OgreTray.scheme");
		guiManager->loadScheme("MankindDefenders.scheme");

		// Cargamos los archivos con las fuentes que usaremos.
		guiManager->loadFont("DejaVuSans-10.font");
		guiManager->loadFont("FairChar-30.font");

		// Establecemos cual será el puntero del ratón.
		guiManager->setDefaultMouseCursor("OgreTrayImages", "MouseArrow");

		// Cerramos la splash screen.
		splash.CloseSplash();

		// Restaurando la ventana principal.
		Core::GraphicsManager::GetInstance()->restoreWindow();

		// Y finalmente tratamos de inicializar los estados.
		return initializeStates();
	}

	//--------------------------------------------------------------------------------------------------------

	void DoMApplication::release() {
		// Borramos la información relacionada con los estados.
		clearTable();

		// Liberamos el resto de la aplicación.
		GenericApplication::release();
	}

	//********************************************************************************************************
	// Constructores y destructor
	//********************************************************************************************************

	DoMApplication::DoMApplication() : GenericApplication() {}

	//--------------------------------------------------------------------------------------------------------

	DoMApplication::~DoMApplication() {}
}
