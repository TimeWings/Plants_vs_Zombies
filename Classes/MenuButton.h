#pragma once
#include "Entity.h"
#include "EntityLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class MenuButton:public Entity
{
public:
	MenuButton();
	~MenuButton();
	static void addListener();
	static void enable();
	static void disable();
	static void clear();

	static Button* create(Point);

	static Button* getInstance()
	{
		if (instance == nullptr)
			instance = create(Point(460,15));
		return instance;
	}

private:
	static ui::Button* instance;
};
