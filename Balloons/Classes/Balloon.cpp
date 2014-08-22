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

#define COUNTER_LABEL_NAME "CounterLabel"

inline static std::string getTexturePath(int layers)
{
	switch (layers) {
		case 1:
			return BALLOON_RED_TEXTURE_PATH;
		case 2:
			return BALLOON_BLUE_TEXTURE_PATH;
		case 3:
			return BALLOON_BLACK_TEXTURE_PATH;
	}
	return BALLOON_BLUE_TEXTURE_PATH;
}

Balloon * Balloon::create(float risingSpeed, int layers)
{
	auto ret = new Balloon(risingSpeed, layers);
	if (ret) {
		ret->autorelease();
	} else {
		CC_SAFE_RELEASE_NULL(ret);
	}
	return ret;
}

Balloon::Balloon(float risingSpeed, int layers)
: m_risingSpeed(risingSpeed), m_layers(layers)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BALLOON_POP_SOUND_PATH);
	
	setName(BALLOON_TAG_NAME);
	
	initWithFile(getTexturePath(m_layers));
	
	setScale(0.25);
	
	// Add counter (counts down for each layer the balloon has)
	Label *counterLabel = Label::create();
	counterLabel->setName(COUNTER_LABEL_NAME);
	counterLabel->setSystemFontSize(130);
	counterLabel->setString(StringUtils::format("%d", m_layers));
	counterLabel->setPosition(getSpriteFrame()->getRect().getMidX(),
							  getSpriteFrame()->getRect().getMaxY() - 280);
	addChild(counterLabel);
	
	float x = Util::random(100, Director::getInstance()->getVisibleSize().width - 100);
	Point initialPosition(x, -100);
	setPosition(initialPosition);
	
	// Slow down balloons with more layers than 1
	m_risingSpeed += layers - 1;
	
	setOpacity(0);
	
	runAction(FadeIn::create(1));
	
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(-50, 150);
	bezier.controlPoint_2 = Vec2(+50, 150 * 2);
	bezier.endPosition = Vec2(0, 450);
	
	auto sequence = Sequence::create(BezierBy::create(risingSpeed, bezier), NULL);
    auto action = RepeatForever::create(sequence);
	
    runAction(action);
}

float Balloon::getRisingSpeed()
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
		setTexture(getTexturePath(m_layers));
		Label *counterLabel = (Label *) getChildByName(COUNTER_LABEL_NAME);
		counterLabel->setString(StringUtils::format("%d", m_layers));
	}
}