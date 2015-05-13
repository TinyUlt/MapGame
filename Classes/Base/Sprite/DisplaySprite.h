#pragma once
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;
const string g_walk[8] = {"walk4", "walk5", "walk6", "walk7", "walk0", "walk1", "walk2", "walk3"};
const string g_idle[8] = {"idle4", "idle5", "idle6", "idle7", "idle0", "idle1", "idle2", "idle3"};
const string g_sit[8] =  {"sit4", "sit5", "sit6", "sit7", "sit0", "sit1", "sit2", "sit3"};
//const string g_sit[8] =  {"sit3", "sit2", "sit1", "sit7", "sit0", "sit7", "sit5", "sit4"};
class DisplaySprite:public CCArmature
{
public:
	DisplaySprite(const char* name);
	~DisplaySprite(void);

	

	//bool init();
	void walkByAngle(float angle);
	void idle();
	void sitByChairDirection(int location);
	int m_currentAnimationDirection;
};

