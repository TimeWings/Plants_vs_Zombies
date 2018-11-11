#include <iostream>
#include "Title.h"
#include "HelloWorldScene.h"
#include "EntityLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

Title::Title(Scene* scene)
{
	//auto layer = EntityLayer::getInstance();
	TextureCache::getInstance()->addImage("UI\\FateGrandOrder2.jpg");
	bg = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\FateGrandOrder2.jpg"));
	auto s = Director::getInstance()->getWinSize();
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(0, 0);
	bg->setScale(1.0f);
	//bg->setContentSize(Size(s.width, s.height));

	//auto bg2 = Sprite::create("UI\\SelectorScreen_BG_Right.png");
	//bg2->setAnchorPoint(Point(0, 0));
	//bg2->setPosition(230, 0);
	//bg2->setScale(1.5f);

	//auto bg3 = Sprite::create("UI\\SelectorScreen_BG.jpg");
	//bg3->setAnchorPoint(Point(0, 0));
	//bg3->setPosition(0, 0);
	//bg3->setScale(10.0f);
	
	StartButton = Button::create("UI\\StartButton.png", "UI\\StartButton.png", "UI\\StartButton.png");
	StartButton->setPosition(Point(s.width/2, 20));
	StartButton->setTitleText("Start");
	StartButton->setTitleFontSize(5.0f);
	
	StartButton->setEnabled(false);
	StartButton->setVisible(false);

	scene->addChild(bg,5);
	//addChild(bg2,2);
	scene->addChild(StartButton,6);
}

Title::~Title()
{

}

void Title::clear(Scene* scene)
{
	scene->removeChild(bg);
	scene->removeChild(StartButton);

}

void Title::enableStartButton()
{
	StartButton->setVisible(true);
	StartButton->setEnabled(true);
}