//
//  BWStartAnimation.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-6.
//
//

#ifndef __BlackWhiteWorld__BWStartAnimation__
#define __BlackWhiteWorld__BWStartAnimation__

#include <iostream>
#include "Box2D.h"

#include "BWBasicScene.h"
#include "BWStartLayer.h"
#include "BWPlayer.h"

class BWStartAnimation : public BWBasicPhyhics,public cocos2d::CCLayer {
private:
    ScreenResolution screenRes;
    PhysicsSprite *sprite;
    CCSpriteBatchNode *partent;
    CCSize winSize;
public:
    ~BWStartAnimation();
    BWStartAnimation();
    
    // returns a Scene that contains the BWStartAnimation as the only child
    static cocos2d::CCScene* scene();
    bool getResolution();
    
    void action_func();
    
    void EndOfAnim();
    void update(float dt);
    void draw();
    
    void playSpriteAnimation();
    void action_func_ND(cocos2d::CCObject sender,void *data);
};

#endif /* defined(__BlackWhiteWorld__BWStartAnimation__) */
