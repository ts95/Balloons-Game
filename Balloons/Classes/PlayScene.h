//
//  PlayScene.h
//  Balloons
//
//  Created by ts95 on 23.07.14.
//
//

#ifndef __Balloons__PlayScene__
#define __Balloons__PlayScene__

#include "cocos2d.h"
#include "Balloon.h"

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(PlayScene);

	int getRisingSpeed();
	
	int getLayers();
	
	/**
	 * Spawn a new balloon into the scene.
	 */
	void spawnBalloon();
	
	/**
	 * Increments the score for a given balloon.
	 * Balloons with multiple layers yield more points.
	 */
	void incrementScore(Balloon *balloon);
	
	/**
	 * Gets called when a balloon is popped.
	 */
	void balloonPopped(Balloon *balloon);
    
private:
	int m_score;
};

#endif /* defined(__Balloons__PlayScene__) */
