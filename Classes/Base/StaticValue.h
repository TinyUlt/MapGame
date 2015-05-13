#pragma once
// #define MAP_WIDTH 600//要比tmx中的map大1
// #define MAP_HEIGHT 600
#define BASE_ZODER 100000
//#define MOVE_SPEED 1/200.0

 #define PRECISE_SEARCH_PATH//精确的寻 路系统, 需要消耗额外的运算(魔兽争霸级的!)
// #define CREATE_MAP_DATA//创建地图数据
// #define LOCAL_SERVER//是否是本地服务器
//#define PHP_SERVER

#define CREATE_WITHCONTENSIZE(__TYPE__) \
	static __TYPE__* createWithContentSize(CCSize size) \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	pRet->initWithTexture();\
	pRet->setContentSize(size);\
	pRet->autorelease();\
	pRet->enter();\
	return pRet;\
}
