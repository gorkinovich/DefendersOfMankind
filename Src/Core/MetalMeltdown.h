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

#ifndef __CORE_METALMELTDOWN_H__
#define __CORE_METALMELTDOWN_H__

#include "Core/BaseManager.h"
#include "Core/LocalizationManager.h"
#include "Core/Entities/EntitiesManager.h"
#include "Core/Graphics/GraphicsManager.h"
#include "Core/Graphics/TerrainManager.h"
#include "Core/GUI/GUIManager.h"
#include "Core/Input/GamePads.h"
#include "Core/Input/InputListenersManager.h"
#include "Core/Input/InputManager.h"
#include "Core/Input/Joysticks.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Resources/LoadingObserver.h"
#include "Core/Resources/ResourcesManager.h"
#include "Core/Scripting/ScriptingManager.h"
#include "Core/Sequences/SequenceManager.h"
#include "Core/Sound/SoundManager.h"

/**
 * Borrar todos singletons del Core, para evitar los mensajes de memory leaks al salir.
 */
inline void MetalMeltdown() {
#ifdef _DEBUG
	delete Core::BaseManager::GetInstance();
	delete Core::LocalizationManager::GetInstance();
	delete Core::EntitiesManager::GetInstance();
	delete Core::GraphicsManager::GetInstance();
	delete Core::TerrainManager::GetInstance();
	delete Core::GUIManager::GetInstance();
	delete Core::GamePads::GetInstance();
	delete Core::InputListenersManager::GetInstance();
	delete Core::InputManager::GetInstance();
	delete Core::Joysticks::GetInstance();
	delete Core::Keyboard::GetInstance();
	delete Core::Mouse::GetInstance();
	delete Core::LoadingObserver::GetInstance();
	delete Core::ResourcesManager::GetInstance();
	delete Core::ScriptingManager::GetInstance();
	delete Core::SequenceManager::GetInstance();
	delete Core::SoundManager::GetInstance();
#endif
}

#endif
