#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;
class PotatoBullet :public Bullet
{
public:
	PotatoBullet(Point position);
	virtual void move();
	void clear(Node * pSender);
	void clearNode(Node * pSender);
	virtual void Hit_Animation(TestZombie* zombie);
};