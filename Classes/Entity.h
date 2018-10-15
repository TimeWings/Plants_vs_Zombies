#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity 
{
private:
	double _rotate;
	double _scale;
	Sprite* _img;
public:
	Entity();
	Entity(Point position,double rotate=0.0,double scale=1.0);
	Sprite*getImg();
	void setImg(Sprite* img);
	double getRotate();
	double getScale();
	void setRotate(double rotate);
	void setScale(double scale);
	
};