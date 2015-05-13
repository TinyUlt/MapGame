#pragma once
#include "PathSearchLogic.h"
#include "ObstaclesEdgeSearchLogic.h"
#include <functional>
#include <vector>
using namespace std;
class Server
{
public:
	Server(void);
	~Server(void);
	void init();
	
	void startMove( CCPoint startPoint,  CCPoint endPoint );//接收数据

	std::function<void(std::vector<CCPoint>)> m_sendPathList;//发送数据

	CCPoint resetObjPosition(CCPoint point );//保证位置正确

	PathSearchLogic* m_pathSearchLogic;//路径数据
	ObstaclesEdgeSearchLogic* m_obstaclesEdgeSearchLogic;//障碍物数据
};

