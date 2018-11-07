#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;

class IceShooter :public PeaShooter
{
public:
	IceShooter();
	IceShooter(Point position,int row,int col);
	virtual void Die();
	void CreateBullet();
	void clear(Node * pSender);
};