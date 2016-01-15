/**
 * @file BehaviorExecutionContext.h
 *
 * Implementaci�n de un contexto de ejecuci�n simple para las m�quinas de estado,
 * los BTs y las acciones latentes.
 *
 * @author "Gonzalo Fl�rez"
 * @date 11/04/2011
 */

#pragma once

#ifndef __AI_BehaviorExecutionContext_H
#define __AI_BehaviorExecutionContext_H

#include <string>
#include "Core/Math.h"

namespace AI
{

	class CBehaviorExecutionContext
	{
	public:
		CBehaviorExecutionContext(void);
		~CBehaviorExecutionContext(void);

		/**
		Dice si se ha a�adido un atributo.

		@param attr Nombre del atributo.
		@return true si contiene el atributo.
		*/
		bool hasAttribute(const std::string &attr) const;

		/**
		A�ade un atributo de tipo cadena a la lista de atributos de la entidad.

		@param attr Nombre del atributo a a�adir.
		@param value Valor del atributo.
		*/
		void setStringAttribute(const std::string &attr, const std::string &value);

		/**
		Elimina un atributo de la lista

		@param attr Nombre del atributo.
		@return true si el atributo se elimina correctamente.
		*/
		bool removeAttribute(const std::string &attr);

		/**
		Recupera un atributo previamente a�adido. Si no existe devuelve "".

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		const std::string &getStringAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido de tipo entero. Si no existe 
		salta una excepci�n.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		int getIntAttribute(const std::string &attr) const;

		/**
		A�ade un atributo de tipo entero a la lista de atributos de la entidad.

		@param attr Nombre del atributo a a�adir.
		@param value Valor del atributo.
		*/
		void setIntAttribute(const std::string &attr, int value);

		/**
		Recupera un atributo previamente a�adido de tipo flotante. Si no existe 
		salta una excepci�n.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		float getFloatAttribute(const std::string &attr) const;

		/**
		A�ade un atributo de tipo float a la lista de atributos de la entidad.

		@param attr Nombre del atributo a a�adir.
		@param value Valor del atributo.
		*/
		void setFloatAttribute(const std::string &attr, float value);

		/**
		Recupera un atributo previamente a�adido de tipo posici�n. Si no existe 
		salta una excepci�n. Las posiciones deben tener el formato "(x,y,z)".

		@param attr Nombre del atributo a recuperar.
		@param x Valor del eje X.
		@param y Valor del eje Y.
		@param z Valor del eje Z.
		*/
		const Vector3 getVector3Attribute(const std::string &attr) const;

		/**
		A�ade un atributo de tipo float a la lista de atributos de la entidad.

		@param attr Nombre del atributo a a�adir.
		@param value Valor del atributo.
		*/
		void setVector3Attribute(const std::string &attr, const Vector3 &value);

		void setUserData(const std::string &attr, void* value);
		
		void* getUserData(const std::string &attr);

	private:
		struct TContextData{
			int _int;
			float _float;
			std::string _string;
			Vector3 _vector3;
			void* _userData;
		} ;

		std::map<std::string, TContextData> _attributes;

		void setData(const std::string &attr, const TContextData & data);

	}; // class CBTExecutionContext

} //namespace AI

#endif __AI_BehaviorExecutionContext_H
