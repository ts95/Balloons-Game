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

// 1 layer: blue
// 2 layers: red
// 3 or more layers: black

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
	
	/**
	 * Sets the texture of the balloon based on the current layer.
	 */
	void setTextureForLayer();

private:
    Balloon(int risingSpeed, int layers);
	
	int m_risingSpeed, m_layers;
};

#endif /* defined(__Balloons__Balloon__) */
