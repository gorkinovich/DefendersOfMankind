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

#include "Logic/MissionManager.h"
#include "Core/Entities/RegisterComponent.h"

// En algún lado tienen que haber inclusiones a los direfentes componentes para
// que estos se registren en la factoría... aquí puede ser el sitio.
#include "Logic/Entity/Components/Position.h"
#include "Logic/Entity/Components/GeneralData.h"
#include "Logic/Entity/Components/Light.h"
#include "Logic/Entity/Components/Graphics.h"
#include "Logic/Entity/Components/AnimatedGraphics.h"
#include "Logic/Entity/Components/AvatarController.h"
#include "Logic/Entity/Components/Camera.h"
#include "Logic/Entity/Components/SwitchPosition.h"
#include "Logic/Entity/Components/SwitchTrigger.h"
#include "Logic/Entity/Components/DamageTrigger.h"
#include "Logic/Entity/Components/Life.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "Logic/Entity/Components/PhysicCharacter.h"
#include "Logic/Entity/Components/Generator.h"
//#include "Logic/Entity/Components/SteeringMovement.h"
//#include "Logic/Entity/Components/RouteTo.h"
#include "Logic/Entity/Components/StateMachineExecutor.h"
#include "Logic/Entity/Components/BasicMovement.h"
#include "Logic/Entity/Components/ChangeMaterial.h"
#include "Logic/Entity/Components/ParticleSystem.h"
#include "Logic/Entity/Components/KillEntities.h"
#include "Logic/Entity/Components/Death.h"
#include "Logic/Entity/Components/CameraTrigger.h"
#include "Logic/Entity/Components/EndOfLevelTrigger.h"
#include "Logic/Entity/Components/BifurcationTrigger.h"
#include "Logic/Entity/Components/Sound.h"
#include "Logic/Entity/Components/PowerUpTrigger.h"
#include "Logic/Entity/Components/BTExecutor.h"
#include "Logic/Entity/Components/PowerUpController.h"

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	bool MissionManager::registerComponentTypes() {
		//if(!RegisterComponent()) return false;
		if(!RegisterComponent(Position)) return false;
		if(!RegisterComponent(GeneralData)) return false;
		if(!RegisterComponent(Light)) return false;
		if(!RegisterComponent(Graphics)) return false;
		if(!RegisterComponent(AnimatedGraphics)) return false;
		if(!RegisterComponent(AvatarController)) return false;
		if(!RegisterComponent(Camera)) return false;
		if(!RegisterComponent(SwitchPosition)) return false;
		if(!RegisterComponent(SwitchTrigger)) return false;
		if(!RegisterComponent(DamageTrigger)) return false;
		if(!RegisterComponent(Life)) return false;
		if(!RegisterComponent(PhysicEntity)) return false;
		if(!RegisterComponent(PhysicCharacter)) return false;
		if(!RegisterComponent(Generator)) return false;
		//if(!RegisterComponent(SteeringMovement)) return false;
		//if(!RegisterComponent(RouteTo)) return false;
		if(!RegisterComponent(StateMachineExecutor)) return false;
		if(!RegisterComponent(BasicMovement)) return false;
		if(!RegisterComponent(ChangeMaterial)) return false;
		if(!RegisterComponent(ParticleSystem)) return false;
		if(!RegisterComponent(KillEntities)) return false;
		if(!RegisterComponent(Death)) return false;
		if(!RegisterComponent(CameraTrigger)) return false;
		if(!RegisterComponent(EndOfLevelTrigger)) return false;
		if(!RegisterComponent(BifurcationTrigger)) return false;
		if(!RegisterComponent(Sound)) return false;
		if(!RegisterComponent(PowerUpTrigger)) return false;
		if(!RegisterComponent(BTExecutor)) return false;
		if(!RegisterComponent(PowerUpController)) return false;
		return true;
	}
}
