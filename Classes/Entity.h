#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity
{
private:
	double _rotate;
	Sprite* _img;
public:
	Entity();
	Entity(Point position,double rotate=0.0);
	Sprite*getImg();
	void setImg(Sprite* img);
	double getRotate();
	void setRotate(double rotate);
	
};