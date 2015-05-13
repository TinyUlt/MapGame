#pragma once
#include <vector>
#include <iostream>
//#include "cocos2d.h"
#include "PathSprite.h"
//USING_NS_CC;
class PathSearchLogic
{
public:
	PathSearchLogic(CCSize size, std::vector< std::vector<PathSprite*>> inspectArray):m_mapSize(size),m_roadInspectArray(inspectArray){};
	~PathSearchLogic(){};
	CCSize m_mapSize;
	std::vector< std::vector<PathSprite*>> m_roadInspectArray;
	std::vector<CCPoint> m_pathList;//路径列表
	std::vector<PathSprite*> m_haveInspectList;//检测过的列表
	std::vector<PathSprite*> m_openList;//开放列表(里面存放相邻节点)
	std::function<void(const char* , int , int)> sendData;

	void calculatePath(int startX, int startY, int endX, int endY);//计算路径

	PathSprite* getMinPathFormOpenList();
	
	PathSprite* getObjFromInspectArray( int x, int y );

	void inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent, PathSprite* endNode );
	
	float calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 );
	
	bool removeObjFromOpenList( PathSprite* sprite );

	void clearPath(  );

	void resetInspectArray();

	bool detectWhetherCanPassBetweenTwoPoints( CCPoint p1, CCPoint p2 );
};

