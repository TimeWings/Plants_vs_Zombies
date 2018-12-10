#pragma once
#include "cocos2d.h"
#include "Entity.h"

class ZombieProgressBar :public Entity
{
public:
	ZombieProgressBar(Point);
	~ZombieProgressBar();

	Sprite* sprite;
	//int value = 0;
	//int max = 100;

	float getCurrentValue();
	void setCurrentValue(float);
	void show();
	void hide();
	void clear();
	static ZombieProgressBar* getInstance()
	{
		if (instance == nullptr)
			instance = new ZombieProgressBar(Point(430,280));
		return instance;
	}

private:
	static ZombieProgressBar* instance;
	ProgressTimer* timer;
};

