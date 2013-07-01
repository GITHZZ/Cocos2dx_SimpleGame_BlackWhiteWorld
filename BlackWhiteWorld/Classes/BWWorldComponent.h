//
//  BWWorldComponent.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-24.
//
//

#ifndef __BlackWhiteWorld__BWWorldComponent__
#define __BlackWhiteWorld__BWWorldComponent__

#include "cocos2d.h"
#include "BWGameDefine.h"
#include "BWSoundManager.h"
#include "BWPausePlugin.h"

class BWWWComponent:cocos2d::CCObject{
private:
    bool isFristCreate;
    CC_SYNTHESIZE(cocos2d::CCLayer, *bw_layer, Layer);
public:
    BWWWComponent(){isFristCreate=false;};
    virtual ~BWWWComponent(){};
    
    static BWWWComponent* sharedComponent();
    
    void createComponent(cocos2d::CCLayer *layer,int deathCount);
    void deleteComponent(cocos2d::CCLayer *layer);
    
    void menuPauseCallBack(cocos2d::CCObject *pSender);
    void menuRestartCallBack(cocos2d::CCObject *pSender);
};

class BWBWComponent:cocos2d::CCObject{
    
};

#endif /* defined(__BlackWhiteWorld__BWWorldComponent__) */
