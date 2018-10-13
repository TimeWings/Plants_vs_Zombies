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
	virtual void work(Sprite*sp);
	virtual void Hit_Animation(Sprite*sp);
	virtual Sprite * attack_Animation(Sprite * sp);
	void Self_Animation(Sprite*sp);
	virtual void move(Sprite* sp);
	void clear(Node * pSender, Bullet * bullet);
	void clear1(Node * pSender);
	void test(float t);
};