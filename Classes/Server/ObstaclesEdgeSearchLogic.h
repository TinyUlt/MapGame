#pragma once
#include <vector>
#include <iostream>
//#include "cocos2d.h"
#include "PathSprite.h"
//USING_NS_CC;
class ObstaclesEdgeSearchLogic
{
public:
	ObstaclesEdgeSearchLogic(CCSize size,std::vector< std::vector<PathSprite*>> obstaclesInspect, std::vector< std::vector<PathSprite*>> roadInspectArray):m_mapSize(size),m_obstaclesInspectArray(obstaclesInspect), m_roadInspectArray(roadInspectArray){};
	~ObstaclesEdgeSearchLogic(){};
	CCSize m_mapSize;
	std::vector< std::vector<PathSprite*>> m_roadInspectArray;
	std::vector< std::vector<PathSprite*>> m_obstaclesInspectArray;
	std::vector<CCPoint> m_pathList;//路径列表
	std::vector<PathSprite*> m_haveInspectList;//检测过的列表
	std::vector<PathSprite*> m_openList;//开放列表(里面存放相邻节点)
	std::function<void(const char* , int , int)> sendData;

	CCPoint calculatePath(int startX, int startY);//计算路径

	PathSprite* getMinPathFormOpenList();
	
	PathSprite* getObjFromInspectArray( int x, int y );

	void inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent);
	
	float calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 );
	
	bool removeObjFromOpenList( PathSprite* sprite );

	void clearPath(  );

	void resetInspectArray();
};

