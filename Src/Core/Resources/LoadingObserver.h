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

#ifndef __CORE_LOADINGOBSERVER_H__
#define __CORE_LOADINGOBSERVER_H__

//************************************************************************************************************
// Includes
//************************************************************************************************************

#include <vector>

//************************************************************************************************************
// Core
//************************************************************************************************************

namespace Core {
	class GenericApplication;
	class ILoadingListener;
	class Clock;

	/**
	 * Esta clase representa un gestor para observar un proceso de carga.
	 */
	class LoadingObserver {
	public:
		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Obtiene el listener de la carga actual para estar informado del avance.
		 */
		inline const ILoadingListener * getListener() const { return _listener; }

		/**
		 * Modifica el listener de la carga actual para estar informado del avance.
		 */
		inline void setListener(ILoadingListener * value) { _listener = value; }

		/**
		 * Obtiene el número de secciones en el proceso de carga.
		 */
		inline unsigned int getNumberOfSections() const { return _operationsBySector.size(); }

		/**
		 * Modifica el número de secciones en el proceso de carga.
		 * @remark Esta operación borra toda la información anterior.
		 */
		void setNumberOfSections(unsigned int value);

		/**
		 * Obtiene el número de operaciones en una sección del proceso de carga.
		 */
		inline unsigned int getNumberOfOperations(unsigned int section) const {
			return _operationsBySector.size() > section ? _operationsBySector[section] : 0;
		}

		/**
		 * Modifica el número de operaciones en una sección del proceso de carga.
		 */
		void setNumberOfOperations(unsigned int section, unsigned int value);

		/**
		 * Obtiene si el proceso de carga ha finalizado.
		 */
		bool isLoadingFinished() const;

		/**
		 * Obtiene la sección actual del proceso de carga.
		 */
		inline unsigned int getCurrentSection() const { return _currentSection; }

		/**
		 * Obtiene la operación actual en la sección actual del proceso de carga.
		 */
		inline unsigned int getCurrentOperation() const { return _currentOperation; }

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Devuelve la instancia del singleton.
		 */
		inline static LoadingObserver * GetInstance() {
			return _instance;
		}

		/**
		 * Comunica al gestor que el proceso de carga ha empezado.
		 * @param numberOfSections El número de secciones que tiene el proceso.
		 * @param listener El listener que recibe los eventos del proceso.
		 */
		void startLoading(unsigned int numberOfSections, ILoadingListener * listener = 0);

		/**
		 * Comunica al gestor que una operación de carga ha terminado.
		 */
		void operationFinished();

		/**
		 * Comunica al gestor que el proceso de carga ha terminado.
		 */
		void endLoading();

		//----------------------------------------------------------------------------------------------------
		// Destructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Destructor del objeto.
		 */
		virtual ~LoadingObserver() {}

	private:
		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Este tipo representa una tabla de cantidad de operaciones por sector.
		 */
		typedef std::vector<unsigned int> OperationsBySectorTable;

		//----------------------------------------------------------------------------------------------------
		// Propiedades
		//----------------------------------------------------------------------------------------------------

		/**
		 * Modifica el reloj interno de la aplicación.
		 */
		inline void setClock(Clock * value) { _clock = value; }

		//----------------------------------------------------------------------------------------------------
		// Campos
		//----------------------------------------------------------------------------------------------------

		/**
		 * La instancia del objeto.
		 */
		static LoadingObserver * _instance;

		/**
		 * El listener de la carga actual para estar informado del avance.
		 */
		ILoadingListener * _listener;

		/**
		 * La tabla que contiene la cantidad de operaciones por sector.
		 */
		OperationsBySectorTable _operationsBySector;

		/**
		 * La sección actual del proceso de carga.
		 */
		unsigned int _currentSection;

		/**
		 * La operación actual en la sección actual del proceso de carga.
		 */
		unsigned int _currentOperation;

		/**
		 * El reloj interno de la aplicación.
		*/
		Clock * _clock;

		//----------------------------------------------------------------------------------------------------
		// Métodos
		//----------------------------------------------------------------------------------------------------

		/**
		 * Actualiza la lógica interna de la aplicación cuando se está en un proceso de carga.
		 */
		void update();

		//----------------------------------------------------------------------------------------------------
		// Constructor
		//----------------------------------------------------------------------------------------------------

		/**
		 * Construye un nuevo objeto.
		 */
		LoadingObserver() : _listener(0), _currentSection(0), _currentOperation(0), _clock(0) {}

		friend class Core::GenericApplication;
	};
}

#endif
