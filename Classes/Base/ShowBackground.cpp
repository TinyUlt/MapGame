//
//  ShowBackground.cpp
//  MapGame
//
//  Created by TinyUlt on 14/12/3.
//
//

#include "ShowBackground.h"
#include "MapData.h"
bool ShowBackground::init()
{
    CCSprite::init();
    
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_piceHeight = 128;
    m_piceWidth = 128;
    
    //CCLog("%lu", sizeof(m_inspectArray)/sizeof(int));
    memset(&m_inspectArray, 0, sizeof(m_inspectArray)/sizeof(int));

    return true;
}

void ShowBackground::show(int x, int y)
{
    for (int i = x - m_winSize.width/2; i <= x + m_winSize.width/2; ) {
        
        calculate(i, y + m_winSize.height/2);
     
        calculate(i, y - m_winSize.height/2);
        
        i += m_piceWidth;
    }
    
    for (int i = y - m_winSize.height/2; i <= y + m_winSize.height/2; ) {
       
        calculate(x + m_winSize.width/2 , i);
        
        calculate(x - m_winSize.width/2 , i);
        
        i += m_piceHeight;
    }
    

}

void ShowBackground::calculate(int x, int y)
{
    int _indexX = x/ m_piceHeight;
    int _indexY = (MapData::m_mapAttribute.m_mapSize.height * MapData::m_mapAttribute.m_tiledSize.height - y) / m_piceWidth   ;
    
    if (_indexX == m_oldX && _indexY == m_oldY) {
        return;
    }
    m_oldX = _indexX;
    m_oldY = _indexY;


    if(m_inspectArray[_indexX][_indexY] != 0)
    {
        return;
    }
    m_inspectArray[_indexX][_indexY]++;
    
    CCLog("x = %d, y = %d", _indexX, _indexY);
    
    CCSprite* _sp = CCSprite::create(CCString::createWithFormat("background/%d_%d.jpg", _indexY, _indexX)->getCString());
    if (!_sp) {
        return;
    }
    _sp->setAnchorPoint(CCPoint(0,1));
    this->addChild(_sp);
    
    _indexX = _indexX * m_piceHeight;
    _indexY = -(_indexY) * m_piceWidth + MapData::m_mapAttribute.m_mapSize.height * MapData::m_mapAttribute.m_tiledSize.height;
    
    _sp->setPosition(CCPoint(_indexX, _indexY));
}