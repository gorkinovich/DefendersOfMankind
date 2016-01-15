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

#ifndef __CORE_GUIMANAGER_H__
#define __CORE_GUIMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

#include "Core/Input/Keys.h"
#include "Core/Input/MouseState.h"
#include "Core/Input/JoystickState.h"
#include "Core/Input/GamePadState.h"

//************************************************************************************************************
// CEGUI
//************************************************************************************************************

namespace CEGUI {
	class System;
	class Scheme;
	class Font;
	class Window;
	class Image;
	class Imageset;
}

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa al gestor de la interfaz gráfica de usuario.
	 */
	class GUIManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el gestor CEGUI de la interfaz gráfica.
		 */
		inline CEGUI::System * getCEGUISystem() const { return _system; }

		/**
		 * Obtiene un esquema de la interfaz gráfica.
		 * @remark Si no existe lanza una CEGUI::UnknownObjectException.
		 */
		CEGUI::Scheme & getScheme(const std::string & schemeName);

		/**
		 * Obtiene una fuente de la interfaz gráfica.
		 * @remark Si no existe lanza una CEGUI::UnknownObjectException.
		 */
		CEGUI::Font & getFont(const std::string & fontName);

		/**
		 * Obtiene un conjunto de imagenes de la interfaz gráfica.
		 * @remark Si no existe lanza una CEGUI::UnknownObjectException.
		 */
		CEGUI::Imageset & getImageset(const std::string & imagesetName);

		/**
		 * Obtiene un objeto de la interfaz gráfica.
		 */
		CEGUI::Window * getWindow(const std::string & windowName);

		/**
		 * Obtiene un objeto de la interfaz gráfica.
		 */
		template<class T>
		T * getWindowAs(const std::string & windowName) {
			return dynamic_cast<T *>(getWindow(windowName));
		}

		/**
		 * Obtiene si existe un objeto de la interfaz gráfica.
		 */
		bool containsWindow(const std::string & windowName);

		/**
		 * Obtiene el objeto raíz de la interfaz gráfica.
		 */
		CEGUI::Window * getRootWindow();

		/**
		 * Modifica el objeto raíz de la interfaz gráfica.
		 */
		void setRootWindow(CEGUI::Window * value);

		/**
		 * Obtiene la fuente por defecto.
		 */
		CEGUI::Font * getDefaultFont();

		/**
		 * Modifica la fuente por defecto.
		 */
		void setDefaultFont(const std::string & fontName);

		/**
		 * Obtiene el cursor del ratón por defecto.
		 */
		const CEGUI::Image * getDefaultMouseCursor();

		/**
		 * Modifica el cursor del ratón por defecto.
		 */
		void setDefaultMouseCursor(const std::string & imageSet, const std::string & imageName);

		/**
		 * Obtiene el factor de escalado para el movimiento del cursor del ratón.
		 */
		float getMouseMoveScaling();

		/**
		 * Modifica el factor de escalado para el movimiento del cursor del ratón.
		 */
		void setMouseMoveScaling(float value);

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static GUIManager * GetInstance() {
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
		 * @remark Algunos motores no necesitan llamar a este método, como por ejemplo Ogre.
		 */
		void update();

		/**
		 * Muestra el cursor del ratón de la interfaz gráfica.
		 */
		void showMouseCursor();

		/**
		 * Oculta el cursor del ratón de la interfaz gráfica.
		 */
		void hideMouseCursor();

		/**
		 * Crea un objeto para la interfaz gráfica.
		 * @param objectType El tipo de objeto a crear.
		 * @param windowName El nombre del objeto.
		 * @return El objeto nuevo creado.
		 */
		CEGUI::Window * createWindow(const std::string & objectType, const std::string & windowName);

		/**
		 * Carga un objeto para la interfaz gráfica.
		 * @param fileName El nombre del fichero con el objeto.
		 */
		void loadWindow(const std::string & fileName);

		/**
		 * Descarga un objeto de la interfaz gráfica.
		 * @param windowName El nombre del objeto.
		 */
		void unloadWindow(const std::string & windowName);

		/**
		 * Comprueba si un objeto está cargado o no.
		 * @param windowName El nombre del objeto.
		 * @return Devuelve si el objeto está cargado o no.
		 */
		bool isLoadedWindow(const std::string & windowName);

		/**
		 * Carga un esquema para la interfaz gráfica.
		 * @param fileName El nombre del fichero con el esquema.
		 */
		void loadScheme(const std::string & fileName);

		/**
		 * Descarga un esquema de la interfaz gráfica.
		 * @param schemeName El nombre del esquema.
		 */
		void unloadScheme(const std::string & schemeName);

		/**
		 * Comprueba si un esquema está cargado o no.
		 * @param schemeName El nombre del esquema.
		 * @return Devuelve si el esquema está cargado o no.
		 */
		bool isLoadedScheme(const std::string & schemeName);

		/**
		 * Carga una fuente para la interfaz gráfica.
		 * @param fileName El nombre del fichero con la fuente.
		 */
		void loadFont(const std::string & fileName);

		/**
		 * Descarga una fuente de la interfaz gráfica.
		 * @param fontName El nombre de la fuente.
		 */
		void unloadFont(const std::string & fontName);

		/**
		 * Comprueba si una fuente está cargada o no.
		 * @param fontName El nombre de la fuente.
		 * @return Devuelve si la fuente está cargada o no.
		 */
		bool isLoadedFont(const std::string & fontName);

		/**
		 * Carga un conjunto de imagenes para la interfaz gráfica.
		 * @param fileName El nombre del fichero con el conjunto de imagenes.
		 */
		void loadImageset(const std::string & fileName);

		/**
		 * Descarga un conjunto de imagenes de la interfaz gráfica.
		 * @param imagesetName El nombre del conjunto de imagenes.
		 */
		void unloadImageset(const std::string & imagesetName);

		/**
		 * Comprueba si un conjunto de imagenes está cargado o no.
		 * @param imagesetName El nombre del conjunto de imagenes.
		 * @return Devuelve si el conjunto de imagenes está cargado o no.
		 */
		bool isLoadedImageset(const std::string & imagesetName);

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~GUIManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static GUIManager * _instance;

		/**
		 * El gestor CEGUI de la interfaz gráfica.
		 */
		CEGUI::System * _system;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Delegado para procesar el evento de una tecla pulsada.
		 */
		bool keyPressed(KeyCode key);

		/**
		 * Delegado para procesar el evento de una tecla pulsada.
		 */
		bool keyReleased(KeyCode key);

		/**
		 * Delegado para procesar el evento de un movimiento en el ratón.
		 */
		bool mouseAxis(const MouseState & state);

		/**
		 * Delegado para procesar el evento de un botón pulsado en el ratón.
		 */
		bool mousePressed(const MouseState & state);

		/**
		 * Delegado para procesar el evento de un botón soltado en el ratón.
		 */
		bool mouseReleased(const MouseState & state);

		/**
		 * Delegado para procesar el evento de un movimiento en el mando.
		 */
		bool gamePadAxis(const GamePadState & state, unsigned short player);

		/**
		 * Delegado para procesar el evento de un botón pulsado en el mando.
		 */
		bool gamePadPressed(const GamePadState & state, unsigned short player);

		/**
		 * Delegado para procesar el evento de un botón soltado en el mando.
		 */
		bool gamePadReleased(const GamePadState & state, unsigned short player);

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		GUIManager() : _system(0) {}
	};
}

#endif
