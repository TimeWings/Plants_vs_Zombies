#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;
class DoublePeaShooter :public PeaShooter
{
public:
	DoublePeaShooter(Point position);
	void CreateBullet();
	void addBullet(Node * pSender, Sprite* plant);
};
