//
//  BWGameDefine.h
//  BWGameDemo
//
//  Created by 何遵祖 on 13-3-30.
//
//  这个类里面包括了所有的define的方法。如果你想使用游戏的define值，请导入

#ifndef __BWGameDemo__BWGameDefine__
#define __BWGameDemo__BWGameDefine__

#include "cocos2d.h"
#include "Box2D.h"

//游戏状态
enum GameState{
  gStartAnim  = 1,//游戏开始前动画
  gPlaying    = 2,//游戏进行中
  gEnding     = 3//游戏结束
};

enum WorldState{
    bw_BlackWorld = 1,
    bw_WhiteWorld = 2
};

#define scene_changeTime_interval 3.5 //场景转换的时间间隔
//相关的宏定义
//==============BWControl======================
enum ControlType{
    cLeft,
    cRight,
    cJump
};

enum {
    gControlLeftBtnTag  = 1,
    gControlRightBtnTag = 2,
    gControlJumpBtnTag  = 3
};
//=============================================

//==============BWPlayer=======================
enum{
    kTagSpriteNode = 4,
    kTagParentNode = 5
};
#define spriteBox_tag  99
//=============================================

//==============BWGameStep=======================
enum{
    kTagStepNode = 6,
    kTagStepParentNode = 7
};
//=============================================

//==============Level1_WhiteWorld==============
#define kTagWhiteWorldBGTag             20
#define kTagWhiteWorldKeyTag            22
#define kTagWhiteWorldTimeTag           24
#define kTagWhiteWorldLabelTag          26
#define kTagWhiteWorldDeathCountTag     28
#define kTagWhiteWorldDeathSprTag       30
#define kTagWhiteWorldMenuTag           32
#define kTagWhiteWorldDoorTag           35
#define kTagWhiteWorldTimeLabelTag      37
#define kTagWhiteWorldDeathLabelTag     39
#define kTagWhiteWorldProdTag           42
#define kTagWhiteWorldWord1Tag          43
#define kTagWhiteWorldWord2Tag          44
#define kTagWhiteWorldPauseTag          45
//=============================================

//==============Level1_BlackWorld==============
#define kTagBlackWorldBGTag             21
#define kTagBlackWorldKeyTag            23
#define kTagBlackWorldTimeTag           25
#define kTagBlackWorldLabelTag          27
#define kTagBlackWorldDeathCountTag     29
#define kTagBlackWorldDeathSprTag       31
#define kTagBlackWorldMenuTag           33
#define kTagBlackWorldWheelTag          34
#define kTagBlackWorldDoorKeyTag        36
#define kTagBlackWorldTimeLabelTag      38
#define kTagBlackWorldDeathLabelTag     40
#define kTagBlackWorldParticleTag       41
//=============================================

//BWWhiteComponent
#define kTagPauseBgTag      60
#define kTagPauseMenuTag    61

//移动状态
typedef enum PlayerState{
    pStatic = 1,
    pMoveLeft = 2,
    pMoveRight = 3,
    pJump = 4
}PlayerState;

//player移动速度
#define sprite_move_speed 12
//=============================================

//屏幕分辨率
enum ScreenResolution {
    SCREEN_RESOLUTION_16_9,//16:9
    SCREEN_RESOLUTION_3_2,//3:2
};

//把像素的坐标转换成box2d的坐标
#define PTM_RATIO 32
CC_DLL b2Vec2 _CCBox2DPointMake(float x ,float y);
#define CCB2Vec _CCBox2DPointMake

#endif /* defined(__BWGameDemo__BWGameDefine__) */
