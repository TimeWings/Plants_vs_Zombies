#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;
class PeaBullet :public Bullet
{
public:
	PeaBullet();
	PeaBullet(Point position,int Plant_row);
	virtual void move();
	void clear(Node * pSender);
	void clearNode(Node * pSender);
	virtual void attack_Animation();
	virtual void Hit_Animation(Zombie* zombie);
};