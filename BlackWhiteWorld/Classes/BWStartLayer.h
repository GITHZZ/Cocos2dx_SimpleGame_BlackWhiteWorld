//
//  BWStartLayer.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-7.
//
//

#ifndef __BlackWhiteWorld__BWStartLayer__
#define __BlackWhiteWorld__BWStartLayer__

#include "cocos2d.h"
#include "BWLevel1Scene.h"
#include "BWSoundManager.h"

class BW_mylayer : public cocos2d::CCLayer{
private:
    cocos2d::CCSize Mysize;
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void MyMusic();
    
    void MyGround();
    
    void MyMune();
    
    void MyName();
    
    void menuPlayCallback(CCObject* pSender);
    
    void musicSetting(CCObject *sender);
    void effectSetting(CCObject *sender);
    
    CREATE_FUNC(BW_mylayer);
};

#endif /* defined(__BlackWhiteWorld__BWStartLayer__) */
