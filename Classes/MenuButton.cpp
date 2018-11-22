#include "MenuButton.h"
#include "LevelManager.h"
#include "FontConfig.h"
#include "MainMenu.h"

Button* MenuButton::instance;

MenuButton::MenuButton()
{

}

MenuButton::~MenuButton()
{

}

Button* MenuButton::create(Point position)
{
	auto button = Button::create("UI\\button.png", "UI\\button.png", "UI\\button.png");
	button->setPosition(position);
	button->setScale(1.5f);
	auto label = Label::createWithTTF(*(FontConfig::getInstance()),"Menu");
	label->setTextColor(Color4B::BLACK);
	label->setPosition(Point(18, 6.5f));
	label->setScale(1.3f);
	button->addChild(label);
	button->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);

	EntityLayer::getInstance()->addChild(button, 1000);
	return button;
}

void MenuButton::enable()
{
	getInstance()->setEnabled(true);
	getInstance()->setVisible(true);
}

void MenuButton::disable()
{
	getInstance()->setEnabled(false);
	getInstance()->setVisible(false);
}

void MenuButton::clear()
{
	getInstance()->removeFromParent();
	instance = nullptr;
}

void MenuButton::addListener()
{
	getInstance()->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (MainMenu::getInstance()->isShow() == false)
				MainMenu::getInstance()->show();
			break;
		default:
			break;
		}
	});
}