#ifndef __SCENE1_H__ // <- this changes
#define __SCENE1_H__ // <- this changes

#include "cocos2d.h"


class Scene1 : public cocos2d::Layer // <- this changes
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init(); 
    
    void gotonextScene(float dt); // <- new
    
    
    
    
    
    
    
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene1); // <- this changes
};

#endif // __SCENE1_H__ // <- this changes
