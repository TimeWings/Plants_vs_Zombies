#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"

USING_NS_CC;

class IceBullet :public PeaBullet
{
public:
	IceBullet(Point position);
	virtual void work();
	virtual void Hit_Animation(TestZombie* zombie);
	virtual Sprite * attack_Animation();
	void Self_Animation();
	void resume(Node * pSender, TestZombie* zombie);
	void resume1(Node * pSender);
};