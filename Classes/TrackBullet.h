#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;
class TrackBullet :public Bullet
{
public:
	TrackBullet(Point position, int Plant_row);
	virtual void move();
	void Rotate(Node * pSender);
	void clear(Node * pSender);
	float getAng(Point a, Point b);
	void clearNode(Node * pSender);
	virtual void Hit_Animation(Zombie* zombie);
};
