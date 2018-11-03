#pragma once
#include "cocos2d.h"
#include "JannuDaruku.h"
USING_NS_CC;
class Doom_shroom :public JannuDaruku
{
public:
	Doom_shroom();
	Doom_shroom(Point position, int row, int col);
	virtual void Die();
    void Effect(Node * pSender);
	virtual void creatSprite();
	void clearSprite(Node * pSender, Sprite * sp);

	virtual void zombiesDie();
};