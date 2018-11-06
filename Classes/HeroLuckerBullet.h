#pragma once
#include "cocos2d.h"
#include "MushroomBullet.h"
USING_NS_CC;
class HeroLuckerBullet :public MushroomBullet
{
public:
	HeroLuckerBullet(Point position, int Plant_row);
	void HeroLuckerBullet::releaseZombie(Node* sPender, Zombie * zombie);
	void attack_Animation();
	void Hit_Animation(Zombie* zombie);
};