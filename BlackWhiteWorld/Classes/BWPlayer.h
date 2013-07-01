//
//  BWPlayer.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-14.
//

/*
    文件说明:
        
        玩家控制类，就是游戏主角,主角是物理刚体，注意每次产生刚体时候都会通过initPlayer初始化相关数据:
    
    这里还包含着游戏player的运动的一些方法，主要在update里面，它负责了游戏玩家的移动
 
    注意!!:
        
        BWPlayer是继承自PhysicsSprite的一个类，但是在屏幕添加精灵实质上是添加playerPhysics变量，
 
    所以如果直接获取BWPlayer相关的值是无法获取的，需要通过该类的设置器和读取器来获取player的相关信息。
*/

#ifndef __BlackWhiteWorld__BWPlayer__
#define __BlackWhiteWorld__BWPlayer__

#include "BWBasicPhyhics.h"
#include "BWGameDefine.h"
#include "BWSoundManager.h"

class BWBasicScene;

using namespace cocos2d;

class BWPlayer:public PhysicsSprite{
private:
    CCSize winSize;
    
    CCSpriteBatchNode *partent;
    PhysicsSprite *playerPhysics;
    
    CC_SYNTHESIZE(PlayerState, state, PlayerState);
    CC_SYNTHESIZE(bool, isJumping,IsJumping);
    
public:
    /*游戏玩家的初始类方法，传入参数为文件名字*/
    static BWPlayer* playerWithFile(const char* fileName);
    /*初始化player的相关数据*/
    bool initPlayer(const char* fileName);
    /*析构函数*/
    virtual ~BWPlayer();
    /*相关属性设置和读取器*/
    void setPlayerPosition(CCPoint pos){playerPhysics->setPosition(pos);};
    CCPoint getPlayerPosition(){return playerPhysics->getPosition();};
    CCSize getPlayerContantSize(){return playerPhysics->getContentSize();};
    void setColor(ccColor3B color){playerPhysics->setColor(color);};
    ccColor3B getPlayerColor(){return playerPhysics->getColor();};
    void setIsColliding(bool isCollide){playerPhysics->setIsColliding(isCollide);};
    bool getIsColliding(){return  playerPhysics->getIsColliding();};
    
    /*給玩家精灵施加角速度*/
    void applyAngluarVelocity(float32 vel){
        //    playerPhysics->applyAngluarVelocity((15.0/180.0)*M_PI*30);
        playerPhysics->applyAngluarVelocity(vel);
    };
    /*給玩家施加冲量*/
    void applyLinearImpulse(b2Vec2 vel,b2Vec2 pos){
        playerPhysics->applyLinearImpulse(vel,pos);
        //    playerPhysics->applyLinearImpulse(CCB2Vec(2*PTM_RATIO,0),
        //                                      CCB2Vec(playerPhysics->getPosition().x,
        //                                              playerPhysics->getPosition().y));
    };
    /*设置刚体位置*/
    void applySetTransform(b2Vec2 pos,float32 angle){
        playerPhysics->applySetTransform(pos, angle);
    };
    
    /*添加player到屏幕上*/
    void addPlayerToScreen(BWBasicScene* layer);

    //玩家碰撞之后的动画(残影)
    void playPlayerAnimation(BWBasicScene *layer);
    
    /*玩家消失*/
    void explodePlayer(BWBasicScene *layer,CCPoint pos);
    
    void update(float dt);
};

#endif /* defined(__BlackWhiteWorld__BWPlayer__) */
