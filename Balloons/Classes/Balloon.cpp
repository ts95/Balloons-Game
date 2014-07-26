//
//  Balloon.cpp
//  Balloons
//
//  Created by ts95 on 24.07.14.
//
//

#include "Balloon.h"
#include "Util.h"

USING_NS_CC;

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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BALLOON_POP_SOUND_PATH);
	
	setName(BALLOON_TAG_NAME);
	
	initWithFile(Balloon::getTexturePath(m_layers));
	
	setScale(0.25);
	
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(-50, 150);
	bezier.controlPoint_2 = Vec2(+50, 150 * 2);
	bezier.endPosition = Vec2(0, 450);
	
	float x = Util::random(100, Director::getInstance()->getVisibleSize().width - 100);
	Point initialPosition(x, -10);
	setPosition(initialPosition);
	
	setOpacity(0);
	
	runAction(FadeIn::create(0.5));
	
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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BALLOON_POP_SOUND_PATH);
	
	m_layers--;
	
	if (m_layers == 0) {
		removeFromParent();
	} else {
		setTexture(Balloon::getTexturePath(m_layers));
	}
}