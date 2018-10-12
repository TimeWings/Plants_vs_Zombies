#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
#include "Bullet.h"
USING_NS_CC;
class PeaBullet :public Bullet
{
public:
	PeaBullet(Point position);
	virtual void Hit_Animation(Sprite*sp);
	virtual void Self_Animation(Sprite*sp);
	virtual void move(Sprite* sp,Bullet*bullet);
	void clear(Node * pSender, Bullet * bullet);
};