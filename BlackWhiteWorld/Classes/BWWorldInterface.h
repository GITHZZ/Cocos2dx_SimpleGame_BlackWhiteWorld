//
//  BWWorldInterface.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-27.
//
//

/*
 作用:
 
        本类提供的作用的作为一个接口,这个接口是用在黑白世界里面用于产生
    
    黑色世界或者白色世界的接口。
 
 */


#ifndef __BlackWhiteWorld__BWWorldInterface__
#define __BlackWhiteWorld__BWWorldInterface__

#include "cocos2d.h"
#include "BWTime.h"

class BWWorldInterface{
public:
    BWWorldInterface(){};
    virtual ~BWWorldInterface(){};
    
    virtual void createWorld(cocos2d::CCLayer *layer,int deathCount)=0;//初始化黑色/白色世界
    virtual void deleteWorld(cocos2d::CCLayer *layer)=0;//删除世界
    virtual void update(BWTime *time,cocos2d::CCLayer *layer)=0;//函数更新
};

#endif /* defined(__BlackWhiteWorld__BWWorldInterface__) */
