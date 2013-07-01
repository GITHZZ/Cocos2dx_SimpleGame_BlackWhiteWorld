//
//  BWSoundManager.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//  音频管理为单例子

#ifndef __BlackWhiteWorld__BWSoundManager__
#define __BlackWhiteWorld__BWSoundManager__

#include "cocos2d.h"

class BWSoundManager{
private:
    bool bw_isSoundOpen;
    bool bw_isEffectOpen;
public:
    BWSoundManager();
    virtual ~BWSoundManager();
    
    static BWSoundManager* sharedManager();
    
    bool getIsBackgroundMusicOpen();
    void setIsBackgroundMusicOpen(bool isOpen);
    bool getIsEffectOpen();
    void setIsEffectOpen(bool isOpen);
    
    void preloadBackgroundMusic(const char* pszFileName);
    void playBackgroundMusic(const char* pszFileName);
    
    void playEffect(const char* pszFileName);
    
    void setBgMusicName(const char* name);
};

#endif /* defined(__BlackWhiteWorld__BWSoundManager__) */
