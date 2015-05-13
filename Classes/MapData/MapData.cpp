#include "MapData.h"

MapAttribute MapData::m_mapAttribute;

CCTMXTiledMap* MapData::m_tiledMap;

 MapPathXML MapData::m_opcityPathXml;
 
 std::vector< std::vector<PathSprite*>> MapData::m_opcityInspectArray;

void MapData::createMapData(CCTMXTiledMap* tiledMap, std::string mapPath)
{
	m_tiledMap = tiledMap;
	m_mapAttribute.m_mapSize = tiledMap->getMapSize();
	m_mapAttribute.m_tiledSize = tiledMap->getTileSize();
    m_mapAttribute.m_mapWorldSize = CCSize( m_mapAttribute.m_mapSize.width * m_mapAttribute.m_tiledSize.width, m_mapAttribute.m_mapSize.height * m_mapAttribute.m_tiledSize.height);
 	getMapdataFromXML(mapPath);

	{
		std::string & _str = m_opcityPathXml.m_data;
		int  _width = m_opcityPathXml.m_size.width;
		int  _height = m_opcityPathXml.m_size.height;
		int index = 0;

		for (int j = 0;  j < _width; j++) {
			std::vector<PathSprite*> _pathSprite;
			m_opcityInspectArray.push_back(_pathSprite);
			for (int i = 0;  i < _height; i++) {
				index = j * _height + i;
				if (_str[index]=='1') {

					PathSprite* _pathSprite = new PathSprite();
					_pathSprite->m_x = j;
					_pathSprite->m_y =i;

					m_opcityInspectArray[j].push_back(_pathSprite); //把地图中所有的点一一对应放入检测列表中
				}
				else
				{
					m_opcityInspectArray[j].push_back(NULL);
				}
			}
		}	
	}
}

void MapData::getMapdataFromXML( std::string mapPath )
{
	std::string wirtePath      = CCFileUtils::sharedFileUtils()->fullPathForFilename(mapPath.c_str()); //CCFileUtils::sharedFileUtils()->getWritablePath()+mapPath;//"mapData.xml";
    CCLog("%s", wirtePath.c_str());
    
    FILE *fp = fopen(wirtePath.c_str(),"rb");
    if(fp)
    {
        CCLog("ok");
    }
    else
    {
        CCLog("fail");
    }
    
	TiXmlDocument* myDocument = new TiXmlDocument(wirtePath.c_str());
	myDocument->LoadFile();
CCLog("111");
	TiXmlElement* MapDataElement = myDocument->RootElement();  // MapData
    CCLog("111");
	std::string _strwidth = MapDataElement->Attribute("width");  //获得student的name属性
	std::string _strheight = MapDataElement->Attribute("height");  //获得student的name属性
CCLog("111");
	m_opcityPathXml.m_size.width =std::atoi( _strwidth.c_str() );
	m_opcityPathXml.m_size.height =std::atoi( _strheight.c_str() );
	TiXmlElement* roadDataElement = MapDataElement->FirstChildElement();
	//m_roadPathXml.m_data = roadDataElement->GetText();
CCLog("111");
	TiXmlElement* obstaclesElement = roadDataElement->NextSiblingElement();
	//m_obstaclesPathXml.m_data = obstaclesElement->GetText();

	TiXmlElement* opcityElement = obstaclesElement->NextSiblingElement();
	m_opcityPathXml.m_data = opcityElement->GetText();
CCLog("111");
	delete myDocument;
}

CCPoint MapData::getWorldPositionByMapPosition( CCPoint point )
{
	return CCPoint(m_mapAttribute.m_tiledSize.width * point.x, (m_mapAttribute.m_mapSize.height - point.y)*m_mapAttribute.m_tiledSize.height);
}

CCPoint MapData::getMapPositionByWorldPosition( CCPoint point )
{
	return CCPoint((int)(point.x/m_mapAttribute.m_tiledSize.width),(int)(m_mapAttribute.m_mapSize.height - point.y/m_mapAttribute.m_tiledSize.height) );
}