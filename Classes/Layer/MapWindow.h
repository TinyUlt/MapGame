#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
#include <functional>
using namespace std;
class MoveSprite;
class ShowBackground;
class Paddle;
class MapWindow : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
    // a selector callback
    
	void onEnter();
    // implement the "static node()" method manually
    CREATE_FUNC(MapWindow);
	void load();//加载资源
	void update(float dt);//跟新大地图(行走时, 人不动, 地图跟着人动);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	void moveDone(MoveSprite* obj, CCPoint point);//移动结束回调

	void selectObjCallback(CCPoint point, Paddle* selectObj);//选择物体回调

	void worldOutlookTouch(CCPoint point);//触摸小地图时发送到该函数

	void sendDone();//传送结束时执行

	cocos2d::CCPoint m_offsetPoint;
	cocos2d::CCPoint m_orignPoint;

	MoveSprite* m_player;//人物
	Paddle* m_currentSelect;//当前选中的物体

	CCRect m_worldOutLookRect;//小地图尺寸
	function<void(CCPoint)> m_worldOutLookCallback;//发送点给小地图
	
    ShowBackground* m_showBackground;
    
    CCSize m_winSize;


};

#endif // __HELLOWORLD_SCENE_H__
