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
@file Graphics.h

Contiene la declaraci�n del componente que controla la representaci�n
gr�fica de la entidad.

@see Logic::Graphics
@see Core::Component

@author David Llans�
@date Agosto, 2010
*/
#ifndef __Logic_Graphics_H
#define __Logic_Graphics_H

#include "Core/Entities/Component.h"

namespace Core {
	class GraphicEntity;
	class Scene;
}

namespace Logic {
	/**
	Componente que se encarga de la representaci�n gr�fica de una entidad.
	En concreto se encarga de las entidades con representaciones gr�ficas
	no animadas. Para otros tipos de representaciones hay otros componentes
	que especializan �ste (AnimatedGraphics y CStaticGraphics).
	<p>
	Acepta mensajes de cambio de posici�n y orientaci�n (matriz de 
	transformaci�n) mediante el mensaje SET_TRANSFORM.
	
    @ingroup logicGroup
	@author David Llans� Garc�a
	@date Agosto, 2010
	*/
	class Graphics : public Core::Component
	{
	public:
		ComponentCreateMethod(Graphics);

		/**
		Constructor por defecto; inicializa los atributos a su valor por defecto.
		*/
		Graphics() : Component("Graphics"), _graphicsEntity(0) {}

		/**
		Destructor (virtual); Quita de la escena y destruye la entidad gr�fica.
		*/
		virtual ~Graphics();
		
		/**
		Retorna el puntero a la entidad gr�fica
		@param puntero a la entidad gr�fica
		*/
		Core::GraphicEntity* getGraphicsEntity() { return _graphicsEntity; }

	protected:

		/**
		Constructor por defecto; inicializa los atributos a su valor por defecto.
		*/
		Graphics(const std::string & name) : Component(name), _graphicsEntity(0) {}

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
		Inicializaci�n del componente, utilizando la informaci�n extra�da de
		la entidad le�da del mapa (Maps::Entity). Toma del mapa el atributo
		model con el modelo que se deber� cargar e invoca al m�todo virtual
		createGraphicsEntity() para generar la entidad gr�fica.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa L�gico en el que se registrar� el objeto.
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Cierto si la inicializaci�n ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		M�todo virtual que construye la entidad gr�fica de la entidad. Otros
		componentes pueden sobreescribirlo para inicializar otro tipo de
		entidades gr�ficas (animadas, etc.).
		@param entityInfo Informaci�n de construcci�n del objeto le�do del fichero de disco.
		@return Entidad gr�fica creada, NULL si hubo alg�n problema.
		*/
		virtual Core::GraphicEntity* createGraphicsEntity(const Core::EntityInfoTable *entityInfo);

		/**
		Atributo con el nombre del modelo gr�fico de la entidad.
		*/
		std::string _model;
		
		/**
		Entidad gr�fica.
		*/
		Core::GraphicEntity *_graphicsEntity;

		/**
		Escena gr�fica donde se encontrar�n las representaciones gr�ficas de
		las entidades. La guardamos para la destrucci�n de la entidad gr�fica.
		*/
		Core::Scene* _scene;
	};
}

#endif
