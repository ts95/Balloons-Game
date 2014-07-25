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
    if (!Layer::init()) {
        return false;
    }
	
	// Initialize member variables
	m_score = 0;
	
	// Events
	auto touchEventListener = EventListenerTouchAllAtOnce::create();
	touchEventListener->onTouchesBegan = [this](const std::vector<Touch *> &touches,
									Event *event) {
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
	keyboardEventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode,
												  cocos2d::Event *event) {
		// Back button on Android
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			Director::getInstance()->popScene();
		}
	};
	Director::getInstance()
		->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);
	
    return true;
}

int PlayScene::getRisingSpeed()
{
	float speed = (-0.02 * m_score) + 1.5;
	if (speed < 0.55) {
		speed = 0.55;
	}
	return speed;
}

int PlayScene::getLayers()
{
	int layers = 1;
	
	if (m_score > 30) {
		layers = Util::random(1, 3);
	} else if (m_score > 20) {
		layers = Util::random(1, 2);
	}
	
	return layers;
}

void PlayScene::spawnBalloon()
{
	auto balloon = Balloon::create(getRisingSpeed(), getLayers());
	addChild(balloon);
}

void PlayScene::incrementScore(Balloon *balloon)
{
	m_score += balloon->getLayers();
}

void PlayScene::balloonPopped(Balloon *balloon)
{
	incrementScore(balloon);
	balloon->pop();
}