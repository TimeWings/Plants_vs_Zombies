#pragma once
#include "Entity.h"
#include "EntityLayer.h"
#include "UILayer.h"
#include "PlantsEnum.h"
#include <iostream>

class CardEntity: public Entity
{
public:
	int cost = 0;
	float CD = 0;
	float remainCD = 0;
	bool isSelecting = false;
	PlantsEnum plantsEnum = PlantsEnum::IceShooter;
	std::string plantsTypeName;
	Sprite* plantSprite;
	EventListenerTouchOneByOne* listener;
	EventListenerMouse* listener1;

	void addLayer(Node * entity, int order = 0)
	{
		UILayer* layer = UILayer::getInstance();
		layer->addChild(entity, order);
	}

	void removeLayer(Node * entity)
	{
		UILayer* layer = UILayer::getInstance();
		layer->removeChild(entity);
	}

	virtual void addListener() = 0;
	virtual void removeListener()
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener1);
		std::cout << "¼àÌýÆ÷ÒÑÒÆ³ý" << std::endl;
	}
	virtual void clear()
	{
		getImg()->removeFromParent();
		removeListener();
	}
	virtual void setCost();
	virtual void setCD();
};