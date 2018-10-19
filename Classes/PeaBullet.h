#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
#include "Bullet.h"
USING_NS_CC;
class PeaBullet :public Bullet
{
public:
	PeaBullet();
	PeaBullet(Point position);
	virtual void move();
	void clear(Node * pSender);
	void clearNode(Node * pSender);
	virtual void attack_Animation();
	virtual void Hit_Animation(TestZombie* zombie);
};