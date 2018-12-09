#include "WinMenu.h"
#include "LevelManager.h"
#include "UILayer.h"

WinMenu* WinMenu::instance;

WinMenu::WinMenu()
{
	auto winSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\Win.jpg"));
	auto size = Director::getInstance()->getVisibleSize();
	winSprite->setPosition(size.width / 2, size.height / 2);
	winSprite->setScale(1.2f);
	winSprite->setOpacity(0);
	UILayer::getInstance()->addChild(winSprite);
	setImg(winSprite);

	auto label = Label::createWithTTF(*(FontConfig::getInstance()), "You Win");
	label->setTextColor(Color4B(78, 238, 148, 255));
	label->setPosition(98, 110);
	label->setScale(4.0f);
	winSprite->addChild(label);

	auto titleLabel = Label::createWithTTF(*(FontConfig::getInstance()), "Win");
	titleLabel->setTextColor(Color4B::BLACK);
	titleLabel->setPosition(98, 132);
	titleLabel->setScale(1.2f);
	winSprite->addChild(titleLabel);

	retryButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(retryButton);
	retryButton->setPosition(Point(96, 55));
	retryButton->setScale(1.5f);
	auto labelRetry = Label::createWithTTF(*(FontConfig::getInstance()), "Retry");
	labelRetry->setTextColor(Color4B::BLACK);
	labelRetry->setPosition(Point(96, 57));
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

	nextButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(nextButton);
	nextButton->setPosition(Point(96, 85));
	nextButton->setScale(1.5f);
	auto labelNext = Label::createWithTTF(*(FontConfig::getInstance()), "Next");
	labelNext->setTextColor(Color4B::BLACK);
	labelNext->setPosition(Point(96, 87));
	labelNext->setScale(1.5f);
	getImg()->addChild(labelNext);
	if(LevelManager::currentLevel >=1 && LevelManager::currentLevel <= 14)
	nextButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			LevelManager::loadLevel(LevelManager::currentLevel + 1);
			break;
		default:
			break;
		}
	});

	exitButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(exitButton);
	exitButton->setPosition(Point(96, 25));
	exitButton->setScale(1.5f);
	auto labelExit = Label::createWithTTF(*(FontConfig::getInstance()), "Exit");
	labelExit->setTextColor(Color4B::BLACK);
	labelExit->setPosition(Point(96, 27));
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


WinMenu::~WinMenu()
{
}

bool WinMenu::isShow()
{
	return showing;
}

void WinMenu::show()
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
	nextButton->setEnabled(true);
	exitButton->setEnabled(true);
	//closeButton->setEnabled(true);
	showing = true;
}

void WinMenu::hide()
{
	FadeOut* fadeout = FadeOut::create(0.3f);
	getImg()->runAction(fadeout);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->runAction(fadeout->clone());
	}
	retryButton->setEnabled(false);
	nextButton->setEnabled(false);
	exitButton->setEnabled(false);
	//closeButton->setEnabled(false);
	showing = false;
}

void WinMenu::clear()
{
	retryButton->removeFromParent();
	nextButton->removeFromParent();
	exitButton->removeFromParent();
	//closeButton->removeFromParent();
	getImg()->removeFromParent();
	delete instance;
	instance = nullptr;
}