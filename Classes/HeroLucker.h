#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "HeroLuckerBullet.h"
#include "Mushroom.h"
USING_NS_CC;

class HeroLucker : public Mushroom
{
private:
	Point position;
public:
	HeroLucker(Point position, int row, int col);
	virtual void CreateBullet();
	void Self_Animation();
	void clearBullet(Node * pSender, HeroLuckerBullet * bp);
	void Die();
};