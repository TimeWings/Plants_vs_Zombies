#pragma once
#include "cocos2d.h"

USING_NS_CC;
class PlantList
{
public:
	PlantList(Point position);
	void RemoveRegister();
	bool Register(int row, int col);

};
