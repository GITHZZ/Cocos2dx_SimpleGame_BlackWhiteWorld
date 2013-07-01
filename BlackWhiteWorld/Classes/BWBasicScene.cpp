//
//  BWBasicScene.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-9.
//
//  基础类

#include "BWBasicScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

BWBasicScene::~BWBasicScene(){
    //释放对象
    CC_SAFE_RELEASE(player);
    //删除对象
    CC_SAFE_DELETE(basic_physic);
}

BWBasicScene::BWBasicScene(){
    //产生物理环境
    //basic physics
    basic_physic=new BWBasicPhyhics();
    
    this->initWithPhySics();
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();

    //添加玩家
    player=BWPlayer::playerWithFile("player2.png");
    player->addPlayerToScreen(this);
    
    //Controller
    //GameController::sharedController(this);
    GameController *test=new GameController(this);
    
    //更新
    this->schedule(schedule_selector(BWBasicScene::playerAnim),0.2f);
}

void BWBasicScene::initWithPhySics(){
    basic_physic->initWithPhysics();
}

void BWBasicScene::createBody(PhysicsSprite *phySpr,
                              CCPoint pos,
                              float restitution,
                              b2BodyType type,
                              CCPoint boxData){
    basic_physic->createBody(phySpr, pos, restitution, type, boxData);
}

void BWBasicScene::destroyBody(b2Body *body){
    basic_physic->destroyBody(body);
}

void BWBasicScene::action_func(cocos2d::CCObject sender,void *data){
    CCLayer *layer=(CCLayer*)data;
    layer->removeChildByTag(spriteBox_tag, true);
}

void BWBasicScene::update(float dt){
    player->update(dt);
    //物理更新
    basic_physic->update(dt);
}

void BWBasicScene::playerAnim(){
    //播放碰撞的动画
    player->playPlayerAnimation(this);
}

void BWBasicScene::draw(){
    //BWBasicPhyhics::draw();
}