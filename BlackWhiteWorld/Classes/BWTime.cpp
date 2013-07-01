//
//  BWTime.cpp
//  BlackWhiteWorld
//
//  Created by 何遵祖 on 13-4-22.
//
//

#include "BWTime.h"

using namespace cocos2d;

BWTime::BWTime(int minuate,int second){
    if (minuate<0) minuate=0;
    if (second<0) second=0;
    
    this->initWithTime(minuate, second);
}

BWTime::~BWTime(){
    
}

void BWTime::initWithTime(int minuate, int second){
    this->minuate=minuate;
    this->second=second;
}

void BWTime::updateTime(){
    if (this->isTimeUp()) return;//如果时间尽头不再更新
    this->second--;
    if (this->isTimeUp()) return;//如果时间尽头不再更新
    
    if (this->second<=0) {
        this->minuate--;
        this->second=60;
    }
    CCLOG("%d-%d",this->minuate,this->second);
}

bool BWTime::isTimeUp(){
    if (this->second==0&&this->minuate==0) {
        return true;
    }
    return false;
}
