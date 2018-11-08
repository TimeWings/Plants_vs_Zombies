#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Magnet :public PeaShooter
{
public:
	Magnet(Point position, int row, int col);
	virtual bool isWorking();//是否能工作
	virtual void work();
	virtual void Die();
	//产生子弹
	virtual void CreateBullet();
	//清理精灵
	void attractEquiment();
};