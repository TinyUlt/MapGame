#include "MapXMLCreater.h"
#include "tinyxml.h"

void MapXMLCreater::createXML(CCTMXTiledMap* tiledMap)//"baseMap.tmx"
{
	

	string wirtePath      =   CCFileUtils::sharedFileUtils()->getWritablePath()+"mapData.xml";

    
    CCLog("%s", wirtePath.c_str());
    
	CCSize m_mapSize = tiledMap->getMapSize();//获取地图的尺寸 地图单位
	CCSize m_tileSize = tiledMap->getTileSize();//获取瓦片的尺寸  世界单位
	CCTMXLayer* m_road = tiledMap->layerNamed("road");//行走路径的地图
	//CCTMXLayer* m_obstacles = tiledMap->layerNamed("obstacles");//障碍物路径的地图
	CCTMXLayer* m_opcityPart = tiledMap->layerNamed("opcityPart");//透明路径的地图
	CCTMXLayer* m_objObs = tiledMap->layerNamed("objObs");//透明路径的地图


	
	TiXmlDocument *mapDocument = new TiXmlDocument();

	TiXmlElement *MapDataElement = new TiXmlElement("MapData");
	mapDocument->LinkEndChild(MapDataElement);

	char ch[10];
	sprintf(ch , "%d", (int)m_mapSize.width);
	MapDataElement->SetAttribute("width", ch);
	sprintf(ch , "%d", (int)m_mapSize.height);
	MapDataElement->SetAttribute("height", ch);

	{
		TiXmlElement *NameElement = new TiXmlElement("roadData");

		MapDataElement->LinkEndChild(NameElement);

		string _str;
		for (int j = 0;  j < m_mapSize.width; j++) {
			for (int i = 0;  i < m_mapSize.height ; i++) {
				CCSprite* _sp = m_road->tileAt(CCPoint(j, i));
				CCSprite* _objObs = m_objObs->tileAt(CCPoint(j, i));
				if (_sp && !_objObs ) {
					_str = _str + "1";
				}
				else
				{
					_str = _str + "0";
				}
			}
		}


		TiXmlText *NameContent = new TiXmlText(_str.c_str());

		NameElement->LinkEndChild(NameContent);
	}
	{
		TiXmlElement *NameElement = new TiXmlElement("obstaclesData");

		MapDataElement->LinkEndChild(NameElement);

		string _str;
//		for (int j = 0;  j < m_mapSize.width; j++) {
//			for (int i = 0;  i < m_mapSize.height ; i++) {
//				CCSprite* _sp = m_obstacles->tileAt(CCPoint(j, i));
//				CCSprite* _objObs = m_objObs->tileAt(CCPoint(j, i));
//				if (_sp || _objObs) {
//					_str = _str + "1";
//				}
//				else
//				{
//					_str = _str + "0";
//				}
//			}
//		}

        for (int j = 0;  j < m_mapSize.width; j++) {
            for (int i = 0;  i < m_mapSize.height ; i++) {
                CCSprite* _sp = m_road->tileAt(CCPoint(j, i));
                CCSprite* _objObs = m_objObs->tileAt(CCPoint(j, i));
                if (_sp && !_objObs ) {
                    _str = _str + "0";
                }
                else
                {
                    _str = _str + "1";
                }
            }
        }

		TiXmlText *NameContent = new TiXmlText(_str.c_str());

		NameElement->LinkEndChild(NameContent);
	}
	{
		TiXmlElement *NameElement = new TiXmlElement("opcityPart");

		MapDataElement->LinkEndChild(NameElement);

		string _str;
		for (int j = 0;  j < m_mapSize.width; j++) {
			for (int i = 0;  i < m_mapSize.height ; i++) {
				CCSprite* _sp = m_opcityPart->tileAt(CCPoint(j, i));
				if (_sp) {
					_str = _str + "1";
				}
				else
				{
					_str = _str + "0";
				}
			}
		}


		TiXmlText *NameContent = new TiXmlText(_str.c_str());

		NameElement->LinkEndChild(NameContent);
	}

	mapDocument->SaveFile(wirtePath.c_str());
	
}
