#include "Options.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Options::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Options::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void Options::SongOne(cocos2d::Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("RichForever.mp3", true);
}

void Options::SongTwo(cocos2d::Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("SomethingNew.mp3", true);
}

void Options::toHome(cocos2d::Ref *pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

// on "init" you need to initialize your instance
bool Options::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto playOne = MenuItemFont::create("Play Song 1",CC_CALLBACK_1(Options::SongOne,this));
    auto playTwo = MenuItemFont::create("Play Song 2",CC_CALLBACK_1(Options::SongTwo,this));
    auto homeMenu = MenuItemFont::create("Menu", CC_CALLBACK_1(Options::toHome, this));
    
    playOne->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*3));
    playTwo->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*2));
    homeMenu->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*1));
    
    auto newMenu = Menu::create(playOne,playTwo,homeMenu,NULL);
    newMenu->setPosition(Vec2::ZERO);
    this->addChild(newMenu,1);     
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("somethingNew.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("richForever.mp3");
    
    return true;
}


void Options::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
