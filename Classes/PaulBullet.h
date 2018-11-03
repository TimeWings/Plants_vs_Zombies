#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "Doom_shroom.h"
USING_NS_CC;
class PaulBullet :public Doom_shroom
{
private:
	double delayTime;
public:
	PaulBullet(Point position,double delayTime);
	virtual void move();
	void work();
	const double speed = 500.0f;
	virtual void zombiesDie();
	virtual void creatSprite();
};