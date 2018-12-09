#pragma once
#include "Entity.h"
#include "ui/CocosGUI.h"
using namespace ui;

class LoseMenu: Entity
{
public:
	LoseMenu();
	~LoseMenu();

	void show();
	void hide();
	void clear();
	bool isShow();

	static LoseMenu* getInstance()
	{
		if (instance == nullptr)
			instance = new LoseMenu();
		return instance;
	}

private:
	bool showing = false;
	Button* retryButton;
	//Button* nextButton;
	Button* exitButton;
	//Button* closeButton;
	static LoseMenu* instance;
};

