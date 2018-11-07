#include "Background.h"
#include "EntityLayer.h"
#include "Global.h"
using namespace map;
Background::Background()
{
	if (type == 0)
	{
		MapRow = 5;
		MapCol = 9;
		BlockSize.first = 38;
		BlockSize.second = 46;
		Deviation.first = 95;
		Deviation.second = 12;
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Scene\\background1.jpg"));
		sprite->retain();
		sprite->setPosition(-20, 0);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setScale(2.0f);
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(sprite);
		setImg(sprite);
	}
	else if (type == 1)
	{
		MapRow = 6;
		MapCol = 9;
		BlockSize.first = 41;
		BlockSize.second = 42;
		Deviation.first = 88;
		Deviation.second = 13;
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Scene\\background2.jpg"));
		sprite->retain();
		sprite->setPosition(-50, 10);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setScale(2.2f);
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(sprite);
		setImg(sprite);
	}
	initPlantStatus();

	
}
void Background::initPlantStatus()
{
	if (type == 0)
	{
		for (int i = 1; i <= MapRow; i++)
		{
			for (int j = 1; j <= MapCol; j++)
			{
				plantstatus.push_back(new PlantStatus(i, j, 0));
			}
		}
	}
	else if (type == 1)
	{
		for (int i = 1; i <= MapRow; i++)
		{
			for (int j = 1; j <= MapCol; j++)
			{
				if (i == 3 || i == 4)
				{
					plantstatus.push_back(new PlantStatus(i, j, 1));
				}
				else
				{
					plantstatus.push_back(new PlantStatus(i, j, 0));
				}
				
			}
		}
	}
}
