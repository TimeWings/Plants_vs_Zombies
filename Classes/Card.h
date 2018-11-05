#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "EntityLayer.h"
#include "PlantStatus.h"
#include "Plants.h"
using namespace std;
using namespace cocos2d;

template <class T>
class Card :public Entity
{
public:
	Card();
	~Card();
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
			Rect rect = Rect(position.x - s.width*sprite->getScaleX() / 2, position.y - s.height*sprite->getScaleX() / 2, s.width*sprite->getScaleX(), s.height*sprite->getScaleX());
			auto rank = Point2Rank(clickLocation);
			std::cout << "第" << rank.first << "行" << "     第" << rank.second << "列" << std::endl;
			//cout << target->getPositionX() << "," << target->getPositionY() << endl;
			//cout << locationInNode.x << "," << locationInNode.y << endl;
			//cout << position.x << "," << position.y << endl;
			//cout << clickLocation.x << ","<<clickLocation.y << endl;
			// 点击范围判断检测
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

				//	// 点击范围判断检测
				//	if (rect.containsPoint(clickLocation) && plantableList[i]->hasPlant == false)
				//	{
				//		removeLayer(plantFollowSprite);
				//		plantableList[i]->hasPlant = true;
				//		PutPlant<T>(position, plantableList[i]->row, plantableList[i]->col);
				//		return;
				//	}
				//}
				isFollowingMouse = false;
				plantFollowSprite->removeFromParent();
				auto rank = Point2Rank(clickLocation);
				//PutPlant<T>(Rank2Point(rank.first, rank.second), rank.first, rank.second);
				Register<T>(rank.first, rank.second);
			}
			//return true;
		};
		//this->setTouchEnabled(true);
		//listener->setSwallowTouches(false);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
	}
	PlantStatus* find(int row, int col)
	{
		for (PlantStatus* x : plantstatus)
		{
			if (x->_row == row && x->_col == col)
			{
				return x;
			}
		}
		return NULL;
	}
	bool find1(PlantStatus* plantstatus, char* name)
	{
		for (Plants* x : plantstatus->plantVector)
		{
			if (strcmp(typeid(*x).name(), name) == 0)
			{
				return true;
			}
		}
		return false;
	}
	template <class T>
	void Register(int row, int col)
	{
		PlantStatus* ps = find(row, col);
		if (ps != NULL)
		{
			if ((strcmp(typeid(T).name(), "class Cushaw") == 0)&& ps->plantVector.size() != 0&&!find1(ps,"class Cushaw"))
			{
				std::cout << "可以种植南瓜"<<std::endl;
				ps->plantVector.insert(ps->plantVector.begin(), PutPlant<T>(Rank2Point(row, col), row, col));
				//ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
			}
			else if (ps->plantVector.size() == 1 && find1(ps, "class Cushaw")&& (strcmp(typeid(T).name(), "class Cushaw") != 0))
			{
				std::cout << "种植成功" << std::endl;
				ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
			}
			else if (ps->plantVector.size() != 0)
			{
				std::cout << "不可以种植" << std::endl;
				return;
			}
			else 
			{
				std::cout << "种植成功" << std::endl;
				//PutPlant<T>(Rank2Point(row, col), row, col);
				//std::cout << typeid(T).name();
				ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
			}
		}
		else 
		{
			return;
		}
	}
	
};

