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
	virtual void work();
	virtual void Hit_Animation(TestZombie* zombie);
	virtual Sprite * attack_Animation();
	void Self_Animation();
	virtual void move();
	void clear(Node * pSender);
	void clear1(Node * pSender);
};