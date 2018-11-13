#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Title.h"
using namespace cocos2d;

class Loading :public Entity
{
private:
	ProgressTimer* timer;
public:
	Loading(Point,Scene* scene, Title* title);
	void afterload(Node * pSender, Title * title);
	void clear(Node*pSender);
	~Loading();
	Sprite* sprite;
	//int value = 0;
	//int max = 100;

	float getCurrentValue();
	void setCurrentValue(float);
};

