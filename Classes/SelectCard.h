#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "CardEntity.h"
#include "EntityLayer.h"
#include "PlantStatus.h"
#include "Plants.h"
#include "PlantsEnum.h"
#include "Global.h"
//using namespace std;
using namespace cocos2d;

template <class T>
class SelectCard :public CardEntity
{
public:
	SelectCard();
	~SelectCard();
	//PlantsEnum plantsEnum = PlantsEnum::IceShooter;
	std::string plantsTypeName;
	//bool isSelecting;
	//int cost;
	//Sprite* plantSprite;

	void addLayer(Node * entity, int order = 0)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(entity, order);
	}

	void removeLayer(Node * entity)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->removeChild(entity);
	}

	SelectCard(Point position, PlantsEnum plantsEnum)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cardbackground\\card_green.png"));
		this->setImg(sprite);

		sprite->retain();
		//sprite->setScale(0.15f);
		sprite->setContentSize(Size(20, 30));
		sprite->setPosition(position);
		addLayer(sprite, 200);

		string className = typeid(T).name();
		className = className.erase(0, 6);
		string str = string("Card\\") + className + string(".png");
		plantSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		Size size = sprite->getContentSize();
		auto position1 = Point(size.width / 2, size.height / 2);
		position1.y += 0;
		plantSprite->setPosition(position1);
		//plantSprite->setScale(0.08f);
		plantSprite->setContentSize(Size(15, 20));
		plantSprite->retain();
		//addLayer(plantSprite, 200);
		sprite->addChild(plantSprite);

		plantsTypeName = typeid(T).name();
		this->plantsEnum = plantsEnum;
		isSelecting = true;

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event *event)
		{
			
			Point clickLocation = touch->getLocation();
			Size s = sprite->getContentSize();
			Rect rect = Rect(position.x - s.width*sprite->getScaleX() / 2, position.y - s.height*sprite->getScaleX() / 2, s.width*sprite->getScaleX(), s.height*sprite->getScaleX());
			auto rank = Point2Rank(clickLocation);

			// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
			if (rect.containsPoint(clickLocation))
			{
				if (isSelecting == false)
				{
					//selectingCards.push_back(plantsEnum);
					//selectingCardsEntity.push_back(entity);
					//isSelecting = true;
				}
				else
				{
					isSelecting = false;
					for (int i = 0; i < selectingCards.size(); i++)
					{
						if (selectingCards[i] == this->plantsEnum)
						{
							selectingCards.erase(selectingCards.begin() + i);
							removeLayer(selectingCardsEntity[i]->getImg());
							removeLayer(selectingCardsEntity[i]->plantSprite);
							selectingCardsEntity.erase(selectingCardsEntity.begin() + i);
						}
					}
					for (int i = 0; i < unSelectingCardsEntity.size(); i++)
					{
						if (unSelectingCardsEntity[i]->plantsEnum == this->plantsEnum)
						{
							unSelectingCardsEntity[i]->isSelecting = false;
						}
					}
				}
				for (int i = 0; i < selectingCards.size(); i++)
				{
					cout<<(int)	selectingCards[i]<<endl;
				}
				return true;
			}
			
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
	}

};

