//
//  Util.h
//  Balloons
//
//  Created by ts95 on 23.07.14.
//
//

#ifndef Balloons_Util_h
#define Balloons_Util_h

#include "cocos2d.h"

namespace Util
{
    USING_NS_CC;
    
    inline void quit()
    {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
    }
	
	inline float randomf()
	{
		return rand() / (float) RAND_MAX;
	}
	
	inline bool randomb()
	{
		return randomf() > 0.5;
	}
	
	inline int random(int low, int high)
	{
		return (int)(randomf() * (high - low + 1) + low);
	}
}

#endif
