//
//  Level2_BlackWorld.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#include "Level2_BlackWorld.h"
#include "BWLevel2Scene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

void Level2BW::createWorld(cocos2d::CCLayer *layer, int deathCount){
    if (!bw_isFristCreate) return;
    
    bw_isFristCreate=false;
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    //play music
    BWSoundManager::sharedManager()->playBackgroundMusic("bgmusic_b.mp3");
    
    CCSprite *bg=CCSprite::create("bg_b.png");
    bg->setPosition(CCPoint(winSize.width/2,winSize.height/2));
    layer->addChild(bg,0,kTagBlackWorldBGTag);

    BWLevel2Scene *scene=(BWLevel2Scene*)layer;
    
    BWPlayer *player=scene->getPlayer();
    player->setColor(ccWHITE);
    
    this->setLevelScene(scene);
    
    //添加时间图标
    CCSprite* timeTex=CCSprite::create("time_w.png");
    timeTex->setScale(0.3f);
    timeTex->setPosition(ccp(55,winSize.height-25));
    scene->addChild(timeTex,99,kTagBlackWorldTimeTag);
    CCSprite *timeLabel=CCSprite::create("timel_w.png");
    timeLabel->setPosition(ccp(93,winSize.height-20));
    timeLabel->setScale(0.3f);
    scene->addChild(timeLabel,99,kTagBlackWorldTimeLabelTag);
    
    //Time
    CCLabelAtlas *num=CCLabelAtlas::create("", "num_2_w.png", 32, 32, '0');
    num->setScale(0.35f);
    num->setPosition(ccp(73,
                         winSize.height-num->getContentSize().height-10));
    scene->addChild(num,100,kTagBlackWorldLabelTag);
    
    //death Count
    CCSprite *deathSprite=CCSprite::create("die2.png");
    deathSprite->setPosition(ccp(160,winSize.height-deathSprite->getContentSize().height/2+15));
    deathSprite->setScale(0.5f);
    scene->addChild(deathSprite,99,kTagBlackWorldDeathSprTag);
    CCSprite *deathLabel=CCSprite::create("deaths_w.png");
    deathLabel->setPosition(ccp(210,winSize.height-20));
    scene->addChild(deathLabel,99,kTagBlackWorldDeathSprTag);
    
    CCString *string=CCString::createWithFormat("%d",deathCount);
    CCLabelAtlas *death=CCLabelAtlas::create(string->getCString(), "num_2_w.png", 32, 32, '0');
    death->setScale(0.35f);
    death->setPosition(ccp(210,winSize.height-death->getContentSize().height-15));
    scene->addChild(death,100,kTagBlackWorldDeathCountTag);
    
    //menu
    CCMenuItemImage *restart=CCMenuItemImage::create("replay1.png", "replay2.png", this , menu_selector(Level2BW::menuRestartCallBack));
    restart->setScale(0.65f);
    
    CCMenuItemImage *pause=CCMenuItemImage::create("stop1.png", "stop2.png",this,menu_selector(Level2BW::menuPauseCallBack));
    pause->setScale(0.65f);
    
    CCMenu *menu=CCMenu::create(restart,pause,NULL);
    menu->alignItemsHorizontallyWithPadding(5.0f);
    menu->setPosition(ccp(winSize.width-70,
                          winSize.height-restart->getContentSize().height/2));
    scene->addChild(menu,99,kTagBlackWorldMenuTag);
    
    //particle
    CCParticleSystem *particleBg=CCParticleSystemQuad::create("particle_bg_bw.plist");
    particleBg->setPosition(winSize.width/2,winSize.height/2);
    layer->addChild(particleBg,70,kTagBlackWorldParticleTag);
    
    //change
    CCParticleSystem *key=CCParticleSystemQuad::create("SpaceDoor.plist");
    key->setPosition(ccp(50,260));
    key->setScale(0.5f);
    scene->addChild(key,99,kTagBlackWorldKeyTag);
    
    this->createSteps(scene);
    this->createWheel(scene);
    this->createDoorKey(scene);
}

void Level2BW::deleteWorld(cocos2d::CCLayer *layer){
    if (bw_isFristCreate) return;
    
    BWLevel2Scene *scene=(BWLevel2Scene*)layer;
    
    layer->removeChildByTag(kTagBlackWorldBGTag, true);
    layer->removeChildByTag(kTagBlackWorldKeyTag, true);
    layer->removeChildByTag(kTagBlackWorldTimeTag, true);
    layer->removeChildByTag(kTagBlackWorldLabelTag, true);
    layer->removeChildByTag(kTagBlackWorldDeathCountTag, true);
    layer->removeChildByTag(kTagBlackWorldDeathSprTag, true);
    layer->removeChildByTag(kTagBlackWorldMenuTag, true);
    layer->removeChildByTag(kTagBlackWorldDoorKeyTag, true);
    layer->removeChildByTag(kTagBlackWorldTimeLabelTag, true);
    layer->removeChildByTag(kTagBlackWorldDeathLabelTag, true);
    layer->removeChildByTag(kTagBlackWorldParticleTag, true);
    layer->removeChildByTag(kTagBlackWorldDoorKeyTag, true);

    for (int i=0; i<5; i++) steps[i]->removeStepToScreen(scene);
    //移除刺轮
    for (int i=0; i<4; i++) layer->removeChild(wheels[i], true);
    //stop music
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    bw_isFristCreate=true;
}

void Level2BW::update(BWTime *time, cocos2d::CCLayer *layer){
    CCString *string1=CCString::createWithFormat("%d:%d",time->getMinuate(),time->getSecond());
    CCLabelAtlas *num=(CCLabelAtlas*)layer->getChildByTag(kTagBlackWorldLabelTag);
    if (time->getMinuate()==0&&time->getSecond()<30) {
        num->setOpacity(0);
        num->runAction(CCFadeIn::create(0.3f));
    }
    if (num) num->setString(string1->getCString());
}

