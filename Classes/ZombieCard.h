#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "EntityLayer.h"
#include "PlantStatus.h"
#include "Plants.h"
#include "Global.h"
using namespace std;
using namespace cocos2d;

template <class T>
class ZombieCard :public Entity
{
public:
	ZombieCard();
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
		T*t = new T(ccp(position.x,position.y+0.3*BlockSize.second), row, col);
		return t;
	}

	void addLayer(Node * entity,int order=0)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(entity,order);
	}

	void removeLayer(Node * entity)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->removeChild(entity);
	}
	ZombieCard(Point position)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cardbackground\\card_green.png"));
		this->setImg(sprite);

		sprite->retain();
		//sprite->setScale(0.15f);
		sprite->setContentSize(Size(20, 30));
		//this->Scale = this->getImg()->getScale();
		sprite->setPosition(position);
		addLayer(sprite,200);

		string className = typeid(T).name();
		className = className.erase(0, 6);
		string str = string("Card\\") + className + string(".png");
		plantSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto position1 = position;
		position1.y += 0;
		plantSprite->setPosition(position1);
		//plantSprite->setScale(0.08f);
		plantSprite->setContentSize(Size(15, 20));
		plantSprite->retain();
		addLayer(plantSprite,200);

		plantsTypeName = typeid(T).name();

		auto listener = EventListenerTouchOneByOne::create();
		auto listener1 = EventListenerMouse::create();
		listener->onTouchBegan = [=](Touch* touch, Event *event)
		{
			if (!isFollowingMouse)
			{
				Point clickLocation = touch->getLocation();
				Size s = sprite->getContentSize();
				Rect rect = Rect(position.x - s.width*sprite->getScaleX() / 2, position.y - s.height*sprite->getScaleX() / 2, s.width*sprite->getScaleX(), s.height*sprite->getScaleX());
				auto rank = Point2Rank(clickLocation);

				// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
				if (rect.containsPoint(clickLocation))
				{
					string className = typeid(T).name();
					className = className.erase(0, 6);
					string str = string("Card\\") + className + string(".png");
					plantFollowSprite = Sprite::create(str.c_str());
					plantFollowSprite->setContentSize(Size(15, 20));
					plantFollowSprite->setPosition(clickLocation);
					plantFollowSprite->retain();
					addLayer(plantFollowSprite,200);
					isFollowingMouse = true;
					return true;

				}
			}
			else
			{
				Point clickLocation = touch->getLocation();
				if (isFollowingMouse == true)
				{
					isFollowingMouse = false;
					plantFollowSprite->removeFromParent();
					auto rank = Point2Rank(clickLocation);
					PutPlant<T>(Rank2Point(rank.first,rank.second), rank.first, rank.second);
					
				}
			}

			return false;
		};
		listener1->onMouseMove = [=](Event *event)
		{
			if (isFollowingMouse)
			{
				EventMouse* e = (EventMouse*)event;
				plantFollowSprite->setPosition(Point(e->getCursorX(), e->getCursorY()));
			}
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, sprite);
	}

};

