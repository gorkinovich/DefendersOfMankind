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
@file PhysicEntity.h

Contiene la declaraci�n del componente encargado de la representaci�n f�sica de las
entidades. Esta clase sirve para representar cualquier entidad excepto los denominados
character controllers.

@see Logic::PhysicEntity
@see Core::Component
@see Logic::PhysicCharacter

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/
#ifndef __Logic_PhysicEntity_H
#define __Logic_PhysicEntity_H

#include "Core/Entities/Component.h"
#include "Physics/Server.h"

#include "Core/Scripting/InfoTableUtils.h"

namespace Core {
	class Entity;
}

class IPhysicModel;
class CPhysicModelSimple;
class CPhysicModelGeneric;
class IPhysicObj;

// Los componentes pertenecen al namespace Logic
namespace Logic {
	// Constantes para las cadenas que se usan para definir las entidades en el fichero de mapa. 
	const std::string STR_PHYSIC_ENTITY = "physic_entity";
	const std::string STR_SIMPLE = "simple";
	const std::string STR_GENERIC = "generic";
	const std::string STR_CONTROLLER = "controller";
	const std::string STR_PHYSIC_FILE = "physic_file";
	const std::string STR_PHYSIC_TYPE =	"physic_type";
	const std::string STR_STATIC = "static";
	const std::string STR_DYNAMIC = "dynamic";
	const std::string STR_KINEMATIC = "kinematic";
	const std::string STR_PHYSIC_SHAPE = "physic_shape";
	const std::string STR_CAPSULE = "capsule";
	const std::string STR_PHYSIC_RADIUS = "physic_radius";
	const std::string STR_PHYSIC_HEIGHT = "physic_height";
	const std::string STR_PLANE = "plane";
	const std::string STR_PHYSIC_NORMAL = "physic_normal";
	const std::string STR_BOX = "box";
	const std::string STR_PHYSIC_DIMENSIONS = "physic_dimensions";
	const std::string STR_PHYSIC_MASS = "physic_mass";
	const std::string STR_PHYSIC_TRIGGER = "physic_trigger";
	const std::string STR_PHYSIC_COLLISION_GROUP = "physic_collision_group";

	/**
	Componente encargardo de la representaci�n f�sica de una entidad. Puede ser utilizado
	para representar cualquier tipo de entidad f�sica excepto los denominados character 
	controllers, que se representan usando un tipo de componente espec�fico.
	<p>
	En un videojuego m�s complejo seguramente convendr�a dividir la funcionalidad que ofrece 
	este componente en varios componentes m�s especializados. Para nuestro juego, sin embargo, 
	no necesitamos cosas muy elaboradas. 
	<p>
	Esta clase actualiza la posici�n y rotaci�n de las entidades l�gicas en cada tick usando
	la infomaci�n que proporciona el motor de f�sica. 
	<p>
	Con respecto a mover las entidades f�sicas, debemos tener en cuenta que existen 3 tipos 
	de entidades: est�ticas, din�micas y kinem�ticas. Las entidades est�ticas no se pueden mover
	una vez creadas. Las entidades din�micas responden a fuerzas y, en principio, no deber�an 
	moverse directamente desde el juego si no es mediante la aplicaci�n	de fuerzas.	Las 
	entidades kinem�ticas, por el contrario, se mueven tal y como dicta la l�gica del juego. 
	Cuando este componente se utiliza para representar una entidad kinem�tica acepta mensajes de 
	tipo SET_TRANSFORM, y en cada tick pide la motor de f�sica que mueva la entidad de acuerdo
	a la transformaci�n recibida desde la l�gica.
	
    @ingroup logicGroup
	@author Antonio S�nchez Ruiz-Granados
	@date Octubre, 2010
	*/
	class PhysicEntity : public Core::Component {
	public:
		ComponentCreateMethod(PhysicEntity);
	
		/**
		Constructor por defecto.
		*/
		PhysicEntity();

		/**
		Destructor (virtual). Elimina el objeto f�sico de la escena y lo destruye. 
		*/
		virtual ~PhysicEntity();
		
		/**
		Este m�todo se invoca cada vez que la entidad f�sica asociada a este 
		componente choca contra otra entidad. Debemos tener en cuenta que las 
		dos entidades involucradas en el choque ser�n notificadas a trav�s de 
		este m�todo.
		@param otherEntity La otra entidad involucrada en el choque.
		 */
		virtual void onEntityHit(const Core::Entity *otherEntity);

