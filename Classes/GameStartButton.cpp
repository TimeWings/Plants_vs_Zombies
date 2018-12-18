#include "GameStartButton.h"
#include "Global.h"
#include "UILayer.h"
#include "SelectCardBG.h"
#include "FontConfig.h"
#include "HelloWorldScene.h"
using namespace map;
Button* GameStartButton::instance = nullptr;

GameStartButton::GameStartButton()
{

}

Button* GameStartButton::create(Point position)
{
	auto button = Button::create("UI\\SelectCardButton.png", "UI\\SelectCardButton_Light.png", "UI\\SelectCardButton.png");
	button->setPosition(position);
	button->setScale(2.0f);
	auto label = Label::createWithTTF(*(FontConfig::getInstance()), "GameStart");
	label->setTextColor(Color4B::BLACK);
	label->setScale(0.8f);
	button->setTitleLabel(label);
	button->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);

	
	UILayer::getInstance()->addChild(button, 196);
	return button;
}


GameStartButton::~GameStartButton()
{
}

void GameStartButton::enable()
{
	getInstance()->setEnabled(true);
	getInstance()->setVisible(true);
}

void GameStartButton::disable()
{
	getInstance()->setEnabled(false);
	getInstance()->setVisible(false);
}

void GameStartButton::clear()
{
	getInstance()->removeFromParent();
	instance = nullptr;
}

void GameStartButton::addListener()
{
	getInstance()->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			std::cout << "GameStart Button Clicked" << std::endl;
			//GameStart = true;
			for (int i = 0; i < unSelectingCardsEntity.size(); i++)
			{
				unSelectingCardsEntity[i]->clear();
			}
			unSelectingCardsEntity.clear();
			for (int i = 0; i < selectingCardsEntity.size(); i++)
			{
				selectingCardsEntity[i]->clear();
			}
			selectingCardsEntity.clear();
			selectingCards.clear();
			for (int i = 0; i < readyCards.size(); i++)
			{
				readyCards[i]->getImg()->setVisible(true);
				//readyCards[i]->removeListener();
				readyCards[i]->addListener();
			}
			disable();
			SelectCardBG::getInstance()->hide();
			Director::getInstance()->getRunningScene()->scheduleOnce(schedule_selector(HelloWorld::moveCameraLeft), 0.5f);
			break;
		default:
			break;
		}
	});
}