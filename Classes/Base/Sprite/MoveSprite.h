#pragma once
#include "cocos2d.h"
#include "PathSprite.h"
#include "MoveByPath.h"
#include "DisplaySprite.h"


USING_NS_CC;
class MoveSprite:public PathSprite,public MoveByPath, public CCSprite
{
public:
	MoveSprite(std::function<void(MoveSprite*, CCPoint)> moveDoneCallback);
	~MoveSprite(void);
	DisplaySprite* m_display;
	CCPoint m_oldPoint;
	CCMotionStreak* m_motionStreak;
	float m_moveSpeed;
	std::function<void(MoveSprite*, CCPoint)> m_moveDoneCallback;
	function<void(std::vector<CCPoint> *)> m_sendPathListToWorldOutlook;


	void update(float dt);

	void startMove(CCPoint point);

	void moveDone(CCPoint point);

	void recvPathList(std::vector<CCPoint> _pathList);

	void setMotionStreak(const char* fileName);

};

