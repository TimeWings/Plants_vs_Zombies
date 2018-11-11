#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
//using namespace ui;
using namespace cocos2d;

class Title
{
public:
	Sprite* bg;
	ui::Button* StartButton;

	Title(Scene*);
	~Title();
	void clear(Scene* scene);
	void enableStartButton();
	//static cocos2d::Scene* createScene();
	//static Scene* scene;

	//virtual bool init();
};