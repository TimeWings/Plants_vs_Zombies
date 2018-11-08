#include "Background.h"
#include "EntityLayer.h"
#include "Global.h"
using namespace map;
int Background::type = 1;
Node* Background::holesStencil = NULL;
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

		Sprite* sp= Sprite::createWithTexture(TextureCache::getInstance()->addImage("Scene\\Water\\1.png"));
		sp->setPosition(268, 132);
		sp->setScale(2.2);
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 1; i <= 6; i++)
		{
			sprintf(str, "Scene\\Water\\%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.3);
		sp->runAction(RepeatForever::create(Animate::create(an)));
		layer->addChild(sp);
	}
	else if (type == 2)
	{
		MapRow = 5;
		MapCol = 9;
		BlockSize.first = 38;
		BlockSize.second = 46;
		Deviation.first = 95;
		Deviation.second = 12;
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Scene\\background3.jpg"));
		sprite->retain();
		sprite->setPosition(-20, 0);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setScale(2.0f);
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(sprite);
		setImg(sprite);

		holesStencil = Node::create();
		
		auto clippingNode = ClippingNode::create();
		clippingNode->setStencil(holesStencil);
		clippingNode->setInverted(true);
		clippingNode->setAlphaThreshold(0);
		auto floor = LayerColor::create(Color4B(0, 0, 0, 200));
		clippingNode->addChild(floor);
		layer->addChild(clippingNode,190);
		
	}
	else if (type == 3)
	{
		MapRow = 5;
		MapCol = 9;
		BlockSize.first = 38;
		BlockSize.second = 46;
		Deviation.first = 95;
		Deviation.second = 12;
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Scene\\background4.png"));
		sprite->retain();
		sprite->setPosition(-155, -25);
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setScale(2.0f);
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
	else if (type == 2)
	{
		for (int i = 1; i <= MapRow; i++)
		{
			for (int j = 1; j <= MapCol; j++)
			{
				plantstatus.push_back(new PlantStatus(i, j, 2));
			}
		}
	}
}

//Ä£°å½ÌÑ§ http://www.mamicode.com/info-detail-247772.html
