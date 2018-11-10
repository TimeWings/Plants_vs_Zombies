#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
#include "Zombie.h"
USING_NS_CC;
class Thunder :public PeaShooter
{

private:
	bool hasThunder;
	Point lastPoint;
	int curtentDamage;
public:
	Thunder(Point position, int row, int col);
	virtual void work();;
	void creatSprite();
	void createThunder(Point startPoint, Point endPoint, Zombie* zombie);
	void clear(Node *pSender);
};