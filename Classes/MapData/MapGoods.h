#pragma once
#include "cocos2d.h"
#include <functional>
using namespace std;
USING_NS_CC;
class Paddle;
class MapGoods
{
public:

	static void initMapObject( const char* layerName, const char* objName);////初始化地图里的物体(设置深度,设置物体回调函数)
	static void initNPC(const char* layerName, const char* objName);
	static void initSendingDevice(const char* layerName, const char* objName);
	static void initTable(const char* layerName, const char* objName);
	static void initChair(const char* layerName, const char* objName);
	static void initChairPart(const char* layerName, const char* objName);
	static std::function<void(CCPoint point, Paddle* selectObj)> m_selectObj;//选中物体回调
};

