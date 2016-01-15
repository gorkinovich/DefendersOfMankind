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
@file PhysicCharacter.h

Contiene la declaración del componente que se utiliza para representar jugadores y enemigos en
el mundo físico usando character controllers.

@see Logic::PhysicCharacter
@see Logic::PhysicEntity

@author Antonio Sánchez Ruiz-Granados
@date Octubre, 2010
*/
#ifndef __Logic_PhysicCharacter_H
#define __Logic_PhysicCharacter_H

#include "PhysicEntity.h"

namespace Logic {
	/**
	Componente que se utiliza para representar jugadores y enemigos en el mundo físico usando 
	character controllers.<p>
	Este componente recibe mensajes de tipo AVATAR_WALK para mover el controller.<p>
	La implementación de esta clase también gestiona las diferencias que existen entre el
	sistema de coordenadas local (SCL) lógico y físico. El SCL que usa la lógica para cada 
	entidad tiene su origen en la parte inferior de la entidad (los pies), mientras que 
	PhysX coloca por defecto el origen del SCL en medio de la entidad. En las entidades 
	físicas simples, podemos unificar los dos SCL definiendo una sencilla traslación en la 
	descripción del modelo, pero la descripción de los character controllers no ofrece esa
	posibilidad. La conclusión es que debemos realizar una traslación en el eje Y para 
	convertir entre coordenadas lógicas y coordenadas físicas.
	
    @ingroup logicGroup
	@author Antonio Sánchez Ruiz-Granados
	@date Octubre, 2010
	*/
	class PhysicCharacter : public PhysicEntity
	{
	public:
		ComponentCreateMethod(PhysicCharacter);

		/**
		Constructor por defecto.
		*/
		PhysicCharacter();

		/**
		Destructor (virtual).
		*/
		virtual ~PhysicCharacter();

		virtual void setMovement(Vector3);

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

		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		virtual void prepareUpdate(unsigned int lastInterval);
		/**
		Este método se invoca en cada ciclo de la simulación y hace lo siguiente:
		<ul>
		<li>Actualiza la posición de la entidad lógica usando la información que proporciona
		el motor de física.</li>
		<li>Mueve el character controller de acuerdo al último mensaje AVATAR_WALK recibido.</li>
		</ul>
		<p>
		Necesitamos sobreescribir el método de la clase padre ya que los character controllers
		no tienen orientación, sólo posición. Además debemos aplicar una traslación al vector 
		de posición que obtenemos de PhysX ya que la lógica y la física	usan distintos orígenes 
		para los sistemas de coordenadas locales a la entidad (en los pies / en el centro de la 
		entidad).
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Debemos sobreescribir este método de la clase padre para aplicar una traslación
		al character controller una vez creado (conversión entre coordenadas lógicas y físicas).
		*/
		virtual IPhysicObj* createPhysicEntity(const Core::EntityInfoTable *entityInfo);

		/**
		Creamos un modelo para describir el character controller físico.
		 */
		virtual IPhysicModel* createPhysicModel(const Core::EntityInfoTable *entityInfo);

	private:
		/**
		Tranforma posiciones lógicas a posiciones físicas.
		 */
		Vector3 fromLogicToPhysics(const Vector3 &v) { return Vector3(v.x, v.y + _offsetY, v.z); };

		/**
		Transforma posiciones físicas a posiciones lógicas.
		*/
		Vector3 fromPhysicsToLogic(const Vector3 &v) { return Vector3(v.x, v.y - _offsetY, v.z); };

		/**
		Desplazamiento en el eje Y para transformar entre coordenadas lógicas y coordenadas
		físicas.
		 */
		float _offsetY;

		/**
		Vector de desplazamiento recibido en el último mensaje de tipo AVATAR_WALK. 
		*/
		Vector3 _movement;

		/**
		Indica si el character controller esta apoyado sobre una superficie o cayendo.
		*/
		bool _falling;
	};
}

#endif
