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

#ifndef __CORE_WINDOWEVENTS_H__
#define __CORE_WINDOWEVENTS_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>
#include "Core/GUI/GUIManager.h"

//************************************************************************************************************
// CEGUI
//************************************************************************************************************

namespace CEGUI {
	class EventArgs;
}

//************************************************************************************************************
// SubscribeToClickedEvent
//************************************************************************************************************

/**
 * A�ade a un objeto ventana de CEGUI una funci�n para recibir eventos de pulsar un bot�n.
 * @param windowName El nombre del objeto ventana.
 * @param func El puntero a la funci�n que va a recibir los eventos.
 * @param obj El objeto a la que pertenece la funci�n.
 */
template<class T>
inline void SubscribeToClickedEvent(const std::string & windowName, bool(T::*func)(const CEGUI::EventArgs &), T * obj) {
	Core::GUIManager::GetInstance()->getWindow(windowName)->subscribeEvent(
		CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(func, obj)
	);
}

#endif
