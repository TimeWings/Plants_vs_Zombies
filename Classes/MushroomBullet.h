#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;
class MushroomBullet :public Bullet
{
private:
	float existTime;
public:
	MushroomBullet();
	MushroomBullet(Point position, int Plant_row);
	MushroomBullet(Point position, int Plant_row, float Scale, float existTime);
	virtual void move();
	void clear(Node * pSender);
	void clearNode(Node * pSender);
	virtual void attack_Animation();
	virtual void Hit_Animation(Zombie* zombie);
};