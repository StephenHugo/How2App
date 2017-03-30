#ifndef __SCENE3_H__ // <- this changes
#define __SCENE3_H__ // <- this changes

#include "cocos2d.h"
#include "editor-support/spine/json.h"

class Scene3 : public cocos2d::Layer // <- this changes
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void gotonextScene(float dt); // <- this changes
    
    
    
    void textAppears(float dt);
    
    
    
    // loads the script
    Json *script;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene3); // <- this changes
};

#endif // __SCENE3_H__ // <- this changes
