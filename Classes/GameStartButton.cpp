#include "GameStartButton.h"
#include "Global.h"
#include "EntityLayer.h"
#include "SelectCardBG.h"
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
	button->setTitleText("GameStart");
	button->setTitleFontSize(4.0f);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			std::cout << "GameStart Button Clicked" << std::endl;
			GameStart = true;
			for (int i = 0; i < unSelectingCardsEntity.size(); i++)
			{
				unSelectingCardsEntity[i]->getImg()->setVisible(false);
			}
			for (int i = 0; i < selectingCardsEntity.size(); i++)
			{
				selectingCardsEntity[i]->getImg()->setVisible(false);
			}
			for (int i = 0; i < readyCards.size(); i++)
			{
				readyCards[i]->getImg()->setVisible(true);
				readyCards[i]->addListener();
			}
			EntityLayer::getInstance()->removeChild(button);
			SelectCardBG::getInstance()->hide();
			break;
		default:
			break;
		}
	});
	EntityLayer::getInstance()->addChild(button);
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
}