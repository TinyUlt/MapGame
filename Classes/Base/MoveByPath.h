#pragma once
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;
class MoveSprite;
class MoveByPath:public CCObject
{
public:
	MoveByPath(void);
	~MoveByPath(void);

	vector<CCPoint> m_pathList;//路径列表
	bool m_isMoving;
	int m_playerMoveStep;

	std::function<void(CCPoint)> m_moveDone;//移动结束回调

	MoveSprite* m_moveObj;


	void moveSprite(MoveSprite* sprite, vector<CCPoint> pathList);
	void moveObj();
	bool detectWhetherCanPassBetweenTwoPoints( CCPoint p1, CCPoint p2 );
	bool getIsMoving();
};

