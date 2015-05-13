#pragma once
#include "cocos2d.h"
#include <functional>
using namespace std;
USING_NS_CC;
class Paddle;
class MapGoods
{
public:

	static void initMapObject( const char* layerName, const char* objName);////��ʼ����ͼ�������(�������,��������ص�����)
	static void initNPC(const char* layerName, const char* objName);
	static void initSendingDevice(const char* layerName, const char* objName);
	static void initTable(const char* layerName, const char* objName);
	static void initChair(const char* layerName, const char* objName);
	static void initChairPart(const char* layerName, const char* objName);
	static std::function<void(CCPoint point, Paddle* selectObj)> m_selectObj;//ѡ������ص�
};

