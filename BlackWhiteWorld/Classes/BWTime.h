//
//  BWTime.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-22.
//
//

/*
    文件说明:
        
        游戏的时间类,用于设计游戏的时间倒数.
 */

#ifndef __BlackWhiteWorld__BWTime__
#define __BlackWhiteWorld__BWTime__

#include "cocos2d.h"

class BWTime:public cocos2d::CCObject{
private:
    CC_SYNTHESIZE_READONLY(int , minuate, Minuate);
    CC_SYNTHESIZE_READONLY(int , second, Second);
public:
    BWTime(int minuate,int second);
 
    virtual ~BWTime();
    void updateTime();
    
    void initWithTime(int minuate,int second);

    /*是否已经结束时间*/
    bool isTimeUp();
};

#endif /* defined(__BlackWhiteWorld__BWTime__) */
