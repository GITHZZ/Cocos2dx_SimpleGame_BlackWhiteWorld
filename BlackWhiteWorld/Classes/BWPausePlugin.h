//
//  BWPausePlugin.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-22.
//
//

/*
    文件说明:本组件的作用是游戏的暂停菜单.作用包括了本游戏中菜单按钮提供的所有功能,
 
本插件只能调用createPlugin方法,使用单例,例如
 
    BWPausePlugin::sharedPlugin()->createPlugin(level);//level为CCLayer类
 
会自动释放,删除操作.无需在继续游戏时候手动删除。
    
    只用于cocos2dx环境下
 */

#ifndef __BlackWhiteWorld__BWPausePlugin__
#define __BlackWhiteWorld__BWPausePlugin__

#include "cocos2d.h"
#include "BWSoundManager.h"
#include "BWGameDefine.h"
#include "BWSoundManager.h"

class BWPausePlugin:cocos2d::CCObject{
private:
    bool isFristCreate;
    cocos2d::CCLayer *glayer;
public:
    BWPausePlugin(){isFristCreate=false;};
    virtual ~BWPausePlugin(){};
    
    static BWPausePlugin* sharedPlugin();
    
    void setLayer(cocos2d::CCLayer* ly){this->glayer=ly;};
    
    /*产生插件,外部调用此方法*/
    void createPlugin(cocos2d::CCLayer* layer);
    
    /*插件移除动画*/
    void deletePlugin(cocos2d::CCLayer* layer);
    /*以下用于删除插件操作*/
    void removeAllPlugin(cocos2d::CCObject sender,void *data);
    
    /*按钮对应的回调事件*/
    void musicSetting(cocos2d::CCObject *sender);
    void effectSetting(cocos2d::CCObject *sender);
    void homeSetting(cocos2d::CCObject *sender);
    void backFunc(cocos2d::CCObject *sender);
};

#endif /* defined(__BlackWhiteWorld__BWPausePlugin__) */
