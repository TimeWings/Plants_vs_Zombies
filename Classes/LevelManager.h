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
	static void createZombie();
	static void checkWin();
	static void checkLose();

	static LevelManager* getInstance()
	{
		if (instance == nullptr)
			instance = new LevelManager();
		return instance;
	}

	static void test();
	static void drawRect();
	static int kill;
	static int currentLevel;

private:
	bool showing = false;
	static Card<Shovel>* shovel;
	std::vector<Button*> buttons;
	Button* closeButton;
	static LevelManager* instance;
	//static int targetLevel;
	static int bg[16];
	static int zombieCount;
	static int zombie[16][36];
};