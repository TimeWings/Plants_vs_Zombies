#include "SelectCardBG.h"
#include "cocos2d.h"
#include "EntityLayer.h"
#include "Global.h"
using namespace cocos2d;
using namespace map;
SelectCardBG* SelectCardBG::instance = nullptr;

SelectCardBG::SelectCardBG()
{
	auto layer = EntityLayer::getInstance();
	auto bg = Sprite::create("UI\\SelectCard_BG.png");
	bg->setAnchorPoint(Point(0,0));
	bg->setPosition(8, 25);
	bg->setScale(2.0f);
	layer->addChild(bg);
	setImg(bg);
}


SelectCardBG::~SelectCardBG()
{
}

void SelectCardBG::show()
{
	getImg()->setVisible(true);
}

void SelectCardBG::hide()
{
	getImg()->setVisible(false);
}

void SelectCardBG::clear()
{
	getImg()->removeFromParent();
}
