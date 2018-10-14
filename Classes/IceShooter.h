#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;

class IceShooter :public PeaShooter
{
public:
	IceShooter(Point position);
	void CreateBullet();
};