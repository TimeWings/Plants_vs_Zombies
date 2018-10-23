#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"

USING_NS_CC;

class IceBullet :public PeaBullet
{
private:
	MotionStreak* streak;
public:
	IceBullet(Point position,int Plant_row);
	void Hit_Animation(Zombie* zombie);
	void attack_Animation();
	void resume(Node * pSender, Zombie* zombie);
};