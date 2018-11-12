#pragma once
#include "Entity.h"
#include "EntityLayer.h"
#include "PlantsEnum.h"

class CardEntity: public Entity
{
public:
	int cost = 0;
	bool isSelecting = false;
	PlantsEnum plantsEnum = PlantsEnum::IceShooter;
	std::string plantsTypeName;
	Sprite* plantSprite;
	EventListenerTouchOneByOne* listener;
	EventListenerMouse* listener1;

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

	virtual void addListener() = 0;
	virtual void removeListener()
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener1);

	}
	void setCost()
	{
		if (plantsTypeName == "PotatoMine" || plantsTypeName == "Lotus" || plantsTypeName == "Lantern")
		{
			cost = 25;
		}
		else if (plantsTypeName == "Sunflower" || plantsTypeName == "Nut")
		{
			cost = 50;
		}
		else if (plantsTypeName == "GraveBuster")
		{
			cost = 75;
		}
		else if (plantsTypeName == "PeaShooter" || plantsTypeName == "Lucker" || plantsTypeName == "Clover" || plantsTypeName == "Magnet")
		{
			cost = 100;
		}

		else if (plantsTypeName == "NutPlus" || plantsTypeName == "Cushaw")
		{
			cost = 125;
		}
		else if (plantsTypeName == "Doom_shroom" || plantsTypeName == "Chomper")
		{
			cost = 150;
		}
		else if (plantsTypeName == "IceShooter" || plantsTypeName == "Torch")
		{
			cost = 175;
		}

		else if (plantsTypeName == "TripleShooter")
		{
			cost = 325;
		}
	}
};