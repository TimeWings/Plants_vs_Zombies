#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity
{
public:
	Sprite* _img;
	double _rotate;
	double _scale;
public:
	Entity();
	Entity(Sprite* img,Point position,double rotate=0.0,double scale=1.0);
	Sprite* getImg();
	double getRotate();
	double getScale();
	void setImg(Sprite* img);
	void setRotate(double rotate);
	void setScale(double scale);
	
};