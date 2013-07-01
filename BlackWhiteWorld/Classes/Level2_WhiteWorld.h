//
//  Level2_WhiteWorld.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#ifndef __BlackWhiteWorld__Level2_WhiteWorld__
#define __BlackWhiteWorld__Level2_WhiteWorld__

#include "cocos2d.h"
#include "BWPlayer.h"
#include "BWWorldInterface.h"
#include "BWGameDefine.h"
#include "BWGameStep.h"
#include "BWTime.h"
#include "BWPausePlugin.h"

class BWLevel2Scene;

using namespace cocos2d;

class Level2WW:public cocos2d::CCObject,public BWWorldInterface{
private:
    bool bw_isFristCreate;
    BWGameStep *steps[3];
    BWLevel2Scene *level2;
public:
    Level2WW(){bw_isFristCreate=true;};
    virtual ~Level2WW(){};
    
    void createWorld(cocos2d::CCLayer *layer,int deathCount);
    void deleteWorld(cocos2d::CCLayer *layer);
    void update(BWTime *time,cocos2d::CCLayer *layer);
    void updatesteps();
    
    void setDeathCount(int count,BWBasicScene *scene);
    
    // a selector callback
    void menuRestartCallBack(CCObject* pSender);
    void menuPauseCallBack(CCObject* pSender);
    
    bool playerIsContactKey(CCLayer* layer,BWPlayer *player);
    bool playerIsContactProds(CCLayer* layer,BWPlayer *player);
    bool playerIsContactDoor(CCLayer* layer,BWPlayer *player);
    
    void createSteps(BWLevel2Scene *scene);
    void createProds(BWLevel2Scene* scene);
    
    void setLevelScene(BWLevel2Scene* level){this->level2=level;};
    BWLevel2Scene* getLevelScene(){return this->level2;};
};

#endif /* defined(__BlackWhiteWorld__Level2_WhiteWorld__) */
