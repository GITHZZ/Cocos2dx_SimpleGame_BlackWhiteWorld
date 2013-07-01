//
//  BWLevel2Scene.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#include "BWLevel2Scene.h"
#include "BWStartLayer.h"

using namespace cocos2d;

CCScene* BWLevel2Scene::scene(){
    CCScene *scene=new CCScene();
    
    BWLevel2Scene *layer=new BWLevel2Scene();
    
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

BWLevel2Scene::~BWLevel2Scene(){
    if (whiteWorld) {
        whiteWorld->deleteWorld(this);
        CC_SAFE_RELEASE(whiteWorld);
    }
    if (blackWorld) {
        blackWorld->deleteWorld(this);
        CC_SAFE_RELEASE(blackWorld);
    }
    CC_SAFE_RELEASE(time);
}

BWLevel2Scene::BWLevel2Scene(){
    
    //窗口大小
    winSize=CCDirector::sharedDirector()->getWinSize();
    
    whiteWorld=new Level2WW();
    blackWorld=new Level2BW();

    time=new BWTime(10,10);
    
    //初始化level2
    this->initWithLevel2();
    
    scheduleUpdate();
    this->schedule(schedule_selector(BWLevel2Scene::clockUpdate), 1.0f);
}

void BWLevel2Scene::initWithLevel2(){
    worldState=bw_WhiteWorld;
    
    //init player
    BWPlayer *player=this->getPlayer();
    player->applySetTransform(CCB2Vec(50,200), 0);
    
    BWSoundManager::sharedManager()->playEffect("begin.mp3");
    
    //init clock
    time->initWithTime(1,30);

    //init death count
    deathCount=0;
    
    isTouchKey=false;//没有碰撞到钥匙
}

void BWLevel2Scene::clockUpdate(float dt){
    time->updateTime();
    if (worldState==bw_WhiteWorld) {
        whiteWorld->update(time,this);
    }else if(worldState==bw_BlackWorld){
        blackWorld->update(time, this);
    }
}

void BWLevel2Scene::level2Update(){
    //根据不同世界产生不同效果
    if (worldState==bw_BlackWorld) {
        blackWorld->createWorld(this, deathCount);
        //碰到时空碎片
        if (blackWorld->playerIsContactKey(this, this->getPlayer())) {
            blackWorld->deleteWorld(this);
            worldState=bw_WhiteWorld;
            return;
        }
        if (blackWorld->playerIsContactWheel(this, this->getPlayer())) {
            this->isTouchKey=false;
            this->getPlayer()->explodePlayer(this,ccp(430,250));
            if(this->isTouchKey) blackWorld->createDoorKey(this);
            
            deathCount++;
            blackWorld->setDeathCount(deathCount, this);
        }
        if (blackWorld->playerIsContactDoorKey(this, this->getPlayer())&&!this->isTouchKey) {
            this->isTouchKey=true;
        }
    }else if(worldState==bw_WhiteWorld){
        whiteWorld->createWorld(this, deathCount);
        if (whiteWorld->playerIsContactKey(this, this->getPlayer())) {
            whiteWorld->deleteWorld(this);
            worldState=bw_BlackWorld;
            return;
        }
        if (whiteWorld->playerIsContactProds(this, this->getPlayer())) {
            //玩家爆炸
            this->getPlayer()->explodePlayer(this,ccp(50,50));
            deathCount++;
            whiteWorld->setDeathCount(deathCount, this);
        }
        if (whiteWorld->playerIsContactDoor(this, this->getPlayer())&&this->isTouchKey){
            //胜利条件
            CCDirector::sharedDirector()->replaceScene(BWLevel2Scene::scene());
        }
    }
    
    //是否时间结束了
    if (time->isTimeUp()) {
        CCSprite *timeUp=CCSprite::create("timeup.png");
        timeUp->setPosition(ccp(winSize.width/2,winSize.height/2));
        timeUp->setOpacity(0);
        CCFadeIn *fadeIn=CCFadeIn::create(2.0f);
        CCCallFunc *func=CCCallFunc::create(this, callfunc_selector(BWLevel2Scene::reviewScene));
        timeUp->runAction(CCSequence::create(fadeIn,func,NULL));
        this->addChild(timeUp,99);
    }
}

void BWLevel2Scene::update(float dt){
    BWBasicScene::update(dt);
    this->level2Update();
}

void BWLevel2Scene::reviewScene(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,
                                                            BWLevel2Scene::scene()));
}


