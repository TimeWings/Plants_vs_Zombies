#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PeaShooter :public Plants
{
public:
	PeaShooter(Point position);
	virtual void work(Sprite * sp);
	virtual void Die(Sprite *sp);
	void Self_Animation(Sprite*sp);
	virtual void init(Sprite * sp);
	virtual void Attack_Animation(Sprite*sp);
	virtual void Attacked(Sprite* sp);
	virtual bool isAttacking();
	void CreateBullet(Sprite* sp);

	void clear(Node * pSender, Plants* plant);
	
};