//
//  BWGameStep.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-2.
//
//

#include "BWGameStep.h"
#include "BWBasicScene.h"

using namespace cocos2d;

BWGameStep* BWGameStep::fileWithGameStep(const char *fileName){
    BWGameStep *step=new BWGameStep();
    if (step&&step->initWithSprite(fileName)) {
        return step;
    }
    CC_SAFE_DELETE(step);
    return NULL;
}

bool BWGameStep::initWithSprite(const char *fileName){
    partent=CCSpriteBatchNode::create(fileName, 100);
    CCTexture2D *m_SpriteTexture=partent->getTexture();
    
    if (!partent) return false;
    
    stepPhysics=new PhysicsSprite();
    stepPhysics->initWithTexture(m_SpriteTexture,CCRectMake(0, 0, 64, 32));
    
    partent->addChild(stepPhysics,0,kTagStepNode);
    stepPhysics->setPosition(ccp(0,0));
    
    return true;
}

void BWGameStep::addStepToScreen(BWBasicScene* layer){
    layer->createBody(stepPhysics,stepPhysics->getPosition(),0.0f,b2_staticBody,
                      ccp(1.0f,0.4f));
    layer->addChild(partent,99,kTagStepParentNode);
}

void BWGameStep::removeStepToScreen(BWBasicScene *layer){
    layer->removeChildByTag(kTagStepParentNode, true);
    if (stepPhysics->getBody()) layer->destroyBody(stepPhysics->getBody());
}

void BWGameStep::rotateStep(float angle){
    stepPhysics->applySetTransform(CCB2Vec(stepPhysics->getPosition().x,stepPhysics->getPosition().y),
                                   (angle/180.0)*M_PI);
}
