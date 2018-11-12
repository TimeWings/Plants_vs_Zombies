#pragma once
#include "cocos2d.h"
#include "Mushroom.h"
USING_NS_CC;
class SmallMushRoom : public Mushroom
{
public:
	SmallMushRoom(Point position, int row, int col);
	virtual void CreateBullet();
	virtual void Self_Animation();
	void clearBullet(Node *pSender);
};