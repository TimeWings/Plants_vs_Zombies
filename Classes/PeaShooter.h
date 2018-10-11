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
	virtual void Self_Animation();
	virtual void Attack_Animation();
	virtual void Attacked();
	virtual bool isAttacking();
	virtual void CreateBullet();
	
};