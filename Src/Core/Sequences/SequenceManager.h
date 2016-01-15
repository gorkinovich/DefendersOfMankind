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

#ifndef __CORE_SEQUENCEMANAGER_H__
#define __CORE_SEQUENCEMANAGER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <map>
#include <list>
#include <string>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class ISequence;

	/**
	 * Esta clase representa al gestor de secuencias, que son cadenas de acciones en un orden determinado
	 * para realizar operaciones complejas durante el juego como los cut-scenes.
	 */
	class SequenceManager {
	public:
		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static SequenceManager * GetInstance() {
			return _instance;
		}

		/**
		 * Inicializa el gestor.
		 */
		void initialize();

		/**
		 * Finaliza el gestor.
		 */
		void release();

		/**
		 * Actualiza la lógica interna del gestor.
		 * @param lastInterval El tiempo total del último intervalo entre frame y frame.
		 */
		void update(unsigned int lastInterval);

		/**
		 * Inicia la ejecución de una secuencia del gestor.
		 * @param name El nombre de la secuencia.
		 * @return Devuelve true si la secuencia es ejecutada.
		 */
		bool playSequence(const std::string & name);

		/**
		 * Para la ejecución de una secuencia del gestor.
		 * @param name El nombre de la secuencia.
		 */
		void stopSequence(const std::string & name);

		/**
		 * Para la ejecución de todas las secuencias del gestor.
		 */
		void stopAllSequences();

		/**
		 * Comprueba si una secuencia del gestor se está ejecutando.
		 * @param name El nombre de la secuencia.
		 * @return Devuelve true si la secuencia se está ejecutando.
		 */
		bool isPlayingSequence(const std::string & name);

		/**
		 * Comprueba si una secuencia existe dentro del gestor.
		 * @param name El nombre de la secuencia.
		 * @return Devuelve true si la secuencia está registrada.
		 */
		bool containsSequence(const std::string & name);

		/**
		 * Obtiene una secuencia del gestor.
		 * @param name El nombre de la secuencia.
		 * @return La secuencia si la encuentra o sino devuelve NULL.
		 */
		ISequence * getSequence(const std::string & name);

		/**
		 * Añade una secuencia al gestor.
		 * @param sequence La secuencia a añadir.
		 * @return Devuelve true si la secuencia es añadida.
		 */
		bool addSequence(ISequence * sequence);

		/**
		 * Elimina una secuencia del gestor.
		 * @param sequence La secuencia a eliminar.
		 * @remark Elimina de la memoria la secuencia borrada.
		 */
		void removeSequence(ISequence * sequence);

		/**
		 * Añade una secuencia al gestor.
		 * @param name El nombre de la secuencia a añadir.
		 * @param sequence La secuencia a añadir.
		 * @return Devuelve true si la secuencia es añadida.
		 */
		bool addSequence(const std::string & name, ISequence * sequence);

		/**
		 * Elimina una secuencia del gestor.
		 * @param name El nombre de la secuencia a eliminar.
		 * @remark Elimina de la memoria la secuencia borrada.
		 */
		void removeSequence(const std::string & name);

		/**
		 * Elimina todas las secuencias del gestor.
		 * @remark Elimina de la memoria las secuencias borradas.
		 */
		void removeAllSequences();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~SequenceManager() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Tipos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de secuencias.
		 */
		typedef std::map<std::string, ISequence *> SequenceTable;

		/**
		 * Este tipo representa un iterador de una tabla de secuencias.
		 */
		typedef SequenceTable::iterator SequenceTableIterator;

		/**
		 * Este tipo representa una lista de secuencias.
		 */
		typedef std::list<ISequence *> SequenceList;

		/**
		 * Este tipo representa un iterador de una lista de secuencias.
		 */
		typedef SequenceList::iterator SequenceListIterator;

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static SequenceManager * _instance;

		/**
		 * La tabla de secuencias.
		 */
		SequenceTable _sequences;

		/**
		 * La lista de secuencias que están siendo ejecutadas.
		 */
		SequenceList _updateableSequences;

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		SequenceManager() {}
	};
}

#endif
