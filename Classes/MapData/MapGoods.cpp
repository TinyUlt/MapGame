#include "MapGoods.h"
#include "paddle.h"
#include "StaticValue.h"
#include "MapData.h"
#include "NPC.h"
#include "SendingDevice.h"
#include "Table.h"
#include "Chair.h"
#include "ChairPart.h"
std::function<void(CCPoint point, Paddle* selectObj)> MapGoods::m_selectObj;


void MapGoods::initMapObject( const char* layerName, const char* objName )
{
// 	//ͼƬ��
// 	CCTMXLayer* _layer = MapData::m_tiledMap->layerNamed(layerName);
// 	if (!_layer)
// 	{
// 		return;
// 	}
// 	//�����
// 	CCTMXObjectGroup* objectGroup = MapData::m_tiledMap->objectGroupNamed(objName);
// 	if (!objectGroup)
// 	{
// 		return;
// 	}
// 	//�õ����еĶ���
// 	CCArray* _array = objectGroup->getObjects();
// 	CCObject *_obj;
// 	CCARRAY_FOREACH(_array, _obj )
// 	{
// 		//��һ��
// 		CCDictionary* _dictionary  = (CCDictionary*)_obj;
// 
// 		//�õ�����
// 		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//���絥λ
// 		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
// 		float _widht = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//���絥λ
// 		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
// 		
// 		CCString* _type = ((CCString*)_dictionary->objectForKey("type"));//��������
// 		CCString* _enableSit = ((CCString*)_dictionary->objectForKey("enableSit"));//�Ƿ�������
// 		CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//�Ƿ��ܴ���
// 		CCString* _enablePickUp =(( CCString*)_dictionary->objectForKey("enablePickUp"));//�Ƿ��ܴ���
// 		CCString* _chairType =(( CCString*)_dictionary->objectForKey("chairType"));//�Ƿ��д��͹���
// 
// 		Paddle* _parent = Paddle::paddleWithContentSize(CCSize(_widht, _height));//����һ��������
// 
// 		//������������
// 		
// 
// 		if (_chairType)
// 		{
// 			_parent->m_chairType = _chairType->intValue();
// 		}
// 		
// 		_parent->m_type = _type?  (OBJTYPE)_type->intValue():NONE_TYPE;
// 		_parent->m_enableSit = _enableSit? _enableSit->boolValue():false;
// 		_parent->m_enableTouch = _enableTouch?_enableTouch->boolValue():false;
// 		if (_parent->m_enableTouch)
// 		{
// 			_parent->m_selectCallback =m_selectObj;
// 		}
// 		if (_enablePickUp)
// 		{
// 			_parent->m_enablePickUp = _enablePickUp->boolValue();
// 			_parent->m_selectCallback =m_selectObj;
// 		}
// 		else
// 		{
// 			_parent->m_enablePickUp =false;
// 		}
// 		//��������λ��
// 		CCPoint _offset = CCPoint(_x, _y  );//ƫ����
// 		_parent->setPosition(_offset);
// 		_parent->setAnchorPoint(CCPoint(0,0));
// 
// 		for (int i = 0; i < _widht/MapData::m_mapAttribute.m_tiledSize.width; i++)
// 		{
// 			for (int j = 0; j < _height/MapData::m_mapAttribute.m_tiledSize.height; j++)
// 			{
// 				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/MapData::m_mapAttribute.m_tiledSize.width+i,MapData::m_mapAttribute.m_mapSize.height-1-_y/MapData::m_mapAttribute.m_tiledSize.height-j));
// 				if (_Sprite)
// 				{
// 
// 					_Sprite->retain();
// 					_Sprite->removeFromParent();
// 					_Sprite->setPosition(_Sprite->getPosition()-_offset);
// 					_parent->addChild(_Sprite);
// 					_Sprite->release();
// 
// #if 0//���Ը�����
// 					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
// 					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
// 					CCSequence* seq = CCSequence::create(action, actionR, NULL);
// 					_Sprite->runAction(CCRepeatForever::create(seq));
// #endif
// 
// 				}
// 
// 			}
// 		}
// 
// 		//���ö������
// 		if (_parent->m_enablePickUp)
// 		{
// 			MapData::m_tiledMap->addChild(_parent, BASE_ZODER - MapData::getWorldPositionByMapPosition(MapData::m_mapAttribute.m_mapSize).y  );
// 		}
// 		else
// 		{
// 			MapData::m_tiledMap->addChild(_parent, BASE_ZODER - _y );
// 		}
// 
// 
// 	}
}

