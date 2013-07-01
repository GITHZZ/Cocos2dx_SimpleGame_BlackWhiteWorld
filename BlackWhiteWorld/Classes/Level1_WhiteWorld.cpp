//
//  Level1_WhiteWorld.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-27.
//
//

#include "Level1_WhiteWorld.h"
#include "BWLevel1Scene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

void Level1WW::createWorld(cocos2d::CCLayer *layer,int deathCount){
    if (!bw_isFristCreate) return;//如果不是第一次产生返回
    
    bw_isFristCreate=false;
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    BWLevel1Scene *scene=(BWLevel1Scene*)layer;
    
    //设置场景
    this->setLevelScene(scene);
    
    //添加每层必须有的插件
    BWWWComponent::sharedComponent()->createComponent(layer,deathCount);
    
    //文字提示
    if (!scene->getIsTouchKey()) {
        CCSprite *word1=CCSprite::create("word1.png");
        word1->setPosition(ccp(winSize.width/2,winSize.height/2));
        word1->setOpacity(0);
        CCFadeIn *fadeIn=CCFadeIn::create(6.0f);
        CCFadeOut *fadeOut=CCFadeOut::create(6.0f);
        CCCallFuncND *func=CCCallFuncND::create(this, callfuncND_selector(Level1WW::action_funcND),scene);
        word1->runAction(CCSequence::create(fadeIn,fadeOut,func,NULL));
        scene->addChild(word1,10,kTagWhiteWorldWord1Tag);
    }
    
    BWPlayer *player=scene->getPlayer();
    player->setColor(ccBLACK);
    
    //key
    CCParticleSystem *key=CCParticleSystemQuad::create("SpaceDoor.plist");
    key->setPosition(ccp(430,200+key->getContentSize().height/2+10));
    key->setScale(0.5f);
    scene->addChild(key,0,kTagWhiteWorldKeyTag);
    
    //restart
    CCMenuItemImage *restart=CCMenuItemImage::create("replay2.png", "replay1.png", this , menu_selector(Level1WW::menuRestartCallBack));
    restart->setScale(0.65f);
    
    CCMenuItemImage *pause=CCMenuItemImage::create("stop2.png", "stop1.png",this,menu_selector(Level1WW::menuPauseCallBack));
    pause->setScale(0.65f);
    
    CCMenu *menu=CCMenu::create(restart,pause,NULL);
    menu->alignItemsHorizontallyWithPadding(5.0f);
    menu->setPosition(ccp(winSize.width-70,
                          winSize.height-restart->getContentSize().height/2));
    scene->addChild(menu,99,kTagWhiteWorldMenuTag);
    
    //产生阶梯
    this->createSteps(scene);
    
    //产生门
    CCString *doorString;
    if (!scene->getIsTouchKey()) {
        doorString=CCString::create("spaceDoor2.plist");
    }else{
        doorString=CCString::create("SpaceDoor.plist");
    }
    
    CCParticleSystem *door=CCParticleSystemQuad::create(doorString->getCString());
    door->setPosition(ccp(130,210));
    door->setScale(0.5f);
    scene->addChild(door,100,kTagWhiteWorldDoorTag);
    
    //添加针刺
    this->createProds(scene);
}

void Level1WW::action_funcND(cocos2d::CCObject sender, void *data){
    CCLayer *scene=(CCLayer*)data;
    scene->removeChildByTag(kTagWhiteWorldWord1Tag, true);
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCSprite *word2=CCSprite::create("word2.png");
    word2->setPosition(ccp(winSize.width/2,winSize.height/2));
    word2->setOpacity(0);
    CCFadeIn *fadeIn=CCFadeIn::create(6.0f);
    CCFadeOut *fadeOut=CCFadeOut::create(6.0f);
    CCCallFuncND *func=CCCallFuncND::create(this, callfuncND_selector(Level1WW::action_funcND2),scene);
    word2->runAction(CCSequence::create(fadeIn,fadeOut,func,NULL));
    scene->addChild(word2,91,kTagWhiteWorldWord2Tag);
}

void Level1WW::action_funcND2(cocos2d::CCObject sender, void *data){
    CCLayer *scene=(CCLayer*)data;
    scene->removeChildByTag(kTagWhiteWorldWord2Tag, true);
}

void Level1WW::menuRestartCallBack(cocos2d::CCObject *pSender){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,BWLevel1Scene::scene()));
}

void Level1WW::menuPauseCallBack(cocos2d::CCObject *pSender){
    BWPausePlugin::sharedPlugin()->createPlugin(level1);
}


