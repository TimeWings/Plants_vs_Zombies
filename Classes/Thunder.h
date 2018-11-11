#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
#include "Zombie.h"
USING_NS_CC;
class Thunder :public PeaShooter
{

protected:
	bool hasThunder;
	Point lastPoint;
	int curtentDamage;
	float thunderHeight;
public:
	Thunder();
	Thunder(Point position, int row, int col);
	virtual bool isWorking();
	virtual void work();
	void creatSprite();
	void createThunder(Point startPoint, Point endPoint, Zombie* zombie);
};