//
//  Level2_WhiteWorld.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#include "Level2_WhiteWorld.h"
#include "BWLevel2Scene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

void Level2WW::createWorld(cocos2d::CCLayer *layer, int deathCount){
    if (!bw_isFristCreate) return;
    
    bw_isFristCreate=false;
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    BWLevel2Scene *scene=(BWLevel2Scene*)layer;
    
    this->setLevelScene(scene);
    
    //bg
    CCSprite *bg=CCSprite::create("bg_w.png");
    bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    scene->addChild(bg,0,kTagWhiteWorldBGTag);
    
    BWPlayer *player=scene->getPlayer();
    player->setColor(ccBLACK);
    
    //steps
    this->createSteps(scene);
    //prods
    this->createProds(scene);
    
    //添加背景音乐
    BWSoundManager::sharedManager()->playBackgroundMusic("bgmusic_w.mp3");
    
    //添加时间图标
    CCSprite* timeTex=CCSprite::create("time_b.png");
    timeTex->setScale(0.3f);
    timeTex->setPosition(ccp(55,winSize.height-25));
    scene->addChild(timeTex,99,kTagWhiteWorldTimeTag);
    CCSprite *timeLabel=CCSprite::create("timel_b.png");
    timeLabel->setPosition(ccp(93,winSize.height-20));
    timeLabel->setScale(0.3f);
    scene->addChild(timeLabel,99,kTagWhiteWorldTimeLabelTag);
    
    //Time
    CCLabelAtlas *num=CCLabelAtlas::create("", "num_2_b.png", 32, 32, '0');
    num->setScale(0.35f);
    num->setPosition(ccp(73,
                         winSize.height-num->getContentSize().height-10));
    scene->addChild(num,100,kTagWhiteWorldLabelTag);
    
    //death Count
    CCSprite *deathSprite=CCSprite::create("die.png");
    deathSprite->setPosition(ccp(160,
                                 winSize.height-deathSprite->getContentSize().height/2+15));
    
    deathSprite->setScale(0.5f);
    scene->addChild(deathSprite,99,kTagWhiteWorldDeathSprTag);
    
    CCSprite *deathLabel=CCSprite::create("deaths_b.png");
    deathLabel->setPosition(ccp(210,winSize.height-20));
    scene->addChild(deathLabel,99,kTagWhiteWorldDeathLabelTag);
    
    CCString *string=CCString::createWithFormat("%d",deathCount);
    CCLabelAtlas *death=CCLabelAtlas::create(string->getCString(), "num_2_b.png", 32, 32, '0');
    death->setScale(0.35f);
    death->setPosition(ccp(200,winSize.height-death->getContentSize().height-15));
    scene->addChild(death,100,kTagWhiteWorldDeathCountTag);
    
    //restart
    CCMenuItemImage *restart=CCMenuItemImage::create("replay2.png", "replay1.png", this , menu_selector(Level2WW::menuRestartCallBack));
    restart->setScale(0.65f);
    
    CCMenuItemImage *pause=CCMenuItemImage::create("stop2.png", "stop1.png",this,menu_selector(Level2WW::menuPauseCallBack));
    pause->setScale(0.65f);
    
    CCMenu *menu=CCMenu::create(restart,pause,NULL);
    menu->alignItemsHorizontallyWithPadding(5.0f);
    menu->setPosition(ccp(winSize.width-70,
                          winSize.height-restart->getContentSize().height/2));
    scene->addChild(menu,99,kTagWhiteWorldMenuTag);
    
    //key
    CCParticleSystem *key=CCParticleSystemQuad::create("SpaceDoor.plist");
    key->setPosition(ccp(430,200+key->getContentSize().height/2+10));
    key->setScale(0.5f);
    scene->addChild(key,0,kTagWhiteWorldKeyTag);
    
    //产生门
    CCString *doorString;
    if (!scene->getIsTouchKey()) {
        doorString=CCString::create("spaceDoor2.plist");
    }else{
        doorString=CCString::create("SpaceDoor.plist");
    }
    
    CCParticleSystem *door=CCParticleSystemQuad::create(doorString->getCString());
    door->setPosition(ccp(80,210));
    door->setScale(0.5f);
    scene->addChild(door,100,kTagWhiteWorldDoorTag);
    
}

