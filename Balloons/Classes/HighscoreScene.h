//
//  HighscoreScene.h
//  Balloons
//
//  Created by ts95 on 27.07.14.
//
//

#ifndef __Balloons__HighscoreScene__
#define __Balloons__HighscoreScene__

#include "cocos2d.h"

class HighscoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene(int score);
	static HighscoreScene *create(int score);
	
	HighscoreScene(int score);
	
	virtual bool init();
	
private:
	int m_score;
};

#endif /* defined(__Balloons__HighscoreScene__) */
