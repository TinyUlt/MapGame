#include "WorldOutLook.h"
#include "MapData.h"
#define SCARE 0.08
#
WorldOutLook::WorldOutLook(void)
{
}


WorldOutLook::~WorldOutLook(void)
{
}
CCRect WorldOutLook::rect()
{
	CCRect _rect = this->m_map->boundingBox();
	//_rect = CCRect(this->getPositionX()-_rect.size.width/2,this->getPositionY()-_rect.size.height/2, _rect.size.width, _rect.size.height );
	return _rect;
	
	//return CCRectMake(this->getPositionX(),  this->getPositionY(), s.width * SCARE, s.height * SCARE);
}
WorldOutLook* WorldOutLook::create(const char *mapFile, const char* playerFile)
{
	WorldOutLook *_sp = new WorldOutLook();
	
	if (_sp)
	{
		_sp->init();

		_sp->m_map = CCSprite::create(mapFile);
		_sp->m_map->setScale(SCARE);
		_sp->addChild(_sp->m_map,-1);

		_sp->m_player = CCSprite::create(playerFile);
		_sp->addChild(_sp->m_player);

		

		_sp->autorelease();
		
		return _sp;
	}
	CC_SAFE_DELETE(_sp);
	return NULL;
}

void WorldOutLook::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void WorldOutLook::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool WorldOutLook::containsTouchLocation( CCPoint point )
{
	
	return rect().containsPoint((point));
}

bool WorldOutLook::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	//CCPoint _a = touch->getLocation();
	auto nodePosition = this->convertToNodeSpace( touch->getLocation() );
	if ( !containsTouchLocation(nodePosition) ) return false;
// 	if (m_touchMap)
// 	{
// 		m_touchMap()
// 	}
	if (m_touchMap)
	{
		m_touchMap((nodePosition + m_map->getContentSize()/2 * SCARE)/ SCARE);
	}
	CCLOG("touch %f, %f",nodePosition.x, nodePosition.y );
}

void WorldOutLook::ccTouchMoved( CCTouch* touch, CCEvent* event )
{

}

void WorldOutLook::ccTouchEnded( CCTouch* touch, CCEvent* event )
{

}

void WorldOutLook::touchDelegateRetain()
{

}

void WorldOutLook::touchDelegateRelease()
{

}

void WorldOutLook::playerMoving( CCPoint point )
{
	m_player->setPosition((point - m_map->getContentSize()/2)* SCARE  );
}

bool WorldOutLook::init()
{
	CCSprite::init();
	
	m_pathLine = CCPointArray::create(10);
	m_pathLine->initWithCapacity(10);
	m_pathLine->retain();

	CCPoint _temp_pos = CCPoint(0,0);
	m_pathLine->addControlPoint(_temp_pos);

	return true;
}

void WorldOutLook::draw()
{
	kmGLPushMatrix();
	kmGLTranslatef(0, 0, 0);
	glLineWidth( 2.0f );  
	ccDrawCardinalSpline(m_pathLine, 0, 100);
	kmGLPopMatrix();
}

void WorldOutLook::recvPathList( std::vector<CCPoint> *pathList )
{
	//m_pathLine->
	m_pathLine->initWithCapacity(10);
	for (int i= 0; i < pathList->size(); i++)
	{
		CCPoint _point = MapData::getWorldPositionByMapPosition((*pathList)[i]);
		 _point = ( _point - m_map->getContentSize()/2) * SCARE;
		CCLOG("%f, %f", _point.x, _point.y);
		m_pathLine->addControlPoint(_point);
	}
}
