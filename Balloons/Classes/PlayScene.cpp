//
//  PlayScene.cpp
//  Balloons
//
//  Created by ts95 on 23.07.14.
//
//

#include "PlayScene.h"
#include "Highscore.h"
#include "HighscoreScene.h"
#include "Util.h"

USING_NS_CC;

#define SPAWN_BALLOONS_ACTION_TAG 0

#define SCORE_LABEL_NAME "ScoreLabel"

Scene * PlayScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayScene::create();
    scene->addChild(layer);
    return scene;
}

bool PlayScene::init()
{
	if (!LayerColor::initWithColor(Color4B(50, 50, 255, 255))) {
		return false;
	}
	
	setColor(Color3B(50, 50, 200));
	
	// Events
	auto touchEventListener = EventListenerTouchAllAtOnce::create();
	touchEventListener->onTouchesBegan = [this](const std::vector<Touch *> &touches, Event *event) {
		// Balloon touch events
		std::for_each(touches.begin(), touches.end(), [this](Touch *touch) {
			enumerateChildren(BALLOON_TAG_NAME, [this, touch](Node *node) -> bool {
				if (node->getBoundingBox().containsPoint(touch->getLocation())) {
					balloonPopped((Balloon *)node);
					return true;
				} else {
					gameover();
					return true;
				}
				return false;
			});
		});
	};
	Director::getInstance()
		->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(touchEventListener, this);

	auto keyboardEventListener = EventListenerKeyboard::create();
	keyboardEventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
		// Back button on Android
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		}
	};
	Director::getInstance()
		->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);
	
	auto scoreLabel = Label::create();
	scoreLabel->setName(SCORE_LABEL_NAME);
	scoreLabel->setSystemFontSize(100);
	scoreLabel->setPosition(Director::getInstance()->getVisibleSize().width / 2,
							Director::getInstance()->getVisibleSize().height - 100);
	
	addChild(scoreLabel);
	
	startGame();
	
    return true;
}

float PlayScene::getRisingSpeed()
{
	float base = 1.5;
	float variance = Util::randomf() * 0.5;
	float risingSpeed = (-0.005 * m_score) + base - variance;
	if (risingSpeed < 0.55) {
		risingSpeed = 0.55;
	}
	return risingSpeed;
}

int PlayScene::getLayers()
{
	int layers = 1;
	if (m_score >= 20) {
		layers = Util::random(1, 3);
	} else if (m_score >= 10) {
		layers = Util::random(1, 2);
	}
	return layers;
}

void PlayScene::incrementScore()
{
	m_score++;
	auto scoreLabel = (Label *) getChildByName(SCORE_LABEL_NAME);
	scoreLabel->setString(StringUtils::format("%d", m_score));
}

void PlayScene::resetScore()
{
	m_score = 0;
	auto scoreLabel = (Label *) getChildByName(SCORE_LABEL_NAME);
	scoreLabel->setString(StringUtils::format("%d", m_score));
}

void PlayScene::balloonPopped(Balloon *balloon)
{
	incrementScore();
	balloon->pop();
}

void PlayScene::startGame()
{
	resetScore();
	
	m_isGameRunning = true;
	
	auto spawnBalloon = CallFunc::create([this]() {
		auto balloon = Balloon::create(getRisingSpeed(), getLayers());
		
		auto detectLostBalloon = CallFunc::create([this, balloon]() {
			float screenHeight = Director::getInstance()->getVisibleSize().height;
			if (balloon->getPositionY() > screenHeight - 30) {
				balloon->removeFromParent();
				
				if (m_isGameRunning) {
					gameover();
				}
			}
		});
		
		balloon->runAction(RepeatForever::create(Sequence::create(detectLostBalloon, NULL)));
		
		addChild(balloon);
	});

	auto sequence = Sequence::create(spawnBalloon, DelayTime::create(1),
									 spawnBalloon, DelayTime::create(0.5), NULL);
	auto spawnBalloons = RepeatForever::create(sequence);
	spawnBalloons->setTag(SPAWN_BALLOONS_ACTION_TAG);

	runAction(spawnBalloons);
}

void PlayScene::gameover()
{
	m_isGameRunning = false;
	
	stopActionByTag(SPAWN_BALLOONS_ACTION_TAG);
	
	int score = m_score;
	
	resetScore();
	
	if (score > Highscore::getHighscore()) {
		Highscore::setHighscore(score);
	}
	
	Director::getInstance()->replaceScene(HighscoreScene::createScene(score));
}