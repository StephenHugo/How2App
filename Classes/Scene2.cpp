#include "Scene2.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Scene3.h"

#include "editor-support/spine/json.h"

USING_NS_CC;

Scene* Scene2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Scene2::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Scene2::init()
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
    script = Json_getItem(chapterScript, "scene 2");
    
    //// background
    
    auto backgroundImage = Sprite::create(BCKIMAGE2);
    
    backgroundImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    backgroundImage->setScale( visibleSize.width/backgroundImage->getContentSize().width, 1.0);
                             // visibleSize.height/backgroundImage->getContentSize().height );
    
    this->addChild(backgroundImage,-2);
    
    //// Add Text
    
    this->scheduleOnce(schedule_selector(Scene2::textAppears), SCENETRANSITIONTIME);
    
    return true;
}

void Scene2::gotonextScene(cocos2d::Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    auto scene3 = Scene3::createScene();
    
    Director::getInstance()->pushScene(TransitionFadeBL::create(SCENETRANSITIONTIME, scene3));
}

void Scene2::repeatScene(cocos2d::Ref* pSender)
{
    
    this->unscheduleAllCallbacks();
    
    auto scene2 = Scene2::createScene();
    
    Director::getInstance()->pushScene(TransitionFade::create(SCENETRANSITIONTIME, scene2));
}

void Scene2::textAppears(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.1", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    text->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*2.15/20 + origin.y));
    
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    
    text->setColor(cocos2d::Color3B::WHITE);
    text->setOpacity(0);
    
    this->addChild(text,43);
    
    auto appear = FadeIn::create(0.2);
    text->runAction(Sequence::create(appear, DelayTime::create( 1.5*SCENETRANSITIONTIME ), FadeOut::create(0.2), RemoveSelf::create(), nullptr));
    
    //// Add a menu
    
    this->scheduleOnce(schedule_selector(Scene2::menuAppears), 1.5*SCENETRANSITIONTIME + 0.4);
    
}

void Scene2::menuAppears(float dt)
{

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "2.2", "Go Gators!");
    
    //// set up text
    
    auto text = Label::createWithTTF(textString, FELTFONT, visibleSize.height*TEXTSIZE);
    
    text->setWidth(0.6*visibleSize.width);
    text->setHeight(visibleSize.height*3.2/20);
    text->setColor(cocos2d::Color3B::WHITE);
    
    //// Use the text label as a menu item
    
    auto repeatItem = MenuItemLabel::create(
                                            text,
                                            CC_CALLBACK_1(Scene2::gotonextScene, this));
    
    repeatItem->setPosition(Vec2(visibleSize.width*0.45 + origin.x, visibleSize.height*2.15/20 + origin.y));
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Scene2::repeatScene, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width ,
                                origin.y + closeItem->getContentSize().height));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, repeatItem, NULL);
    menu->setPosition(Vec2::ZERO);
    
    menu->setOpacity(0);
    
    this->addChild(menu, 1);
    
    //// Have the menu fade in
    
    auto appear = FadeIn::create(0.2);
    menu->runAction(appear);
    
    //// Do not schedule a new callback or transition. Wait for user input via the menu.
    
}