#include "Background.h"
#include "EntityLayer.h"


Background::Background()
{
	
	auto sprite = Sprite::create("Scene\\Background5x9.jpg");
	sprite->retain();
	sprite->setPosition(-20, 0);
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setScale(2.0f);
	EntityLayer* layer = EntityLayer::getInstance();
	layer->addChild(sprite);
	setImg(sprite);
	
}


Background::~Background()
{
}
