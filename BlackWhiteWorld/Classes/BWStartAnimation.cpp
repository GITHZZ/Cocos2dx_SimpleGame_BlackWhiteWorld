//
//  BWStartAnimation.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-6.
//
//

#include "BWStartAnimation.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* BWStartAnimation::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new BWStartAnimation();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

BWStartAnimation::~BWStartAnimation(){
}

BWStartAnimation::BWStartAnimation(){
    //获得屏幕的长宽比例
    if (getResolution()) {
        //预加载资源
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("bgmusic_t.mp3"));
        
        //初始化物理环境
        BWBasicPhyhics::initWithPhysics();

        winSize=CCDirector::sharedDirector()->getWinSize();
        
        //添加运动物体
        partent=CCSpriteBatchNode::create("player2.png",100);
        CCTexture2D *m_SpriteTextire=partent->getTexture();
        
        if (!partent) return;
        
        sprite=new PhysicsSprite();
        sprite->initWithTexture(m_SpriteTextire, CCRectMake(0, 0, 32, 32));
        
        
        partent->addChild(sprite,0,kTagSpriteNode);
        sprite->setColor(ccWHITE);
        sprite->setPosition(ccp(50, 197));

        BWBasicPhyhics::createBody(sprite,sprite->getPosition(), 0.5f, b2_dynamicBody, ccp(0.5f,0.5f));
        this->addChild(partent,99);
        
        sprite->applyAngluarVelocity(-(25.0/180.0)*M_PI*30);
        sprite->applyLinearImpulse(CCB2Vec(2*PTM_RATIO,0),
                                              CCB2Vec(sprite->getPosition().x,
                                                      sprite->getPosition().y));
        
        scheduleUpdate();
    }else{
        CCLOG("BWGAMEERROR:ERROR TO GET RATIO");
        exit(0);
    }
}

void BWStartAnimation::action_func(){
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(4.0f,BW_mylayer::scene()));
    
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("sound.mp3"));
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(5.0f);
}

void BWStartAnimation::EndOfAnim(){
    //获得精灵
    if (sprite->getPosition().y<sprite->getContentSize().height/2+3.4
        &&sprite->getState()==Active) {
        sprite->setState(Static);
        sprite->setColor(ccBLACK);
        
        CCSize size=CCDirector::sharedDirector()->getWinSize();
   
        CCSprite *proTitle=CCSprite::create("BFP_Pic.png");
        proTitle->setPosition(ccp(size.width/2,size.height/2));
        proTitle->setScale(1.5f);
        proTitle->setOpacity(0);
        this->addChild(proTitle,99);
        
        //产生背景
        CCSprite *bg=CCSprite::create("bg_w.png");
        bg->setPosition(CCPoint(winSize.width/2,winSize.height/2));
        bg->setOpacity(0);
        this->addChild(bg,0);
        bg->runAction(CCFadeIn::create(scene_changeTime_interval));
        
        CCFadeIn *fadeIn=CCFadeIn::create(scene_changeTime_interval);
        CCCallFunc *func=CCCallFunc::create(this, callfunc_selector(BWStartAnimation::action_func));
        
        proTitle->runAction(CCSequence::create(fadeIn,func,NULL));
    }
}

bool BWStartAnimation::getResolution(){
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    float ratio=winSize.width/winSize.height;
    if (ratio==1.5) {//3:2
        screenRes=SCREEN_RESOLUTION_3_2;//kTargetIpad
        CCLOG("[INFO]:Screen ratio 3:2");
    }else if(ratio==1.777){
        screenRes=SCREEN_RESOLUTION_16_9;
        CCLOG("[INFO]:Screen ratio 16:9");
    }else{
        return false;
    }
    return true;
}

void BWStartAnimation::update(float dt){
    BWBasicPhyhics::update(dt);
    this->EndOfAnim();//结尾动画
    this->playSpriteAnimation();
}

void BWStartAnimation::playSpriteAnimation(){
    if(sprite->getIsColliding()){
        CCSprite *sprite2=CCSprite::create("player2.png");
        sprite2->setPosition(sprite->getPosition());
        sprite2->setColor(sprite->getColor());
        sprite2->setRotation(sprite->getRotation());
        this->addChild(sprite2,99,spriteBox_tag);
        
        CCScaleTo *scale=CCScaleTo::create(1.0f, 3.0f);
        CCFadeOut *fade=CCFadeOut::create(1.0f);
        CCCallFuncND *func=CCCallFuncND::create(this, callfuncND_selector(BWStartAnimation::action_func_ND), this);
        sprite2->runAction(CCSequence::create(CCSpawn::create(scale,fade,NULL),func,NULL));
        
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("jump.mp3"));
        sprite->setIsColliding(false);
    }
}

void BWStartAnimation::action_func_ND(cocos2d::CCObject sender, void *data){
    CCLayer *layer=(CCLayer*)data;
    layer->removeChildByTag(spriteBox_tag, true);
}

void BWStartAnimation::draw(){
    //CCLayer::draw();
    //BWBasicPhyhics::draw();
}
