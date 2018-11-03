#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Melancholy :public PeaShooter
{
public:
	Melancholy(Point position, int row, int col);
	void CreateBullet();
};
