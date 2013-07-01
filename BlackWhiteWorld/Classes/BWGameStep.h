//
//  BWGameStep.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-2.
//

/*
    文件说明:
    
        该文件中包含的是游戏的台阶类,主要是游戏的台阶,该类是继承自PhysicsSprite,不过是静态刚体
    
    
 */

#ifndef __BlackWhiteWorld__BWGameStep__
#define __BlackWhiteWorld__BWGameStep__

#include "cocos2d.h"
#include "BWPhysicsSprite.h"
#include "BWGameDefine.h"

class BWBasicScene;

using namespace cocos2d;

class BWGameStep:public PhysicsSprite{
private:
    CCSpriteBatchNode *partent;
    PhysicsSprite *stepPhysics;
public:
    /*构造方法*/
    BWGameStep(){};
    virtual ~BWGameStep(){};
    /*游戏中的初始化方法*/
    static BWGameStep* fileWithGameStep(const char* fileName);
    /*台阶的初始化方法*/
    bool initWithSprite(const char *fileName);
    /*各种获取和读取方法*/
    void setStepPosition(CCPoint pos){stepPhysics->setPosition(pos);};
    CCPoint getStepPosition(){return stepPhysics->getPosition();};
    void addStepToScreen(BWBasicScene *layer);
    void removeStepToScreen(BWBasicScene *layer);
    void setStepOpacity(GLubyte var){stepPhysics->setOpacity(var);};
    void setStepIsAwake(bool isAwake){stepPhysics->applySetStepAwake(isAwake);};
    
    void rotateStep(float angle);
};

#endif /* defined(__BlackWhiteWorld__BWGameStep__) */
