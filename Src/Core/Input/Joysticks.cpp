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
#include <OISJoystick.h>
#include <OISInputManager.h>

#include "Core/Input/InputManager.h"
#include "Core/Input/Joysticks.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	Joysticks * Joysticks::_instance = new Joysticks();

	//********************************************************************************************************
	// Propiedades
	//********************************************************************************************************

	const JoystickState & Joysticks::getState(unsigned int device) const {
		assert(_states.size() > 0 && _states.size() > device &&
			"Joysticks::getState -> The devices have not been created...");
		return _states[device];
	}

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void Joysticks::resetStates() {
		unsigned int index = 0;
		// Recorremos todos los dispositivos conectados para resetearlo y luego actualizar el estado.
		DeviceVector::iterator end = _devices.end();
		for(DeviceVector::iterator i = _devices.begin(); i != end; ++i) {
			OIS::JoyStickState & devState = const_cast<OIS::JoyStickState &>((*i)->getJoyStickState());
			devState.clear();
			updateState(index++, *i);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Joysticks::initialize() {
		assert(InputManager::GetInstance() && InputManager::GetInstance()->_system &&
			"Joysticks::initialize -> The input manager has not been created...");
		OIS::InputManager * system = InputManager::GetInstance()->_system;
		// Obtenemos los dispositivos de tipo joystick si hay alguno conectado.
		int numOfDev = system->getNumberOfDevices(OIS::OISJoyStick);
		if(numOfDev > 0) {
			_devices.resize(numOfDev);
			_states.resize(numOfDev);
			unsigned int index = 0;
			DeviceVector::iterator end = _devices.end();
			for(DeviceVector::iterator i = _devices.begin(); i != end; ++i) {
				(*i) = static_cast<OIS::JoyStick *>(system->createInputObject(OIS::OISJoyStick, true));
				// Inicializamos el estado del joystick actual.
				updateState(index++, *i);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Joysticks::release() {
		assert(InputManager::GetInstance() && InputManager::GetInstance()->_system &&
			"Joysticks::release -> The input manager has not been created...");
		OIS::InputManager * system = InputManager::GetInstance()->_system;
		// Destruimos los dispositivos de tipo joystick de haber obtenido alguno.
		if(_devices.size() > 0) {
			DeviceVector::iterator end = _devices.end();
			for(DeviceVector::iterator i = _devices.begin(); i != end; ++i) {
				system->destroyInputObject(*i);
			}
			_devices.clear();
			_states.clear();
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Joysticks::update() {
		unsigned int index = 0;
		// Recorremos todos los dispositivos para actualizarlos y actualizar el estado actual.
		DeviceVector::iterator end = _devices.end();
		for(DeviceVector::iterator i = _devices.begin(); i != end; ++i) {
			(*i)->capture();
			updateState(index++, *i);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void Joysticks::updateState(unsigned int index, OIS::JoyStick * device) {
		unsigned int i;
		const OIS::JoyStickState & devState = device->getJoyStickState();
		JoystickState & victim = _states[index];
		// Actualizamos los valores de los ejes.
		for(i = 0; i < MAX_JOYSTICK_AXIS; ++i) {
			victim.axis[i] = (devState.mAxes.size() > i) ? devState.mAxes[i].abs : 0;
		}
		// Actualizamos los pads digitales.
		for(i = 0; i < MAX_JOYSTICK_POVS; ++i) {
			victim.povs[i].up = (devState.mPOV[i].direction & OIS::Pov::North) != 0;
			victim.povs[i].down = (devState.mPOV[i].direction & OIS::Pov::South) != 0;
			victim.povs[i].left = (devState.mPOV[i].direction & OIS::Pov::West) != 0;
			victim.povs[i].right = (devState.mPOV[i].direction & OIS::Pov::East) != 0;
		}
		// Actualizamos los sliders.
		for(i = 0; i < MAX_JOYSTICK_SLIDERS; ++i) {
			victim.sliders[i].x = devState.mSliders[i].abX;
			victim.sliders[i].y = devState.mSliders[i].abY;
		}
		// Actualizamos los botones.
		for(i = 0; i < MAX_JOYSTICK_BUTTONS; ++i) {
			victim.buttons[i] = (devState.mButtons.size() > i) ? devState.mButtons[i] : false;
		}
	}
}
