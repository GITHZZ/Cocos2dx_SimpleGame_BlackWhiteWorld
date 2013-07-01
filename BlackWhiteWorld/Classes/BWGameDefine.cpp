//
//  BWGameDefine.cpp
//  BWGameDemo
//
//  Created by 何遵祖 on 13-3-30.
//
//

#include "BWGameDefine.h"

using namespace cocos2d;

CC_DLL b2Vec2 _CCBox2DPointMake(float x ,float y){
    return b2Vec2(x/PTM_RATIO,y/PTM_RATIO);
}
