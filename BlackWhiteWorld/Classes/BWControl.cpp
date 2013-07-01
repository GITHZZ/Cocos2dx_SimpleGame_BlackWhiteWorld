//
//  BWControl.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-16.
//
//

#include "BWControl.h"
#include "BWBasicScene.h"

using namespace cocos2d;
using namespace extension;

void GameController::addLeftButton(){
    //left
    CCString *leftImage=dynamic_cast<CCString*>(plistDic->objectForKey("LeftImage"));
    CCControlButton*leftBtn=CCControlButton::create(CCScale9Sprite::create(leftImage->getCString()));
    leftBtn->setPreferredSize(preferSize);
    leftBtn->setPosition(leftBtn->getContentSize().width/2+5,100);
    this->scene->addChild(leftBtn,99,gControlLeftBtnTag);
    leftBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(GameController::touchDownAction),
                                                 CCControlEventTouchDown);
    leftBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameController::touchUpAction), CCControlEventTouchUpInside);
    leftBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameController::touchUpAction), CCControlEventTouchUpOutside);
}

void GameController::addRightButton(){
    CCString *rightImage=dynamic_cast<CCString*>(plistDic->objectForKey("RightImage"));
    CCControlButton *rightBtn=CCControlButton::create(CCScale9Sprite::create(rightImage->getCString()));
    rightBtn->setPreferredSize(preferSize);
    rightBtn->setPosition(ccp(winSize.width-rightBtn->getContentSize().width/2-5,100));
    this->scene->addChild(rightBtn,99,gControlRightBtnTag);
    rightBtn->addTargetWithActionForControlEvents(this,
                                                  cccontrol_selector(GameController::touchDownAction),
                                                  CCControlEventTouchDown);
    rightBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(GameController::touchUpAction),CCControlEventTouchUpInside);
    rightBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(GameController::touchUpAction), CCControlEventTouchUpOutside);
}

void GameController::addJumpButton(CCPoint pos){
    CCString *upImage=dynamic_cast<CCString*>(plistDic->objectForKey("UpImage"));
    CCControlButton *jumpBtn=CCControlButton::create(CCScale9Sprite::create(upImage->getCString()));
    jumpBtn->setPreferredSize(preferSize);
    jumpBtn->setPosition(pos);
    jumpBtn->setVisible(false);
    jumpBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(GameController::touchDownAction),
                                                 CCControlEventTouchDown);
    jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameController::touchUpAction), CCControlEventTouchUpInside);
    jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameController::touchUpAction),
                                                 CCControlEventTouchUpOutside);
    this->scene->addChild(jumpBtn,100,gControlJumpBtnTag);
}

GameController::~GameController(){
    //释放对象
}

static GameController *gameController;

GameController* GameController::sharedController(BWBasicScene *layer){
    if (!gameController) {
        gameController=new GameController(layer);
    }
    return gameController;
}


//初始化
GameController::GameController(BWBasicScene *layer){
    winSize=CCDirector::sharedDirector()->getWinSize();
    
    const char* plistPath=CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("ControlPlist.plist");
    plistDic=CCDictionary::createWithContentsOfFile(plistPath);
    
    CCString *preStr=dynamic_cast<CCString*>(plistDic->objectForKey("ControlImagePreferredSize"));
    preferSize=CCSizeFromString(preStr->getCString());
    
    
    this->setScene(layer);
    //left
    this->addLeftButton();
    //right
    this->addRightButton();
    //jump
    this->addJumpButton(ccp(-10,-10));
    
    CCControlButton *jumpBtn=CCControlButton::create(CCScale9Sprite::create("up2.png"));
    jumpBtn->setPreferredSize(preferSize);
    jumpBtn->setPosition(ccp(200,200));
    jumpBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(GameController::touchDownAction),
                                                 CCControlEventTouchDown);
    jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameController::touchUpAction), CCControlEventTouchUpInside);
    jumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameController::touchUpAction),
                                                 CCControlEventTouchUpOutside);
    this->scene->addChild(jumpBtn,100,1000);
}

/*游戏对应事件响应方法,通过移除移动按钮并且添加跳的按钮实现按钮转换,复原则反*/
void GameController::touchDownAction(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent){
    CCControlButton *tempButton=(CCControlButton*)sender;
    /*状态判断,是按着左键还是右键*/
    if (tempButton->getTag()==gControlLeftBtnTag) {
        scene->getPlayer()->setPlayerState(pMoveLeft);
        CCControlButton *rightBtn=(CCControlButton*)this->scene->getChildByTag(gControlRightBtnTag);
        rightBtn->setVisible(false);
        //获得跳跃按钮
        CCControlButton *jumpBtn=(CCControlButton*)this->scene->getChildByTag(gControlJumpBtnTag);
        jumpBtn->setVisible(true);
        jumpBtn->setPosition(rightBtn->getPosition());
    }else if(tempButton->getTag()==gControlRightBtnTag){
        scene->getPlayer()->setPlayerState(pMoveRight);
        CCControlButton *leftBtn=(CCControlButton*)this->scene->getChildByTag(gControlLeftBtnTag);
        leftBtn->setVisible(false);
        //获得跳跃按钮
        CCControlButton *jumpBtn=(CCControlButton*)this->scene->getChildByTag(gControlJumpBtnTag);
        jumpBtn->setVisible(true);
        jumpBtn->setPosition(leftBtn->getPosition());
    }else if(tempButton->getTag()==gControlJumpBtnTag||tempButton->getTag()==1000){
        scene->getPlayer()->setIsJumping(true);
    }
}

/*当按钮提起时候的事件*/
void GameController::touchUpAction(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent){
    CCControlButton *tempButton=(CCControlButton*)sender;
    if (tempButton->getTag()==gControlLeftBtnTag) {
        scene->getPlayer()->setPlayerState(pStatic);
        CCControlButton *rightBtn=(CCControlButton*)this->scene->getChildByTag(gControlRightBtnTag);
        rightBtn->setVisible(true);
        //获得跳跃按钮
        CCControlButton *jumpBtn=(CCControlButton*)this->scene->getChildByTag(gControlJumpBtnTag);
        jumpBtn->setVisible(false);
        jumpBtn->setPosition(ccp(-10, -10));
    }else if(tempButton->getTag()==gControlRightBtnTag){
        scene->getPlayer()->setPlayerState(pStatic);
        CCControlButton *leftBtn=(CCControlButton*)this->scene->getChildByTag(gControlLeftBtnTag);
        leftBtn->setVisible(true);
        //获得跳跃按钮
        CCControlButton *jumpBtn=(CCControlButton*)this->scene->getChildByTag(gControlJumpBtnTag);
        jumpBtn->setVisible(false);
        jumpBtn->setPosition(ccp(-10, -10));
    }
}

void GameController::setScene(BWBasicScene* scene){
    this->scene=scene;
}