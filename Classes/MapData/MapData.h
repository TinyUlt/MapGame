#pragma once
#include "tinyxml.h"
#include <string>
#include <vector>
#include <iostream>
#include "cocos2d.h"
#include "PathSprite.h"
#include "MapGoods.h"
USING_NS_CC;

struct MapAttribute
{
	CCSize m_mapSize;
    CCSize m_mapWorldSize;
	CCSize m_tiledSize;
};
class MapData:public MapGoods
{
public:

 	static MapPathXML m_opcityPathXml;
	static MapAttribute m_mapAttribute;

 	static std::vector< std::vector<PathSprite*>> m_opcityInspectArray;
	static CCTMXTiledMap* m_tiledMap;
	static void createMapData(CCTMXTiledMap* tiledMap, std::string mapXMLPath);//µØÍ¼ ºÍ Â·¾¶
	static void getMapdataFromXML( std::string mapPath);

	static CCPoint getWorldPositionByMapPosition( CCPoint point );
	static CCPoint getMapPositionByWorldPosition( CCPoint point );
	
};

