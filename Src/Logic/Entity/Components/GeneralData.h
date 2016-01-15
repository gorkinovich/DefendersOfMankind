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

#ifndef __LOGIC_GENERALDATA_H__
#define __LOGIC_GENERALDATA_H__

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	class GeneralData : public Core::Component {
	public:
		ComponentCreateMethod(GeneralData);

		inline bool isPlayer() const { return _isPlayer; }
		inline bool isCamera() const { return _isCamera; }
		inline int getIDSquadron() const { return _IDSquadron; }

		GeneralData(const std::string & name = "GeneralData") : Component(name),
			_isPlayer(false), _isCamera(false), _IDSquadron(-1) {}

		virtual ~GeneralData() {}

	protected:

		bool _isPlayer;
		bool _isCamera;
		int _IDSquadron;

		virtual bool acceptMessage(const Core::SmartMessage & message);
		virtual void processMessage(const Core::SmartMessage & message);

		virtual bool spawn(const Core::EntityInfoTable * entityInfo);
		virtual bool activate();
		virtual void deactivate();
	};
}

#endif
