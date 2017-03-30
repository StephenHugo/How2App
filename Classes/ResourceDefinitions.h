#ifndef __RESOURCE_DEFINITIONS_H__
#define __RESOURCE_DEFINITIONS_H__

#include "cocos2d.h"

    // These resources are generally used throughout the app

const std::string FELTFONT = "fonts/Marker Felt.ttf";

const float TEXTSIZE = 1.0f/20; // This was chosen so that 3 lines of text fits into text boxes

const float TEMPO = 1.0f / 1.0f; // works inversely to control app speed: 1/10 == 10x faster

const float SCENETRANSITIONTIME = 2.0f*TEMPO; // times for screen wipes

    // This defines the path to the script

const std::string THESCRIPT = "scripts/Session2Script.txt";

    // These define the audio resources

const char BCKMUSIC[26] = "audio/BackgroundMusic.wav";

const char SOUNDEFFECT[22] = "audio/SoundEffect.wav";

    // These resources are background images

const std::string BCKIMAGE1 = "res/Scene1Background.png";
const std::string BCKIMAGE2 = "res/Scene2Background.png";
const std::string BCKIMAGE3 = "res/Scene3Background.png";
const std::string BCKIMAGE4 = "res/Scene4Background.png";

    // These resources are sprites

const std::string STARSPRITE = "res/StarSprite.png";

#endif // __RESOURCE_DEFINITIONS_H__
