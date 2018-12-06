#pragma once
#include "Entity.h"
#include "EntityLayer.h"
#include "ui/CocosGUI.h"
#include "Shovel.h"
#include "Card.h"
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
	static void showSelectCard();
	static void createAllCard();
	static void gameStart();

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
	static Card<Shovel>* shovel;
	std::vector<Button*> buttons;
	Button* closeButton;
	static LevelManager* instance;
	static int currentLevel;
	//static int targetLevel;
	static int bg[16];
};