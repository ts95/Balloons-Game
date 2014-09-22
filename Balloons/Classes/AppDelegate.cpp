#include "AppDelegate.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) {
        glview = GLView::create("Balloons");
        director->setOpenGLView(glview);
    }
    
    glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
    
    const double FPS = 60;
    
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / FPS);
    
    auto scene = MenuScene::createScene();
	director->runWithScene(scene);

	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.2);
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
