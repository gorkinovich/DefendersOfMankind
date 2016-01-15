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

#include "HUDController.h"

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIWindow.h>

#include <assert.h>

namespace Logic {

	HUDController::HUDController()
	{
		// Cargamos la ventana de juego
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("ZGame.layout");
		_gameWindow = CEGUI::WindowManager::getSingleton().getWindow("Game");

		// Cargamos la ventana de la puntuación
		_scoreWindow = CEGUI::WindowManager::getSingleton().getWindow("GameScore");
		
		// Cargamos la ventana de información de debug (FPS)
		_infoDebugWindow = CEGUI::WindowManager::getSingleton().getWindow("InfoDebug");
		_infoDebugWindow->setVisible(false);
		
		// Cargamos las imágenes de la barra de vida
		_lifeBar[0] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar1");
		_lifeBar[1] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar2");
		_lifeBar[2] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar3");
		_lifeBar[3] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar4");
		_lifeBar[4] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar5");
		_lifeBar[5] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar6");
		_lifeBar[6] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar7");
		_lifeBar[7] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar8");
		_lifeBar[8] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar9");
		_lifeBar[9] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar10");
		_lifeBar[10] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar11");
		_lifeBar[11] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar12");
		_lifeBar[12] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar13");
		_lifeBar[13] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar14");
		_lifeBar[14] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar15");
		_lifeBar[15] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar16");
		_lifeBar[16] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar17");
		_lifeBar[17] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar18");
		_lifeBar[18] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar19");
		_lifeBar[19] = CEGUI::WindowManager::getSingleton().getWindow("LifeBar20"); 

		// Cargamos la imagen (x3) del número de vidas restantes
		_nLife[0] = CEGUI::WindowManager::getSingleton().getWindow("LifePicture1");
		_nLife[1] = CEGUI::WindowManager::getSingleton().getWindow("LifePicture2"); 
		_nLife[2] = CEGUI::WindowManager::getSingleton().getWindow("LifePicture3");

		// Obtenemos el ratio de resolución adecuado
		CEGUI::Imageset& set = CEGUI::ImagesetManager::getSingleton().create("HUD.imageset", "imagesets");
		_ratio = (float) (_gameWindow->getParentPixelWidth() * set.getNativeResolution().d_width) /
			(_gameWindow->getParentPixelHeight() * set.getNativeResolution().d_height);
		// HACK
		_ratio = (float) 0.4f;

		// Establecemos el área correspondiente de las imagenes de la barra de vida
		setAreaOfLifeBar();

		// Establecemos el área corrrespondiente de las imágenes del nº de vidas restantes
		setAreaOfLifeCounter();

	

	} // HUDController

	//--------------------------------------------------------

	HUDController::~HUDController()
	{
		deactivate();

	} // ~HUDController

	//--------------------------------------------------------

	void HUDController::activate()
	{
		CEGUI::System::getSingletonPtr()->setGUISheet(_gameWindow);
		_gameWindow->setVisible(true);
		_gameWindow->activate();

	} // activate

	//--------------------------------------------------------

	void HUDController::deactivate()
	{
		// Desactivamos la ventana de juego.
		_gameWindow->deactivate();
		_gameWindow->setVisible(false);

	} // deactivate

	//--------------------------------------------------------

	void HUDController::setScore(unsigned int score)
	{
		std::string text;
		std::stringstream out;
		out << score;
		text = out.str();
		_scoreWindow->setText(text);
	} // setScore

	//--------------------------------------------------------

	void HUDController::updateLifeBar(float life)
	{
		// Según el parámetro recibido, actualizamos las imágenes de la barra de vida
		// con el valor de transparencia que corresponda
		_lifeBar[19]->setAlpha((life-95)/5);
		_lifeBar[18]->setAlpha((life-90)/5);
		_lifeBar[17]->setAlpha((life-85)/5);
		_lifeBar[16]->setAlpha((life-80)/5);
		_lifeBar[15]->setAlpha((life-75)/5);
		_lifeBar[14]->setAlpha((life-70)/5);
		_lifeBar[13]->setAlpha((life-65)/5);
		_lifeBar[12]->setAlpha((life-60)/5);
		_lifeBar[11]->setAlpha((life-55)/5);
		_lifeBar[10]->setAlpha((life-50)/5);
		_lifeBar[9]->setAlpha((life-45)/5);
		_lifeBar[8]->setAlpha((life-40)/5);
		_lifeBar[7]->setAlpha((life-35)/5);
		_lifeBar[6]->setAlpha((life-30)/5);
		_lifeBar[5]->setAlpha((life-25)/5);
		_lifeBar[4]->setAlpha((life-20)/5);
		_lifeBar[3]->setAlpha((life-15)/5);
		_lifeBar[2]->setAlpha((life-10)/5);
		_lifeBar[1]->setAlpha((life-5)/5);
		_lifeBar[0]->setAlpha(life/5);

	} // setLife


