//
//  Level1_blackWorld.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-27.
//
//

#ifndef __BlackWhiteWorld__Level1_blackWorld__
#define __BlackWhiteWorld__Level1_blackWorld__

#include "cocos2d.h"
#include "BWWorldInterface.h"
#include "BWPlayer.h"
#include "BWGameStep.h"
#include "BWGameDefine.h"
#include "BWSoundManager.h"
#include "BWPausePlugin.h"

using namespace cocos2d;

class BWLevel1Scene;

class Level1BW:public cocos2d::CCObject,public BWWorldInterface{
private:
    bool bw_isFristCreate;
    BWGameStep *steps[4];
    CCSprite* wheels[3];
    BWLevel1Scene *level1;
public:
    Level1BW(){bw_isFristCreate=true;};
    virtual ~Level1BW(){};
    
    bool playerIsContactKey(CCLayer* layer,BWPlayer *player);
    bool playerIsContactWheel(CCLayer* layer,BWPlayer *player);
    bool playerIsContactDoorKey(CCLayer* layer,BWPlayer *player);
    
    void createWorld(cocos2d::CCLayer *layer,int deathCount);
    void deleteWorld(cocos2d::CCLayer *layer);
    void update(BWTime *time,cocos2d::CCLayer *layer);
    
    void setDeathCount(int count,BWBasicScene *scene);
    
    // a selector callback
    void menuRestartCallBack(CCObject* pSender);
    void menuPauseCallBack(CCObject* pSender);
    
    void createSteps(BWLevel1Scene* scene);
    void createWheel(BWLevel1Scene* scene);
    void createDoorKey(BWLevel1Scene* scene);
    
    void setLevelScene(BWLevel1Scene* level){this->level1=level;};
    BWLevel1Scene* getLevelScene(){return this->level1;};
};

#endif /* defined(__BlackWhiteWorld__Level1_blackWorld__) */
