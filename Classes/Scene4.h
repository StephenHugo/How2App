#ifndef __SCENE4_H__ // <- this changes
#define __SCENE4_H__ // <- this changes

#include "cocos2d.h"
#include "editor-support/spine/json.h"

class Scene4 : public cocos2d::Layer // <- this changes
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotonextScene(float dt); // <- this changes
    
    
    
    void textAppears(float dt);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event); // <- new
    
    // loads the script
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene4); // <- this changes
};

#endif // __SCENE4_H__ // <- this changes
