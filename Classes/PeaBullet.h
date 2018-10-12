#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
#include "Bullet.h"
USING_NS_CC;
class PeaBullet :public Bullet
{
public:
	PeaBullet(Point position);
	virtual void work(Sprite*sp);
	virtual void Hit_Animation(Sprite*sp);
	void Self_Animation(Sprite*sp);
	virtual void move(Sprite* sp);
	void clear(Node * pSender, Bullet * bullet);
	void test(float t);
};