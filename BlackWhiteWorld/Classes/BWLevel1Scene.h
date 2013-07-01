//
//  BWLevel1Scene.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-18.
//
//

#ifndef __BlackWhiteWorld__BWLevel1Scene__
#define __BlackWhiteWorld__BWLevel1Scene__

#include "BWBasicScene.h"
#include "BWLevel2Scene.h"

#include "Level1_WhiteWorld.h"
#include "Level1_blackWorld.h"

#include "BWTime.h"

class BWLevel1Scene:public BWBasicScene{
private:
    CCSize winSize;
    BWTime *time;
    int deathCount;
    WorldState worldState;//世界状态
    
    //黑色世界和白色世界
    Level1WW *whiteWorld;
    Level1BW *blackWorld;
    
    //是否接触过钥匙
    bool isTouchKey;
    BWPlayer *player;
    
public:
    BWLevel1Scene();
    virtual ~BWLevel1Scene();
    
    static CCScene *scene();
    
    void initWithLevel1();//关卡一初始化
    
    void update(float dt);
    void level1Update();
    
    void clockUpdate(float dt);
    void draw();
    
    void setIsTouchKey(bool isTouchKey){this->isTouchKey=isTouchKey;};
    bool getIsTouchKey(){return this->isTouchKey;};
    
    void reviewScene();
};

#endif /* defined(__BlackWhiteWorld__BWLevel1Scene__) */
