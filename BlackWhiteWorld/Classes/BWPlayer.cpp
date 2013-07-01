//
//  BWPlayer.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-14.
//
//

#include "BWPlayer.h"
#include "BWBasicScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

BWPlayer::~BWPlayer(){
}

BWPlayer* BWPlayer::playerWithFile(const char* fileName){
    BWPlayer *player=new BWPlayer();
    if (player&&player->initPlayer(fileName)) {
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

/*产生BWPlayer的方法:首先通过获取纹理产生纹理图添加到partent中之后在通过partent添加到屏幕上去
 */
bool BWPlayer::initPlayer(const char* fileName){
    //产生纹理
    partent=CCSpriteBatchNode::create(fileName,100);
    CCTexture2D *m_SpriteTextire=partent->getTexture();
    
    if (!partent) return false;
    
    playerPhysics=new PhysicsSprite();
    playerPhysics->initWithTexture(m_SpriteTextire, CCRectMake(0, 0, 32, 32));
    
    
    partent->addChild(playerPhysics,0,kTagSpriteNode);
    playerPhysics->setColor(ccBLACK);
    playerPhysics->setOpacity(0);
    playerPhysics->setPosition(ccp(50, 50));
    
    this->state=pStatic;
    this->isJumping=false;
    
    winSize=CCDirector::sharedDirector()->getWinSize();
    
    return true;
}

void BWPlayer::addPlayerToScreen(BWBasicScene* layer){
    layer->addChild(partent,98,kTagParentNode);
    layer->createBody(playerPhysics, playerPhysics->getPosition(),0.0f,b2_dynamicBody,ccp(0.5f,0.5f));
    playerPhysics->runAction(CCFadeIn::create(2.0f));
}

void BWPlayer::playPlayerAnimation(BWBasicScene* layer){
    if(this->getIsColliding()){
        CCSprite *sprite=CCSprite::create("player2.png");
        sprite->setPosition(this->getPlayerPosition());
        sprite->setColor(this->getPlayerColor());
        sprite->setRotation(this->getRotation());
        layer->addChild(sprite,99,spriteBox_tag);
        
        CCScaleTo *scale=CCScaleTo::create(1.0f, 3.0f);
        CCFadeOut *fade=CCFadeOut::create(1.0f);
        CCCallFuncND *func=CCCallFuncND::create(this, callfuncND_selector(BWBasicScene::action_func), layer);
        sprite->runAction(CCSequence::create(CCSpawn::create(scale,fade,NULL),func,NULL));
        
        this->setIsColliding(false);
    }
}

void BWPlayer::explodePlayer(BWBasicScene *layer,CCPoint pos){
    CCParticleSystem *particle=CCParticleSystemQuad::create("player_exp.plist");
    particle->setPosition(this->getPlayerPosition());
    layer->addChild(particle,99);
    playerPhysics->applyLinearVelocity(CCB2Vec(0,0));
    this->applySetTransform(CCB2Vec(pos.x,pos.y), 0);
    
    //effect
    BWSoundManager::sharedManager()->playEffect("begin.mp3");
}

void BWPlayer::update(float dt){
    //jump
    if (this->isJumping) {
        //如果player接触到地面而且竖直速度向上就可以跳
        if (!(playerPhysics->GetLinearVelocity().y>=-2.0f&&playerPhysics->getIsContinueColliding())){
            this->isJumping=false;
            return;
        }
        
        int dir=-(playerPhysics->GetLinearVelocity().x/abs(playerPhysics->GetLinearVelocity().x));
        if (dir!=1&&dir!=-1) dir=0;
 
        playerPhysics->applyAngluarVelocity(dir*(15.0/180.0)*M_PI*30);
        playerPhysics->applyLinearImpulse(CCB2Vec(0,7*PTM_RATIO),
                                          CCB2Vec(playerPhysics->getPosition().x,
                                                  playerPhysics->getPosition().y));
        //play Sound
        BWSoundManager::sharedManager()->playEffect("jump.mp3");
    
        this->isJumping=false;
        return;
    }
    
    //moving
    if (this->state==pStatic) {//静止状态返回
        return;
    }else if(this->state==pMoveLeft){//左边移动
        if (playerPhysics->GetLinearVelocity().x<=-5) return;//超过速度最大值就不在添加冲量
        playerPhysics->applyLinearImpulse(CCB2Vec(-sprite_move_speed,0),
                                          CCB2Vec(playerPhysics->getPosition().x,
                                                  playerPhysics->getPosition().y));
    }else if(this->state==pMoveRight){
        //超过速度最大值就不在添加冲量
        if (playerPhysics->GetLinearVelocity().x>=5) return;
        playerPhysics->applyLinearImpulse(CCB2Vec(sprite_move_speed,0),
                                          CCB2Vec(playerPhysics->getPosition().x,
                                                  playerPhysics->getPosition().y));
    }
}