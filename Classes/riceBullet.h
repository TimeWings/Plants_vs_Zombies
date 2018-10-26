#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
#include "Zombie.h"
#include <iostream>
class riceBullet :public PeaBullet
{
private:
	Zombie* targetZb;
public:
	riceBullet(Point a, Zombie* zb, int Plant_row);
	void clear(Node * pSender);
	virtual void move();
	virtual void attack_Animation();
	virtual void Hit_Animation(Zombie* zombie);
};