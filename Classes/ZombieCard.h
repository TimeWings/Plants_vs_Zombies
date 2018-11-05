#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "EntityLayer.h"
#include "Zombie.h"
using namespace std;
using namespace cocos2d;

template <class T>
class ZombieCard :public Entity
{
public:
	ZombieCard();
	~ZombieCard();
	string plantsTypeName;
	bool isFollowingMouse = false;
	int cost;
	Sprite* plantSprite;
	Sprite* plantFollowSprite;

	template <class T>
	void BindPlant()
	{
		plantsTypeName = typeid(T).name();
	}

	template <class T>
	T* PutPlant(Point position, int row, int col)
	{
		T*t = new T(position, row, col);
		return t;
	}

	void addLayer(Node * entity)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(entity);
	}

	void removeLayer(Node * entity)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->removeChild(entity);
	}
	ZombieCard(Point position)
	{

		Sprite* sprite = Sprite::create("cardbackground\\card_green.png");
		this->setImg(sprite);

		sprite->retain();
		//sprite->setScale(0.15f);
		sprite->setContentSize(Size(20, 30));
		sprite->setPosition(position);
		addLayer(sprite);

		string className = typeid(T).name();
		className = className.erase(0, 6);
		string str = string("Card\\") + className + string(".png");
		plantSprite = Sprite::create(str);
		auto position1 = position;
		position1.y += 0;
		plantSprite->setPosition(position1);
		plantSprite->setContentSize(Size(15, 20));
		plantSprite->retain();
		addLayer(plantSprite);

		plantsTypeName = typeid(T).name();

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event *event)
		{
			Point clickLocation = touch->getLocation();
			Size s = sprite->getContentSize();
			Rect rect = Rect(position.x - s.width*sprite->getScaleX() / 2, position.y - s.height*sprite->getScaleX() / 2, s.width*sprite->getScaleX(), s.height*sprite->getScaleX());
			auto rank = Point2Rank(clickLocation);
			std::cout << "第" << rank.first << "行" << "     第" << rank.second << "列" << std::endl;
			// 点击范围判断检测
			if (rect.containsPoint(clickLocation))
			{
				cout << position.x << "," << position.y << endl << s.width << "," << s.height << endl;
				string className = typeid(T).name();
				className = className.erase(0, 6);
				string str = string("Card\\") + className + string(".png");
				plantFollowSprite = Sprite::create(str.c_str());
				plantFollowSprite->setContentSize(Size(15, 20));
				plantFollowSprite->setPosition(clickLocation);
				plantFollowSprite->retain();
				addLayer(plantFollowSprite);
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
				plantFollowSprite->setPosition(clickLocation);
			}
		};
		listener->onTouchEnded = [=](Touch* touch, Event *event)
		{
			Point clickLocation = touch->getLocation();
			if (isFollowingMouse == true)
			{
				isFollowingMouse = false;
				plantFollowSprite->removeFromParent();
				auto rank = Point2Rank(clickLocation);
				PutPlant<T>(Rank2Point(rank.first, rank.second), rank.first, rank.second);
			
			}
			
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
	}

};


