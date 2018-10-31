#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
USING_NS_CC;
class PeaBulletPlus :public PeaBullet
{
private:
	double _angle;
public:
	PeaBulletPlus(Point position, int Plant_row,double angle);
	virtual void move();
	void clear(Node * pSender);
};