#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Sunflower :public Plants
{
public:
	Sunflower(Point position);
	virtual void work(Sprite * sp);
	virtual void Die(Sprite *sp);
	virtual void init(Sprite * sp);
	virtual void Attacked(Sprite* sp);
	virtual bool isAttacking();
	void Self_Animation(Sprite*sp);
	void CreateSun(Sprite* sp);
	void clear(Node * pSender, Plants* plant);

};