#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;

class Mushroom : public PeaShooter
{
private:
	bool haveBullet;
	float Scale;
public:
	Mushroom();
	Mushroom(Point position, int row,int col);
	virtual void CreateBullet();
	void Self_Animation();
	void clearBullet(Node *pSender);
	void Die();
};