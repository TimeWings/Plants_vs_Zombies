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
	
	static LevelManager* getInstance()
	{
		if (instance == nullptr)
			instance = new LevelManager();
		return instance;
	}

private:
	static LevelManager* instance;
	int currentLevel;
	bool showing = false;
};