		/**
		Este m�todo se invoca cada vez que la entidad f�sica asociada a este 
		componente interact�a con otra, siendo alguna de ellas un trigger. Debemos 
		tener en cuenta que las dos entidades involucradas ser�n notificadas a 
		trav�s de este m�todo. Por tanto, el par�metro "otherEntity" puede representar
		tanto una entidad asociada a un trigger (cuando se notifica a la otra entidad)
		como una entidad f�sica de cualquier tipo (cuando se notifica al trigger).
		@param otherEntity La otra entidad involucrada.
		@param enter Indica si una entidad f�sica ha entrado en el trigger.
		@param leave Indica si una entidad f�sica ha salido del trigger.
		@param stay Indica si una entidad f�sica permanece dentro del trigger.
		*/
		virtual void onEntityTrigger(const Core::Entity *otherEntity, bool enter, bool leave, bool stay);

		/*
		M�todo que devuelve el puntero a la entidad f�sica.
		*/
		IPhysicObj* getPhysicEntity() { return _physicObj; } 



	protected:
		/**
		Constructor por defecto.
		*/
		PhysicEntity(const std::string & name);

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

		/**
		Inicializa el componente usando los atributos definidos en el fichero de mapa.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Este m�todo se invoca en cada ciclo de la simulaci�n y hace lo siguiente:
		<ul>
		<li>Actualiza la posici�n y rotaci�n de la entidad l�gica usando la informaci�n 
		que proporciona el motor de f�sica.</li>
		<li>Si la entidad f�sica asociada al componente es de tipo kinem�tico, 
		solicita al motor de f�sica que la mueva de acuerdo al �ltimo mensaje 
		SET_TRANSFORM recibido.</li>
		</ul>
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Este m�todo construye y devuelve la entidad f�sica asociada a este componente, 
		en base a la informaci�n del mapa. La implementaci�n por defecto utiliza el 
		m�todo "createPhysicModel" para conseguir el modelo l�gico que describe el tipo 
		de entidad f�sica que se debe crear.
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Entidad f�sica creada, NULL si hubo alg�n problema.
		*/
		virtual IPhysicObj* createPhysicEntity(const Core::EntityInfoTable *entityInfo);

		/**
		Este m�todo devuelve el modelo f�sico que describe el tipo de entidad f�sica
		que se debe crear.
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@param Modelo f�sico que describe el tipo de entidad f�sica deseado,
			   NULL si hubo alg�n problema.
		*/
		virtual IPhysicModel* createPhysicModel(const Core::EntityInfoTable *entityInfo);

		/**
		Servidor de f�sica.
		*/
		Physics::CServer *_physicServer;
		
		/**
		Entidad f�sica asociada a este componente.
		*/
		IPhysicObj *_physicObj;

		/**
		Matriz de transformaci�n recibida en el �ltimo mensaje de tipo SET_TRANSFORM. Sirve
		para mover entidades f�sicas kinem�ticas.
		*/
		Matrix4 _transform;

	private:
		/**
		Este m�todo indica el tipo de entidad f�sica que debemos crear (est�tica, din�mica o 
		kinem�tica) a partir de la descripci�n de la entidad en el fichero de mapa.
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Tipo de entidad f�sica: est�tica, din�mica o kinem�tica.
		*/
		Physics::TPhysicMode getPhysicMode(const Core::EntityInfoTable *entityInfo);

		/**
		Este m�todo construye y devuelve un modelo que describe un tipo de entidad f�sica simple.
		Las entidades f�sicas simples pueden estar formadas por varios vol�menes de colisi�n.
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Modelo que describe una entidad f�sica simple.
		*/
		CPhysicModelSimple* createPhysicModelSimple(const Core::EntityInfoTable *entityInfo);

		/**
		Este m�todo a�ade un volumen de colisi�n (shape) a un modelo f�sco simple. El tipo de volumen
		que se debe crear (caja, cilindro, plano, etc) se obtiene a partir de la descripci�n de la
		entidad en el fichero de mapa.
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@param model Modelo f�sico que describe un tipo de entidad f�sica simple.
		@param scale Factor que permite escalar el tama�o del volumen de colision creado.
		*/
		void createPhysicShape(const Core::EntityInfoTable *entityInfo, CPhysicModelSimple *model, float scale);

		/**
		Este m�todo construye y devuelve un modelo que describe un tipo de entidad f�sica gen�rica.
		Las entidades f�sicas gen�ricas pueden estar formadas por varias entidades f�sicas simples
		o gen�ricas. Este tipo de entidades se suelen crear a partir de ficheros exportados desde
		editores tipo 3DMAX.
		@param entityInfo Descripci�n de la entidad en el fichero de mapa.
		@return Modelo que describe una entidad f�sica gen�rica.
		*/
		CPhysicModelGeneric* createPhysicModelGeneric(const Core::EntityInfoTable *entityInfo);
	};
}

#endif
