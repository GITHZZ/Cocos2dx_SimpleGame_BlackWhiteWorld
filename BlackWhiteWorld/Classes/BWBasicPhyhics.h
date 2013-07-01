//
//  BWBasicPhyhics.h
//  BWGameDemo
//
//  Created by 何遵祖 on 13-3-28.
//

/*
    文件说明:
        
        box2d的物理环境基础类，所有继承自此类必须重写update方法,注意该游戏中只有一个物理环境，所以
 
    初始化物理世界只调用了一次.
    
*/

#ifndef __BWGameDemo__BWBasicPhyhics__
#define __BWGameDemo__BWBasicPhyhics__

#include <list>

#include "cocos2d.h"
#include "Box2D.h"
#include "BWGameDefine.h"

#import "GLES-Render.h"
#import "BWPhysicsSprite.h"

//box2d基础类 用于生成物理世界
class BWBasicPhyhics{
private:
    b2World *world;
    GLESDebugDraw * m_debugDraw;//会出测试图用
    BWContactListener *contactListener;//碰撞检测
public:
    //构造方法
    ~BWBasicPhyhics();
    BWBasicPhyhics();
    
    virtual void draw();
    //初始化物理世界
    void initWithPhysics();
    //传入一个精灵将它编程Box2d刚体
    void createBody(PhysicsSprite *sprite,
                    cocos2d::CCPoint position,
                    float restitution,
                    b2BodyType type,
                    cocos2d::CCPoint boxData);
    //销毁刚体
    void destroyBody(b2Body* body);
    
    //更新
    void update(float dt);
};

#endif /* defined(__BWGameDemo__BWBasicPhyhics__) */
