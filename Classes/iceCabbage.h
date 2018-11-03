#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "JannuDaruku.h"
USING_NS_CC;
class iceCabbage : public JannuDaruku
{
public:
	iceCabbage(Point position, int row, int col);
	virtual void Die();
	void creatSprite();
	void Effect(Node *pSender);
	void clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie);
};