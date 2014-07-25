//
//  Highscore.cpp
//  Balloons
//
//  Created by ts95 on 23.07.14.
//
//

#include "Highscore.h"

USING_NS_CC;

#define DEFAULT_HIGHSCORE 0

void Highscore::setHighscore(int newHighscore)
{
    UserDefault::getInstance()->setIntegerForKey("Highscore", newHighscore);
}

int Highscore::getHighscore()
{
    return UserDefault::getInstance()->getIntegerForKey("Highscore", DEFAULT_HIGHSCORE);
}