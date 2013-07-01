//
//  BWBasicScene.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-9.
//

/*
 文件说明:
 
    这个类是场景基础类,所有其它场景都要继承此类。
*/

#ifndef __BlackWhiteWorld__BWBasicScene__
#define __BlackWhiteWorld__BWBasicScene__

#include "cocos2d.h"


#include "BWBasicPhyhics.h"
#include "BWGameStep.h"
#include "BWControl.h"
#include "BWGameDefine.h"
#include "BWPlayer.h"

class BWBasicScene:public cocos2d::CCLayer{
private:
    BWPlayer *player;

    BWBasicPhyhics *basic_physic;
    
    CC_SYNTHESIZE(GameState, gState, GameState);
public:
    BWBasicScene();
    ~BWBasicScene();
    /*场景的初始化方法*/
    void initWithPhySics();
    /*产生刚体*/
    void createBody(PhysicsSprite *phySpr,
                    CCPoint pos,
                    float restitution,
                    b2BodyType type,
                    CCPoint boxData);
    void destroyBody(b2Body *body);
    
    /*设置器和读取器*/
    BWPlayer *getPlayer(){return player;};
    
    /*更新*/
    void update(float dt);
    void playerAnim();
    void draw();
    
    void action_func(cocos2d::CCObject sender,void *data);
};

#endif /* defined(__BlackWhiteWorld__BWBasicScene__) */
