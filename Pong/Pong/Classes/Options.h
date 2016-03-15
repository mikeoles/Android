#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__

#include "cocos2d.h"

class Options : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Options);
    
    void SongOne(cocos2d::Ref *pSender);
    void SongTwo(cocos2d::Ref *pSender);   
    void toHome(cocos2d::Ref *pSender);
    
};

#endif // __HELLOWORLD_SCENE_H__
