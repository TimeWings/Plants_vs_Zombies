#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
USING_NS_CC;
class FireBullet :public PeaBullet
{
public:
	FireBullet(int Plant_row,Bullet*bullet,double plantWidth);
	virtual void Self_Animation();
	virtual void attack_Animation();
	virtual void Hit_Animation(Zombie* zombie);
};
