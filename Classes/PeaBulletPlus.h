#pragma once
#include "cocos2d.h"
#include "PeaBullet.h"
USING_NS_CC;
class PeaBulletPlus :public PeaBullet
{
protected:
	double _angle;
	double _distance;
public:
	PeaBulletPlus();
	PeaBulletPlus(Point position, int Plant_row,double angle,double distance);
	virtual void move();
	void clear(Node * pSender);
};