//
//  ShowBackground.h
//  MapGame
//
//  Created by TinyUlt on 14/12/3.
//
//

#ifndef __MapGame__ShowBackground__
#define __MapGame__ShowBackground__

#include <stdio.h>
#include "cocos2d.h"
#include <map>
using namespace std;
USING_NS_CC;
class ShowBackground:public CCSprite
{
public:
    CREATE_FUNC(ShowBackground);
    bool init();
    
    void show(int x, int y);
    void calculate(int x, int y);
    
    int m_piceWidth;
    int m_piceHeight;
    
    int m_oldX;
    int m_oldY;
    
    int m_oldPositionX;
    int m_oldPositionY;
    
    int m_inspectArray[50][50];
    std::map<int, int> m_passed;
    CCSize m_winSize;
    
    

    
};
#endif /* defined(__MapGame__ShowBackground__) */
