#include "GameScene.h"
#include "MapWindow.h"
#include "WorldOutLook.h"
#include "MoveSprite.h"
GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

CCScene* GameScene::createScene()
{
	//创建大地图和小地图
    CCSize _winSize = CCDirector::sharedDirector()->getWinSize();
    
	MapWindow* _mapWindw = MapWindow::create();
	WorldOutLook* _worldOutLook = WorldOutLook::create("mapResources/baseMap.jpg","mapResources/playerPosition.png");
	

	//设置对方的接口
	_mapWindw->m_worldOutLookCallback = std::bind(&WorldOutLook::playerMoving, _worldOutLook, std::placeholders::_1);
	_mapWindw->m_player->m_sendPathListToWorldOutlook = std::bind(&WorldOutLook::recvPathList, _worldOutLook, std::placeholders::_1);
	_worldOutLook->m_touchMap = std::bind(&MapWindow::worldOutlookTouch, _mapWindw, std::placeholders::_1);

	//设置大地图中小地图的位置为不可触摸
	CCRect _rect = _worldOutLook->m_map->boundingBox();
    _worldOutLook->setPosition(CCPoint(180, _winSize.height- _rect.size.height/2));
	_rect.origin = _worldOutLook->getPosition() - _rect.size/2;
	_mapWindw->m_worldOutLookRect = _rect;
    
    
	CCScene* _scene = CCScene::create();
	_scene->addChild(_mapWindw);
	_scene->addChild(_worldOutLook);
	return _scene;
}
