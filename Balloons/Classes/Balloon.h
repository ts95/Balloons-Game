//
//  Balloon.h
//  Balloons
//
//  Created by ts95 on 24.07.14.
//
//

#ifndef __Balloons__Balloon__
#define __Balloons__Balloon__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define BALLOON_POP_SOUND_PATH "BalloonPop.mp3"

#define BALLOON_BLUE_TEXTURE_PATH "BalloonBlue.png"
#define BALLOON_RED_TEXTURE_PATH "BalloonRed.png"
#define BALLOON_BLACK_TEXTURE_PATH "BalloonBlack.png"

#define BALLOON_TAG_NAME "Balloon"

class Balloon : public cocos2d::Sprite
{
public:
    static Balloon * create(int risingSpeed, int layers);
	
	/**
	 * Returns the rate at which the balloon is rising upwards.
	 */
	int getRisingSpeed();

	/**
	 * Returns the number of layers the balloon has.
	 */
	int getLayers();
	
	/**
	 * Makes a popping sound and removes a layer of the balloon.
	 * The balloon is removed once all the layers are popped.
	 */
	void pop();

private:
	inline static std::string getTexturePath(int layers)
	{
		switch (layers) {
			case 1:
				return BALLOON_BLUE_TEXTURE_PATH;
			case 2:
				return BALLOON_RED_TEXTURE_PATH;
			default:
				return BALLOON_BLACK_TEXTURE_PATH;
		}
	}
	
    Balloon(int risingSpeed, int layers);
	
	int m_risingSpeed, m_layers;
};

#endif /* defined(__Balloons__Balloon__) */
