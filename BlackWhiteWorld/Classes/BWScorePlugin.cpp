//
//  BWScorePlugin.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-6-14.
//
//

#include "BWScorePlugin.h"

using namespace cocos2d;

static BWScorePlugin *scorePlugin;

BWScorePlugin* BWScorePlugin::sharedPlugin(){
    if (!scorePlugin) {
        scorePlugin=new BWScorePlugin();
    }
    return scorePlugin;
}

BWScorePlugin::BWScorePlugin(){
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *sprite=CCSprite::create("scoreBg.png");
    sprite->setPosition(ccp(size.width/2,size.height/2));
    
}

BWScorePlugin::~BWScorePlugin(){
    
}
