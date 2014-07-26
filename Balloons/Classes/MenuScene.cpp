//
//  MenuScene.cpp
//  Balloons
//
//  Created by ts95 on 01.07.14.
//
//

#include "MenuScene.h"
#include "PlayScene.h"
#include "Util.h"

USING_NS_CC;

#define ITEM_FONT_SIZE 120

Scene * MenuScene::createScene()
{
   auto scene = Scene::create();
   auto layer = MenuScene::create();
   scene->addChild(layer);
   return scene;
}

bool MenuScene::init()
{
   if (!Layer::init()) {
	  return false;
   }
   
   auto keyboardEventListener = EventListenerKeyboard::create();
   keyboardEventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
	  // Back button on Android
	  if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		 Util::quit();
	  }
   };
   Director::getInstance()
	  ->getEventDispatcher()
	  ->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);
   
   MenuItemFont::setFontSize(ITEM_FONT_SIZE);
   
   auto *playMenuItem = MenuItemFont::create("Play", [](Ref *ref) {
	  Director::getInstance()->pushScene(PlayScene::createScene());
   });
   playMenuItem->setPosition(10, 50 + ITEM_FONT_SIZE);
   
   auto *quitMenuItem = MenuItemFont::create("Exit", [](Ref *ref) {
	  Util::quit();
   });
   quitMenuItem->setPosition(10, 10);
   
   auto *menu = Menu::create();
   menu->addChild(playMenuItem);
   menu->addChild(quitMenuItem);
   
   this->addChild(menu);
   
   return true;
}