void MapGoods::initNPC( const char* layerName, const char* objName )
{
	//ͼƬ��
	CCTMXLayer* _layer = MapData::m_tiledMap->layerNamed(layerName);
	if (!_layer)
	{
		return;
	}
	//�����
	CCTMXObjectGroup* objectGroup = MapData::m_tiledMap->objectGroupNamed(objName);
	if (!objectGroup)
	{
		return;
	}
	//�õ����еĶ���
	CCArray* _array = objectGroup->getObjects();
	CCObject *_obj;

	CCARRAY_FOREACH(_array, _obj )
	{
		CCDictionary* _dictionary  = (CCDictionary*)_obj;

		//�õ�����
		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//���絥λ
		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
		float _widht = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//���絥λ
		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
		CCString* _name = ((CCString*)_dictionary->objectForKey("name"));
		CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//�Ƿ��ܴ���

		NPC* _parent = NPC::createWithContentSize(CCSize(_widht, _height));//����һ��������

		if (_name)
		{
			_parent->m_name = _name->getCString();
		}
		if (_enableTouch)
		{
			_parent->m_selectCallback =m_selectObj;
		}

		//��������λ��
		CCPoint _offset = CCPoint(_x, _y  );//ƫ����
		_parent->setPosition(_offset);
		_parent->setAnchorPoint(CCPoint(0,0));

		for (int i = 0; i < _widht/MapData::m_mapAttribute.m_tiledSize.width; i++)
		{
			for (int j = 0; j < _height/MapData::m_mapAttribute.m_tiledSize.height; j++)
			{
				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/MapData::m_mapAttribute.m_tiledSize.width+i,MapData::m_mapAttribute.m_mapSize.height-1-_y/MapData::m_mapAttribute.m_tiledSize.height-j));
				if (_Sprite)
				{

					_Sprite->retain();
					_Sprite->removeFromParent();
					_Sprite->setPosition(_Sprite->getPosition()-_offset);
					_parent->addChild(_Sprite);
					_Sprite->release();

#if 0//���Ը�����
					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
					CCSequence* seq = CCSequence::create(action, actionR, NULL);
					_Sprite->runAction(CCRepeatForever::create(seq));
#endif

				}

			}
		}

		//���ö������
		MapData::m_tiledMap->addChild(_parent, BASE_ZODER - _y );
	}
}

void MapGoods::initSendingDevice( const char* layerName, const char* objName )
{
	//ͼƬ��
	CCTMXLayer* _layer = MapData::m_tiledMap->layerNamed(layerName);
	if (!_layer)
	{
		return;
	}
	//�����
	CCTMXObjectGroup* objectGroup = MapData::m_tiledMap->objectGroupNamed(objName);
	if (!objectGroup)
	{
		return;
	}
	//�õ����еĶ���
	CCArray* _array = objectGroup->getObjects();
	CCObject *_obj;

	CCARRAY_FOREACH(_array, _obj )
	{
		CCDictionary* _dictionary  = (CCDictionary*)_obj;

		//�õ�����
		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//���絥λ
		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
		float _widht = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//���絥λ
		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
		CCString* _name = ((CCString*)_dictionary->objectForKey("name"));
		CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//�Ƿ��ܴ���
		CCString* _target =(( CCString*)_dictionary->objectForKey("target"));//�Ƿ��д��͹���

		SendingDevice* _parent =SendingDevice::createWithContentSize(CCSize(_widht, _height));//����һ��������
		
		if (_name)
		{
			_parent->m_name = _name->getCString();
		}
		if (_enableTouch)
		{
			_parent->m_selectCallback =m_selectObj;
		}
		if (_target)
		{
			CCArray* _arrayin = objectGroup->getObjects();
			CCObject *_objin;
			string _targetStr =  _target->getCString();
			_parent->m_targetName = _targetStr;
			CCARRAY_FOREACH(_arrayin, _objin )
			{
				CCDictionary* _dictionaryin  = (CCDictionary*)_objin;
				CCString* name = ((CCString*)_dictionaryin->objectForKey("name"));
				string _nameStr = name->getCString();
				if (_targetStr == _nameStr)
				{
					float _x = ((CCString*)_dictionaryin->objectForKey("x"))->floatValue();//���絥λ
					float _y= ((CCString*)_dictionaryin->objectForKey("y"))->floatValue();
					float _widht = ((CCString*)_dictionaryin->objectForKey("width"))->floatValue();//���絥λ
					float _height = ((CCString*)_dictionaryin->objectForKey("height"))->floatValue();
					_parent->m_target = CCPoint(_x + _widht/2, _y + _height/2);
					break;
				}
			}
			//_parent
		}
		//��������λ��
		CCPoint _offset = CCPoint(_x, _y  );//ƫ����
		_parent->setPosition(_offset);
		_parent->setAnchorPoint(CCPoint(0,0));

		for (int i = 0; i < _widht/MapData::m_mapAttribute.m_tiledSize.width; i++)
		{
			for (int j = 0; j < _height/MapData::m_mapAttribute.m_tiledSize.height; j++)
			{
				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/MapData::m_mapAttribute.m_tiledSize.width+i,MapData::m_mapAttribute.m_mapSize.height-1-_y/MapData::m_mapAttribute.m_tiledSize.height-j));
				if (_Sprite)
				{

					_Sprite->retain();
					_Sprite->removeFromParent();
					_Sprite->setPosition(_Sprite->getPosition()-_offset);
					_parent->addChild(_Sprite);
					_Sprite->release();

#if 0//���Ը�����
					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
					CCSequence* seq = CCSequence::create(action, actionR, NULL);
					_Sprite->runAction(CCRepeatForever::create(seq));
#endif

				}

			}
		}

		//���ö������
		MapData::m_tiledMap->addChild(_parent, BASE_ZODER - _y );
	}
}

