#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "EntityLayer.h"
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
	int cost;
	Sprite* plantSprite;
	Sprite* plantFollowSprite;

	template <class T>
	void BindPlant()
	{
		plantsTypeName = typeid(T).name();
	}

	template <class T>
	void PutPlant(Point position, int row, int col)
	{
		T* t = new T(position, row, col);
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

	Card(Point position)
	{
		Sprite* sprite = Sprite::create("cardbackground\\card_green.png");
		this->setImg(sprite);
		
		sprite->retain();
		//sprite->setScale(0.15f);
		sprite->setContentSize(Size(20, 30));
		//this->Scale = this->getImg()->getScale();
		sprite->setPosition(position);
		addLayer(sprite);

		string className = typeid(T).name();
		className = className.erase(0, 6);
		string str = string("Card\\") + className + string(".png");
		plantSprite = Sprite::create(str);
		auto position1 = position;
		position1.y += 0;
		plantSprite->setPosition(position1);
		//plantSprite->setScale(0.08f);
		plantSprite->setContentSize(Size(15, 20));
		plantSprite->retain();
		addLayer(plantSprite);

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
				cout << position.x << "," << position.y << endl <<s.width<<","<<s.height<<endl;
				//target->setOpacity(180);
				//T* plant = new T(position, row);
				string className = typeid(T).name();
				className = className.erase(0, 6);
				string str = string("Card\\") + className + string(".png");
				plantFollowSprite = Sprite::create(str.c_str());
				//plantFollowSprite->setScale(0.3);
				plantFollowSprite->setContentSize(Size(15, 20));
				plantFollowSprite->setPosition(clickLocation);
				plantFollowSprite->retain();
				addLayer(plantFollowSprite);
				//cout << "click " << plantsTypeName << " card" << endl;
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
			//return true;
		};
		listener->onTouchEnded = [=](Touch* touch, Event *event)
		{
			Point clickLocation = touch->getLocation();
			if (isFollowingMouse == true)
			{
				//for (int i = 0; i < plantableList.size(); i++)
				//{
				//	Size s = plantableList[i]->sprite->getContentSize();
				//	auto position = plantableList[i]->sprite->getPosition();
				//	Rect rect = Rect(position.x - s.width / 2, position.y - s.height / 2, s.width, s.height);

				//	// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
				//	if (rect.containsPoint(clickLocation) && plantableList[i]->hasPlant == false)
				//	{
				//		removeLayer(plantFollowSprite);
				//		plantableList[i]->hasPlant = true;
				//		PutPlant<T>(position, plantableList[i]->row, plantableList[i]->col);
				//		return;
				//	}
				//}
				removeLayer(plantFollowSprite);
				auto rank = Point2Rank(clickLocation);
				PutPlant<T>(Rank2Point(rank.first,rank.second), rank.first, rank.second);
			}
			//return true;
		};
		//this->setTouchEnabled(true);
		//listener->setSwallowTouches(false);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
	}
};

