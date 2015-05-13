#pragma once
#include "cocos2d.h"
#include <functional>
using namespace std;
USING_NS_CC;
class WorldOutLook : public CCSprite, public CCTargetedTouchDelegate
{
public:
	WorldOutLook(void);
	~WorldOutLook(void);

	static WorldOutLook* create(const char *mapFile, const char* playerFile);
	bool init();
	virtual void onEnter();
	virtual void onExit();
	CCRect rect();
	bool containsTouchLocation(CCPoint point);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

	void playerMoving(CCPoint point);//人物移动时执行该函数
	void recvPathList(std::vector<CCPoint> *pathList);//接收到路径
	virtual void draw(); 

	CCSprite* m_player;//小地图上的人物
	CCSprite* m_map;//小地图纹理
	CCPointArray* m_pathLine;//路径类
	function<void(CCPoint)> m_touchMap;
};

