//
//  BWBasicPhyhics.cpp
//  BWGameDemo
//
//  Created by 何遵祖 on 13-3-28.
//
//

#include "BWBasicPhyhics.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

BWBasicPhyhics::~BWBasicPhyhics(){
    delete world;
    world=NULL;
    delete m_debugDraw;
}

BWBasicPhyhics::BWBasicPhyhics(){
    
}

//物理世界初始化
void BWBasicPhyhics::initWithPhysics(){
    CCSize s=CCDirector::sharedDirector()->getWinSize();
    b2Vec2 gravity;//设置重力
    gravity.Set(0.0f, -10.0f);//设置重力加速度
    world=new b2World(gravity);
    
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);//是否持续的物理效果
    
    m_debugDraw = new GLESDebugDraw(PTM_RATIO);
    world->SetDebugDraw(m_debugDraw);
    
    //debug
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body* groundBody=world->CreateBody(&groundBodyDef);
    b2EdgeShape groundBox;
    
    //产生四边的碰撞墙壁
    //底部
    groundBox.Set(CCB2Vec(0,0),CCB2Vec(s.width,0));
    groundBody->CreateFixture(&groundBox,0);
    //顶部
    groundBox.Set(CCB2Vec(0,s.height), CCB2Vec(s.width,s.height));
    groundBody->CreateFixture(&groundBox,0);
    //左边
    groundBox.Set(CCB2Vec(0,s.height), CCB2Vec(0,0));
    groundBody->CreateFixture(&groundBox,0);
    //右边
    groundBox.Set(CCB2Vec(s.width,s.height), CCB2Vec(s.width,0));
    groundBody->CreateFixture(&groundBox,0);
    
    //碰撞侦听事件
    contactListener=new BWContactListener();
    world->SetContactListener(contactListener);
}

void BWBasicPhyhics::createBody(PhysicsSprite *sprite,
                                CCPoint position,
                                float restitution,
                                b2BodyType type,
                                CCPoint boxData){
    //CCLOG("Add Sprite %.2f,%.2f",position.x,position.y);
    
    b2BodyDef bodyDef;
    bodyDef.type=type;
    bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    bodyDef.userData=sprite;
    
    //在世界中产生body
    b2Body *body=world->CreateBody(&bodyDef);
    
    //产生一个square box
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(boxData.x,boxData.y);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape=&dynamicBox;
    fixtureDef.density=1.0f;
    fixtureDef.friction=0.5f;//设置摩擦
    fixtureDef.restitution=restitution;
    
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
}

void BWBasicPhyhics::destroyBody(b2Body *body){
    world->DestroyBody(body);
}

//物理世界更新
void BWBasicPhyhics::update(float dt){
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

void BWBasicPhyhics::draw(){
    //#if !defined(COCOS2D_DEBUG)||COCOS2D_DEBUG == 0
    //用于测试用
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    world->DrawDebugData();
    
    kmGLPopMatrix();
    //#endif
}
