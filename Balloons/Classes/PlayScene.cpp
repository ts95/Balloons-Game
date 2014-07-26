//
//  PlayScene.cpp
//  Balloons
//
//  Created by ts95 on 23.07.14.
//
//

#include "PlayScene.h"
#include "Util.h"

USING_NS_CC;

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
			Director::getInstance()->popScene();
		}
	};
	Director::getInstance()
		->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);
	
	startGame();
	
    return true;
}

int PlayScene::getRisingSpeed()
{
	float speed = (-0.1 * m_score) + 1.5;
	if (speed < 0.8) {
		speed = 0.8;
	}
	return speed;
}

int PlayScene::getLayers()
{
	int layers = 1;
	if (m_score > 20) {
		layers = Util::random(1, 3);
	} else if (m_score > 10) {
		layers = Util::random(1, 2);
	}
	return 3;//layers;
}

void PlayScene::incrementScore()
{
	m_score++;
}

void PlayScene::balloonPopped(Balloon *balloon)
{
	incrementScore();
	balloon->pop();
}

void PlayScene::startGame()
{
	m_score = 0;
	m_isGameRunning = true;
	
	auto spawnBalloon = CallFunc::create([this]() {
		auto balloon = Balloon::create(getRisingSpeed(), getLayers());
		
		auto detectLostBalloon = CallFunc::create([this, balloon]() {
			if (balloon->getPositionY() > Director::getInstance()->getVisibleSize().height + 100) {
				balloon->removeFromParent();
				
				if (m_isGameRunning) {
					//gameover();
				}
			}
		});
		
		balloon->runAction(detectLostBalloon);
		addChild(balloon);
	});
	
	auto spawnBalloons = RepeatForever::create(Sequence::create(spawnBalloon, DelayTime::create(1.5), NULL));
	runAction(spawnBalloons);
}

void PlayScene::gameover()
{
	m_isGameRunning = false;
	
	
}