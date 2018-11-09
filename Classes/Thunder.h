#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Thunder :public PeaShooter
{

private:
	float curDetail;
public:
	Thunder(Point position, int row, int col);
	virtual void work();
	void creatSprite();
	void createThunder(float x1, float y1, float x2, float y2, float displace);
};