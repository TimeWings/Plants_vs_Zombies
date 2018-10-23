#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;
class PotatoBullet :public Bullet
{
public:
	PotatoBullet(Point position, int Plant_row);
	virtual void move();
	void clear(Node * pSender);
	void clearNode(Node * pSender);
	void removeSprite();
	virtual void Hit_Animation(Zombie* zombie);
};