#pragma once
#include "Entity.h"
#include "ui/CocosGUI.h"
using namespace ui;

class WinMenu: Entity
{
public:
	WinMenu();
	~WinMenu();

	void show();
	void hide();
	void clear();
	bool isShow();

	static WinMenu* getInstance()
	{
		if (instance == nullptr)
			instance = new WinMenu();
		return instance;
	}

private:
	bool showing = false;
	Button* retryButton;
	Button* nextButton;
	Button* exitButton;
	//Button* closeButton;
	static WinMenu* instance;
};

