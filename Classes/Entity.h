#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity
{
public:
	double _rotate;
	double _scale;
public:
	Entity();
	Entity(Point position,double rotate=0.0,double scale=1.0);
	double getRotate();
	double getScale();
	void setRotate(double rotate);
	void setScale(double scale);
	
};