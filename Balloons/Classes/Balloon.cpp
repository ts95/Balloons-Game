//
//  Balloon.cpp
//  Balloons
//
//  Created by ts95 on 24.07.14.
//
//

#include "Balloon.h"

USING_NS_CC;

#define POP_SOUND_PATH "BalloonPop.mp3"

#define BLUE_TEXTURE_PATH "BalloonBlue.png"
#define RED_TEXTURE_PATH "BalloonRed.png"
#define BLACK_TEXTURE_PATH "BalloonBlack.png"

Balloon * Balloon::create(int risingSpeed, int layers)
{
	auto ret = new Balloon(risingSpeed, layers);
	if (ret) {
		ret->autorelease();
	} else {
		CC_SAFE_RELEASE_NULL(ret);
	}
	return ret;
}

Balloon::Balloon(int risingSpeed, int layers)
: m_risingSpeed(risingSpeed), m_layers(layers)
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(POP_SOUND_PATH);
	
	setName(BALLOON_TAG_NAME);
	
	setTextureForLayer();
	
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(-50, 150);
	bezier.controlPoint_2 = Vec2(+50, 150 * 2);
	bezier.endPosition = Vec2(0, 450);
	
	auto sequence = Sequence::create(BezierBy::create(risingSpeed, bezier), NULL);
    auto action = RepeatForever::create(sequence);
    runAction(action);
}

int Balloon::getRisingSpeed()
{
	return m_risingSpeed;
}

int Balloon::getLayers()
{
	return m_layers;
}

void Balloon::pop()
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(POP_SOUND_PATH);
	
	m_layers--;
	
	if (m_layers == 0) {
		removeFromParent();
	} else {
		setTextureForLayer();
	}
}

void Balloon::setTextureForLayer()
{
	switch (m_layers) {
		case 1:
			setTexture(BLUE_TEXTURE_PATH);
			break;
		case 2:
			setTexture(RED_TEXTURE_PATH);
			break;
		default:
			setTexture(BLACK_TEXTURE_PATH);
			break;
	}
}