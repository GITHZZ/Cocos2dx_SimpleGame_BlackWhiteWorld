//
//  BWControl.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-16.
//
//

/*
    文件说明:
    
        该类主要是游戏的控制类,主要是负责游戏的控制,主要是利用了cocos2dx的按钮事件,通过
 
    对应事件来改变BWPlayer的状态来移动,主要是BWPlayer的update方法会通过状态来进行移动。
 
 */

#ifndef __BlackWhiteWorld__BWControl__
#define __BlackWhiteWorld__BWControl__

#include <iostream>
#include "BWPlayer.h"
#include "BWGameDefine.h"
#include "cocos-ext.h"

using namespace extension;

class BWBasicScene;

class GameController:public cocos2d::CCObject{
private:
    BWBasicScene *scene;
    CCSize winSize;
    
    CCDictionary *plistDic;
    CCSize preferSize;
public:
    static GameController* sharedController(BWBasicScene *layer);
    
    /*类的构造方法*/
    GameController(BWBasicScene *layer);
    ~GameController();
    
    /*添加左边，右边移动，跳的按钮*/
    void addLeftButton();
    void addRightButton();
    void addJumpButton(CCPoint pos);
    
    void setScene(BWBasicScene* scene);
    
    /*游戏控制对应的响应事件*/
    void touchDownAction(cocos2d::CCObject *sender,cocos2d::extension::CCControlEvent controlEvent);
    void touchUpAction(cocos2d::CCObject *sender,cocos2d::extension::CCControlEvent controlEvent);
};

#endif /* defined(__BlackWhiteWorld__BWControl__) */