void Level2BW::menuRestartCallBack(cocos2d::CCObject *pSender){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,BWLevel2Scene::scene()));
}

void Level2BW::menuPauseCallBack(cocos2d::CCObject *pSender){
    BWPausePlugin::sharedPlugin()->createPlugin(level2);
}

void Level2BW::createSteps(BWLevel2Scene *scene){
    steps[0]=BWGameStep::fileWithGameStep("step1_b.png");
    steps[0]->setStepPosition(ccp(120,170));
    steps[0]->addStepToScreen(scene);
    
    steps[1]=BWGameStep::fileWithGameStep("step1_b.png");
    steps[1]->setStepPosition(ccp(230,145));
    steps[1]->addStepToScreen(scene);
    steps[1]->rotateStep(-30);
    
    steps[2]=BWGameStep::fileWithGameStep("step1_b.png");
    steps[2]->setStepPosition(ccp(330,85));
    steps[2]->addStepToScreen(scene);
    steps[2]->rotateStep(-30);
    
    steps[3]=BWGameStep::fileWithGameStep("step1_b.png");
    steps[3]->setStepPosition(ccp(440,35));
    steps[3]->addStepToScreen(scene);
    
    steps[4]=BWGameStep::fileWithGameStep("step1_b.png");
    steps[4]->setStepPosition(ccp(50,230));
    steps[4]->addStepToScreen(scene);
    
}

void Level2BW::createWheel(BWLevel2Scene *scene){
    wheels[0]=CCSprite::create("cilun.png");
    wheels[0]->setPosition(ccp(375,35));
    wheels[0]->setScale(0.85f);
    scene->addChild(wheels[0],99);
    wheels[0]->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 100)));
    
    wheels[1]=CCSprite::create("cilun.png");
    wheels[1]->setPosition(ccp(265,90));
    wheels[1]->setScale(0.85f);
    scene->addChild(wheels[1],99);
    wheels[1]->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 100)));
    
    wheels[2]=CCSprite::create("cilun.png");
    wheels[2]->setPosition(ccp(170,135));
    wheels[2]->setScale(0.85f);
    scene->addChild(wheels[2],99);
    wheels[2]->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 100)));
    
    wheels[3]=CCSprite::create("cilun.png");
    wheels[3]->setPosition(ccp(50,180));
    wheels[3]->setScale(0.85f);
    scene->addChild(wheels[3],99);
    wheels[3]->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 100)));
}

void Level2BW::createDoorKey(BWLevel2Scene *scene){
    if (scene->getIsTouchKey()) return;
    CCSprite *doorKey=CCSprite::create("doorkey.png");
    doorKey->setScale(0.65f);
    doorKey->setRotation(-30);
    doorKey->setPosition(ccp(230,200));
    doorKey->runAction(CCRepeatForever::create(CCRotateBy::create(2.0f, 30)));
    scene->addChild(doorKey,99,kTagBlackWorldDoorKeyTag);
}

bool Level2BW::playerIsContactKey(cocos2d::CCLayer *layer, BWPlayer *player){
    if (bw_isFristCreate) return false;
    
    CCSprite *key=(CCSprite*)layer->getChildByTag(kTagBlackWorldKeyTag);
    CCRect keyRect=CCRectMake(key->getPosition().x-5,
                              key->getPosition().y-5,
                              key->getContentSize().width+50,
                              key->getContentSize().height+50);
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-key->getContentSize().width/2,
                                 player->getPlayerPosition().y-key->getContentSize().height/2,
                                 key->getContentSize().width,
                                 key->getContentSize().height);
    if (keyRect.intersectsRect(playerRect)) {
        return true;
    }
    return false;
}

bool Level2BW::playerIsContactWheel(cocos2d::CCLayer *layer, BWPlayer *player){
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    for (int i=0; i<4; i++) {
        CCRect wheelRect=CCRectMake(wheels[i]->getPosition().x-wheels[i]->getContentSize().width/2,
                                    wheels[i]->getPosition().y-wheels[i]->getContentSize().height/2,
                                    wheels[i]->getContentSize().width,
                                    wheels[i]->getContentSize().height);
        if (wheelRect.intersectsRect(playerRect)) {
            return true;
        }
    }
    
    return false;
}

bool Level2BW::playerIsContactDoorKey(cocos2d::CCLayer *layer, BWPlayer *player){
    CCRect playerRect=CCRectMake(player->getPlayerPosition().x-player->getPlayerContantSize().width/2,
                                 player->getPlayerPosition().y-player->getPlayerContantSize().height/2,
                                 player->getPlayerContantSize().width/2,
                                 player->getPlayerContantSize().height/2);
    CCSprite *sprite=(CCSprite*)layer->getChildByTag(kTagBlackWorldDoorKeyTag);
    if (!sprite) return false;
    CCRect rect=CCRectMake(sprite->getPosition().x-sprite->getContentSize().width/2,
                           sprite->getPosition().y-sprite->getContentSize().height/2,
                           sprite->getContentSize().width,
                           sprite->getContentSize().height);
    if (rect.intersectsRect(playerRect)) {
        layer->removeChildByTag(kTagBlackWorldDoorKeyTag, true);
        return true;
    }
    return false;
}
    
void Level2BW::setDeathCount(int count, BWBasicScene *scene){
    CCLabelAtlas *death=(CCLabelAtlas*)scene->getChildByTag(kTagBlackWorldDeathCountTag);
    CCString *string=CCString::createWithFormat("%d",count);
    if (death) death->setString(string->getCString());
}