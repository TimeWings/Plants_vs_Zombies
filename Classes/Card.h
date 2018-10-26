#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "BulletLayer.h"
#include "Plants.h"
using namespace std;
using namespace cocos2d;

template <class T>
class Card :public Entity
{
public:
	Card();
	~Card();

	//template <class T>
	
	string plantsTypeName;
	bool isFollowingMouse = false;
	Sprite* plantSprite;

	template <class T>
	void BindPlant()
	{
		plantsTypeName = typeid(T).name();
	}

	template <class T>
	void PutPlant(Point position, int row)
	{
		T* t = new T(position, row);
	}

	void addLayer(Node * entity)
	{
		BulletLayer* bl = BulletLayer::getInstance();
		bl->addChild(entity);
	}

	void removeLayer(Node * entity)
	{
		BulletLayer* bl = BulletLayer::getInstance();
		bl->removeChild(entity);
	}

	Card(Point position, int row)
	{
		Sprite* sprite = Sprite::create("cardbakcground\\card_icon_green.png");
		this->setImg(sprite);
		
		sprite->retain();
		sprite->setScale(1.0);
		//this->Scale = this->getImg()->getScale();
		sprite->setPosition(position);
		addLayer(sprite);
		plantsTypeName = typeid(T).name();

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event *event)
		{
			//EventMouse* e = (EventMouse*)event;
			//string str = "Mouse Down detected, Key: ";
			//cout << e->getCursorX()<<","<<e->getCursorY() << endl;
			//auto target = static_cast<Sprite*>(touch->getCurrentTarget());
			//Point locationInNode = target->convertToNodeSpace(e->getLocation());

			Point clickLocation = touch->getLocation();
			Size s = sprite->getContentSize();
			Rect rect = Rect(position.x - s.width / 2, position.y - s.height / 2, s.width, s.height);

			//cout << target->getPositionX() << "," << target->getPositionY() << endl;
			//cout << locationInNode.x << "," << locationInNode.y << endl;
			//cout << position.x << "," << position.y << endl;
			//cout << clickLocation.x << ","<<clickLocation.y << endl;
			// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
			if (rect.containsPoint(clickLocation))
			{
				//log("sprite began... x = %f, y = %f", clickLocation.x, clickLocation.y);
				//target->setOpacity(180);
				//T* plant = new T(position, row);
				string className = typeid(T).name();
				className = className.erase(0, 6);
				string str = string("Card\\") + className + string(".png");
				plantSprite = Sprite::create(str.c_str());
				plantSprite->setScale(0.3);
				plantSprite->setPosition(clickLocation);
				plantSprite->retain();
				addLayer(plantSprite);
				cout << "click " << plantsTypeName << " card" << endl;
				isFollowingMouse = true;
				return true;

			}
			return false;
		};
		listener->onTouchMoved = [=](Touch* touch, Event *event)
		{
			if (isFollowingMouse)
			{
				Point clickLocation = touch->getLocation();
				plantSprite->setPosition(clickLocation);
			}
			//return true;
		};
		listener->onTouchEnded = [=](Touch* touch, Event *event)
		{
			Point clickLocation = touch->getLocation();
			if (isFollowingMouse == true)
			{
				removeLayer(plantSprite);
				PutPlant<T>(clickLocation, 3);
			}
			//return true;
		};
		//this->setTouchEnabled(true);
		//listener->setSwallowTouches(false);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
	}
};

