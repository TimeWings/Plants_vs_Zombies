#include "GameStartButton.h"
#include "Global.h"
#include "EntityLayer.h"
#include "SelectCardBG.h"
using namespace map;


GameStartButton::GameStartButton(Point position)
{
	gameStartButton = Button::create("UI\\SelectCardButton.png", "UI\\SelectCardButton_Light.png", "UI\\SelectCardButton.png");
	gameStartButton->setPosition(position);
	gameStartButton->setScale(2.0f);
	gameStartButton->setTitleText("GameStart");
	gameStartButton->setTitleFontSize(4.0f);
	gameStartButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
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
			EntityLayer::getInstance()->removeChild(gameStartButton);
			EntityLayer::getInstance()->removeChild(SelectCardBG::bg);
			break;
		default:
			break;
		}
	});
	EntityLayer::getInstance()->addChild(gameStartButton);
}


GameStartButton::~GameStartButton()
{
}
