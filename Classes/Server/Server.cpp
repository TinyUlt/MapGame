#include "Server.h"
#include "PathData.h"
#include "MapXMLCreater.h"
Server::Server(void)
{
}

Server::~Server(void)
{
}

void Server::init()
{
#if 1
    CCTMXTiledMap* _tiledMap = CCTMXTiledMap::create("mapResources/baseMap.tmx");
    MapXMLCreater::createXML(_tiledMap);
#endif
	PathData::createPathData("mapData.xml");
	m_pathSearchLogic = new PathSearchLogic(PathData::m_roadPathXml.m_size, PathData::m_roadInspectArray);
	m_obstaclesEdgeSearchLogic = new ObstaclesEdgeSearchLogic(PathData::m_roadPathXml.m_size, PathData::m_obstaclesInspectArray, PathData::m_roadInspectArray);
}

void Server::startMove( CCPoint startPoint, CCPoint endPoint )
{
	startPoint = resetObjPosition(startPoint);
	if (endPoint.x>=PathData::m_roadPathXml.m_size.width  || endPoint.y>=PathData::m_roadPathXml.m_size.height)
	{
		return;
	}
	PathSprite*_sp = PathData::m_roadInspectArray[(int)endPoint.x][(int)(endPoint.y)];
	if (_sp)
	{
		m_pathSearchLogic->calculatePath(startPoint.x, startPoint.y, _sp->m_x, _sp->m_y);

		if (m_sendPathList)
		{
			m_sendPathList(m_pathSearchLogic->m_pathList);
		}
	}
	else
	{
		_sp = PathData::m_obstaclesInspectArray[(int)endPoint.x][(int)(endPoint.y)];
		if (_sp)
		{
			CCPoint _point =m_obstaclesEdgeSearchLogic->calculatePath(_sp->m_x, _sp->m_y);
			if (_point.x !=-1 && _point.y !=-1)
			{

				m_pathSearchLogic->calculatePath(startPoint.x, startPoint.y, _point.x, _point.y);

				if (m_sendPathList)
				{
					m_sendPathList(m_pathSearchLogic->m_pathList);
				}
			}
		}
	}
}
CCPoint Server::resetObjPosition(CCPoint point )
{
	PathSprite* _sp = PathData::m_roadInspectArray[point.x][point.y];

	if (_sp)
	{
		return point;
	} 
	else
	{
		CCPoint _PArray[4] = {point + CCPoint(0, -1),point +  CCPoint(0, 1), point + CCPoint(-1, 0), point + CCPoint(1, 0)};

		for (int i = 0 ; i < 4 ; i++)
		{
			PathSprite* _up = PathData::m_roadInspectArray[_PArray[i].x][_PArray[i].y];
			if (_up)
			{
				return _PArray[i];
			}
		}
	}
	return point;
}