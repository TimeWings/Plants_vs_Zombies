#pragma once
#include "cocos2d.h"
#include "riceShooter.h"

USING_NS_CC;
class Lancer :public riceShooter
{
public:
	Lancer(Point position, int row, int col);
	virtual void CreateBullet();
};