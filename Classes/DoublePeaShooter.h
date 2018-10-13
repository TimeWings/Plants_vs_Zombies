#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;
class DoublePeaShooter :public PeaShooter
{
public:
	DoublePeaShooter(Point position);
	void CreateBullet(Sprite* sp);
	void addBullet(Node * pSender, Sprite* plant);

};
