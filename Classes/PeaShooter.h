#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PeaShooter :public Plants
{
public:
	PeaShooter(Point position);
	virtual void Attack();
	virtual void Die();
	virtual void Self_Animation(Sprite*sp);
	virtual void Attack_Animation(Sprite*sp);
	virtual void Attacked();
	virtual bool isAttacking();
	virtual void CreateBullet(Sprite* sp);
	
};