#pragma once
#include "cocos2d.h"

//USING_NS_CC;
//using namespace std;
class Plantable
{
public:
	Plantable(cocos2d::Point position);
	~Plantable();
	cocos2d::Size size = cocos2d::Size(35.0f, 45.0f);
	cocos2d::Sprite* sprite;
	int row;
	int col;
	bool hasPlant = false;
};

