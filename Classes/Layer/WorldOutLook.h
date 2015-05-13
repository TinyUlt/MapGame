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

	void playerMoving(CCPoint point);//�����ƶ�ʱִ�иú���
	void recvPathList(std::vector<CCPoint> *pathList);//���յ�·��
	virtual void draw(); 

	CCSprite* m_player;//С��ͼ�ϵ�����
	CCSprite* m_map;//С��ͼ����
	CCPointArray* m_pathLine;//·����
	function<void(CCPoint)> m_touchMap;
};

