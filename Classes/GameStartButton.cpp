#include "GameStartButton.h"
#include "Global.h"
#include "UILayer.h"
#include "SelectCardBG.h"
#include "FontConfig.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LevelManager.h"

using namespace CocosDenshion;
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

void GameStartButton::playBGM()
{
	auto audio = SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	audio->stopBackgroundMusic();
	switch (LevelManager::currentLevel)
	{
	case 1:
	case 2:
	case 3:audio->playBackgroundMusic("Sound\\day.mp3", true);
		break;
	case 4:
	case 5:
	case 6:audio->playBackgroundMusic("Sound\\water.mp3", true);
		break;
	case 7:
	case 8:
	case 9:audio->playBackgroundMusic("Sound\\night.mp3", true);
		break;
	case 10:
	case 11:
	case 12:audio->playBackgroundMusic("Sound\\cloud.mp3", true);
		break;
	case 13:
	case 14:
	case 15:audio->playBackgroundMusic("Sound\\night2.mp3", true);
		break;
	}
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
			playBGM();
			break;
		default:
			break;
		}
	});
}