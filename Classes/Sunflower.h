#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Sunflower :public Plants
{
public:
	Sunflower(Point position);
	virtual void work();
	virtual void Die();
	virtual void init();
	virtual void Attacked();
	virtual bool isAttacking();
	void Self_Animation();
	void CreateSun();
	void clear(Node * pSender);

};