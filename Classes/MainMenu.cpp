#include "MainMenu.h"
#include "EntityLayer.h"
#include "Global.h"
#include "FontConfig.h"
#include "LevelManager.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace map;

MainMenu* MainMenu::instance;

MainMenu::MainMenu()
{
	auto layer = EntityLayer::getInstance();
	auto s = Director::getInstance()->getWinSize();
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\dialog.png"));
	bg->setAnchorPoint(Point(0.5f, 0.5f));
	bg->setPosition(s.width / 2, s.height / 2 - 20);
	bg->setContentSize(Size(300, 300));
	layer->addChild(bg, 1500);
	setImg(bg);

	closeButton = Button::create("UI\\close.png", "UI\\close.png", "UI\\close.png");
	getImg()->addChild(closeButton);
	closeButton->setPosition(Point(250, 240));
	closeButton->setScale(1.5f);
	closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			break;
		default:
			break;
		}
	});

	retryButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(retryButton);
	retryButton->setPosition(Point(150, 215));
	retryButton->setScale(2.0f);
	auto labelRetry = Label::createWithTTF(*(FontConfig::getInstance()), "Retry");
	labelRetry->setTextColor(Color4B::BLACK);
	labelRetry->setPosition(Point(150, 217));
	labelRetry->setScale(1.5f);
	getImg()->addChild(labelRetry);
	retryButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			LevelManager::loadLevel(-1);
			break;
		default:
			break;
		}
	});

	levelButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(levelButton);
	levelButton->setPosition(Point(150, 185));
	levelButton->setScale(2.0f);
	auto labelLevel = Label::createWithTTF(*(FontConfig::getInstance()), "Level");
	labelLevel->setTextColor(Color4B::BLACK);
	labelLevel->setPosition(Point(150, 187));
	labelLevel->setScale(1.5f);
	getImg()->addChild(labelLevel);
	levelButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			LevelManager::getInstance()->show();
			break;
		default:
			break;
		}
	});

	exitButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(exitButton);
	exitButton->setPosition(Point(150, 155));
	exitButton->setScale(2.0f);
	auto labelExit = Label::createWithTTF(*(FontConfig::getInstance()), "Exit");
	labelExit->setTextColor(Color4B::BLACK);
	labelExit->setPosition(Point(150, 157));
	labelExit->setScale(1.5f);
	getImg()->addChild(labelExit);
	exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			exit(0);
			break;
		default:
			break;
		}
	});
}


MainMenu::~MainMenu()
{
}

bool MainMenu::isShow()
{
	return showing;
}

void MainMenu::show()
{
	FadeIn* fadein = FadeIn::create(0.3f);
	getImg()->setOpacity(0);
	getImg()->runAction(fadein);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->setOpacity(0);
		childerns.at(i)->runAction(fadein->clone());
	}
	retryButton->setEnabled(true);
	levelButton->setEnabled(true);
	exitButton->setEnabled(true);
	closeButton->setEnabled(true);
	showing = true;
}

void MainMenu::hide()
{
	FadeOut* fadeout = FadeOut::create(0.3f);
	getImg()->runAction(fadeout);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->runAction(fadeout->clone());
	}
	retryButton->setEnabled(false);
	levelButton->setEnabled(false);
	exitButton->setEnabled(false);
	closeButton->setEnabled(false);
	showing = false;
}

void MainMenu::clear()
{
	retryButton->removeFromParent();
	levelButton->removeFromParent();
	exitButton->removeFromParent();
	closeButton->removeFromParent();
	getImg()->removeFromParent();
	delete instance;
	instance = nullptr;
}