#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PlantStatus
{
public:
	PlantStatus(int row,int col);
	~PlantStatus();
	int _row;
	int _col;
	std::vector<Plants*> plantVector;
};

