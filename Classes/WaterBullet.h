#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
USING_NS_CC;
class WaterBullet :public PeaBullet
{
public:
	WaterBullet(Point position, int Plant_row);
	virtual void Hit_Animation(Zombie* zombie);
	virtual void attack_Animation();
};