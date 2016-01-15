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

/**
@file ParticleSystem.h

Contiene la declaración del componente que controla los sistemas de partículas (SP) de la entidad.
Recibe y procesa mensajes de tipo PARTICLE_SYSTEM.

@see Logic::ParticleSystem
@see Core::Component

@author Grupo 3
@date Abril, 2011
*/
#ifndef __Logic_ParticleSystem_H
#define __Logic_ParticleSystem_H

#include "Core/Entities/Component.h"

#include <ParticleUniverseSystem.h>
#include <ParticleUniverseSystemManager.h>

namespace Ogre {
	//class ParticleSystem;
	class SceneNode;
}

namespace Logic {
/**
	Contiene la declaración del componente que controla los sistemas de partículas de la entidad.
	Recibe y procesa mensajes de tipo PARTICLE_SYSTEM.
	
    @ingroup logicGroup

	@author Grupo 3
	@date Abril, 2011
*/
	class ParticleSystem : public Core::Component
	{
	public:
		ComponentCreateMethod(ParticleSystem);

		/*
		Nodo con la información necesaria para cada sistema de partículas
		*/
		struct TNode{
			ParticleUniverse::ParticleSystem* _particleSystem;	// Puntero al sistema de partículas de Ogre
			float _timeToLife;						// Tiempo de vida del sistema de partículas
			std::string _name;						// Nombre del sistema de partículas
		};

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		ParticleSystem() : Component("ParticleSystem"), _entitySceneNode(0), _idPS(0), _sceneManager(0), _particleManager(0) {}

		/**
		Destructor. Se encarga de destruir todos aquellos sistemas de partículas que aún no han sido destruidos.
		*/
		~ParticleSystem();
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		Se encarga de mover la entidad enemigo según el tipo de movimiento establecido.
		
		@param lastInterval Milisegundos transcurridos desde el último tick.
		*/
		virtual void update(unsigned int lastInterval);


		/*
		===================================================
		Métodos de control sobre cada sistema de partículas
		===================================================
		*/

		/*
		Método encargado de crear un sistema de partículas y añadirlo a la lista.
		@param name Nombre del SP a crear.
		@return true si todo fue correcto.
		*/
		bool createParticleSystem(const std::string &name);

		/*
		Método encargado de liberar un sistema de partículas.
		@param node Nodo con el SP a liberar.
		@retunr true si todo fue correcto.
		*/
		bool releaseParticleSystem(TNode * & node);


	protected:

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

		/*
		Lista con los sistemas de partículas de la entidad que actualmente se están mostrando.
		*/
		typedef std::list<TNode*> TParticleSystemList;
		typedef TParticleSystemList::iterator TParticleSystemListIterator;

		TParticleSystemList _particleSystemList;

		/*
		Tabla hash que contiene información de los sistemas de partículas (SP) que mostrará la entidad:
			- Clave: nombre que se le dará al SP al crearlo. Ha de coincidir con el nombre del SP definido en el ".particles"
			- Valor: tiempo de vida del SP (en milisegundos)
		*/
		typedef std::map<std::string, float> TParticleSystemTable;
		typedef TParticleSystemTable::iterator TParticleSystemTableIterator;

		TParticleSystemTable _particleSystemTable;

		/*
		Nodo de escena de la entidad propietaria del componente.
		Este nodo contendrá todos los sistemas de partículas asociados a la entidad.
		*/
		Ogre::SceneNode* _entitySceneNode;

		/*
		Contador del número de partículas creados hasta el momento. Necesario para no repetir nombre del SP al crearlo.
		Contrucción del nombre único:
			- Nombre del sistema de partículas ("explosion", "humo", ...) +
			- Dirección de memoria de la entidad (para evitar duplicados de nombres con otras entidades que tengan éste componente y que compartan un mismo SP) +
			- Número de SP creados por el momento
		Ejemplo: explosion+232508264+3 --> "explosion2325082643"
		*/
		unsigned int _idPS;

		/*
		Puntero al manager de escena (para evitar múltiples llamadas).
		*/
		Ogre::SceneManager* _sceneManager;

		/*
		Puntero al manager del sistema de partículas (para evitar múltiples llamadas).
		*/
		ParticleUniverse::ParticleSystemManager* _particleManager;
	};
}

#endif
