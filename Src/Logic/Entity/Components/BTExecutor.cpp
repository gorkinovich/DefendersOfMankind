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

/*
Componente encargado de ejecutar un árbol de comportamiento (BT)
*/

#include "BTExecutor.h"

#include "Core/Data/EntityInfoTable.h"
#include "AI/BehaviorExecutionContext.h"
#include "AI/DoMBehaviourTrees.h"


namespace Logic
{
	//---------------------------------------------------------

	BTExecutor::BTExecutor() : Component("BTExecutor"), _bt(0) , _context(0)
	{
		// Creamos y guardamos un contexto de ejecución para el BT
		_context = new AI::CBehaviorExecutionContext();
	}

	//---------------------------------------------------------

	BTExecutor::~BTExecutor(void)
	{ 
		// Liberamos el contexto de ejecución
		delete _context;
		_context = 0;

		// Liberamos el BT
		if (_bt != NULL)
		{
			delete _bt;
			_bt = 0;
		}

	}

	//---------------------------------------------------------

	bool BTExecutor::spawn(const Core::EntityInfoTable *entityInfo)
	{
		assert(_owner && "The component does not have an entity...");

		std::string BTname;
		int targetQ1 = 0;
		int targetQ2 = 0;

		// Añadimos una referencia a la entidad en el contexto
		_context->setUserData("entity", _owner);

		// Leemos los datos del descriptor
		if(entityInfo->hasAttribute("BTname") && entityInfo->hasAttribute("targetQ1")
			&& entityInfo->hasAttribute("targetQ2") )
		{
			BTname = entityInfo->getAttribute("BTname");
			targetQ1 = entityInfo->getAttributeAsInteger("targetQ1");
			targetQ2 = entityInfo->getAttributeAsInteger("targetQ2");
		}
		else return false;

		// Guardamos en el contexto el cuadrante objetivo inicial
		_context->setIntAttribute("targetQ1", targetQ1);
		_context->setIntAttribute("targetQ2", targetQ2);

		// Creamos el BT
		_bt = AI::CBehaviourTreeFactory::getBehaviourTree(BTname, _owner);

		// Establecer el contexto de ejecución del BT
		_bt->useContext(_context);


		return true;
	}

	//---------------------------------------------------------

	void BTExecutor::update(unsigned int lastInterval)
	{
		// Invocar al método de la clase padre (IMPORTANTE)
		Component::update(lastInterval);

		// Ordenamos ejecutar un paso más del BT
		AI::BEHAVIOR_STATUS status = _bt->execute(NULL);
		
		// Si la ejecución del BT ha terminado... lo iniciamos de nuevo desde el principio
		if (status != AI::BT_RUNNING) {
			_bt->init(NULL);
		}
		
	}

	//---------------------------------------------------------

	bool BTExecutor::acceptMessage(const Core::SmartMessage & message)
	{
		// Llamamos al "accept" del nodo del BT que se esta ejecutando actualmente
		return _bt->accept(message);
	}

	//---------------------------------------------------------

	void BTExecutor::processMessage(const Core::SmartMessage & message)
	{
		// Llamamos al "process" del nodo del BT que se está ejecutando actualmente
		_bt->process(message);
	}


} // namespace Logic
