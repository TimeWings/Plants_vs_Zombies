#pragma once
#include "cocos2d.h"
#include "MushroomBullet.h"
USING_NS_CC;
class HeroLuckerBullet :public MushroomBullet
{
private:
	int row;

public:
	HeroLuckerBullet(Point position, int Plant_row);
	void HeroLuckerBullet::releaseZombie(Node* sPender, Zombie * zombie);
	void attack_Animation();
	void Hit_Animation(Zombie* zombie);
	void clear(Node * pSender);
	void clearSprite(Node * pSender, Sprite* sp);
};