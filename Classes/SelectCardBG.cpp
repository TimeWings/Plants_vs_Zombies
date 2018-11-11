#include "SelectCardBG.h"
#include "cocos2d.h"
#include "EntityLayer.h"
using namespace cocos2d;

Sprite* SelectCardBG::bg;

SelectCardBG::SelectCardBG()
{
	auto layer = EntityLayer::getInstance();
	bg = Sprite::create("UI\\SelectCard_BG.png");
	bg->setAnchorPoint(Point(0,0));
	bg->setPosition(8, 5);
	bg->setScale(1.9f);

	auto bg2 = Sprite::create("UI\\CardBank.png");
	bg2->setAnchorPoint(Point(0, 0));
	bg2->setPosition(8, 235);
	bg2->setScale(2.2f);

	layer->addChild(bg);
	layer->addChild(bg2);

}


SelectCardBG::~SelectCardBG()
{
}
