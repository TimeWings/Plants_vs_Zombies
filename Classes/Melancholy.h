#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Melancholy :public PeaShooter
{
private:
	double distance;
public:
	Melancholy(Point position, int row, int col);
	bool isWorking();
	void work();
	void CreateBullet();
};
