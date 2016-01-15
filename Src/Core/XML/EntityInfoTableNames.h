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

#ifndef __CORE_ENTITYINFOTABLENAMES_H__
#define __CORE_ENTITYINFOTABLENAMES_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	/**
	 * Esta clase representa el conjunto de nombres que el cargador necesita para indicar a los
	 * descriptores de entidades de qué atributo se trata.
	 */
	class EntityInfoTableNames {
	public:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		std::string position;
		std::string orientation;
		std::string scale;

		std::string graphicMeshFile;
		std::string graphicMaterialFile;
		std::string graphicStatic;
		std::string graphicCastShadows;

		std::string particleSystemName;
		std::string particleSystemFile;

		std::string lightType;
		std::string lightTypeOfLight;
		std::string lightVisible;
		std::string lightCastShadows;
		std::string lightDirection;
		std::string lightColourDiffuse;
		std::string lightColourSpecular;
		std::string lightSpotlightRangeInner;
		std::string lightSpotlightRangeOuter;
		std::string lightSpotlightRangeFalloff;
		std::string lightAttenuationRange;
		std::string lightAttenuationConstant;
		std::string lightAttenuationLinear;
		std::string lightAttenuationQuadratic;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		virtual void initialize() {
			position                   = "Position";
			orientation                = "Orientation";
			scale                      = "Scale";

			graphicMeshFile            = "Graphic.MeshFile";
			graphicMaterialFile        = "Graphic.MaterialFile";
			graphicStatic              = "Graphic.Static";
			graphicCastShadows         = "Graphic.CastShadows";

			particleSystemName         = "ParticleSystem.Name";
			particleSystemFile         = "ParticleSystem.File";

			lightType                  = "Light";
			lightTypeOfLight           = "Light.Type";
			lightVisible               = "Light.Visible";
			lightCastShadows           = "Light.CastShadows";
			lightDirection             = "Light.Direction";
			lightColourDiffuse         = "Light.ColourDiffuse";
			lightColourSpecular        = "Light.ColourSpecular";
			lightSpotlightRangeInner   = "Light.SpotlightRangeInner";
			lightSpotlightRangeOuter   = "Light.SpotlightRangeOuter";
			lightSpotlightRangeFalloff = "Light.SpotlightRangeFalloff";
			lightAttenuationRange      = "Light.AttenuationRange";
			lightAttenuationConstant   = "Light.AttenuationConstant";
			lightAttenuationLinear     = "Light.AttenuationLinear";
			lightAttenuationQuadratic  = "Light.AttenuationQuadratic";
		}

		//----------------------------------------------------------------------------------------------------
		// Constructor y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		EntityInfoTableNames() { initialize(); }

		/**
		 * Destructor del objeto.
		 */
		virtual ~EntityInfoTableNames() {}
	};
}

#endif