void Level2WW::deleteWorld(cocos2d::CCLayer *layer){
    if (bw_isFristCreate) {
        CCLOG("World has not create!");
        return;
    }
    
    BWLevel2Scene *scene=(BWLevel2Scene*)layer;
    
    scene->removeChildByTag(kTagWhiteWorldBGTag, true);
    //stop music
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    //remove timeTex
    scene->removeChildByTag(kTagWhiteWorldTimeTag, true);
    scene->removeChildByTag(kTagWhiteWorldLabelTag, true);
    scene->removeChildByTag(kTagWhiteWorldTimeLabelTag, true);
    //remove deathCount
    scene->removeChildByTag(kTagWhiteWorldDeathCountTag, true);
    scene->removeChildByTag(kTagWhiteWorldDeathSprTag, true);
    scene->removeChildByTag(kTagWhiteWorldDeathLabelTag, true);
    //remove menu
    scene->removeChildByTag(kTagWhiteWorldMenuTag, true);
    //remove all prod
    scene->removeChildByTag(kTagWhiteWorldProdTag , true);
    //remove door
    scene->removeChildByTag(kTagWhiteWorldDoorTag, true);
    
    for (int i=0; i<3; i++) steps[i]->removeStepToScreen(scene);
        
    bw_isFristCreate=true;
}

void Level2WW::update(BWTime *time,cocos2d::CCLayer *layer){
    CCString *string1=CCString::createWithFormat("%d:%d",time->getMinuate(),time->getSecond());
    CCLabelAtlas *num=(CCLabelAtlas*)layer->getChildByTag(kTagWhiteWorldLabelTag);
    if (time->getMinuate()==0&&time->getSecond()<30) {
        num->setOpacity(0);
        num->runAction(CCFadeIn::create(0.3f));
    }
    if(num) num->setString(string1->getCString());
}


void Level2WW::menuRestartCallBack(cocos2d::CCObject *pSender){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,BWLevel2Scene::scene()));
}

void Level2WW::menuPauseCallBack(cocos2d::CCObject *pSender){
    BWPausePlugin::sharedPlugin()->createPlugin(level2);
}

bool Level2WW::playerIsContactKey(CCLayer* layer,BWPlayer *player){
    if (bw_isFristCreate) return false;
    
    CCSprite *key=(CCSprite*)layer->getChildByTag(kTagWhiteWorldKeyTag);
    CCRect keyRect=CCRectMake(key->getPosition().x-10,
                              key->getPosition().y-10,
                              key->getContentSize().width+50,
                              key->getContentSize().height+50);
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    
    if (keyRect.intersectsRect(playerRect)) {
        return true;
    }
    return false;
}

bool Level2WW::playerIsContactProds(cocos2d::CCLayer *layer, BWPlayer *player){
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    
    CCSprite *prod=(CCSprite*)layer->getChildByTag(kTagWhiteWorldProdTag);
    
    CCRect prodRect=CCRectMake(prod->getPosition().x-prod->getContentSize().width/2+70,
                               prod->getPosition().y-prod->getContentSize().height/2-5,
                               prod->getContentSize().width*prod->getScaleX(),
                               prod->getContentSize().height*prod->getScaleY());
    
    if (prodRect.intersectsRect(playerRect)) {
        return  true;
    }
    return false;
}

void Level2WW::createSteps(BWLevel2Scene *scene){
    //产生阶梯
    steps[0]=BWGameStep::fileWithGameStep("step2.png");
    steps[0]->setStepPosition(ccp(150,35));
    steps[0]->addStepToScreen(scene);
    steps[0]->rotateStep(30);
    
    steps[1]=BWGameStep::fileWithGameStep("step2.png");
    steps[1]->setStepPosition(ccp(250,95));
    steps[1]->addStepToScreen(scene);
    steps[1]->rotateStep(30);
    
    steps[2]=BWGameStep::fileWithGameStep("step2.png");
    steps[2]->setStepPosition(ccp(350,155));
    steps[2]->addStepToScreen(scene);
    steps[2]->rotateStep(30);
}

void Level2WW::updatesteps(){
    
}

void Level2WW::createProds(BWLevel2Scene *scene){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *prod=CCSprite::create("ci2.png");
    prod->setPosition(ccp(winSize.width/2+66,prod->getContentSize().height/2-9));
    prod->setScale(0.75f);
    scene->addChild(prod,95,kTagWhiteWorldProdTag);
}

bool Level2WW::playerIsContactDoor(cocos2d::CCLayer *layer, BWPlayer *player){
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    
    CCSprite *door=(CCSprite*)layer->getChildByTag(kTagWhiteWorldDoorTag);
    CCRect doorRect=CCRectMake(door->getPosition().x-door->getContentSize().width/2,
                               door->getPosition().y-door->getContentSize().height/2,
                               door->getContentSize().width,
                               door->getContentSize().height);
    if (doorRect.intersectsRect(playerRect)) {
        return true;
    }
    return false;
}

void Level2WW::setDeathCount(int count,BWBasicScene *scene){
    CCLabelAtlas *death=(CCLabelAtlas*)scene->getChildByTag(kTagWhiteWorldDeathCountTag);
    CCString *string=CCString::createWithFormat("%d",count);
    if (death) death->setString(string->getCString());
}