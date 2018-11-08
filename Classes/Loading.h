#pragma once
#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

class Loading :public Entity
{
private:
	ProgressTimer* timer;
public:
	Loading(Point,Scene* scene);
	void clear();
	~Loading();
	Sprite* sprite;
	//int value = 0;
	//int max = 100;

	float getCurrentValue();
	void setCurrentValue(float);
};

