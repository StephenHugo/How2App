#include "Scene3.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Scene4.h"

#include "editor-support/spine/json.h"

USING_NS_CC;

Scene* Scene3::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Scene3::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Scene3::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// set up the script
    
    auto scriptString = cocos2d::__String::createWithContentsOfFile(THESCRIPT);
    auto fullScript = Json_create(scriptString->getCString());
    auto chapterScript = Json_getItem(fullScript, "English");
    script = Json_getItem(chapterScript, "scene 3");
    
    //// background
    
    auto backgroundImage = Sprite::create(BCKIMAGE3);
    
    backgroundImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    backgroundImage->setScale( visibleSize.width/backgroundImage->getContentSize().width, 1.0);
                             // visibleSize.height/backgroundImage->getContentSize().height );
    
    this->addChild(backgroundImage,-2);
    
    //// Add Text
    
    this->scheduleOnce(schedule_selector(Scene3::textAppears), SCENETRANSITIONTIME);
    
    return true;
}

void Scene3::gotonextScene(float dt)
{
    
    this->unscheduleAllCallbacks();
    
    auto scene4 = Scene4::createScene();
    
    Director::getInstance()->pushScene(TransitionSlideInR::create(SCENETRANSITIONTIME, scene4));
}

void Scene3::textAppears(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "3.1", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.15 + origin.x, visibleSize.height*3.75/20 + origin.y));
    text->setAnchorPoint(Vec2(0, 1));
    
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    this->addChild(text,43);
    
    auto appear = FadeIn::create(0.2);
    text->runAction(appear);
    
    //// Add a listener to detect clicks and movements
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        text->setOpacity(0);
        text->runAction(FadeIn::create(0.2));
        
        auto pos = touch->getLocation();
        
        text->setPosition(Vec2(pos.x, pos.y));
        text->setColor(cocos2d::Color3B(255 - 255*pos.x/visibleSize.width,
                                        255*pos.y/visibleSize.height,
                                        255*pos.x/visibleSize.width));
        
        return true;
    };
    
    listener->onTouchMoved = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        //// move the text around
        auto pos = touch->getLocation();
    
        text->setPosition(Vec2(pos.x, pos.y));
        text->setColor(cocos2d::Color3B(255 - 255*pos.x/visibleSize.width,
                                        255*pos.y/visibleSize.height,
                                        255*pos.x/visibleSize.width));
        
        return true;
    };
    
    listener->onTouchEnded = [=](cocos2d::Touch *touch, cocos2d::Event *event){
        
        // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CH5AUDIOCHIMES);
        
        auto y = touch->getLocation().y/visibleSize.height;
        
        //// go to scene 4 if text was moved to the top of the screen
        
        if ( y > 0.78 ) {
            
            this->scheduleOnce(schedule_selector(Scene3::gotonextScene), 0);
            
            return true;
        }
        
        text->setOpacity(0);
        text->runAction(FadeIn::create(0.2));
        text->setPosition(Vec2(visibleSize.width*0.15 + origin.x, visibleSize.height*3.75/20 + origin.y));
        text->setColor(cocos2d::Color3B::WHITE);
        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}