#include "Scene1.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Scene2.h"

USING_NS_CC;

Scene* Scene1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Scene1::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Scene1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// background
    
    auto backgroundImage = Sprite::create(BCKIMAGE1);
    
    backgroundImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    backgroundImage->setScale( visibleSize.width/backgroundImage->getContentSize().width, 1.0);
                              // visibleSize.height/backgroundImage->getContentSize().height );
    
    this->addChild(backgroundImage,-2);
    
    //// Transition to next Scene
    
    this->scheduleOnce(schedule_selector(Scene1::gotonextScene), SCENETRANSITIONTIME+1);
    
    return true;
}

void Scene1::gotonextScene(float dt)
{
    
    auto Scene2 = Scene2::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, Scene2));
    
}