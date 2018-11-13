#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
#include "Zombie.h"
USING_NS_CC;
class WhiteJannu : public PeaShooter
{
public:
	WhiteJannu(Point position, int row, int col);
	virtual bool isWorking();
	virtual void work();
	void Effect(Node * pSender);
	void creatSprite();
	void cleanBuff(Node * pSender, Zombie* zombie);
};