#pragma once
#include "cocos2d.h"
class MapWindow;
class WorldOutLook;
USING_NS_CC;
class GameScene:public CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	static CCScene* createScene();

};

