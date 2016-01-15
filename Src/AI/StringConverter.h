#ifndef __AI_StringConverter_H
#define __AI_StringConverter_H

#include <sstream>

namespace AI
{

	template <class T>
	inline std::string to_string (const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

} //namespace AI

#endif __AI_StringConverter_H
