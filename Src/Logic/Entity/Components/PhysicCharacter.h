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
@file PhysicCharacter.h

Contiene la declaraci�n del componente que se utiliza para representar jugadores y enemigos en
el mundo f�sico usando character controllers.

@see Logic::PhysicCharacter
@see Logic::PhysicEntity

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/
#ifndef __Logic_PhysicCharacter_H
#define __Logic_PhysicCharacter_H

#include "PhysicEntity.h"

namespace Logic {
	/**
	Componente que se utiliza para representar jugadores y enemigos en el mundo f�sico usando 
	character controllers.<p>
	Este componente recibe mensajes de tipo AVATAR_WALK para mover el controller.<p>
	La implementaci�n de esta clase tambi�n gestiona las diferencias que existen entre el
	sistema de coordenadas local (SCL) l�gico y f�sico. El SCL que usa la l�gica para cada 
	entidad tiene su origen en la parte inferior de la entidad (los pies), mientras que 
	PhysX coloca por defecto el origen del SCL en medio de la entidad. En las entidades 
	f�sicas simples, podemos unificar los dos SCL definiendo una sencilla traslaci�n en la 
	descripci�n del modelo, pero la descripci�n de los character controllers no ofrece esa
	posibilidad. La conclusi�n es que debemos realizar una traslaci�n en el eje Y para 
	convertir entre coordenadas l�gicas y coordenadas f�sicas.
	
    @ingroup logicGroup
	@author Antonio S�nchez Ruiz-Granados
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

		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		virtual void prepareUpdate(unsigned int lastInterval);
		/**
		Este m�todo se invoca en cada ciclo de la simulaci�n y hace lo siguiente:
		<ul>
		<li>Actualiza la posici�n de la entidad l�gica usando la informaci�n que proporciona
		el motor de f�sica.</li>
		<li>Mueve el character controller de acuerdo al �ltimo mensaje AVATAR_WALK recibido.</li>
		</ul>
		<p>
		Necesitamos sobreescribir el m�todo de la clase padre ya que los character controllers
		no tienen orientaci�n, s�lo posici�n. Adem�s debemos aplicar una traslaci�n al vector 
		de posici�n que obtenemos de PhysX ya que la l�gica y la f�sica	usan distintos or�genes 
		para los sistemas de coordenadas locales a la entidad (en los pies / en el centro de la 
		entidad).
		*/
		virtual void update(unsigned int lastInterval);

		/**
		Debemos sobreescribir este m�todo de la clase padre para aplicar una traslaci�n
		al character controller una vez creado (conversi�n entre coordenadas l�gicas y f�sicas).
		*/
		virtual IPhysicObj* createPhysicEntity(const Core::EntityInfoTable *entityInfo);

		/**
		Creamos un modelo para describir el character controller f�sico.
		 */
		virtual IPhysicModel* createPhysicModel(const Core::EntityInfoTable *entityInfo);

	private:
		/**
		Tranforma posiciones l�gicas a posiciones f�sicas.
		 */
		Vector3 fromLogicToPhysics(const Vector3 &v) { return Vector3(v.x, v.y + _offsetY, v.z); };

		/**
		Transforma posiciones f�sicas a posiciones l�gicas.
		*/
		Vector3 fromPhysicsToLogic(const Vector3 &v) { return Vector3(v.x, v.y - _offsetY, v.z); };

		/**
		Desplazamiento en el eje Y para transformar entre coordenadas l�gicas y coordenadas
		f�sicas.
		 */
		float _offsetY;

		/**
		Vector de desplazamiento recibido en el �ltimo mensaje de tipo AVATAR_WALK. 
		*/
		Vector3 _movement;

		/**
		Indica si el character controller esta apoyado sobre una superficie o cayendo.
		*/
		bool _falling;
	};
}

#endif
