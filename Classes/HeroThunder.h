#pragma once
#include "cocos2d.h"
#include "Thunder.h"
#include "Zombie.h"
class HeroThunder :public Thunder
{
private:
	int currentCol;
public:
	HeroThunder(Point position, int row, int col);
	virtual bool isWorking();
	virtual void work();
	void creatSprite();
};