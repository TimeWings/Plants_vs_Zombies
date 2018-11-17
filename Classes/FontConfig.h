#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class FontConfig
{
public:
	static TTFConfig* create();

	static TTFConfig* getInstance()
	{
		if (instance == nullptr)
			instance = create();
		return instance;
	}
private:
	static TTFConfig* instance;
};
