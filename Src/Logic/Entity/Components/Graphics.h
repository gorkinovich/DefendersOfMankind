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
@file Graphics.h

Contiene la declaración del componente que controla la representación
gráfica de la entidad.

@see Logic::Graphics
@see Core::Component

@author David Llansó
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
	Componente que se encarga de la representación gráfica de una entidad.
	En concreto se encarga de las entidades con representaciones gráficas
	no animadas. Para otros tipos de representaciones hay otros componentes
	que especializan éste (AnimatedGraphics y CStaticGraphics).
	<p>
	Acepta mensajes de cambio de posición y orientación (matriz de 
	transformación) mediante el mensaje SET_TRANSFORM.
	
    @ingroup logicGroup
	@author David Llansó García
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
		Destructor (virtual); Quita de la escena y destruye la entidad gráfica.
		*/
		virtual ~Graphics();
		
		/**
		Retorna el puntero a la entidad gráfica
		@param puntero a la entidad gráfica
		*/
		Core::GraphicEntity* getGraphicsEntity() { return _graphicsEntity; }

	protected:

		/**
		Constructor por defecto; inicializa los atributos a su valor por defecto.
		*/
		Graphics(const std::string & name) : Component(name), _graphicsEntity(0) {}

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
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::Entity). Toma del mapa el atributo
		model con el modelo que se deberá cargar e invoca al método virtual
		createGraphicsEntity() para generar la entidad gráfica.
		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const Core::EntityInfoTable *entityInfo);

		/**
		Método virtual que construye la entidad gráfica de la entidad. Otros
		componentes pueden sobreescribirlo para inicializar otro tipo de
		entidades gráficas (animadas, etc.).
		@param entityInfo Información de construcción del objeto leído del fichero de disco.
		@return Entidad gráfica creada, NULL si hubo algún problema.
		*/
		virtual Core::GraphicEntity* createGraphicsEntity(const Core::EntityInfoTable *entityInfo);

		/**
		Atributo con el nombre del modelo gráfico de la entidad.
		*/
		std::string _model;
		
		/**
		Entidad gráfica.
		*/
		Core::GraphicEntity *_graphicsEntity;

		/**
		Escena gráfica donde se encontrarán las representaciones gráficas de
		las entidades. La guardamos para la destrucción de la entidad gráfica.
		*/
		Core::Scene* _scene;
	};
}

#endif
