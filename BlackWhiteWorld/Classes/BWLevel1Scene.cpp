//
//  BWLevel1Scene.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-18.
//
//

#include "BWLevel1Scene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* BWLevel1Scene::scene(){
    CCScene *scene=CCScene::create();
    
    BWLevel1Scene *layer=new BWLevel1Scene();
    
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

BWLevel1Scene::~BWLevel1Scene(){
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

BWLevel1Scene::BWLevel1Scene(){
    BWBasicScene::BWBasicScene();
    
    //窗口大小
    winSize=CCDirector::sharedDirector()->getWinSize();
    
    whiteWorld=new Level1WW();
    blackWorld=new Level1BW();
    
    time=new BWTime(10,10);
    
    //初始化
    this->initWithLevel1();
    
    scheduleUpdate();
    this->schedule(schedule_selector(BWLevel1Scene::clockUpdate), 1.0f);

    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    this->setTouchEnabled(true);
}

//Level1 初始化
void BWLevel1Scene::initWithLevel1(){
    
    worldState=bw_WhiteWorld;
    
    //init player
    BWPlayer *player=this->getPlayer();
    player->applySetTransform(CCB2Vec(50,100), 0);
    
    BWSoundManager::sharedManager()->playEffect("begin.mp3");
    
    //init clock
    time->initWithTime(2,30);
    
    //init death count
    deathCount=0;
    
    isTouchKey=false;//没有碰撞到钥匙
}

void BWLevel1Scene::clockUpdate(float dt){
    time->updateTime();
    if (worldState==bw_WhiteWorld) {
        whiteWorld->update(time,this);
    }else if(worldState==bw_BlackWorld){
        blackWorld->update(time, this);
    }
}

void BWLevel1Scene::level1Update(){
    //根据不同世界产生不同效果
    if (worldState==bw_BlackWorld) {
        blackWorld->createWorld(this,deathCount);
        if (blackWorld->playerIsContactKey(this, this->getPlayer())) {
              blackWorld->deleteWorld(this);
              worldState=bw_WhiteWorld;
              return;
        }
        if (blackWorld->playerIsContactWheel(this, this->getPlayer())) {
            this->getPlayer()->explodePlayer(this,ccp(430,250));
            if(this->isTouchKey) blackWorld->createDoorKey(this);
            
            this->isTouchKey=false;
            deathCount++;
            blackWorld->setDeathCount(deathCount, this);
        }
        if (blackWorld->playerIsContactDoorKey(this, this->getPlayer())&&!this->isTouchKey) {
            this->isTouchKey=true;
        }
    }else if(worldState==bw_WhiteWorld){
        whiteWorld->createWorld(this,deathCount);
        if (whiteWorld->playerIsContactProds(this, this->getPlayer())) {
            //玩家爆炸
            this->getPlayer()->explodePlayer(this,ccp(50,50));
            deathCount++;
            whiteWorld->setDeathCount(deathCount, this);
        }
        //碰到时空碎片
        if(whiteWorld->playerIsContactKey(this,this->getPlayer())){
            whiteWorld->deleteWorld(this);
            worldState=bw_BlackWorld;
            return;
        }
        if (whiteWorld->playerIsContactDoor(this, this->getPlayer())&&this->isTouchKey){
            //胜利条件
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,BWLevel2Scene::scene()));
        }
    }
    //是否时间结束了
    if (time->isTimeUp()) {
        CCSprite *timeUp=CCSprite::create("timeup.png");
        timeUp->setPosition(ccp(winSize.width/2,winSize.height/2));
        timeUp->setOpacity(0);
        CCFadeIn *fadeIn=CCFadeIn::create(2.0f);
        CCCallFunc *func=CCCallFunc::create(this, callfunc_selector(BWLevel1Scene::reviewScene));
        timeUp->runAction(CCSequence::create(fadeIn,func,NULL));
        this->addChild(timeUp,99);
    }
}

void BWLevel1Scene::update(float dt){
    BWBasicScene::update(dt);
    this->level1Update();
}

void BWLevel1Scene::reviewScene(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,BWLevel1Scene::scene()));
}

void BWLevel1Scene::draw(){
    BWBasicScene::draw();
}