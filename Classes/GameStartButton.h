#pragma once

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class GameStartButton
{
public:
	GameStartButton(Point);
	~GameStartButton();
	Button* gameStartButton;
};

