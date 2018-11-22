#pragma once
#include "Entity.h"
#include "EntityLayer.h"

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

private:
	bool showing = false;
	static LevelManager* instance;
	static int currentLevel;
	//static int targetLevel;
	static int bg[11];
};