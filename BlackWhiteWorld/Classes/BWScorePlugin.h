//
//  BWScorePlugin.h
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-6-14.
//
//

#ifndef __BlackWhiteWorld__BWScorePlugin__
#define __BlackWhiteWorld__BWScorePlugin__

#include "cocos2d.h"

using namespace cocos2d;

class BWScorePlugin : CCObject{
private:

public:
    static BWScorePlugin *sharedPlugin();
    BWScorePlugin();
    virtual ~BWScorePlugin();
    
    void createBackground();
    void createButton();

};

#endif /* defined(__BlackWhiteWorld__BWScorePlugin__) */
