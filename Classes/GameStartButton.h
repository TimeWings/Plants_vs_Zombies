#pragma once

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class GameStartButton
{
public:
	GameStartButton();
	~GameStartButton();
	static void addListener();
	static void enable();
	static void disable();
	static void clear();

	static Button* create(Point);
	static Button* getInstance()
	{
		if (instance == nullptr)
			instance = create(Point(120, 35));
		return instance;
	}

private:
	static Button* instance;
};

