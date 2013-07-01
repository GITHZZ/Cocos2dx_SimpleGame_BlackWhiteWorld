//
//  BWWorldComponent.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-24.
//
//

#include "BWWorldComponent.h"

using namespace cocos2d;

#pragma mark BWWorldComponent WhiteWorld Method

static BWWWComponent* bw_wwCommponent;

BWWWComponent* BWWWComponent::sharedComponent(){
    if (!bw_wwCommponent) {
        bw_wwCommponent=new BWWWComponent();
    }
    return bw_wwCommponent;
}

void BWWWComponent::createComponent(cocos2d::CCLayer *layer,int deathCount){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    //添加背景音乐
    BWSoundManager::sharedManager()->playBackgroundMusic("bgmusic_w.mp3");

    //背景
    CCSprite *bg=CCSprite::create("bg_w.png");
    bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    layer->addChild(bg,0,kTagWhiteWorldBGTag);

    //添加时间图标
    CCSprite* timeTex=CCSprite::create("time_b.png");
    timeTex->setScale(0.3f);
    timeTex->setPosition(ccp(55,winSize.height-25));
    layer->addChild(timeTex,99,kTagWhiteWorldTimeTag);
    CCSprite *timeLabel=CCSprite::create("timel_b.png");
    timeLabel->setPosition(ccp(93,winSize.height-20));
    timeLabel->setScale(0.3f);
    layer->addChild(timeLabel,99,kTagWhiteWorldTimeLabelTag);
    
    //Time
    CCLabelAtlas *num=CCLabelAtlas::create("", "num_2_b.png", 32, 32, '0');
    num->setScale(0.35f);
    num->setPosition(ccp(73,winSize.height-num->getContentSize().height-10));
    layer->addChild(num,100,kTagWhiteWorldLabelTag);
    
    //death Count
    CCSprite *deathSprite=CCSprite::create("die.png");
    deathSprite->setPosition(ccp(160,
                                 winSize.height-deathSprite->getContentSize().height/2+15));
    
    deathSprite->setScale(0.5f);
    layer->addChild(deathSprite,99,kTagWhiteWorldDeathSprTag);
    
    CCSprite *deathLabel=CCSprite::create("deaths_b.png");
    deathLabel->setPosition(ccp(210,winSize.height-20));
    layer->addChild(deathLabel,99,kTagWhiteWorldDeathLabelTag);
    
    CCString *string=CCString::createWithFormat("%d",deathCount);
    CCLabelAtlas *death=CCLabelAtlas::create(string->getCString(), "num_2_b.png", 32, 32, '0');
    death->setScale(0.35f);
    death->setPosition(ccp(200,winSize.height-death->getContentSize().height-15));
    layer->addChild(death,100,kTagWhiteWorldDeathCountTag);
    
    //restart
    CCMenuItemImage *restart=CCMenuItemImage::create("replay2.png", "replay1.png", this , menu_selector(BWWWComponent::menuRestartCallBack));
    restart->setScale(0.65f);
    
    CCMenuItemImage *pause=CCMenuItemImage::create("stop2.png", "stop1.png",this,menu_selector(BWWWComponent::menuPauseCallBack));
    pause->setScale(0.65f);
    
    CCMenu *menu=CCMenu::create(restart,pause,NULL);
    menu->alignItemsHorizontallyWithPadding(5.0f);
    menu->setPosition(ccp(winSize.width-70,
                          winSize.height-restart->getContentSize().height/2));
    layer->addChild(menu,99,kTagWhiteWorldMenuTag);
    
    bw_layer=layer;
}

void BWWWComponent::deleteComponent(cocos2d::CCLayer *layer){
    layer->removeChildByTag(kTagWhiteWorldBGTag, true);
    layer->removeChildByTag(kTagWhiteWorldTimeTag, true);
    layer->removeChildByTag(kTagWhiteWorldTimeLabelTag, true);
    layer->removeChildByTag(kTagWhiteWorldLabelTag, true);
    layer->removeChildByTag(kTagWhiteWorldDeathSprTag, true);
    layer->removeChildByTag(kTagWhiteWorldDeathLabelTag, true);
    layer->removeChildByTag(kTagWhiteWorldDeathCountTag, true);
    layer->removeChildByTag(kTagWhiteWorldMenuTag, true);
}

void BWWWComponent::menuPauseCallBack(cocos2d::CCObject *pSender){
    
}

void BWWWComponent::menuRestartCallBack(cocos2d::CCObject *pSender){
    
}
    
#pragma mark BWWWComponent BlackWorld Method
