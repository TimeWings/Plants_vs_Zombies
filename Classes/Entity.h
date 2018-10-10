#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity
{
private:
	Sprite* _img;
	double _rotate;
	double _scale;
	Point _position;
public:
	Entity(Sprite* img,Point position,double rotate=0.0,double scale=1.0);
	Sprite* getImg();
	double getRotate();
	double getScale();
	Point getPosition();
	void setImg(Sprite* img);
	void setRotate(double rotate);
	void setScale(double scale);
	void setPosition(Point position);
	
};