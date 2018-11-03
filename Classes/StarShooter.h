#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class StarShooter :public PeaShooter
{
public:
	StarShooter(Point position, int row, int col);
	void CreateBullet();
};