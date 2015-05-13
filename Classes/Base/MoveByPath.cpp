#include "MoveByPath.h"
#include "MapData.h"
#include "MathLogic.h"
#include "StaticValue.h"
#include "MoveSprite.h"
#define PRECISE_SEARCH_PATH
MoveByPath::MoveByPath(void):m_isMoving(false),m_playerMoveStep(0)
{

}


MoveByPath::~MoveByPath(void)
{
}

void MoveByPath::moveSprite( MoveSprite* sprite, vector<CCPoint> pathList )
{
	m_pathList = pathList;
	m_moveObj = sprite;
	m_playerMoveStep = 0;
	moveObj(  );
}

void MoveByPath::moveObj( )
{
	
//#ifdef PRECISE_SEARCH_PATH
	m_playerMoveStep++;
	m_isMoving = true;
	//如果运动完毕
	if (m_playerMoveStep >= (m_pathList).size())
	{
		if (m_moveDone)
		{
			m_isMoving = false;
			m_moveDone(*((m_pathList).end()-1));
		}
		return;
	}
	//存储当前的移动进程

	m_moveObj->m_x = (m_pathList)[m_playerMoveStep].x;
	m_moveObj->m_y = (m_pathList)[m_playerMoveStep].y;

	CCPoint _worldPosition = MapData::getWorldPositionByMapPosition(CCPoint((m_pathList)[m_playerMoveStep].x, (m_pathList)[m_playerMoveStep].y));
	
	//设置深度
	//m_moveObj->m_sprite->setZOrder(BASE_ZODER - (*m_pathList)[m_playerMoveStep]->m_sprite->getPositionY());

	//根据路径列表移动人物
	CCPoint _terminalPosition =  _worldPosition+MapData::m_mapAttribute.m_tiledSize/2;
	float _length =  MathLogic::calculateLengthRequiredTwoPoint(_terminalPosition,m_moveObj->getPosition());
	m_moveObj->runAction(CCSequence::create(CCMoveTo::create(m_moveObj->m_moveSpeed * _length,_terminalPosition),  CCCallFunc::create(this, SEL_CallFunc(&MoveByPath::moveObj)), NULL));
// #else
// 	m_isMoving = true;
// 
// 	if (m_playerMoveStep == (*m_pathList).size()-1)
// 	{
// 		//sitChairJudge();
// 		if (m_moveDone)
// 		{
// 			m_isMoving = false;
// 			m_moveDone(*((*m_pathList).end()-1));
// 		}
// 		return ;
// 	}
// 
// 	for (int i = 1;i <= (*m_pathList).size() ;i++)
// 	{
// 		m_playerMoveStep = (*m_pathList).size()-i;
// 		CCPoint _worldPosition = MapData::getWorldPositionByMapPosition(CCPoint((*m_pathList)[m_playerMoveStep].x, (*m_pathList)[m_playerMoveStep].y));
// 
// 		if(detectWhetherCanPassBetweenTwoPoints(CCPoint(m_moveObj->m_x, m_moveObj->m_y), ((*m_pathList)[m_playerMoveStep])))
// 		{
// 			CCPoint _terminalPosition = _worldPosition+MapData::m_mapAttribute.m_tiledSize/2;
// 			CCPoint _po = m_moveObj->m_sprite->getPosition();
// 			CCPoint _p = MapData::getMapPositionByWorldPosition(_po);
// 			float _length = MathLogic::calculateLengthRequiredTwoPoint(_terminalPosition,m_moveObj->m_sprite->getPosition());
// 			m_moveObj->m_sprite->runAction(CCSequence::create(CCMoveTo::create(MOVE_SPEED * _length,_terminalPosition),  CCCallFunc::create(this, SEL_CallFunc(&MoveByPath::moveObj)), NULL));
// 			//存储当前的移动进程
// 			m_moveObj->m_x = (*m_pathList)[m_playerMoveStep].x;
// 			m_moveObj->m_y = (*m_pathList)[m_playerMoveStep].y;
// 
// 			break;
// 		}
// 	}
// 
// 
// #endif
}


bool MoveByPath::getIsMoving()
{
	return m_isMoving;
}
