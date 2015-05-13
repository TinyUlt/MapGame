#include "DisplaySprite.h"
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
float abs(float a)
{
	if (a < 0) {
		a = -a;
	}
	return a;
}
#endif

DisplaySprite::DisplaySprite(const char* name):m_currentAnimationDirection(0)
{
	init(name);
	this->autorelease();

	this->getAnimation()->play("sit0");
	this->setAnchorPoint(CCPoint(0.5, 0.25));
}


DisplaySprite::~DisplaySprite(void)
{
}

void DisplaySprite::walkByAngle( float angle )
{
	int _index=0;
	int _oldAngleOffset = 360;
	if (angle >= 360 - 22.5)
	{
		angle  =  - angle;
	}
	for (int i = 0 ; i < 8; i++)
	{
		float _angleOffset =abs( i * 45 - angle);
		
		if (_oldAngleOffset > _angleOffset)
		{
			_oldAngleOffset = _angleOffset;
			_index = i;
		}
	}
	if (_index  != m_currentAnimationDirection)
	{
		getAnimation()->play(g_walk[_index].c_str());
		m_currentAnimationDirection = _index;
	}
	

// 	for (int i = 1; i <= 8; i++)
// 	{
// 		if (angle <= 45 * i -22.5)
// 		{
// 			if (i-1 == m_currentAnimationDirection)
// 			{
// 				break;
// 			}
// 			getAnimation()->play(g_walk[i-1].c_str());
// 			m_currentAnimationDirection = i-1;
// 			break;
// 		}
// 		if (angle>45 * 8 -22.5)
// 		{
// 			if (8-1 == m_currentAnimationDirection)
// 			{
// 				break;
// 			}
// 			getAnimation()->play(g_walk[8-1].c_str());
// 			m_currentAnimationDirection = 8-1;
// 			break;
// 		}
// 	}
}

void DisplaySprite::idle(  )
{
	if (m_currentAnimationDirection>=0)
	{
		getAnimation()->play(g_idle[m_currentAnimationDirection].c_str());
	}
	m_currentAnimationDirection = -1;
}

void DisplaySprite::sitByChairDirection( int location )
{
	getAnimation()->play(g_sit[location].c_str());
	//this->setAnchorPoint(CCPoint(0, 0));
	this->setAnchorPoint(CCPoint(0.5, 0.5));

}