void MapGoods::initTable( const char* layerName, const char* objName )
{
	//ͼƬ��
	CCTMXLayer* _layer = MapData::m_tiledMap->layerNamed(layerName);
	if (!_layer)
	{
		return;
	}
	//�����
	CCTMXObjectGroup* objectGroup = MapData::m_tiledMap->objectGroupNamed(objName);
	if (!objectGroup)
	{
		return;
	}
	//�õ����еĶ���
	CCArray* _array = objectGroup->getObjects();
	CCObject *_obj;

	CCARRAY_FOREACH(_array, _obj )
	{
		CCDictionary* _dictionary  = (CCDictionary*)_obj;

		//�õ�����
		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//���絥λ
		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
		float _widht = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//���絥λ
		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
		CCString* _name = ((CCString*)_dictionary->objectForKey("name"));
		CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//�Ƿ��ܴ���

		Table* _parent = Table::createWithContentSize(CCSize(_widht, _height));//����һ��������

		if (_name)
		{
			_parent->m_name = _name->getCString();
		}
		if (_enableTouch)
		{
			_parent->m_selectCallback =m_selectObj;
		}

		//��������λ��
		CCPoint _offset = CCPoint(_x, _y  );//ƫ����
		_parent->setPosition(_offset);
		_parent->setAnchorPoint(CCPoint(0,0));

		for (int i = 0; i < _widht/MapData::m_mapAttribute.m_tiledSize.width; i++)
		{
			for (int j = 0; j < _height/MapData::m_mapAttribute.m_tiledSize.height; j++)
			{
				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/MapData::m_mapAttribute.m_tiledSize.width+i,MapData::m_mapAttribute.m_mapSize.height-1-_y/MapData::m_mapAttribute.m_tiledSize.height-j));
				if (_Sprite)
				{

					_Sprite->retain();
					_Sprite->removeFromParent();
					_Sprite->setPosition(_Sprite->getPosition()-_offset);
					_parent->addChild(_Sprite);
					_Sprite->release();

#if 0//���Ը�����
					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
					CCSequence* seq = CCSequence::create(action, actionR, NULL);
					_Sprite->runAction(CCRepeatForever::create(seq));
#endif

				}

			}
		}

		//���ö������
		MapData::m_tiledMap->addChild(_parent, BASE_ZODER - _y );
	}
}

