#pragma once
#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class WaterShooter :public PeaShooter
{
public:
	WaterShooter(Point position, int row, int col);
	virtual void Die();
	//²úÉú×Óµ¯
	void CreateBullet();
};