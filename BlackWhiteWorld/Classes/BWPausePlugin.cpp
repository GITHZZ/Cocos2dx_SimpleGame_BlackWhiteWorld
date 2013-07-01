//
//  BWPausePlugin.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-22.
//
//

#include "BWPausePlugin.h"
#include "BWStartLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

static BWPausePlugin* bw_pausePlugin;

BWPausePlugin* BWPausePlugin::sharedPlugin(){
    if (!bw_pausePlugin) {
        bw_pausePlugin=new BWPausePlugin();
    }
    return bw_pausePlugin;
}

void BWPausePlugin::createPlugin(cocos2d::CCLayer *layer){
    if (isFristCreate) return;
    
    isFristCreate=true;
    
    //获得配置文件
    const char* plistPath=CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("PausePluginPlist.plist");
    CCDictionary *plistDic=CCDictionary::createWithContentsOfFile(plistPath);
    
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    this->setLayer(layer);
    
    //添加暂停背景
    CCString *pauseBtnSpr=dynamic_cast<CCString*>(plistDic->objectForKey("BackgroundImage"));
    CCSprite *pauseBg=CCSprite::create(pauseBtnSpr->getCString());
    pauseBg->setPosition(ccp(size.width+pauseBg->getContentSize().width/2,size.height/2));
    pauseBg->runAction(CCMoveTo::create(1.0f, ccp(size.width+20,
                                                  size.height/2)));
    layer->addChild(pauseBg,100,kTagPauseBgTag);
    
    //添加声音控制按钮
    CCString *musicImage1=dynamic_cast<CCString*>(plistDic->objectForKey("MusicImage1"));
    CCString *musicImageUse1=dynamic_cast<CCString*>(plistDic->objectForKey("MusicImageUse1"));
    CCMenuItemImage *itemImage=CCMenuItemImage::create(musicImage1->getCString(), musicImageUse1->getCString());
    
    CCString *musicImage2=dynamic_cast<CCString*>(plistDic->objectForKey("MusicImage2"));
    CCString *musicImageUse2=dynamic_cast<CCString*>(plistDic->objectForKey("MusicImageUse2"));
    CCMenuItemImage *itemImage2=CCMenuItemImage::create(musicImage2->getCString(),musicImageUse2->getCString());
    
    CCMenuItemToggle *toggleItem;
    if(BWSoundManager::sharedManager()->getIsBackgroundMusicOpen()){
        toggleItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::musicSetting),itemImage,itemImage2,NULL);
    }else{
        toggleItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::musicSetting),itemImage2,itemImage,NULL);
    }
    toggleItem->setScale(0.35f);
    
    //音效按钮添加
    CCString *effectImage1=dynamic_cast<CCString*>(plistDic->objectForKey("EffectImage1"));
    CCString *effectImageUse1=dynamic_cast<CCString*>(plistDic->objectForKey("EffectImageUse1"));
    CCMenuItemImage *effectImage=CCMenuItemImage::create(effectImage1->getCString(), effectImageUse1->getCString());
    
    CCString *effectImage2=dynamic_cast<CCString*>(plistDic->objectForKey("EffectImage2"));
    CCString *effectImageUse2=dynamic_cast<CCString*>(plistDic->objectForKey("EffectImageUse2"));
    CCMenuItemImage *effectBtn2=CCMenuItemImage::create(effectImage2->getCString(), effectImageUse2->getCString());
    
    CCMenuItemToggle *effectItem;
    if (BWSoundManager::sharedManager()->getIsEffectOpen()) {
        effectItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::effectSetting),effectImage,effectBtn2,NULL);
    }else{
        effectItem=CCMenuItemToggle::createWithTarget(this, menu_selector(BWPausePlugin::effectSetting),effectBtn2,effectImage,NULL);
    }
    effectItem->setScale(0.35f);
    
    //主页按钮
    CCString *homeImage=dynamic_cast<CCString*>(plistDic->objectForKey("HomeImage"));
    CCString *homeImageUse=dynamic_cast<CCString*>(plistDic->objectForKey("HomeImageUse"));
    CCMenuItemImage *homeItem=CCMenuItemImage::create(homeImage->getCString(),homeImageUse->getCString(), this, menu_selector(BWPausePlugin::homeSetting));
    homeItem->setScale(0.35f);
    
    CCString *backImage=dynamic_cast<CCString*>(plistDic->objectForKey("BackImage"));
    CCString *backImageUse=dynamic_cast<CCString*>(plistDic->objectForKey("BackImageUse"));
    CCMenuItemImage *backItem=CCMenuItemImage::create(backImage->getCString(), backImageUse->getCString(),this,menu_selector(BWPausePlugin::backFunc));
    backItem->setScale(0.35f);
    
    //游戏菜单
    CCString *alignStr=dynamic_cast<CCString*>(plistDic->objectForKey("AlignItemsVerticallyWithMenu"));
    float align=alignStr->floatValue();
    
    CCMenu *menu=CCMenu::create(toggleItem,effectItem,homeItem,backItem,NULL);
    menu->alignItemsVerticallyWithPadding(align);
    menu->setPosition(ccp(size.width+menu->getContentSize().width/2,size.height/2));
    menu->runAction(CCMoveTo::create(1.0f, ccp(size.width-50,
                                               size.height/2)));
    layer->addChild(menu,100,kTagPauseMenuTag);
    layer->pauseSchedulerAndActions();
}

void BWPausePlugin::deletePlugin(cocos2d::CCLayer *layer){
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCSprite *pauseBg=(CCSprite*)layer->getChildByTag(kTagPauseBgTag);
    pauseBg->runAction(CCMoveTo::create(1.0f, ccp(size.width+pauseBg->getContentSize().width/2,size.height/2)));
    CCMenu *menu=(CCMenu*)layer->getChildByTag(kTagPauseMenuTag);
    CCMoveTo *moveTo=CCMoveTo::create(1.0f, ccp(size.width+menu->getContentSize().width/2,size.height/2));
    CCCallFuncND *func=CCCallFuncND::create(this, callfuncND_selector(BWPausePlugin::removeAllPlugin), layer);
    menu->runAction(CCSequence::create(moveTo,func,NULL));
}

void BWPausePlugin::removeAllPlugin(cocos2d::CCObject sender, void *data){
    CCLayer *layer=(CCLayer*)data;
    layer->removeChildByTag(kTagPauseBgTag, true);
    layer->removeChildByTag(kTagPauseMenuTag, true);
    layer->resumeSchedulerAndActions();
    isFristCreate=false;
}

void BWPausePlugin::musicSetting(cocos2d::CCObject *sender){
    if (BWSoundManager::sharedManager()->getIsBackgroundMusicOpen()) {
        BWSoundManager::sharedManager()->setIsBackgroundMusicOpen(false);
    }else{
        BWSoundManager::sharedManager()->setIsBackgroundMusicOpen(true);
    }
}

void BWPausePlugin::effectSetting(cocos2d::CCObject *sender){
    if (BWSoundManager::sharedManager()->getIsEffectOpen()) {
        BWSoundManager::sharedManager()->setIsEffectOpen(false);
    }else{
        BWSoundManager::sharedManager()->setIsEffectOpen(true);
    }
}

void BWPausePlugin::homeSetting(cocos2d::CCObject *sender){
    this->deletePlugin(glayer);
    if (!BWSoundManager::sharedManager()->getIsBackgroundMusicOpen()) {
        BWSoundManager::sharedManager()->setBgMusicName("bgmusic_t.mp3");
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,BW_mylayer::scene()));
}

void BWPausePlugin::backFunc(cocos2d::CCObject *sender){
    this->deletePlugin(glayer);
}