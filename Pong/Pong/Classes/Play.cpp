#include "Play.h"
#include "HelloWorldScene.h"
#define toString( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

USING_NS_CC;

cocos2d::Label *scoreboardOne;
cocos2d::Label *scoreboardTwo;
cocos2d::Sprite* ball;
cocos2d::Sprite* paddleOne;
cocos2d::Sprite* paddleTwo;
cocos2d::Sprite* topWall;
cocos2d::Sprite* botWall;
int scoreOne = 0;
int scoreTwo = 0;
int ball_x = 0; 
int ball_y = 0;
int delta_x = 4;
int delta_y = 3;

Scene* Play::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Play::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Play::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    ball_x = visibleSize.width/2 + origin.x; 
    ball_y = visibleSize.height/2 + origin.y;
    
    //Create background
    auto gameBoard = Sprite::create("gameboard.png");
    float scale = MAX(visibleSize.width / gameBoard->getContentSize().width, visibleSize.height / gameBoard->getContentSize().height);
    gameBoard->setScale(scale);
    gameBoard->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(gameBoard, 0);

    topWall = Sprite::create("wall.png");
    topWall->setScaleX((visibleSize.width / topWall->getContentSize().width));
    topWall->setScaleY((visibleSize.height / topWall->getContentSize().height)*.05);
    topWall->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height - topWall->getContentSize().height + origin.y ));
    this->addChild(topWall, 1);    

    botWall = Sprite::create("wall.png");
    botWall->setScaleX((visibleSize.width / botWall->getContentSize().width));
    botWall->setScaleY((visibleSize.height / botWall->getContentSize().height)*.05);
    botWall->setPosition(Vec2(visibleSize.width/2 + origin.x,botWall->getContentSize().height + origin.y));
    this->addChild(botWall, 1);  

    paddleOne = Sprite::create("paddleOne.png");
    paddleOne->setPosition(Vec2(visibleSize.width/10 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(paddleOne, 1); 

    paddleTwo = Sprite::create("paddleTwo.png");
    paddleTwo->setPosition(Vec2(visibleSize.width/1.1 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(paddleTwo, 1); 
    
    ball = Sprite::create("ball.png");
    ball->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(ball, 1); 

    auto homeMenu = MenuItemFont::create("Menu", CC_CALLBACK_1(Play::toHome, this));    
    homeMenu->setPosition(Point(visibleSize.width/2,(visibleSize.height/4)*1));
    auto newMenu = Menu::create(homeMenu,NULL);
    newMenu->setPosition(Vec2::ZERO);
    this->addChild(newMenu,2);     
    
    std::string sOne = toString(scoreOne);
    scoreboardOne = Label::createWithTTF(sOne, "fonts/Marker Felt.ttf", 15);
    scoreboardOne->setPosition(Vec2(visibleSize.width / 3, visibleSize.height/1.1));
    this->addChild(scoreboardOne, 1);

    std::string sTwo = toString(scoreTwo);
    scoreboardTwo = Label::createWithTTF(sTwo, "fonts/Marker Felt.ttf", 15);
    scoreboardTwo->setPosition(Vec2(visibleSize.width / 1.5 , visibleSize.height/1.1));
    this->addChild(scoreboardTwo, 1);
    
    this->scheduleUpdate();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Play::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool Play::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int x = touch->getLocation().x;
    int y = touch->getLocation().y;
    
    if(x<visibleSize.width/2 + origin.x){//left side
        paddleOne->setPosition(Vec2(visibleSize.width/10 + origin.x,y));
    }else{//right side
        paddleTwo->setPosition(Vec2(visibleSize.width/1.1 + origin.x,y)); 
    }
    
    return true;
}

void Play::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Play::toHome(cocos2d::Ref *pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Play::update(float dt) 
{
    Rect ballRect = ball->getBoundingBox(); 
    Rect pOneRect = paddleOne->getBoundingBox(); 
    Rect pTwoRect = paddleTwo->getBoundingBox(); 
    Rect tWallRect = topWall->getBoundingBox(); 
    Rect bWallRect = botWall->getBoundingBox(); 
    if(ballRect.intersectsRect(tWallRect)){
        delta_y = - delta_y;
    }
    if(ballRect.intersectsRect(bWallRect)){
        delta_y = - delta_y;
    }    
    if(ballRect.intersectsRect(pOneRect)){
        delta_x = - delta_x;
    }    
    if(ballRect.intersectsRect(pTwoRect)){
        delta_x = - delta_x;
    }        

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    if(ball_x>visibleSize.width+origin.x){
        ball_x = visibleSize.width/2 + origin.x; 
        ball_y = visibleSize.height/2 + origin.y;   
        delta_x = - delta_x; 
        scoreOne++; 
        scoreboardOne->removeFromParentAndCleanup(true);
        std::string sOne = toString(scoreOne);
        scoreboardOne = Label::createWithTTF(sOne, "fonts/Marker Felt.ttf", 15);
        scoreboardOne->setPosition(Vec2(visibleSize.width / 3, visibleSize.height/1.1));
        this->addChild(scoreboardOne, 1);
    }
    
    if(ball_x<origin.x){
        ball_x = visibleSize.width/2 + origin.x; 
        ball_y = visibleSize.height/2 + origin.y;
        delta_x = - delta_x; 
        scoreTwo++;;
        scoreboardTwo->removeFromParentAndCleanup(true);        
        std::string sTwo = toString(scoreTwo);
        scoreboardTwo = Label::createWithTTF(sTwo, "fonts/Marker Felt.ttf", 15);
        scoreboardTwo->setPosition(Vec2(visibleSize.width / 1.5 , visibleSize.height/1.1));
        this->addChild(scoreboardTwo, 1);
    }
       
    if(scoreOne%5==0&&scoreTwo%5==0){
        ball_x += delta_x;         
    }else if(scoreOne%5==0&&scoreOne!=0){
        ball_x += delta_x+3;    
    }else if(scoreTwo%5==0&&scoreTwo!=0){
        ball_x += delta_x-3;        
    }else{
        ball_x += delta_x;        
    }    
    
    ball_y += delta_y;
    ball->setPosition(Vec2(ball_x, ball_y));
}