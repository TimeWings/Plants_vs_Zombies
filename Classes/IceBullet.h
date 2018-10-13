#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
USING_NS_CC;

class IceBullet :public PeaBullet
{
public:
	IceBullet(Point position);
	virtual void work(Sprite*sp);
	virtual void Hit_Animation(Sprite*sp);
	virtual Sprite * attack_Animation(Sprite * sp);
	void Self_Animation(Sprite*sp);
};