void Level1WW::setLevelScene(BWLevel1Scene* level){
    this->level1=level;
}

BWLevel1Scene* Level1WW::getLevelScene(){
    return this->level1;
}

void Level1WW::deleteWorld(cocos2d::CCLayer *layer){
    if (bw_isFristCreate) {
        CCLOG("World has not create!");
        return;
    }
    
    //stop music
//  SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    BWLevel1Scene *scene=(BWLevel1Scene*)layer;
    //remove bg
    scene->removeChildByTag(kTagWhiteWorldBGTag, true);
    //remove key
    scene->removeChildByTag(kTagWhiteWorldKeyTag, true);
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
    //remove door
    scene->removeChildByTag(kTagWhiteWorldDoorTag, true);
    //remove world
    scene->removeChildByTag(kTagWhiteWorldWord1Tag, true);
    scene->removeChildByTag(kTagWhiteWorldWord2Tag, true);
    
    //remove step
    for (int i=0; i<5; i++) steps[i]->removeStepToScreen(scene);
    //remove all prod
    scene->removeChildByTag(kTagWhiteWorldProdTag , true);
    
    bw_isFristCreate=true;
}

void Level1WW::update(BWTime *time,cocos2d::CCLayer *layer){
    CCString *string1=CCString::createWithFormat("%d:%d",time->getMinuate(),time->getSecond());
    CCLabelAtlas *num=(CCLabelAtlas*)layer->getChildByTag(kTagWhiteWorldLabelTag);
    if (time->getMinuate()==0&&time->getSecond()<30) {
        num->setOpacity(0);
        num->runAction(CCFadeIn::create(0.3f));
    }
    if(num) num->setString(string1->getCString());
}

bool Level1WW::playerIsContactKey(CCLayer* layer,BWPlayer *player){
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

bool Level1WW::playerIsContactProds(cocos2d::CCLayer *layer, BWPlayer *player){
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    
    CCSprite *prod=(CCSprite*)layer->getChildByTag(kTagWhiteWorldProdTag);
    
    CCRect prodRect=CCRectMake(prod->getPosition().x-prod->getContentSize().width/2+60,
                                   prod->getPosition().y-prod->getContentSize().height/2,
                                   prod->getContentSize().width*prod->getScaleX(),
                                   prod->getContentSize().height*prod->getScaleY());
        
    if (prodRect.intersectsRect(playerRect)) {
        return true;
    }
    return false;
}

bool Level1WW::playerIsContactDoor(cocos2d::CCLayer *layer, BWPlayer *player){
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    
    CCSprite *door=(CCSprite*)layer->getChildByTag(kTagWhiteWorldDoorTag);
    CCRect doorRect=CCRectMake(door->getPosition().x-door->getContentSize().width/2,
                               door->getPosition().y-door->getContentSize().height/2,
                               door->getContentSize().width+50,
                               door->getContentSize().height+60);
    if (doorRect.intersectsRect(playerRect)) {
        return true;
    }
    return false;
}

void Level1WW::createSteps(BWLevel1Scene *scene){
    //产生阶梯
    steps[0]=BWGameStep::fileWithGameStep("step2.png");
    steps[0]->setStepPosition(ccp(150,35));
    steps[0]->addStepToScreen(scene);
    
    steps[1]=BWGameStep::fileWithGameStep("step2.png");
    steps[1]->setStepPosition(ccp(240,85));
    steps[1]->addStepToScreen(scene);
    
    steps[2]=BWGameStep::fileWithGameStep("step2.png");
    steps[2]->setStepPosition(ccp(330,135));
    steps[2]->addStepToScreen(scene);
    
    steps[3]=BWGameStep::fileWithGameStep("step2.png");
    steps[3]->setStepPosition(ccp(430,170));
    steps[3]->addStepToScreen(scene);
    
    steps[4]=BWGameStep::fileWithGameStep("step2.png");
    steps[4]->setStepPosition(ccp(130,170));
    steps[4]->addStepToScreen(scene);
}

void Level1WW::createProds(BWLevel1Scene *scene){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *prod=CCSprite::create("ci2.png");
    prod->setPosition(ccp(winSize.width/2+66,prod->getContentSize().height/2-9));
    prod->setScale(0.75f);
    scene->addChild(prod,95,kTagWhiteWorldProdTag);
}

void Level1WW::setDeathCount(int count,BWBasicScene *scene){
    CCLabelAtlas *death=(CCLabelAtlas*)scene->getChildByTag(kTagWhiteWorldDeathCountTag);
    CCString *string=CCString::createWithFormat("%d",count);
    if (death) death->setString(string->getCString());
}
