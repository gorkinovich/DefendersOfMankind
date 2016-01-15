#include "BehaviorExecutionContext.h"

#include "StringConverter.h"

namespace AI
{

	CBehaviorExecutionContext::CBehaviorExecutionContext(void)
	{
	}

	//--------------------------------------------------------
	
	CBehaviorExecutionContext::~CBehaviorExecutionContext(void)
	{
	}

	//--------------------------------------------------------

	bool CBehaviorExecutionContext::hasAttribute(const std::string &attr) const
	{
		if(_attributes.count(attr))
			return true;
		return false;
	} // hasAttribute

	//--------------------------------------------------------

	void CBehaviorExecutionContext::setData(const std::string &attr, const TContextData & data)
	{
		if(_attributes.count(attr))
			_attributes.erase(attr);
		_attributes.insert(std::pair<std::string, TContextData>(attr, data));
	}

	//--------------------------------------------------------

	void CBehaviorExecutionContext::setStringAttribute(const std::string &attr, const std::string &value)
	{
		TContextData data;
		data._string = value;
		setData(attr, data);
	} // setAttribute

	//--------------------------------------------------------

	const std::string &CBehaviorExecutionContext::getStringAttribute(const std::string &attr) const
	{
		return (*_attributes.find(attr)).second._string;

	} // getStringAttribute

	//--------------------------------------------------------

	void CBehaviorExecutionContext::setIntAttribute(const std::string &attr, int value)
	{
		TContextData data;
		data._int = value;
		setData(attr, data);
	} // getIntAttribute

	//--------------------------------------------------------

	int CBehaviorExecutionContext::getIntAttribute(const std::string &attr) const
	{
		return (*_attributes.find(attr)).second._int;

	} // getIntAttribute

	//--------------------------------------------------------

	float CBehaviorExecutionContext::getFloatAttribute(const std::string &attr) const
	{
		return (*_attributes.find(attr)).second._float;

	} // getFloatAttribute

	//--------------------------------------------------------

	void CBehaviorExecutionContext::setFloatAttribute(const std::string &attr, float value)
	{
		TContextData data;
		data._float = value;
		setData(attr, data);		
	} // getIntAttribute

	//--------------------------------------------------------

	const Vector3 CBehaviorExecutionContext::getVector3Attribute(const std::string &attr) const
	{
		return (*_attributes.find(attr)).second._vector3;
	} // getVector3Attribute

	//--------------------------------------------------------

	void CBehaviorExecutionContext::setVector3Attribute(const std::string &attr, const Vector3 &value)
	{
		TContextData data;
		data._vector3 = value;
		setData(attr, data);
	} // getIntAttribute

	//--------------------------------------------------------

	bool CBehaviorExecutionContext::removeAttribute(const std::string &attr)
	{
		return _attributes.erase(attr) != 0;
	}

	//--------------------------------------------------------

	void* CBehaviorExecutionContext::getUserData(const std::string &attr)
	{
		return (*_attributes.find(attr)).second._userData;
	}

	//--------------------------------------------------------
	
	void CBehaviorExecutionContext::setUserData(const std::string &attr, void *value)
	{
		TContextData data;
		data._userData = value;
		setData(attr, data);
	}

} // namespace AI