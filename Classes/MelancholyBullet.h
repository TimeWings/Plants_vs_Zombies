#pragma once
#include "cocos2d.h"
#include "PeaBulletPlus.h"
USING_NS_CC;
class MelancholyBullet :public PeaBulletPlus
{
public:
	MelancholyBullet();
	MelancholyBullet(Point position, int Plant_row, double angle, double distance);
	void Hit_Animation(Zombie* zombie);
	void move();
	void Effect();
	void clear(Node * pSender);
}; 
