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

class PlayScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC(PlayScene);

	int getRisingSpeed();
	
	int getLayers();
	
	/**
	 * Increments the score.
	 */
	void incrementScore();
	
	/**
	 * Gets called when a balloon is popped.
	 */
	void balloonPopped(Balloon *balloon);
	
	/**
	 * Starts the game. The game ends when gameover() is called.
	 */
	void startGame();
	
	/**
	 * Gets called when the game is lost.
	 */
	void gameover();
    
private:
	int m_score;
	bool m_isGameRunning;
};

#endif /* defined(__Balloons__PlayScene__) */
