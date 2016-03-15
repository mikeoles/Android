#include "HelloWorldScene.h"
#include "Play.h"
#include "Options.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::Options(cocos2d::Ref *pSender)
{
    auto scene = Options::createScene();
    Director::getInstance()->replaceScene(scene);
}

void HelloWorld::Play(cocos2d::Ref *pSender)
{
    auto scene = Play::createScene();
    Director::getInstance()->replaceScene(scene);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto home = Sprite::create("homeScreen.png");
    float scale = MAX(visibleSize.width / home->getContentSize().width, visibleSize.height / home->getContentSize().height);
    home->setScale(scale);
    home->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(home, 0);
  
    auto menuOptions = MenuItemFont::create("Options",CC_CALLBACK_1(HelloWorld::Options,this));
    auto menuPlay = MenuItemFont::create("Play",CC_CALLBACK_1(HelloWorld::Play,this));
    
    menuOptions->setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*2));
    menuPlay->setPosition(Point(visibleSize.width/2,(visibleSize.height/5)*1));
    
    auto newMenu = Menu::create(menuOptions,menuPlay,NULL);
    newMenu->setPosition(Vec2::ZERO);
    this->addChild(newMenu,1); 
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
