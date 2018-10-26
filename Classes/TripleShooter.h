#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class TripleShooter :public PeaShooter
{
public:
	TripleShooter(Point position, int row);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	//产生子弹
	virtual void CreateBullet();

};
