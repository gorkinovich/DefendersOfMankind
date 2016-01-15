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

/**
@file ParticleSystem.h

Contiene la declaraci�n del componente que controla los sistemas de part�culas (SP) de la entidad.
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
	Contiene la declaraci�n del componente que controla los sistemas de part�culas de la entidad.
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
		Nodo con la informaci�n necesaria para cada sistema de part�culas
		*/
		struct TNode{
			ParticleUniverse::ParticleSystem* _particleSystem;	// Puntero al sistema de part�culas de Ogre
			float _timeToLife;						// Tiempo de vida del sistema de part�culas
			std::string _name;						// Nombre del sistema de part�culas
		};

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		ParticleSystem() : Component("ParticleSystem"), _entitySceneNode(0), _idPS(0), _sceneManager(0), _particleManager(0) {}

		/**
		Destructor. Se encarga de destruir todos aquellos sistemas de part�culas que a�n no han sido destruidos.
		*/
		~ParticleSystem();
		
		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo que activa el componente; invocado cuando se activa
		el mapa donde est� la entidad a la que pertenece el componente.

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();

		/**
		M�todo llamado en cada frame que actualiza el estado del componente.
		Se encarga de mover la entidad enemigo seg�n el tipo de movimiento establecido.
		
		@param lastInterval Milisegundos transcurridos desde el �ltimo tick.
		*/
		virtual void update(unsigned int lastInterval);


		/*
		===================================================
		M�todos de control sobre cada sistema de part�culas
		===================================================
		*/

		/*
		M�todo encargado de crear un sistema de part�culas y a�adirlo a la lista.
		@param name Nombre del SP a crear.
		@return true si todo fue correcto.
		*/
		bool createParticleSystem(const std::string &name);

		/*
		M�todo encargado de liberar un sistema de part�culas.
		@param node Nodo con el SP a liberar.
		@retunr true si todo fue correcto.
		*/
		bool releaseParticleSystem(TNode * & node);


	protected:

		/**
		 * Comprueba si un mensaje es v�lido para ser procesado o no.
		 * @param message El mensaje enviado al puerto.
		 * @return De ser v�lido devolver� true.
		 */
		virtual bool acceptMessage(const Core::SmartMessage & message);

		/**
		 * Procesa un mensaje reci�n sacado de la lista.
		 * @param message El mensaje sacado de la lista.
		 */
		virtual void processMessage(const Core::SmartMessage & message);

		/*
		Lista con los sistemas de part�culas de la entidad que actualmente se est�n mostrando.
		*/
		typedef std::list<TNode*> TParticleSystemList;
		typedef TParticleSystemList::iterator TParticleSystemListIterator;

		TParticleSystemList _particleSystemList;

		/*
		Tabla hash que contiene informaci�n de los sistemas de part�culas (SP) que mostrar� la entidad:
			- Clave: nombre que se le dar� al SP al crearlo. Ha de coincidir con el nombre del SP definido en el ".particles"
			- Valor: tiempo de vida del SP (en milisegundos)
		*/
		typedef std::map<std::string, float> TParticleSystemTable;
		typedef TParticleSystemTable::iterator TParticleSystemTableIterator;

		TParticleSystemTable _particleSystemTable;

		/*
		Nodo de escena de la entidad propietaria del componente.
		Este nodo contendr� todos los sistemas de part�culas asociados a la entidad.
		*/
		Ogre::SceneNode* _entitySceneNode;

		/*
		Contador del n�mero de part�culas creados hasta el momento. Necesario para no repetir nombre del SP al crearlo.
		Contrucci�n del nombre �nico:
			- Nombre del sistema de part�culas ("explosion", "humo", ...) +
			- Direcci�n de memoria de la entidad (para evitar duplicados de nombres con otras entidades que tengan �ste componente y que compartan un mismo SP) +
			- N�mero de SP creados por el momento
		Ejemplo: explosion+232508264+3 --> "explosion2325082643"
		*/
		unsigned int _idPS;

		/*
		Puntero al manager de escena (para evitar m�ltiples llamadas).
		*/
		Ogre::SceneManager* _sceneManager;

		/*
		Puntero al manager del sistema de part�culas (para evitar m�ltiples llamadas).
		*/
		ParticleUniverse::ParticleSystemManager* _particleManager;
	};
}

#endif
