//
//  Highscore.h
//  Balloons
//
//  Created by ts95 on 23.07.14.
//
//

#ifndef __Balloons__Highscore__
#define __Balloons__Highscore__

#include "cocos2d.h"

class Highscore
{
public:
    static void setHighscore(int newHighscore);
    static int  getHighscore();
    
private:
    Highscore();
};

#endif /* defined(__Balloons__Highscore__) */
