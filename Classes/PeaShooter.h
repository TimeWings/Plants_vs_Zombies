#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PeaShooter :public Plants
{
public:
	PeaShooter(Point position);
	PeaShooter();
	virtual void work();
	virtual void Die();
	void Self_Animation();
	virtual void init();
	virtual void Attacked();
	virtual bool isAttacking();
	virtual void CreateBullet();

	void clear(Node * pSender);
	
};