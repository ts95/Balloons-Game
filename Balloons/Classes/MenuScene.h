//
//  MenuScene.h
//  Balloons
//
//  Created by ts95 on 01.07.14.
//
//

#ifndef __Balloons__MenuScene__
#define __Balloons__MenuScene__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MenuScene);
	
};

#endif /* defined(__Balloons__MenuScene__) */
