#ifndef __SCENE2_H__ // <- this changes
#define __SCENE2_H__ // <- this changes

#include "cocos2d.h"
#include "editor-support/spine/json.h" // <- new

class Scene2 : public cocos2d::Layer // <- this changes
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotonextScene(cocos2d::Ref* pSender); // <- this changes
    
    void repeatScene(cocos2d::Ref* pSender); // <- new
    
    void textAppears(float dt); // <- new
    
    void menuAppears(float dt); // <- new
    
    // loads the script
    Json *script; // <- new
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene2); // <- this changes
};

#endif // __SCENE2_H__ // <- this changes
