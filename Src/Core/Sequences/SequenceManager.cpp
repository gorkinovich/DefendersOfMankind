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

#include <algorithm>

#include "Core/Sequences/SequenceManager.h"
#include "Core/Sequences/ISequence.h"

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	//********************************************************************************************************
	// Campos estáticos
	//********************************************************************************************************

	SequenceManager * SequenceManager::_instance = new SequenceManager();

	//********************************************************************************************************
	// Métodos
	//********************************************************************************************************

	void SequenceManager::initialize() {
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::release() {
		removeAllSequences();
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::update(unsigned int lastInterval) {
		// Recorremos la lista de secuencias que están siendo ejecutadas.
		SequenceListIterator i = _updateableSequences.begin();
		SequenceListIterator end = _updateableSequences.end();
		for(; i != end; ++i) {
			// Actualizamos la lógica interna de la secuencia.
			(*i)->update(lastInterval);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SequenceManager::playSequence(const std::string & name) {
		// Buscamos la secuencia en la tabla de secuencias registradas.
		SequenceTableIterator victim = _sequences.find(name);
		if(victim != _sequences.end()) {
			// Si la encuentra iniciamos la secuencia y la añadimos a la lista de las que están siendo ejecutadas.
			victim->second->start();
			_updateableSequences.push_back(victim->second);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::stopSequence(const std::string & name) {
		// Buscamos la secuencia en la tabla de secuencias registradas.
		SequenceTableIterator victim = _sequences.find(name);
		if(victim != _sequences.end()) {
			// Buscamos dentro de la lista de secuencias que están siendo ejecutadas.
			SequenceListIterator end = _updateableSequences.end();
			SequenceListIterator finalVictim = std::find(_updateableSequences.begin(), end, victim->second);
			if(finalVictim != end) {
				// Si encontramos la secuencia dentro de la lista, la paramos y la sacamos de la lista.
				(*finalVictim)->stop();
				_updateableSequences.erase(finalVictim);
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::stopAllSequences() {
		// Recorremos la lista de secuencias que están siendo ejecutadas.
		SequenceListIterator i = _updateableSequences.begin();
		SequenceListIterator end = _updateableSequences.end();
		SequenceListIterator victim;
		while(i != end) {
			// Paramos la secuencia y la borramos de la lista.
			victim = i++;
			(*victim)->stop();
			_updateableSequences.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	bool SequenceManager::isPlayingSequence(const std::string & name) {
		SequenceTableIterator victim = _sequences.find(name);
		return (victim != _sequences.end()) ? victim->second->isPlaying() : false;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SequenceManager::containsSequence(const std::string & name) {
		return _sequences.count(name) > 0;
	}

	//--------------------------------------------------------------------------------------------------------

	ISequence * SequenceManager::getSequence(const std::string & name) {
		SequenceTableIterator victim = _sequences.find(name);
		return (victim != _sequences.end()) ? victim->second : 0;
	}

	//--------------------------------------------------------------------------------------------------------

	bool SequenceManager::addSequence(ISequence * sequence) {
		return sequence ? addSequence(sequence->getName(), sequence) : false;
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::removeSequence(ISequence * sequence) {
		if(sequence) removeSequence(sequence->getName());
	}

	//--------------------------------------------------------------------------------------------------------

	bool SequenceManager::addSequence(const std::string & name, ISequence * sequence) {
		// Si no hay ya una secuencia con el mismo nombre registrada, la añadimos a la tabla.
		if(!containsSequence(name)) {
			_sequences[name] = sequence;
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::removeSequence(const std::string & name) {
		// Buscamos la secuencia en la tabla.
		SequenceTableIterator victim = _sequences.find(name);
		if(victim != _sequences.end()) {
			// Paramos la secuencia si se está ejecutando.
			if(isPlayingSequence(name)) stopSequence(name);
			// Borramos la secuencia de la memoria y de la tabla.
			delete victim->second;
			_sequences.erase(victim);
		}
	}

	//--------------------------------------------------------------------------------------------------------

	void SequenceManager::removeAllSequences() {
		// Paramos todas las secuencias que se estén ejecutando.
		stopAllSequences();
		// Recorremos la tabla de secuencias registradas.
		SequenceTableIterator i = _sequences.begin();
		SequenceTableIterator end = _sequences.end();
		SequenceTableIterator victim;
		while(i != end) {
			// Borramos la secuencia de la memoria.
			victim = i++;
			delete victim->second;
			// Borramos la secuencia de la tabla.
			_sequences.erase(victim);
		}
	}
}
