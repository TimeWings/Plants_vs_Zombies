#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PlantStatus
{
public:
	int _BlockType = 0;//0为陆地,1为水面
	PlantStatus(int row,int col,int BlockType);
	~PlantStatus();
	int _row;
	int _col;
	std::vector<Plants*> plantVector;
};

