//
//  BWPhysicsSprite.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-27.
//

#include "BWPhysicsSprite.h"

void BWContactListener::BeginContact(b2Contact* contact){
    if (contact) {
        //Add Audio
        mc.fixtureA=contact->GetFixtureA();
        mc.fixtureB=contact->GetFixtureB();
        
        mc.bodyA=contact->GetFixtureA()->GetBody();
        mc.bodyB=contact->GetFixtureB()->GetBody();
        
        PhysicsSprite *spriteA=(PhysicsSprite*)mc.bodyA->GetUserData();
        PhysicsSprite *spriteB=(PhysicsSprite*)mc.bodyB->GetUserData();
        
        if (spriteA!=NULL) {
            spriteA->setIsColliding(true);
            if (mc.bodyA->GetLinearVelocity().y<-0.1){//下落
            spriteA->setIsContinueColliding(true);
            }
        }
        if(spriteB!=NULL){
            spriteB->setIsColliding(true);//代表碰撞了
             if (mc.bodyB->GetLinearVelocity().y<-0.1){//下落
                 spriteB->setIsContinueColliding(true);
             }
        }
        
        contact_list.push_back(mc);
    }
    B2_NOT_USED(contact);
    //CCLOG("Begin!");
}

void BWContactListener::EndContact(b2Contact* contact){
    PhysicsSprite *spriteA=(PhysicsSprite*)mc.bodyA->GetUserData();
    PhysicsSprite *spriteB=(PhysicsSprite*)mc.bodyB->GetUserData();
    
    if (spriteA!=NULL) {
        spriteA->setIsColliding(false);
        CCLOG("%f",mc.bodyA->GetLinearVelocity().y);
        //不符合让持续碰撞停止条件
        if (mc.bodyA->GetLinearVelocity().y>0.1){
            spriteA->setIsContinueColliding(false);
        }
    }
    if(spriteB!=NULL){
        spriteB->setIsColliding(false);//代表碰撞了
        CCLOG("%f",mc.bodyB->GetLinearVelocity().y);
        //不符合让持续碰撞停止条件
        if (mc.bodyB->GetLinearVelocity().y>0.1){
            spriteB->setIsContinueColliding(false);
        }
    }
    
    contact_list.clear();
    B2_NOT_USED(contact);
}

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{
    this->isColliding=false;
    this->isContinueCollide=false;
}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
    
    if(m_pBody->GetType()==b2_dynamicBody){//运动的
        state=Active;
    }else if(m_pBody->GetType()==b2_staticBody){//静止的
        state=Static;
    }
}

void PhysicsSprite::applyFroce(b2Vec2 force,b2Vec2 point){
    m_pBody->ApplyForce(force, point);
}

void PhysicsSprite::applyLinearImpulse(b2Vec2 impluse, b2Vec2 point){
    m_pBody->ApplyLinearImpulse(impluse, point);
}

void PhysicsSprite::applyAngluarVelocity(float32 w){
    m_pBody->SetAngularVelocity(w);//添加角速度
}

void PhysicsSprite::applyLinearVelocity(b2Vec2 point){
    m_pBody->SetLinearVelocity(point);
}

void PhysicsSprite::applySetStepAwake(bool isAwake){
    m_pBody->SetAwake(isAwake);
}

b2Vec2 PhysicsSprite::GetLinearVelocity(){
    return m_pBody->GetLinearVelocity();
}

void PhysicsSprite::applySetTransform(b2Vec2 pos,float32 angle){
    m_pBody->SetTransform(pos, angle);
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();
    
    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;
    
    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }
    
    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if( ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }
    
    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
                                         -s,  c,
                                         x,  y );
    
    return m_tTransform;
}