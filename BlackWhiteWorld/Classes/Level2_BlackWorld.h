//
//  Level2_BlackWorld.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#ifndef __BlackWhiteWorld__Level2_BlackWorld__
#define __BlackWhiteWorld__Level2_BlackWorld__

#include "cocos2d.h"
#include "BWWorldInterface.h"
#include "BWPlayer.h"
#include "BWGameStep.h"
#include "BWGameDefine.h"
#include "BWPausePlugin.h"

class BWLevel2Scene;

class Level2BW:public cocos2d::CCObject,private BWWorldInterface{
private:
    bool bw_isFristCreate;
    BWGameStep *steps[5];
    CCSprite* wheels[4];
    BWLevel2Scene *level2;
public:
    Level2BW(){bw_isFristCreate=true;}
    virtual ~Level2BW(){};
    
    void createWorld(cocos2d::CCLayer *layer,int deathCount);
    void deleteWorld(cocos2d::CCLayer *layer);
    void update(BWTime *time,cocos2d::CCLayer *layer);
    
    // a selector callback
    void menuRestartCallBack(CCObject* pSender);
    void menuPauseCallBack(CCObject* pSender);
    
    void createSteps(BWLevel2Scene* scene);
    void createWheel(BWLevel2Scene* scene);
    void createDoorKey(BWLevel2Scene* scene);
    
    bool playerIsContactKey(CCLayer* layer,BWPlayer *player);
    bool playerIsContactWheel(cocos2d::CCLayer *layer, BWPlayer *player);
    bool playerIsContactDoorKey(CCLayer* layer,BWPlayer *player);
    
    void setDeathCount(int count,BWBasicScene *scene);
    
    void setLevelScene(BWLevel2Scene* level){this->level2=level;};
    BWLevel2Scene* getLevelScene(){return this->level2;};
};

#endif /* defined(__BlackWhiteWorld__Level2_BlackWorld__) */
