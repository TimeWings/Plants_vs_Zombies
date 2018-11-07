#pragma once
#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

class Loading :public Entity
{
public:
	Loading(Point);
	~Loading();
	Sprite* sprite;
	//int value = 0;
	//int max = 100;
	ProgressTimer* timer;

	float getCurrentValue();
	void setCurrentValue(float);
};

