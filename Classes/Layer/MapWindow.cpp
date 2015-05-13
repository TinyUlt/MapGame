#include "MapWindow.h"
#include "MapXMLCreater.h"
#include "MapData.h"
#include "MoveSprite.h"
#include "StaticValue.h"
#include "MapGoods.h"
#include "paddle.h"
#include "WorldOutLook.h"
#include "Server.h"
#include "PlistPath.h"
#include "cocos-ext.h"
#include "SendingDevice.h"
#include "MathLogic.h"
#include "Chair.h"
#include "ChairPart.h"
#include "ShowBackground.h"
USING_NS_CC;
USING_NS_CC_EXT;
Server g_server;

// on "init" you need to initialize your instance
void MapWindow::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	CCLayer::onEnter();

}
bool MapWindow::init()
{
    //////////////////////////////
	m_currentSelect = NULL;
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    load();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    m_winSize = visibleSize;

//	CCSprite* _background = CCSprite::create("mapResources/baseMap.jpg");
//	_background->setAnchorPoint(CCPoint(0,0));
//	this->addChild(_background);
//    
     std::string path=CCFileUtils::sharedFileUtils()->fullPathForFilename("HelloWorld.png");
    CCLog("000");
    CCLog("%s", path.c_str());
    
    m_showBackground = ShowBackground::create();
    this->addChild(m_showBackground);
    
	CCTMXTiledMap* _tiledMap = CCTMXTiledMap::create("mapResources/baseMap.tmx");
	_tiledMap->setPosition(CCPoint());
	this->addChild(_tiledMap);
CCLog("111");
	//MapXMLCreater::createXML(_tiledMap);
	MapData::createMapData(_tiledMap,"mapData.xml");
	MapData::m_selectObj = std::bind(&MapWindow::selectObjCallback, this, std::placeholders::_1, std::placeholders::_2);
	MapData::initMapObject("send", "send");

    CCLog("222");
	g_server.init();
	
	//设置起始和终点
	m_offsetPoint = CCPoint(850,200);
	m_orignPoint = CCDirector::sharedDirector()->getWinSize()/2 + m_offsetPoint ;//+ CCSize(0, 100);
CCLog("333");
	m_player = new MoveSprite(std::bind(&MapWindow::moveDone, this, std::placeholders::_1, std::placeholders::_2));
	_tiledMap->addChild(m_player, BASE_ZODER);
	m_player->setPosition(m_orignPoint);//设置人物的起始的世界坐标
	m_player->m_startX =MapData::getMapPositionByWorldPosition(m_orignPoint).x;
	m_player->m_startY =MapData::getMapPositionByWorldPosition(m_orignPoint).y;
	m_player->m_x = m_player->m_startX;
	m_player->m_y = m_player->m_startY;
	m_player->setMotionStreak("mapResources/man/idle0.png");
	//构造地图物体
	MapData::initTable("table_p", "table_p");
	MapData::initChairPart("chairPart_p", "chairPart_p");
	MapData::initChair("chair_p", "chair_p");
	MapData::initNPC("npc_p", "npc_p");
	MapData::initSendingDevice("send_p", "send_p");
CCLog("444");
	//设置服务器接口
	g_server.m_sendPathList = std::bind(&MoveSprite::recvPathList, m_player, std::placeholders::_1);

	this->scheduleUpdate();

	
    return true;
}

void MapWindow::update(float dt)
{
	//移动层
	this->setPosition(m_orignPoint - m_player->getPosition() - m_offsetPoint);
	if (m_player->getIsMoving())
	{
		if (m_worldOutLookCallback)
		{
			m_worldOutLookCallback(m_player->getPosition());
		}
        
        m_showBackground->show(m_player->getPosition().x, m_player->getPosition().y);
	}
}

CCRect getBoundingBox(float x, float y, float width, float height)
{
	return CCRect(x - width/2, y - height/2, width, height);
}

bool MapWindow::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint _p = touch->getLocation();
	if(m_worldOutLookRect.containsPoint(_p))
	{
		return false;
	}

	m_currentSelect = NULL;
	auto nodePosition = convertToNodeSpace( touch->getLocation() );
	m_player ->startMove(MapData::getMapPositionByWorldPosition(nodePosition));

	return true;
}

void MapWindow::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

void MapWindow::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

}

void MapWindow::moveDone( MoveSprite* obj, CCPoint point )
{
	m_player->m_display->idle();
	if (m_currentSelect)
	{
		m_currentSelect->setSelect(false);
		switch (m_currentSelect->m_type)
		{
		case NONE_TYPE:
			{
				break;
			}
		case NPC_TYPE:
			{
				break;
			}
		case SEND_TYPE:
			{
				CCFadeOut* _fadeOut = CCFadeOut::create(0.2);
				CCTargetedAction* _targetFadeOut = CCTargetedAction::create(m_player->m_display, _fadeOut);

				CCFadeIn* _fadeIn = CCFadeIn::create(0.2);
				CCTargetedAction* _targetIn = CCTargetedAction::create(m_player->m_display, _fadeIn);

				SendingDevice* _currentSelect = (SendingDevice*)m_currentSelect;
				m_player->runAction(CCSequence::create(_targetFadeOut, CCMoveTo::create(1,_currentSelect->m_target), _targetIn, CCCallFunc::create(this,SEL_CallFunc(&MapWindow::sendDone)),NULL));//setPosition(m_currentSelect->m_target);

				break;
			}
		case TABLE_TYPE:
			{
				break;
			}
		case CHAIR_TYPE:
			{
				Chair* _currentSelect = (Chair*)m_currentSelect;
				int _chairZoder = _currentSelect->getZOrder();
				CCSize _size= _currentSelect->getContentSize();
				m_player->setZOrder(_chairZoder+1);
				m_player->setPosition(_currentSelect->getPosition() +CCPoint(_size.width/2, _size.height*1.1));
				m_player->m_display->sitByChairDirection(_currentSelect->m_chairLocation);
				//_currentSelect->m_chairPart->setVisible(true);
				
				break;
			}
		case CHAIRPART_TYPE:
			{
				break;
			}
		default:
			break;
		}
	}
}

void MapWindow::selectObjCallback( CCPoint point, Paddle* selectObj )
{
	m_currentSelect = selectObj;
}

void MapWindow::worldOutlookTouch( CCPoint point )
{
	m_currentSelect = NULL;
	
	m_player ->startMove(MapData::getMapPositionByWorldPosition(point));
}

void MapWindow::load()
{
	for (int i = 0; i< g_AnimationFileCount; i++)
	{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(g_AnimationFile[i].name);
	}
}

void MapWindow::sendDone()
{
	if (m_worldOutLookCallback)
	{
		m_worldOutLookCallback(m_player->getPosition());
	}
}
