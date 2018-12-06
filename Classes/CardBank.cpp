#include "CardBank.h"
#include "Global.h"
#include "cocos2d.h"
#include "UILayer.h"
using namespace cocos2d;
using namespace map;

CardBank* CardBank::instance = nullptr;
Label* CardBank::sunLabel = nullptr;

CardBank::CardBank() 
{
	auto layer = UILayer::getInstance();
	auto bg = Sprite::create("UI\\CardBank.png");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(8, 265);
	bg->setScale(2.4f);
	layer->addChild(bg, 195);
	setImg(bg);
}

CardBank::~CardBank()
{

}

void CardBank::updateSunLabel()
{
	if (sunLabel == nullptr)
	{
		sunLabel = Label::createWithTTF(std::to_string(sunCnt.first), "Font\\TianShiYanTi.ttf", 9);
		sunLabel->setAnchorPoint(Point(0.5f, 0.5f));
		sunLabel->setPosition(29.5f, 274);
		sunLabel->setTextColor(Color4B::BLACK);
		sunLabel->setAlignment(TextHAlignment::CENTER);
		UILayer::getInstance()->addChild(sunLabel, 196);
	}
	sunLabel->setString(std::to_string(sunCnt.first));
	std::cout << "sun:" << sunCnt.first << std::endl;
}

void CardBank::show()
{
	getImg()->setVisible(true);
	if (sunLabel != nullptr)
		sunLabel->setVisible(true);
}

void CardBank::hide()
{
	getImg()->setVisible(false);
	if (sunLabel != nullptr)
		sunLabel->setVisible(false);
}

void CardBank::clear()
{
	getImg()->removeFromParent();
	if (sunLabel != nullptr)
		sunLabel->removeFromParent();
	sunLabel = nullptr;
	delete instance;
	instance = nullptr;
}