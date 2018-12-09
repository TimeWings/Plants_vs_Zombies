#include "LoseMenu.h"
#include "LevelManager.h"
#include "UILayer.h"

LoseMenu* LoseMenu::instance;

LoseMenu::LoseMenu()
{
	auto loseSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\Lose.jpg"));
	auto size = Director::getInstance()->getVisibleSize();
	loseSprite->setPosition(size.width / 2, size.height / 2);
	loseSprite->setScale(1.2f);
	loseSprite->setOpacity(0);
	UILayer::getInstance()->addChild(loseSprite);
	setImg(loseSprite);

	auto zombieWin = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\ZombiesWon.png"));
	zombieWin->setPosition(98, 72);
	zombieWin->setScale(0.8f);
	loseSprite->addChild(zombieWin);

	auto titleLabel = Label::createWithTTF(*(FontConfig::getInstance()), "Lose");
	titleLabel->setTextColor(Color4B::BLACK);
	titleLabel->setPosition(98, 130);
	titleLabel->setScale(1.2f);
	loseSprite->addChild(titleLabel);

	retryButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	getImg()->addChild(retryButton);
	retryButton->setPosition(Point(96, 15));
	retryButton->setScale(1.5f);
	auto labelRetry = Label::createWithTTF(*(FontConfig::getInstance()), "Retry");
	labelRetry->setTextColor(Color4B::BLACK);
	labelRetry->setPosition(Point(96, 17));
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

	//exitButton = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	//getImg()->addChild(exitButton);
	//exitButton->setPosition(Point(96, 15));
	//exitButton->setScale(1.5f);
	//auto labelExit = Label::createWithTTF(*(FontConfig::getInstance()), "Exit");
	//labelExit->setTextColor(Color4B::BLACK);
	//labelExit->setPosition(Point(96, 27));
	//labelExit->setScale(1.5f);
	//getImg()->addChild(labelExit);
	//exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	//{
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::BEGAN:
	//		break;
	//	case ui::Widget::TouchEventType::ENDED:
	//		exit(0);
	//		break;
	//	default:
	//		break;
	//	}
	//});
}


LoseMenu::~LoseMenu()
{
}

bool LoseMenu::isShow()
{
	return showing;
}

void LoseMenu::show()
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
	//exitButton->setEnabled(true);
	showing = true;
}

void LoseMenu::hide()
{
	FadeOut* fadeout = FadeOut::create(0.3f);
	getImg()->runAction(fadeout);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->runAction(fadeout->clone());
	}
	retryButton->setEnabled(false);
	//exitButton->setEnabled(false);
	showing = false;
}

void LoseMenu::clear()
{
	retryButton->removeFromParent();
	//exitButton->removeFromParent();
	getImg()->removeFromParent();
	delete instance;
	instance = nullptr;
}