	void HUDController::updateLifeCounter(unsigned short n)
	{
		assert( (n>=0 && n<=3) && "El numero de vidas restantes ha de estar entre [0,3]");

		// Hacemos visible las imágenes correspondientes
		for (int i=0; i<3; i++)
			if (i<=n-1)  _nLife[i]->setVisible(true);
			else _nLife[i]->setVisible(false);

	}


	void HUDController::setAreaOfLifeBar()
	{
		// Establecemos el área correspondiente de las imagenes de la barra de vida
		_lifeBar[0]->setArea(CEGUI::UDim(0.0f,0.0f),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,160.0f*_ratio));

		_lifeBar[1]->setArea(CEGUI::UDim(0.0f,19.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,156.0f*_ratio));

		_lifeBar[2]->setArea(CEGUI::UDim(0.0f,38.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,116.0f*_ratio));

		_lifeBar[3]->setArea(CEGUI::UDim(0.0f,57.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,98.0f*_ratio));

		_lifeBar[4]->setArea(CEGUI::UDim(0.0f,76.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,85.0f*_ratio));

		_lifeBar[5]->setArea(CEGUI::UDim(0.0f,95.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,75.0f*_ratio));

		_lifeBar[6]->setArea(CEGUI::UDim(0.0f,114.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,66.0f*_ratio));

		_lifeBar[7]->setArea(CEGUI::UDim(0.0f,133.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,58.0f*_ratio));

		_lifeBar[8]->setArea(CEGUI::UDim(0.0f,152.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,52.0f*_ratio));

		_lifeBar[9]->setArea(CEGUI::UDim(0.0f,171.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,46.0f*_ratio));

		_lifeBar[10]->setArea(CEGUI::UDim(0.0f,190.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,40.0f*_ratio));

		_lifeBar[11]->setArea(CEGUI::UDim(0.0f,209.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,36.0f*_ratio));

		_lifeBar[12]->setArea(CEGUI::UDim(0.0f,228.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,33.0f*_ratio));

		_lifeBar[13]->setArea(CEGUI::UDim(0.0f,247.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,30.0f*_ratio));

		_lifeBar[14]->setArea(CEGUI::UDim(0.0f,266.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,28.0f*_ratio));

		_lifeBar[15]->setArea(CEGUI::UDim(0.0f,285.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,25.0f*_ratio));

		_lifeBar[16]->setArea(CEGUI::UDim(0.0f,304.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,24.0f*_ratio));

		_lifeBar[17]->setArea(CEGUI::UDim(0.0f,323.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,22.0f*_ratio));

		_lifeBar[18]->setArea(CEGUI::UDim(0.0f,342.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,21.0f*_ratio));

		_lifeBar[19]->setArea(CEGUI::UDim(0.0f,361.0f*_ratio),CEGUI::UDim(0.0f,0.0f),
						CEGUI::UDim(0.0f,16.0f*_ratio),CEGUI::UDim(0.0f,21.0f*_ratio));
	}


	void HUDController::setAreaOfLifeCounter()
	{
		_nLife[0]->setArea(CEGUI::UDim(0.0f,85.0f*_ratio),CEGUI::UDim(0.0f,100.0f*_ratio),
						CEGUI::UDim(0.0f,91.0f*_ratio),CEGUI::UDim(0.0f,44.0f*_ratio));
		_nLife[1]->setArea(CEGUI::UDim(0.0f,185.0f*_ratio),CEGUI::UDim(0.0f,100.0f*_ratio),
						CEGUI::UDim(0.0f,91.0f*_ratio),CEGUI::UDim(0.0f,44.0f*_ratio));
		_nLife[2]->setArea(CEGUI::UDim(0.0f,285.0f*_ratio),CEGUI::UDim(0.0f,100.0f*_ratio),
						CEGUI::UDim(0.0f,91.0f*_ratio),CEGUI::UDim(0.0f,44.0f*_ratio));
	}


	void HUDController::showInfoDebug(bool show)
	{
		_infoDebugWindow->setVisible(show);
	}


	void HUDController::updateInfoDebug(float fps, unsigned int triangleCount)
	{
		std::string text;
		std::stringstream out;
		out << "FPS: " << fps;
		out << "\nNº triángulos: " << triangleCount;
		text = out.str();
		_infoDebugWindow->setText(text);
		
	}

} // namespace GUI
