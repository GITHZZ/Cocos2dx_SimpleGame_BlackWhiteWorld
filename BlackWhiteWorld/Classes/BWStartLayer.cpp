//
//  BWStartLayer.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-7.
//
//

#include "BWStartLayer.h"
#include <iostream>
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* BW_mylayer::scene()
{
    CCScene *scene = CCScene::create();
    
    BW_mylayer *layer = BW_mylayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool BW_mylayer::init()
{
    Mysize = CCDirector::sharedDirector()->getWinSize();
    
    if (!CCLayer::init())
    {
        return false;
    }

    //this->MyMusic();
    this->MyGround();
    this->MyMune();
    this->MyName();
    
    //添加声音控制按钮
    CCMenuItemImage *itemImage=CCMenuItemImage::create("music1.png", "music1_2.png");
    CCMenuItemImage *itemImage2=CCMenuItemImage::create("music2.png", "music2_2.png");
    CCMenuItemToggle *toggleItem;
    if(BWSoundManager::sharedManager()->getIsBackgroundMusicOpen()){
        toggleItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::musicSetting),itemImage,itemImage2,NULL);
    }else{
        toggleItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::musicSetting),itemImage2,itemImage,NULL);
    }
    toggleItem->setScale(0.35f);
    
    CCMenuItemImage *effectImage=CCMenuItemImage::create("effect1.png", "effect1_2.png");
    CCMenuItemImage *effectImage2=CCMenuItemImage::create("effect2.png", "effect2_2.png");
    CCMenuItemToggle *effectItem;
    if (BWSoundManager::sharedManager()->getIsEffectOpen()) {
        effectItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::effectSetting),effectImage,effectImage2,NULL);
    }else{
        effectItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::effectSetting),effectImage2,effectImage,NULL);
    }
    effectItem->setScale(0.35f);
    
    CCMenu *menu=CCMenu::create(toggleItem,effectItem,NULL);
    menu->alignItemsHorizontallyWithPadding(5.0f);
    menu->setOpacity(0);
    menu->setPosition(ccp(Mysize.width-100,effectImage->getContentSize().height/2-30));
    this->addChild(menu);
    
    menu->runAction(CCFadeIn::create(6.0f));
    //添加背景音乐
    BWSoundManager::sharedManager()->playBackgroundMusic("bgmusic_t.mp3");
    
    return true;
}

void BW_mylayer::musicSetting(cocos2d::CCObject *sender){
    if (BWSoundManager::sharedManager()->getIsBackgroundMusicOpen()) {
        BWSoundManager::sharedManager()->setIsBackgroundMusicOpen(false);
    }else{
        BWSoundManager::sharedManager()->setIsBackgroundMusicOpen(true);
    }
    
}

void BW_mylayer::effectSetting(cocos2d::CCObject *sender){
    if (BWSoundManager::sharedManager()->getIsEffectOpen()) {
        BWSoundManager::sharedManager()->setIsEffectOpen(false);
    }else{
        BWSoundManager::sharedManager()->setIsEffectOpen(true);
    }
}

void BW_mylayer::MyMusic(){
    BWSoundManager::sharedManager()->preloadBackgroundMusic("bgmusic_w.mp3");
    BWSoundManager::sharedManager()->preloadBackgroundMusic("bgmusic_b.mp3");
}

void BW_mylayer::MyGround()
{
    Mysize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pGround = CCSprite::create("bg_w.png");
    pGround->setPosition( ccp(Mysize.width/2, Mysize.height/2) );
    pGround->setOpacity(0);
    pGround->runAction(CCFadeIn::create(2.0f));
    this->addChild(pGround, 0);
}

void BW_mylayer::MyMune()
{
    Mysize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *pPlayItem = CCMenuItemImage::create(
                                                         "play2.png",
                                                         "play3.png",
                                                         this,
                                                         menu_selector(BW_mylayer::menuPlayCallback) );
    pPlayItem->setPosition( ccp(Mysize.width/2, Mysize.height/3) );
    pPlayItem->setScale(0.75f);
    
    CCMenu* pMenu = CCMenu::create(pPlayItem,NULL);
    pMenu->setPosition( CCPointZero );
    pMenu->setScale(0.5);
    pMenu->setOpacity(0);
    pMenu->runAction(CCFadeIn::create(7.0f));
    this->addChild(pMenu, 1);
}

void BW_mylayer::MyName()
{
    Mysize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pGamename1 = CCSprite::create("BlackWhiteWorld.png");
    pGamename1->setPosition( ccp(Mysize.width/2, 220) );
    pGamename1->setOpacity(0);
    pGamename1->setScale(0.75f);
    pGamename1->runAction(CCFadeIn::create(5.5f));
    this->addChild(pGamename1, 0);
}

void BW_mylayer::menuPlayCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,
                                                                            BWLevel1Scene::scene()));
    //CCDirector::sharedDirector()->end();
    
}

