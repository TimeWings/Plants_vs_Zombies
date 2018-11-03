#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
#include "Zombie.h"
#include <iostream>
class riceBullet :public PeaBullet
{

public:
	riceBullet();
	riceBullet(Point a, int Plant_row);
	void clear(Node * pSender);
	void findTarget();
	virtual void move();
	virtual void attack_Animation();
	virtual void Hit_Animation(Zombie* zombie);
protected:
	Zombie* targetZb;
};