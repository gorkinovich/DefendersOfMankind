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

#ifndef __Logic_Generator_H
#define __Logic_Generator_H

#include "Core/Math.h"
#include "Core/Entities/Component.h"

namespace Logic {
	class Generator : public Core::Component
	{
	public:
		ComponentCreateMethod(Generator);

		//Esto lo llevan todos los componentes
		Generator() : Component("Generator"), _childCount(0), _lapse(0) {}
		virtual ~Generator();

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
		virtual void update(unsigned int lastInterval);

		/*
		 * Genera entidades a partir de un mensaje CREATE_CHILD
		 */
		void generate(const Core::SmartMessage & message);

		/**
		 * Este tipo representa un conjunto de cadenas.
		 */
		typedef std::set<std::string> StringSet;

	private:

		/**
		 * Tabla hash que contiene la información de los hijos que genera la entidad
		 */
		typedef std::map<std::string, Core::EntityInfoTable*> TChildrenInfo;
		typedef TChildrenInfo::iterator TChildrenInfoIterator;

		TChildrenInfo _childrenInfo;

		//Parámetros que se utilizarán para generar entidades nuevas
		int _childCount;
		Vector3 _childPosition;
		float _lapse, _interval;

		/*
		 * Daño inicial del hijo generado, para guardar en el power up DAMAGEUP
		 */
		float _initialDamage;
		//Core::EntityInfoTable *_entityInProgress;
	};
}

#endif
