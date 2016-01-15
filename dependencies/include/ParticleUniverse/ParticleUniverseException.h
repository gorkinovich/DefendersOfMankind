/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2010 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_EXCEPTION_H__
#define __PU_EXCEPTION_H__

#include "OgreException.h"

namespace ParticleUniverse
{
	// If the Ogre renderer is replaced by another renderer, the type below must be re-implemented.
	typedef Ogre::Exception Exception;
	#define EXCEPT(num, desc, src) throw Ogre::ExceptionFactory::create( \
		Ogre::ExceptionCodeType<num>(), desc, src, __FILE__, __LINE__ );
}
#endif
