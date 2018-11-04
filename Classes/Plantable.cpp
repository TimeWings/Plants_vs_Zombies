#include "Plantable.h"
#include "EntityLayer.h"
#include <iostream>
USING_NS_CC;
using namespace std;
//vector<Plantable*> plantableList;

Plantable::Plantable(Point position)
{
	//Sprite* sprite = Sprite::create("cardbackground\\card_green.png");
	Sprite* sprite = Sprite::create();
	sprite->retain();
	sprite->setContentSize(size);
	sprite->setPosition(position);
	sprite->setVisible(false);
	
	EntityLayer* layer = EntityLayer::getInstance();
	layer->addChild(sprite);
	this->sprite = sprite;

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [=](Touch* touch, Event *event)
	//{
	//	Point clickLocation = touch->getLocation();
	//	Size s = sprite->getContentSize();
	//	Rect rect = Rect(position.x - s.width / 2, position.y - s.height / 2, s.width, s.height);
	//	cout << clickLocation.x << ","<<clickLocation.y << endl;
	//	// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
	//	if (rect.containsPoint(clickLocation))
	//	{
	//		cout << "click " << " plantable" << endl;
	//		return true;

	//	}
	//	return false;
	//};
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
}


Plantable::~Plantable()
{
}


