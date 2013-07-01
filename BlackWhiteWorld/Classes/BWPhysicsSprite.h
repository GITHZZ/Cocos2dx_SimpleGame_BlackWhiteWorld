//
//  BWPhysicsSprite.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-27.
//
//

/*
    文件说明:
 
        本文件主要包含了两个类，BWContact和PhysicsSprite类
 
        BWContact是box2d中的碰撞检测的响应事件，主要重写了b2ContactListener,至于具体用法，
    
    请参照box2d的API文件.
    
        PhySicsSprite是box2d中的一个物理基础类,提供本游戏中的有关物理精灵的一些方法，所有涉及到
 
    物理效果的精灵都要继承自此类。
        
*/

#ifndef __BlackWhiteWorld__BWPhysicsSprite__
#define __BlackWhiteWorld__BWPhysicsSprite__

#include "cocos2d.h"
#include "Box2D.h"
#include "BWGameDefine.h"

#import "GLES-Render.h"

using namespace cocos2d;
using std::list;

//box2d碰撞检测
/*用于放入碰撞检测需要的数据*/
class BWContact{
public:
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    
    b2Body *bodyA;
    b2Body *bodyB;
    
};
class BWContactListener:public b2ContactListener{
    /*开始碰撞时候会调用此方法*/
    virtual void BeginContact(b2Contact* contact);
    /*结束碰撞会调用此方法*/
    virtual void EndContact(b2Contact* contact);
public:
    /*碰撞列表，用于存储碰撞信息*/
    std::list<BWContact> contact_list;
private:
    BWContact mc;//用于存储b2Contact相关信息
};

//物理世界里面的精灵(刚体)
enum SpriteState{
    Static=1,//静止
    Active=2,//活动
};

class PhysicsSprite : public CCSprite
{
public:
    PhysicsSprite();
    
    /*设置和读取相关属性*/
    b2Body* getBody(){return m_pBody;};
    
    void setPhysicsBody(b2Body * body);
    
    /*給刚体施加力*/
    void applyFroce(b2Vec2 force,b2Vec2 point);
    /*給刚体施加一个冲量*/
    void applyLinearImpulse(b2Vec2 impulse,b2Vec2 point);
    /*給刚体施加一个角速度*/
    void applyAngluarVelocity(float32 w);
    /*給刚体施加速度*/
    void applyLinearVelocity(b2Vec2 point);
    /*获得当前的速度*/
    b2Vec2 GetLinearVelocity();
    /*设置刚体的位置*/
    void applySetTransform(b2Vec2 pos,float32 angle);
    /*是否唤醒*/
    void applySetStepAwake(bool isAwake);
    
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
    
    CC_SYNTHESIZE(SpriteState, state, State);
    //是否碰撞
    CC_SYNTHESIZE(bool, isColliding, IsColliding);
    //是否持续碰撞
    CC_SYNTHESIZE(bool, isContinueCollide, IsContinueColliding);
};

#endif /* defined(__BlackWhiteWorld__BWPhysicsSprite__) */
