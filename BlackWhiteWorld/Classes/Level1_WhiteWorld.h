//
//  Level1_WhiteWorld.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-27.
//
//

#ifndef __BlackWhiteWorld__Level1_WhiteWorld__
#define __BlackWhiteWorld__Level1_WhiteWorld__

#include "cocos2d.h"
#include "BWPlayer.h"
#include "BWWorldInterface.h"
#include "BWGameDefine.h"
#include "BWGameStep.h"
#include "BWTime.h"
#include "BWSoundManager.h"
#include "BWPausePlugin.h"
#include "BWWorldComponent.h"

class BWLevel1Scene;

class Level1WW:public cocos2d::CCObject,public BWWorldInterface{
private:
    bool bw_isFristCreate;
    BWGameStep *steps[5];
    BWLevel1Scene *level1;
public:
    Level1WW(){
        bw_isFristCreate=true;
    };
    virtual ~Level1WW(){
    
    };
    
    bool getIsFristCreate(){return bw_isFristCreate;};
    
    bool playerIsContactKey(CCLayer* layer,BWPlayer *player);
    bool playerIsContactProds(CCLayer* layer,BWPlayer *player);
    bool playerIsContactDoor(CCLayer* layer,BWPlayer *player);
    
    void createWorld(cocos2d::CCLayer *layer,int deathCount);
    void deleteWorld(cocos2d::CCLayer *layer);
    void update(BWTime *time,cocos2d::CCLayer *layer);
    
    void createSteps(BWLevel1Scene* scene);
    void createProds(BWLevel1Scene* scene);
    
    void setDeathCount(int count,BWBasicScene *scene);
    
    // a selector callback
    void menuRestartCallBack(CCObject* pSender);
    void menuPauseCallBack(CCObject* pSender);
    
    void setLevelScene(BWLevel1Scene* level);
    BWLevel1Scene* getLevelScene();
    
    void action_funcND(cocos2d::CCObject sender,void *data);
    void action_funcND2(cocos2d::CCObject sender,void *data);
};

#endif /* defined(__BlackWhiteWorld__Level1_WhiteWorld__) */
