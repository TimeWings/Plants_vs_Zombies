#pragma once
#include "Entity.h"
#include "EntityLayer.h"
#include "ui/CocosGUI.h"
using namespace ui;

class LevelManager:public Entity
{
public:
	LevelManager();
	~LevelManager();
	void show();
	void hide();
	void clear();
	bool isShow();

	static void loadLevel(int);
	static void clearAllUI();
	static void showAllUI();
	static void createAllCard();

	static LevelManager* getInstance()
	{
		if (instance == nullptr)
			instance = new LevelManager();
		return instance;
	}

	static void test();
	static void drawRect();

private:
	bool showing = false;
	std::vector<Button*> buttons;
	Button* closeButton;
	static LevelManager* instance;
	static int currentLevel;
	//static int targetLevel;
	static int bg[16];
};