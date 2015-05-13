#include "MoveSprite.h"
#include "MoveByPath.h"
#include "MapData.h"
#include "StaticValue.h"
#include "Server.h"
#include "MathLogic.h"
extern Server g_server;
MoveSprite::MoveSprite(std::function<void(MoveSprite*, CCPoint)> moveDoneCallback):m_moveDoneCallback(moveDoneCallback),m_motionStreak(NULL),m_moveSpeed(0)
{
	m_moveDone = std::bind(&MoveSprite::moveDone, this, std::placeholders::_1);

	CCSprite::init();
	CCSprite::autorelease();

	m_display = new DisplaySprite("manAnimation");
	this->addChild(m_display);

	m_moveSpeed = 1/200.0;
	this->scheduleUpdate();
}

MoveSprite::~MoveSprite(void)
{
}

void MoveSprite::update( float dt )
{
	if (getIsMoving())
	{
		//////////////////////////////////////////////////////////////////////////
		CCPoint playerPoint = getPosition();
		setZOrder(BASE_ZODER-playerPoint.y+16);

		if (m_motionStreak)
		{
			m_motionStreak->setPosition(playerPoint);
			m_motionStreak->setZOrder(BASE_ZODER-playerPoint.y+16);
		}

		CCPoint _point = MapData::getMapPositionByWorldPosition(playerPoint);

		if (MapData::m_opcityInspectArray[_point.x][_point.y])
		{
			m_display->setOpacity(100);
			//m_motionStreak->setOpacity(100);
		}
		else
		{
			m_display->setOpacity(255);
			//m_motionStreak->setOpacity(255);
		}
		//////////////////////////////////////////////////////////////////////////
		CCPoint _newPoint = getPosition();
		if (m_oldPoint.x != _newPoint.x || m_oldPoint.y != _newPoint.y)
		{
			float _angle = MathLogic::getAngleByTwoPoint(m_oldPoint, _newPoint);
			m_display->walkByAngle(_angle);
		}

		m_oldPoint = _newPoint;

		//////////////////////////////////////////////////////////////////////////
	
	}
}

void MoveSprite::startMove( CCPoint point )
{
	
	m_startX = m_x;
	m_startY = m_y;
	stopAllActions();
	//resetObjPosition();
	CCPoint _point =MapData::getMapPositionByWorldPosition(getPosition());
	g_server.startMove(_point, point);
	
	m_oldPoint = getPosition();
	m_display->setAnchorPoint(CCPoint(0.5, 0.25));
}

void MoveSprite::moveDone( CCPoint point )
{
	if (m_moveDoneCallback)
	{
		m_moveDoneCallback(this, point);
	}
}

void MoveSprite::recvPathList( std::vector<CCPoint> _pathList )
{
	moveSprite(this, _pathList);
	if (m_sendPathListToWorldOutlook)
	{
		m_sendPathListToWorldOutlook(&m_pathList);
	}
}

void MoveSprite::setMotionStreak( const char* fileName )
{
	m_motionStreak = CCMotionStreak::create(0.5f, 10.0f, 100.0f, ccc3(255, 255, 255), fileName);
	this->getParent()->addChild(m_motionStreak,BASE_ZODER);
}