void MapGoods::initChair( const char* layerName, const char* objName )
{
	//ͼƬ��
	CCTMXLayer* _layer = MapData::m_tiledMap->layerNamed(layerName);
	if (!_layer)
	{
		return;
	}
	//�����
	CCTMXObjectGroup* objectGroup = MapData::m_tiledMap->objectGroupNamed(objName);
	if (!objectGroup)
	{
		return;
	}
	//�õ����еĶ���
	CCArray* _array = objectGroup->getObjects();
	CCObject *_obj;

	CCARRAY_FOREACH(_array, _obj )
	{
		CCDictionary* _dictionary  = (CCDictionary*)_obj;

		//�õ�����
		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//���絥λ
		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
		float _widht = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//���絥λ
		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
		CCString* _name = ((CCString*)_dictionary->objectForKey("name"));
		CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//�Ƿ��ܴ���
		CCString* _chairPartName =(( CCString*)_dictionary->objectForKey("chairPartName"));//�Ƿ��ܴ���
		CCString* _chairLocation =(( CCString*)_dictionary->objectForKey("chairLocation"));//�Ƿ��ܴ���
		
		Chair* _parent = Chair::createWithContentSize(CCSize(_widht, _height));//����һ��������

		if (_name)
		{
			_parent->m_name = _name->getCString();
		}
		if (_enableTouch)
		{
			_parent->m_selectCallback =m_selectObj;
		}
		if (_chairPartName)
		{
			std::string _str = _chairPartName->getCString();
			for (int i = 0; i < ChairPart::g_array.size(); i++)
			{
				if(_str == ChairPart::g_array[i]->m_name)
				{
					_parent->m_chairPart = ChairPart::g_array[i];
				}
			}
		}
		if (_chairLocation)
		{
			_parent->m_chairLocation =_chairLocation->intValue();
		}

		//��������λ��
		CCPoint _offset = CCPoint(_x, _y  );//ƫ����
		_parent->setPosition(_offset);
		_parent->setAnchorPoint(CCPoint(0,0));

		for (int i = 0; i < _widht/MapData::m_mapAttribute.m_tiledSize.width; i++)
		{
			for (int j = 0; j < _height/MapData::m_mapAttribute.m_tiledSize.height; j++)
			{
				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/MapData::m_mapAttribute.m_tiledSize.width+i,MapData::m_mapAttribute.m_mapSize.height-1-_y/MapData::m_mapAttribute.m_tiledSize.height-j));
				if (_Sprite)
				{

					_Sprite->retain();
					_Sprite->removeFromParent();
					_Sprite->setPosition(_Sprite->getPosition()-_offset);
					_parent->addChild(_Sprite);
					_Sprite->release();

#if 0//���Ը�����
					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
					CCSequence* seq = CCSequence::create(action, actionR, NULL);
					_Sprite->runAction(CCRepeatForever::create(seq));
#endif
				}
			}
		}

		//���ö������
		MapData::m_tiledMap->addChild(_parent, BASE_ZODER - _y );
	}
}

void MapGoods::initChairPart( const char* layerName, const char* objName )
{
	//ͼƬ��
	CCTMXLayer* _layer = MapData::m_tiledMap->layerNamed(layerName);
	if (!_layer)
	{
		return;
	}
	//�����
	CCTMXObjectGroup* objectGroup = MapData::m_tiledMap->objectGroupNamed(objName);
	if (!objectGroup)
	{
		return;
	}
	//�õ����еĶ���
	CCArray* _array = objectGroup->getObjects();
	CCObject *_obj;

	CCARRAY_FOREACH(_array, _obj )
	{
		CCDictionary* _dictionary  = (CCDictionary*)_obj;

		//�õ�����
		float _x = ((CCString*)_dictionary->objectForKey("x"))->floatValue();//���絥λ
		float _y= ((CCString*)_dictionary->objectForKey("y"))->floatValue();
		float _widht = ((CCString*)_dictionary->objectForKey("width"))->floatValue();//���絥λ
		float _height = ((CCString*)_dictionary->objectForKey("height"))->floatValue();
		CCString* _name = ((CCString*)_dictionary->objectForKey("name"));
		CCString* _enableTouch =(( CCString*)_dictionary->objectForKey("enableTouch"));//�Ƿ��ܴ���
		

		ChairPart* _parent = ChairPart::createWithContentSize(CCSize(_widht, _height));//����һ��������

		if (_name)
		{
			_parent->m_name = _name->getCString();
		}
		if (_enableTouch)
		{
			_parent->m_selectCallback =m_selectObj;
		}

		//��������λ��
		CCPoint _offset = CCPoint(_x, _y  );//ƫ����
		_parent->setPosition(_offset);
		_parent->setAnchorPoint(CCPoint(0,0));

		for (int i = 0; i < _widht/MapData::m_mapAttribute.m_tiledSize.width; i++)
		{
			for (int j = 0; j < _height/MapData::m_mapAttribute.m_tiledSize.height; j++)
			{
				CCSprite* _Sprite = _layer->tileAt(CCPoint(_x/MapData::m_mapAttribute.m_tiledSize.width+i,MapData::m_mapAttribute.m_mapSize.height-1-_y/MapData::m_mapAttribute.m_tiledSize.height-j));
				if (_Sprite)
				{

					_Sprite->retain();
					_Sprite->removeFromParent();
					_Sprite->setPosition(_Sprite->getPosition()-_offset);
					_parent->addChild(_Sprite);
					_Sprite->release();

#if 0//���Ը�����
					CCMoveBy* action = CCMoveBy::create(1,CCPoint(0,50));
					CCMoveBy* actionR = CCMoveBy::create(1,CCPoint(0,-50));
					CCSequence* seq = CCSequence::create(action, actionR, NULL);
					_Sprite->runAction(CCRepeatForever::create(seq));
#endif

				}

			}
		}

		//���ö������
		MapData::m_tiledMap->addChild(_parent, BASE_ZODER - _y +2);
		//_parent->setVisible(false);
	}
}


