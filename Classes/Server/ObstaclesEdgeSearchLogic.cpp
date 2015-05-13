#include "ObstaclesEdgeSearchLogic.h"
#include "StaticValue.h"
#include "PathSprite.h"


CCPoint ObstaclesEdgeSearchLogic::calculatePath( int startX, int startY)
{
	clearPath();
#if 0
	//得到开始点的节点
	PathSprite*    _endNode= m_obstaclesInspectArray[startX][startY];
	//得到结束点的节点
	PathSprite*   _startNode = m_obstaclesInspectArray[endX][endY];

	//因为是开始点 把到起始点的距离设为0, F值也为0
	_startNode->m_costToSource = 0;
	_startNode->m_FValue = 0;

	//把已经检测过的点从检测列表中删除
	m_obstaclesInspectArray[endX][endY] = NULL;
	//把该点放入已经检测过点的列表中
	m_haveInspectList.push_back(_startNode);
	//然后加入开放列表
	m_openList.push_back(_startNode);

	PathSprite* _node = NULL;
	while (true)
	{
		//得到离起始点最近的点(如果是第一次执行, 得到的是起点)
		_node = getMinPathFormOpenList();
		if (!_node)
		{
			//不到路径
			break;
		}
		//把计算过的点从开放列表中删除
		removeObjFromOpenList( _node);
		int _x = _node->m_x;
		int _y = _node->m_y;

		//
		if(m_roadInspectArray[_x][_y])
		if (_x ==startX && _y == startY)
		{
			break;
		}

		//检测8个方向的相邻节点是否可以放入开放列表中

		PathSprite* _adjacent = NULL;

		_adjacent = getObjFromInspectArray(  _x +1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x , _y -1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x , _y+1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray( _x + 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x +1, _y-1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);

		_adjacent = getObjFromInspectArray(  _x -1, _y+1);
		inspectTheAdjacentNodes(_node, _adjacent, _endNode);


	}

	while (_node)
	{
		//把路径点加入到路径列表中
		m_pathList.push_back(CCPoint(_node->m_x, _node->m_y) );
		_node = _node->m_parent;
	}
#else
	//得到开始点的节点
	PathSprite*   _startNode = m_obstaclesInspectArray[startX][startY];
	//得到结束点的节点
	//PathSprite*  _endNode = m_obstaclesInspectArray[endX][endY];

	//因为是开始点 把到起始点的距离设为0, F值也为0
	_startNode->m_costToSource = 0;
	_startNode->m_FValue = 0;

	//把已经检测过的点从检测列表中删除
	m_obstaclesInspectArray[startX][startY] = NULL;
	//把该点放入已经检测过点的列表中
	m_haveInspectList.push_back(_startNode);
	//然后加入开放列表
	m_openList.push_back(_startNode);

	PathSprite* _node = NULL;
	while (true)
	{
		//得到离起始点最近的点(如果是第一次执行, 得到的是起点)
		_node = getMinPathFormOpenList();
		if (!_node)
		{
			return CCPoint(-1,-1);
		}
		//把计算过的点从开放列表中删除
		removeObjFromOpenList( _node);
		int _x = _node->m_x;
		int _y = _node->m_y;
		 
		//
		CCPoint _point[4] = {CCPoint(_x, _y+1),CCPoint(_x, _y-1),CCPoint(_x+1, _y),CCPoint(_x -1, _y)};
		for (int i = 0 ; i < 4; i++)
		{
			if ((int)_point[i].x <0 || (int)_point[i].y <0 || (int)_point[i].x >= m_roadInspectArray.size() ||(int)_point[i].y >= m_roadInspectArray[0].size() )
			{
				continue;
			}
			if(m_roadInspectArray[(int)_point[i].x][(int)_point[i].y])
			{
				resetInspectArray();
				return _point[i];
			}
		}
		
		//检测8个方向的相邻节点是否可以放入开放列表中
		PathSprite* _adjacent = NULL;

		_adjacent = getObjFromInspectArray(  _x +1, _y);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray(  _x , _y -1);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray(  _x -1, _y);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray(  _x , _y+1);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray( _x + 1, _y + 1);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray(  _x +1, _y-1);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray(  _x -1, _y - 1);
		inspectTheAdjacentNodes(_node, _adjacent);

		_adjacent = getObjFromInspectArray(  _x -1, _y+1);
		inspectTheAdjacentNodes(_node, _adjacent);
	}

#endif
}

PathSprite* ObstaclesEdgeSearchLogic::getMinPathFormOpenList()
{
	if (m_openList.size()>0) {
		PathSprite* _sp =* m_openList.begin();
		for ( std::vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
		{
			if ((*iter)->m_FValue < _sp->m_FValue)
			{
				_sp = *iter;
			}
		}
		return _sp;
	}
	else
	{
		return NULL;
	}

}

PathSprite* ObstaclesEdgeSearchLogic::getObjFromInspectArray( int x, int y )
{
	if (x >=0 && y >=0 && x < m_mapSize.width && y < m_mapSize.height) {
		return m_obstaclesInspectArray[x][y];
	}
	return  NULL;
}

void ObstaclesEdgeSearchLogic::inspectTheAdjacentNodes( PathSprite* node, PathSprite* adjacent )
{
	if (adjacent)
	{

		float F , G, H1, H2, H3;
		adjacent->m_costToSource = node->m_costToSource + calculateTwoObjDistance(node, adjacent);//获得累计的路程
		G = adjacent->m_costToSource;

	
		//Dijkstra算法
		F = G;

#
		adjacent->m_FValue = F;

		adjacent->m_parent = node;//设置父节点


		m_haveInspectList.push_back(adjacent);
		node->m_child = adjacent;//设置子节点

		m_obstaclesInspectArray[adjacent->m_x][adjacent->m_y] = NULL;//把检测过的点从检测列表中删除
		m_openList.push_back(adjacent);//加入开放列表
	}
}

float ObstaclesEdgeSearchLogic::calculateTwoObjDistance( PathSprite* obj1, PathSprite* obj2 )
{

	float _x = abs(obj2->m_x - obj1->m_x);
	float _y = abs(obj2->m_y - obj1->m_y);

	return _x + _y;
}

void ObstaclesEdgeSearchLogic::clearPath()
{
	resetInspectArray();

	//把移除了障碍物的地图放入检测列表中
	m_openList.clear();
	m_pathList.clear();
	m_haveInspectList.clear();

}

void ObstaclesEdgeSearchLogic::resetInspectArray()
{
	for (std::vector<PathSprite*>::iterator iter = m_haveInspectList.begin(); iter != m_haveInspectList.end(); iter++)
	{
		(*iter)->m_costToSource = 0;
		(*iter)->m_FValue = 0;
		(*iter)->m_parent = NULL;
		(*iter)->m_child = NULL;

		m_obstaclesInspectArray[(*iter)->m_x][(*iter)->m_y] = (*iter);
	}
}

bool ObstaclesEdgeSearchLogic::removeObjFromOpenList( PathSprite* sprite )
{
	if (!sprite) {
		return  false;
	}
	for ( std::vector<PathSprite*>::iterator iter = m_openList.begin(); iter !=  m_openList.end(); iter++)
	{
		if (*iter == sprite)
		{
			m_openList.erase(iter);
			return true;
		}
	}
	return false;

}  
