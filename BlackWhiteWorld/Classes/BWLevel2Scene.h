//
//  BWLevel2Scene.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-5-11.
//
//

#ifndef __BlackWhiteWorld__BWLevel2Scene__
#define __BlackWhiteWorld__BWLevel2Scene__

#include "BWBasicScene.h"

#include "Level2_WhiteWorld.h"
#include "Level2_BlackWorld.h"

#include "BWTime.h"

class BWStartLayer;

class BWLevel2Scene:public BWBasicScene{
private:
    CCSize winSize;
    BWTime *time;
    int deathCount;
    WorldState worldState;//世界状态
    
    //黑色世界和白色世界
    Level2WW *whiteWorld;
    Level2BW *blackWorld;
    
    //是否接触过钥匙
    bool isTouchKey;
    BWPlayer *player;
    
public:
    BWLevel2Scene();
    virtual ~BWLevel2Scene();
    
    static CCScene *scene();
    
    void initWithLevel2();
    
    void update(float dt);
    void level2Update();
    void clockUpdate(float dt);
    
    void setIsTouchKey(bool isTouchKey){this->isTouchKey=isTouchKey;};
    bool getIsTouchKey(){return this->isTouchKey;};
    
    void reviewScene();
};

#endif /* defined(__BlackWhiteWorld__BWLevel2Scene__) */
