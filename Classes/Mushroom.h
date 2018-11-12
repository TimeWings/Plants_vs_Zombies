#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;

class Mushroom : public PeaShooter
{
protected:
	bool haveBullet;
	float Scale;
	int attackCol;
public:
	Mushroom();
	Mushroom(Point position, int row,int col);
	virtual bool isWorking();
	virtual void CreateBullet();
	virtual void Self_Animation();
	void clearBullet(Node *pSender);
	void Die();
};