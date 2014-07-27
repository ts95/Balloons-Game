//
//  HighscoreScene.cpp
//  Balloons
//
//  Created by ts95 on 27.07.14.
//
//

#include "HighscoreScene.h"
#include "Highscore.h"
#include "PlayScene.h"

USING_NS_CC;

Scene * HighscoreScene::createScene(int score)
{
	auto scene = Scene::create();
	auto layer = HighscoreScene::create(score);
	scene->addChild(layer);
	return scene;
}

HighscoreScene * HighscoreScene::create(int score)
{
	HighscoreScene *pRet = new HighscoreScene(score);
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		return pRet = nullptr;
	}
}

HighscoreScene::HighscoreScene(int score)
: m_score(score)
{
}

bool HighscoreScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	float width = Director::getInstance()->getVisibleSize().width;
	float height = Director::getInstance()->getVisibleSize().height;
	
	auto scoreLabel = Label::create();
	scoreLabel->setPosition(width / 2, height * 0.85);
	scoreLabel->setSystemFontSize(80);
	scoreLabel->setString(StringUtils::format("Score %d", m_score));
	addChild(scoreLabel);
	
	auto highscoreLabel = Label::create();
	highscoreLabel->setPosition(width / 2, height * 0.7);
	highscoreLabel->setSystemFontSize(80);
	highscoreLabel->setString(StringUtils::format("Highscore %d", Highscore::getHighscore()));
	addChild(highscoreLabel);
	
	auto menu = Menu::create();
	
	MenuItemFont::setFontSize(100);
	
	auto playAgainMenuItem = MenuItemFont::create("Play again", [](Ref *ref) {
		Director::getInstance()->replaceScene(PlayScene::createScene());
	});
	playAgainMenuItem->setPosition(10, 0);
	menu->addChild(playAgainMenuItem);
	
	addChild(menu);
	
	return true;
}
