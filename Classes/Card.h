#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "EntityLayer.h"
#include "CardEntity.h"
#include "PlantStatus.h"
#include "Plants.h"
#include "Global.h"
using namespace std;
using namespace cocos2d;

template <class T>
class Card :public CardEntity
{
public:
	Card();
	~Card();
	string plantsTypeName;
	bool isFollowingMouse = false;
	//int cost;
	//Sprite* plantSprite;
	Sprite* plantFollowSprite;

	template <class T>
	void BindPlant()
	{
		plantsTypeName = typeid(T).name();
	}

	template <class T>
	T* PutPlant(Point position, int row, int col)
	{
		Point a = Point(position.x, position.y + 0.25*BlockSize.second);
		T*t = new T(a, row, col);
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
	Card(Point position)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cardbackground\\card_green.png"));
		this->setImg(sprite);
		
		sprite->retain();
		//sprite->setScale(0.15f);
		sprite->setContentSize(Size(20, 30));
		//this->Scale = this->getImg()->getScale();
		//sprite->setAnchorPoint(Point(0.5f, 0.5f));
		sprite->setPosition(position);
		addLayer(sprite,200);

		string className = typeid(T).name();
		className = className.erase(0, 6);
		string str = string("Card\\") + className + string(".png");
		plantSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		Size size = sprite->getContentSize();
		auto position1 = Point(size.width/2, size.height/2);
		position1.y += 0;
		plantSprite->setPosition(position1);
		//plantSprite->setScale(0.08f);
		plantSprite->setContentSize(Size(15, 20));
		plantSprite->retain();
		//addLayer(plantSprite,200);
		sprite->addChild(plantSprite);

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

				// 点击范围判断检测
				if (rect.containsPoint(clickLocation))
				{
					string className = typeid(T).name();
					className = className.erase(0, 6);
					string str = string("Card\\") + className + string(".png");
					plantFollowSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str.c_str()));
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
					Register<T>(rank.first, rank.second);
				}
			}
			
			return false;
		};
		listener1->onMouseMove = [=]( Event *event)
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
		if (row > MapRow || row < 1 || col<1 || col>MapCol)
		{
			std::cout << "不可以种植" << std::endl;
			return;
		}
		PlantStatus* ps = find(row, col);
		if (ps != NULL)
		{
			std::cout << row << "----" <<col<< std::endl;
			if (!ps->Enabled)
			{
				std::cout << "此格子不可以种植" << std::endl;
				return;
			}
			if (ps->_BlockType == 0)
			{
				if ((strcmp(typeid(T).name(), "class Cushaw") == 0) && ps->plantVector.size() != 0 && !find1(ps, "class Cushaw"))
				{
					std::cout << "可以种植南瓜" << std::endl;
					ps->plantVector.insert(ps->plantVector.begin(), PutPlant<T>(Rank2Point(row, col), row, col));
					//ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if (strcmp(typeid(T).name(), "class Shovel") == 0)
				{
					std::cout << "铲子种植成功" << std::endl;
					ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if ((strcmp(typeid(T).name(), "class Paul") == 0))
				{
					if (find1(ps, "class Lancer"))
					{
						PlantStatus* ps1 = find(row, col - 1);
						if (ps1 != NULL && find1(ps1, "class Lancer"))
						{
							std::cout << "找到左边有投手，可以放置加农炮" << std::endl;
							RemoveRegister("class Lancer", row, col - 1);
							RemoveRegister("class Lancer", row, col);
							T* plant = PutPlant<T>(Rank2Point(row, col - 1), row, col - 1);
							ps->plantVector.push_back(plant);
							ps1->plantVector.push_back(plant);
							return;
						}
						PlantStatus* ps2 = find(row, col + 1);
						if (ps2 != NULL && find1(ps2, "class Lancer"))
						{
							std::cout << "找到右边边有投手，可以放置加农炮" << std::endl;
							RemoveRegister("class Lancer", row, col + 1);
							RemoveRegister("class Lancer", row, col);
							T* plant = PutPlant<T>(Rank2Point(row, col), row, col);
							ps->plantVector.push_back(plant);
							ps2->plantVector.push_back(plant);
							return;
						}
						std::cout << "只有一个投手,不可放置" << std::endl;
						return;
					}
					else
					{
						std::cout << "没有投手,不可放置" << std::endl;
						return;
					}
				}
				else if (ps->plantVector.size() == 1 && find1(ps, "class Cushaw") && (strcmp(typeid(T).name(), "class Cushaw") != 0))
				{
					std::cout << "种植成功" << std::endl;
					ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if (ps->plantVector.size() != 0)
				{
					std::cout << "不可以种植" << std::endl;
					return;
				}
				else if(strcmp(typeid(T).name(), "class Lotus") != 0)
				{
					std::cout << "种植成功" << std::endl;
					ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
				}
			}
			else if (ps->_BlockType == 1)
			{
				if ((strcmp(typeid(T).name(), "class Lotus") != 0) && ps->plantVector.size() == 0)
				{
					std::cout << "不是睡莲,种植不成功了" << std::endl;
				}
				else if ((strcmp(typeid(T).name(), "class Lotus") == 0) && ps->plantVector.size() == 0)
				{
					std::cout << "是睡莲,种植成功" << std::endl;
					ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if ((strcmp(typeid(T).name(), "class Cushaw") == 0) && ps->plantVector.size() != 0 && !find1(ps, "class Cushaw"))
				{
					std::cout << "可以种植南瓜" << std::endl;
					ps->plantVector.insert(ps->plantVector.begin(), PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if (strcmp(typeid(T).name(), "class Shovel") == 0)
				{
					std::cout << "铲子种植成功" << std::endl;
					ps->plantVector.push_back(PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if ((strcmp(typeid(T).name(), "class Paul") == 0))
				{
					if (find1(ps, "class Lancer"))
					{
						PlantStatus* ps1 = find(row, col - 1);
						if (ps1 != NULL && find1(ps1, "class Lancer"))
						{
							std::cout << "找到左边有投手，可以放置加农炮" << std::endl;
							RemoveRegister("class Lancer", row, col - 1);
							RemoveRegister("class Lancer", row, col);
							T* plant = PutPlant<T>(Rank2Point(row, col - 1), row, col - 1);
							ps->plantVector.insert(ps->plantVector.end()-1 , plant);
							ps1->plantVector.insert(ps1->plantVector.end()-1, plant);
							return;
						}
						PlantStatus* ps2 = find(row, col + 1);
						if (ps2 != NULL && find1(ps2, "class Lancer"))
						{
							std::cout << "找到右边边有投手，可以放置加农炮" << std::endl;
							RemoveRegister("class Lancer", row, col + 1);
							RemoveRegister("class Lancer", row, col);
							T* plant = PutPlant<T>(Rank2Point(row, col), row, col);
							ps->plantVector.insert(ps->plantVector.end() - 1, plant);
							ps2->plantVector.insert(ps2->plantVector.end() - 1, plant);
							return;
						}
						std::cout << "只有一个投手,不可放置" << std::endl;
						return;
					}
					else
					{
						std::cout << "没有投手,不可放置" << std::endl;
						return;
					}
				}
				else if (ps->plantVector.size() == 2 && find1(ps, "class Cushaw") && (strcmp(typeid(T).name(), "class Cushaw") != 0))
				{
					std::cout << "在南瓜上种植成功" << std::endl;
					ps->plantVector.insert(ps->plantVector.end()-1, PutPlant<T>(Rank2Point(row, col), row, col));
				}
				else if (ps->plantVector.size() > 1)
				{
					std::cout << "不可以种植" << std::endl;
					return;
				}
				else if(strcmp(typeid(T).name(), "class Lotus") != 0)
				{
					std::cout << "种植成功" << std::endl;
					ps->plantVector.insert(ps->plantVector.end()-1, PutPlant<T>(Rank2Point(row, col), row, col));
				}

			}
			
		}
		else 
		{
			return;
		}
	}
	
};

