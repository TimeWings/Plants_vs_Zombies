#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Entity
{
private:
	Sprite* _img;
public:
	Entity();
	Sprite*getImg();
	void setImg(Sprite* img);
	
};