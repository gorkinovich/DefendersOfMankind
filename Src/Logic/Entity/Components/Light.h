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

#ifndef __LOGIC_LIGHT_H__
#define __LOGIC_LIGHT_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include "Core/Entities/Component.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class LightEntity;
	class Scene;
}

//************************************************************************************************************
// Logic
//************************************************************************************************************

namespace Logic {
	/**
	 * Esta clase representa un componente para manejar una luz en la escena gráfica.
	 */
	class Light : public Core::Component {
	public:
		ComponentCreateMethod(Light);

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene la entidad gráfica que contiene la luz.
		 */
		inline Core::LightEntity * getLightEntity() { return _lightEntity; }

		//----------------------------------------------------------------------------------------------------
		// Constructores y destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		Light();

		/**
		 * Destructor del objeto.
		 */
		virtual ~Light();

	protected:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La entidad gráfica que contiene la luz.
		 */
		Core::LightEntity * _lightEntity;

		/**
		 * La escena a la que pertenece la entidad gráfica.
		 */
		Core::Scene * _scene;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Comprueba si un mensaje es válido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser válido devolverá true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje recién sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

		/**
		 * Inicializa el componente a la hora de ser añadido al mundo.
		 * @param info La información inicial del componente.
		 * @return Devuelve true si se inicializa correctamente.
		 * @remark Este método es invocado cuando la entidad dueña es inicializada al añadirse al mundo.
		 * @remark En este método es cuando los componentes toman los datos de inicialización o de gestores
		 *         del juego, lo que no se debe hacer es coger datos de otros componentes, porque cabe
		 *         la posibilidad de que todavía no se haya inicializado porque no se haya llamado todavía
		 *         a su respectivo spawn (para este caso en particular existe activate).
		 */
		virtual bool spawn(const Core::EntityInfoTable * info);

		/**
		 * Crea una entidad gráfica que contiene la luz.
		 * @param info La información inicial del componente.
		 * @return La entidad creada si no falla nada, sino devuelve NULL.
		 */
		Core::LightEntity * createLightEntity(const Core::EntityInfoTable * info);
	};
}

#endif
