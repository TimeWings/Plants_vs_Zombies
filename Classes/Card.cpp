#include "Card.h"
#include "EntityLayer.h"
#include "Mushroom.h"
using namespace std;
using namespace cocos2d;

template <class T>
Card<T>::Card()
{

}
/*
template <class T>
Card<T>::Card(Point position, int row)
{
	//setRow(row);
	Sprite* sprite = Sprite::create("cardbakcground\\card_icon_green.png");
	this->setImg(sprite);
	plantSprite = T->getImg();
	sprite->retain();
	sprite->setScale(1.0);
	//this->Scale = this->getImg()->getScale();
	sprite->setPosition(position);
	addLayer(sprite);
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
		Rect rect = Rect(position.x-s.width/2, position.y- s.height/2, s.width, s.height);
		//cout << target->getPositionX() << "," << target->getPositionY() << endl;
		//cout << locationInNode.x << "," << locationInNode.y << endl;
		//cout << position.x << "," << position.y << endl;
		//cout << clickLocation.x << ","<<clickLocation.y << endl;
		// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
		if (rect.containsPoint(clickLocation))
		{
			//log("sprite began... x = %f, y = %f", clickLocation.x, clickLocation.y);
			//target->setOpacity(180);
			cout << "click " <<plantsTypeName<<" card"<< endl;
			isFollowingMouse = true;
			return true;
			
		}
		return false;
		//str += (e->getMouseButton());
		// ...
	};
	listener->onTouchMoved = [=](Touch* touch, Event *event)
	{
		Point clickLocation = touch->getLocation();
		plantSprite->setPosition(clickLocation);
		//return true;
	};
	listener->onTouchEnded = [=](Touch* touch, Event *event)
	{
		Point clickLocation = touch->getLocation();
		if (isFollowingMouse == true)
			PutPlant<Mushroom>(clickLocation, 3);
		//return true;
	};
	//this->setTouchEnabled(true);
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(PlantLayer::onTouchBegan, this);
	//listener->onTouchEnded = CC_CALLBACK_2(PlantLayer::onTouchEnded, this);
	//listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, sprite);
	//plants.
}
*/
template <class T>
Card<T>::~Card()
{
}

//template <class T>
//void Card::PutPlant(Point position, int row)

//template <class T>

