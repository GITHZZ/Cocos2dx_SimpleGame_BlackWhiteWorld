//
//  BWSoundManager.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#include "BWSoundManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

static BWSoundManager *bw_sManager;
static const char* bw_musicName;//音乐声音

BWSoundManager::BWSoundManager(){
    bw_isEffectOpen=true;
    bw_isSoundOpen=true;
}

BWSoundManager::~BWSoundManager(){
    
}

BWSoundManager* BWSoundManager::sharedManager(){
    if (!bw_sManager) {
        bw_sManager=new BWSoundManager();
    }
    
    return bw_sManager;
}

bool BWSoundManager::getIsBackgroundMusicOpen(){
    return bw_isSoundOpen;
}

void BWSoundManager::setIsBackgroundMusicOpen(bool isOpen){
    bw_isSoundOpen=isOpen;
    
    //如果是在播放着音乐且声音是关闭的
    if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()&&!bw_isSoundOpen) {
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }else{
        if (!bw_musicName) return;
        BWSoundManager::sharedManager()->playBackgroundMusic(bw_musicName);
    }
}

bool BWSoundManager::getIsEffectOpen(){
    return bw_isEffectOpen;
}

void BWSoundManager::setIsEffectOpen(bool isOpen){
    bw_isEffectOpen=isOpen;
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void BWSoundManager::preloadBackgroundMusic(const char *pszFileName){
    if (!bw_isSoundOpen) return;
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszFileName));
}

void BWSoundManager::playBackgroundMusic(const char *pszFileName){
    if (!bw_isSoundOpen) return;
    
    bw_musicName=pszFileName;//记录停止前播放的音乐名
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
                                                           std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszFileName)).c_str(), true);
}

void BWSoundManager::playEffect(const char* pszFileName){
    if (!bw_isEffectOpen) return;
    
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszFileName));
}

void BWSoundManager::setBgMusicName(const char* name){
    bw_musicName=name;
}
