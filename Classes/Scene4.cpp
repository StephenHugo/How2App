#include "Scene4.h"
#include "SimpleAudioEngine.h"
#include "ResourceDefinitions.h"

#include "Scene1.h"

#include "editor-support/spine/json.h"

USING_NS_CC;

Scene* Scene4::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Scene4::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // send to director
    return scene;
}

// on "init" you need to initialize your instance
bool Scene4::init()
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
    script = Json_getItem(chapterScript, "scene 4");
    
    //// background
    
    auto backgroundImage = Sprite::create(BCKIMAGE4);
    
    backgroundImage->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    backgroundImage->setScale( visibleSize.width/backgroundImage->getContentSize().width, 1.0);
                             // visibleSize.height/backgroundImage->getContentSize().height );
    
    this->addChild(backgroundImage,-2);
    
    //// Add Text
    
    this->scheduleOnce(schedule_selector(Scene4::textAppears), SCENETRANSITIONTIME);
    
    return true;
}

void Scene4::gotonextScene(float dt)
{
    
    this->unscheduleAllCallbacks();
    
    auto scene1 = Scene1::createScene();
    
    Director::getInstance()->pushScene(TransitionFlipY::create(SCENETRANSITIONTIME, scene1));
}

void Scene4::textAppears(float dt)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //// get text from json script object
    
    auto textString = Json_getString(script, "4.1", "Go Gators!");
    
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
    
    //// Check if music is playing, then preload and play background music
    
    if(!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BCKMUSIC);
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BCKMUSIC, true); // loops
    }
    
    //// Preload a sound effect
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUNDEFFECT);
    
    //// Add a listener to detect clicks and movements
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Scene4::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool Scene4::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto pos = touch->getLocation();
    
    if ( pos.y/visibleSize.height > 0.78 ) {
        
        //// go to scene 1 if the top of the screen is clicked
        
        this->scheduleOnce(schedule_selector(Scene4::gotonextScene), 0);
        
        return true;
    } else {
        
        //// play sound effect
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUNDEFFECT);
        
        //// generate a sprite that shoots around
        
        auto starSprite = Sprite::create(STARSPRITE);
        
        starSprite->setPosition(pos);
        starSprite->setScale( 0.05*visibleSize.width/starSprite->getContentSize().width, 0.05*visibleSize.width/starSprite->getContentSize().height );
        
        auto fromScreen = EaseExponentialIn::create(MoveTo::create(1, Vec2(visibleSize.width*0.85 + origin.x,visibleSize.height*0.2 + origin.y)));
        
        auto growStar = ScaleTo::create(1, 0.35*visibleSize.width/starSprite->getContentSize().width, 0.35*visibleSize.width/starSprite->getContentSize().height );
        auto spinStar = Repeat::create(RotateBy::create(0.5, 540), 2);
        this->addChild(starSprite, 2);
        
        starSprite->setOpacity(0);
        starSprite->runAction(Sequence::create(Spawn::create(FadeIn::create(0.2), growStar, spinStar, fromScreen, nullptr), RemoveSelf::create(), nullptr));
        
        return true;
    }
}